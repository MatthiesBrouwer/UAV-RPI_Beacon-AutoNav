# Decawave DW1000 ranging demo
# Copyright (c) Jeremy P Bentham 2019. See iosoft.blog for details

import sys, time
from ctypes import sizeof, LittleEndianStructure as Structure, Union
from ctypes import c_ubyte as U8, c_short as U16, c_ulonglong as U64
from dw1000_regs import Reg, DW1000, msdelay
from dw1000_spi import Spi

import enum

VERSION = "0.16"

# Specify SPI interfaces:
#   "UDP", "<IP_ADDR>", <PORT_NUM>
SPIF1       = "UDP", "192.168.2.9", 1401
SPIF2       = "UDP", "192.168.2.18", 1401

# Blink frame with IEEE EUI-64 tag ID
BLINK_FRAME_CTRL = 0xc5
BLINK_MSG=(('framectrl',   U8),
           ('seqnum',      U8),
           ('tagid',       U64))

MSG_FRAME_CTRL = 0xCC41
MSG_HDR = (('framectrl',   U16),
           ('seqnum',      U8),
           ('panid',       U16),
           ('destaddr',    U64),
           ('srceaddr',    U64))

LIGHT_SPEED = 299702547.0
TSTAMP_SEC  = 1.0 / (128 * 499.2e6)
#TSTAMP_SEC  = 1.0 / (150 * 499.2e6)
TSTAMP_DIST = LIGHT_SPEED * TSTAMP_SEC

#DISTANCE_ERROR_MARGE = 0.016
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




class flag(enum.Enum):
	SYN = 1
	ACK = 2
	FIN = 3


#--- Initialise the UWB anchor state machine ---#
class TagModule:
	def __init__(self):
		self.spi1 = Spi(SPIF1, '1')
		self.uwb_module = DW1000(spi1)
		self.uwb_module.reset()

		if not self.uwb_module.test_irq():
			print("No interrupt from unit 1")
		        sys.exit(1)

		self.uwb_module.initialise()

		self.blink_message 		= Frame(BLINK_MSG)
		self.blink_message.framectrl 	= BLINK_FRAME_CTRL
		self.blink_message.values.tagid = 0x0101010101010101

		#--- Initialise time values for error maintinance ---#
		self.t_reply_start_1 	= 0
		self.t_reply_end_1 	= 0
		self.t_round_start_1 	= 0
		self.t_round_end_1	= 0
		
		self.t_last_receive 	= 0

		self.state = "IDLE"

	def reply(self):
		txdata = self.blink_message.data()
		self.uwb_module.set_txdata(txdata)
		self.uwb_module.start_tx()

	def loop(self):
		self.uwb_module.start_rx()
		while(true):
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


if __name__ == "__main__":
	anchor_module = AnchorModule()
	anchor_module.loop()

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
