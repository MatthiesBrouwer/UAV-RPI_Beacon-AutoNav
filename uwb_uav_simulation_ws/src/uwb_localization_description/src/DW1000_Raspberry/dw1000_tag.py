# Decawave DW1000 ranging demo
# Copyright (c) Jeremy P Bentham 2019. See iosoft.blog for details

import sys, time
from ctypes import sizeof, LittleEndianStructure as Structure, Union
from ctypes import c_ubyte as U8, c_short as U16, c_ulonglong as U64
from dw1000_regs import Reg, DW1000, msdelay
from dw1000_spi import Spi


VERSION = "0.16"

# Specify SPI interfaces:
#   "UDP", "<IP_ADDR>", <PORT_NUM>
SPIF	    = "UDP", "127.0.0.1", 1401

# Blink frame with IEEE EUI-64 tag ID
BLINK_FRAME_CTRL = 0xc5
BLINK_MSG=(('framectrl',   U8),
           ('seqnum',      U8),
           ('tagid',       U64))

# A message  frame to tranceive between modules
MSG_FRAME_CTRL = 0xCC41
MSG_HDR = (('framectrl',   U16),
           ('seqnum',      U8),
           ('destaddr',    U8),
           ('srceaddr',    U8),
	   ('msgflag',	   U8),
	   ('msgdata',     U64))

# Flags for ranging messages
POLL_FLAG 	= 1
REPLY_FLAG	= 2
FINAL_FLAG	= 3
REPORT_FLAG	= 4
FINISHED_FLAG	= 5
RESET_FLAG	= 6

LIGHT_SPEED = 299702547.0
TSTAMP_SEC  = 1.0 / (128 * 499.2e6)
TSTAMP_DIST = LIGHT_SPEED * TSTAMP_SEC

DISTANCE_ERROR_SUBSTRACTOR = 32500
DISTANCE_ERROR_MULTIPLIER =  0.93

RESET_PERIOD = 10

# Class to encapsulate a message frame or header with fixed-length fields
class Frame(object):
    def __init__(self, fields, bytes=[]):
        self.fields = fields
        self.seqnum = 1
        class struct(Structure):
            _pack_   = 1
            _fields_ = fields
        class union(Union):
            _fields_ = [("values", struct), ("bytes", U8*sizeof(struct))]
        self.u = union()
        for n, b in enumerate(bytes[0:sizeof(struct)]):
            self.u.bytes[n] = b
        self.bytes, self.values = self.u.bytes, self.u.values

    # Return frame data
    def data(self):
        self.values.seqnum = self.seqnum
        self.seqnum += 1
        return list(self.bytes)

    # Return string with field values
    def field_values(self, zeros=True):
        flds = [f[0] for f in self.fields]
        return " ".join([("%s:%x" % (f,getattr(self.values, f))) for f in flds])



#--- Initialise the UWB anchor state machine ---#
class TagModule(DW1000):

	class Anchor:
		def __init__(self, module_id):
			#--- Set the modules ranging variables ---#
			self.module_id = module_id
			self.prev_flag = 1
			self.t_reply = 0
			self.t_round = 0
			self.prev_msg = None

		def reset(self):
			self.prev_flag = 1
			self.t_reply = 0
			self.t_round = 0

		def logTime(self, t_reply, t_round):
			self.t_reply = t_reply
			self.t_round = t_round

		def setFlag(self, new_flag):
			self.prev_flag = new_flag

		def getPrevFlag(self):
			return self.prev_flag

		def getId(self):
			return self.anchor_id

		def messageReceived(self, new_message):
			self.prev_message = new_message
			self.prev_flag = new_message[6]
			print("New message:\t{}\nflag:\t{}".format(new_message, new_message[5]))


	class inactiveException(Exception):
		def __init__(self, ranging_part):
			self.ranging_part = ranging_part
			self.message = 	"!!!EXCEPTION!!!\n\tInactive for too long during " + ranging_part
			Exception.__init__(self.message)

	def __init__(self):

		#--- Initialise the module and the DW1000 ---#
		self.module_id = 0
		self.spi = Spi(SPIF, self.module_id)
		DW1000.__init__(self, self.spi)
		self.reset()

		if not self.uwb_module.test_irq():
			print("No interrupt from unit 1")
		        sys.exit(1)
		self.initialise()


		#--- Initialise the anchor modules ---#
		self.anchor_modules = []
		self.anchor_modules.append(	self.AnchorModule(0))
		self.anchor_modules.append(	self.AnchorModule(1))
		self.anchor_modules.append(	self.AnchorModule(2))
		self.anchor_modules.append(	self.AnchorModule(3))


		#--- Declare ranging values ---#
		self.t_last_transaction = 0
		self.t_ranging_start	= 0
		self.t_ranging_end	= 0

		self.state = "IDLE"

	def printDataMessage(self, data):
		print("\n\n--RECEIVED--")
		print("FROM:\t{}".format(data[4]))
		print("TO:\t{}".format(data[3]))
		print("FLAG:\t{}".format(data[5]))
		print("RXDATA:\t{}"format(data))
		print("------------\n\n")


	def loop(self):
		self.uwb_module.start_rx()

		poll_message = Frame(MSG_HDR)
		poll_message.values.framectrl = MSG_FRAME_CTRl
		poll_message.values.srcaddr = self.module_id
		poll_message.values.msgflag = POLL_FLAG

		final_message = Frame(MSG_HDR)
		final_message.values.framectrl = MSG_FRAME_CTRL
		final_message.values.arcaddr = self.module_id
		final_message.values.msgflag = self.FINAL_FLAG

		while(true):

			time.sleep(3)

			try:
				self.t_ranging_start	= 0
				self.t_ranging_end	= 0
				######################### POLLING ########################
				#--- Send the initial poll message to all anchors ---#
				for anchor in self.anchor_modules:
					anchor.reset()
					poll_message.values.seqnum = 1
					poll_message.values.destaddr = anchor.getId()
					self.set_rxdata(poll_message)
					self.start_tx(rx = True)
				self.t_last_transaction	= time.time()


				#--- Wait for all replies before progressing ---#
				poll_replies_received = 0
				while True:
					#--- Restart if no replies are obtained within the reset period ---#
					if time.time() - self.t_last_transaction < RESET_PERIOD:
						raise inactiveException("poll")

					rxdata = self.get_rxdata()
					if rxdata:
						self.printDataMessage(rxdata)

						#--- If the message is meant for this module and dataflag is a reply flag, ---#
						#--- log the message ---#n raise exception
						if rxdata[3] == self.module_id and rxdata[5] == REPLY_FLAG :
							self.t_last_transaction = time.time()
							self.anchor_modules[rxdata[4].setFlag(FINAL_FLAG)
							poll_replies_received++

					if poll_replies_received >= 4:
						print("ALL REPLIES RECEIVED")
						break

				##########################################################

				######################### RANGING ########################
				#--- Send the final ranging message to all anchors ---#
				for anchor in self.anchor_modules:
					final_message.values.seqnum = 1
					final_message.values.destaddr = anchor.getId()
					self.set_rxdata(final_message)
					self.start_tx(rx = True)
				self.t_last_transaction = time.time()

				#--- Wait for all replies before progressing ---#
				final_replies_received = 0
				while True:
					#--- Restart if no replies are obtained within the reset period ---#
					if time.time() - self.t_last_transaction < RESET_PERIOD:
						raise inactiveException("final")

					rxdata = self.get_rxdata()
					if rxdata:
						self.printDataMessage(rxdata)

						#--- If the message is meant for this module and dataflag is a report flag, ---#
						#--- log the message as report and save the data ---#
						if rxdata[3] == self.module_id and rxdata[5] == REPORT_FLAG :
							self.prev_interaction = time.time()
							self.anchor_modules[rxdata[4].setFlag(FINISHED_FLAG)
							final_replies_received++

					if final_replies_received >= 4:
						print("ALL REPLIES RECEIVED")
						break
				##########################################################


				print("!!!!!!!!!!!!RANGING FINISHED!!!!!!!!!!!!!!!!")

			except(inactiveException):
				print(inactiveException.message)
				time.sleep(2)
				continue


			"""
			rxdata = self.uwb_module.get_rxdata()
			if not rxdata and (time.time() - self.t_last_receive) > RESET_PERIOD:
				print("RESET PERIOD CROSSED")
				self.uwb_module.softreset()
				self.uwb_module.initialise()
				self.t_last_receive = time.time()
				self.start_rx()
				self.state == "IDLE"
				continue

			if rxdata:
				print("RXDATA:\t{}".format(rxdata))
				self.t_last_receive = time.time()

				if self.state == "IDLE":
					print("\tIDLE")
					self.t_reply_start 	= self.uwb_module.rxtime()
					self.reply()
					self.t_reply_end 	= self.uwb_module.txtime()
					self.t_round_start 	= self.t_reply_end
					self.state = "WAIT_FOR_FINAL"

				else if self.state == "WAIT_FOR_FINAL"
					print("\tWAIT_FOR_SIGNAL")
					self.t_round_end 	= self.uwb_module.rxtime()
					self.reply()					self.state = "IDLE"

					print("TIMES:\n\treply:\t{}\n\tround:\t{}\n\n".format(self.t_reply_end - self.t_reply_start, self.t_round_end - self.t_round_start))

				"""
if __name__ == "__main__":
	tag_module = TagModule()
	tag_module.loop()

	"""
	class State:
		def __init__(self):
			print("Processing current state: ", str(self))

		def on_event(self, event):
			#--- Handle events that are deligated to this state ---#
			pass

		def __repr__(self):
			#--- Leverages the __str__ method to describe the state ---#
			return self.__str__()

		def __str__(self):
			#--- Returns the name of the state ---#
			return self.__class__.__name__

	class IdleState(State):
		#--- The idle receiving state ---#
		



if __name__ == "__main__":
    verbose = False
    for arg in sys.argv[1:]:
        if arg.lower() == "-v":
            verbose = True
    
    spi1 = Spi(SPIF1, '1')
    dw1 = DW1000(spi1)

    if verbose:
        spi1.verbose = spi2.verbose = True

    dw1.reset()
    if not dw1.test_irq():
        print("No interrupt from unit 1")
        sys.exit(1)

    dw1.initialise()
    blink1 = Frame(BLINK_MSG)
    blink1.values.framectrl = BLINK_FRAME_CTRL
    blink1.values.tagid = 0x0101010101010101

    errors = count = 0

    mnt_data_collected = 0
    distances = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    timestamps = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]



    while True:
        # Reset devices if 10 concsecutive errors
        errors += 1
        if errors > 10:
            print("Restting")
            dw1.softreset()
            dw1.initialise()
            errors = 0

	dw1.start_rx()
	rxdata = dw1.get_rxdata()

	start_time = time()
	while not rxdata:
		end_time = time()
		if end_time - start_time > 10:
			print(end_time - start_time)
			dw1.softreset()
			dw1.initialise()
			continue

		rxdata = dw1.get_rxdata()



        errors = 0

        # Print message count
        count += 1
        if count%100 == 0:
            sys.stderr.write(str(count) + ' ')
            sys.stderr.flush()
# EOF

"""
