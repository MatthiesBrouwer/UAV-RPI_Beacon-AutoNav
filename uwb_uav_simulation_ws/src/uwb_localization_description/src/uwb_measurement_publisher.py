#!/usr/bin/env python


#---------------------------------------------------------#
# UWB Localisation Description
#
# The purpose of this script is to measure distances
# between two or more UWB DWM1000 IC's. The IC interfacing and 
# distance measuring techniques are provided and copyrighted (c) by
# 
# Jeremy P Bentham 2019. (See iosoft.blog for more details) 
#---------------------------------------------------------#


import rospy

import math
import numpy as np
import tf2_ros

from uwb_localization_description.msg import uwb_data_raw

import sys
import time
import threading
from ctypes import sizeof, LittleEndianStructure as Structure, Union
from ctypes import c_ubyte as U8, c_short as U16, c_ulonglong as U64
from DW1000_Raspberry.dw1000_regs import Reg, DW1000, msdelay
from DW1000_Raspberry.dw1000_spi import Spi


#--- Declare the robot position at 0 ---#
global robot_pose_x,robot_pose_y,robot_pose_z
robot_pose_x =0
robot_pose_y =0
robot_pose_z =0


#--- Specify the SPI interfaces of the RPI's ---#
#--- "UDP", "<IP_ADDR>", "<PORT_NUM>" ---#
SPIF0 = "UDP", "192.168.2.15", 1401
SPIF1 = "UDP", "192.168.2.16", 1401
SPIF2 = "UDP", "192.168.2.17", 1401
SPIF3 = "UDP", "192.168.2.15", 1401
SPIF4 = "UDP", "192.168.2.18", 1401

#--- Blink frame with IEEE EUI-64 tag ID ---#
BLINK_FRAME_CTRL = 0xc5
BLINK_MSG = (('framectrl', 	U8),
	     ('seqnum',		U8),
	     ('tagid', 		U64))
BLINK_ADDRESSES = [0x0101010101010101,
		   0x0202020202020202]

#--- Message frame containing the transfer information ---#
MSG_FRAME_CTRL = 0xCC41
MSG_HDR = (('framectrl', 	U16),
	   ('seqnum', 		U8),
	   ('panid', 	    	U16),
	   ('destaddr',		U64),
	   ('srceaddr',		U64))

#--- Define constants for distance measurement calculations ---#
LIGHT_SPEED = 299702547.0
TSTAMP_SEC  = 1.0 / (128 * 499.2e6)
TSTAMP_DIST = LIGHT_SPEED * TSTAMP_SEC

#--- Distance error calibration values (Each anchor has a different value) ---#
#ANCHOR_CALIBRATION_SUBSTRACTOR = 32500
#ANCHOR_CALIBRATION_MULTIPLIER = 0.93
CALIBRATION_SUBSTRACTOR_1 = 32200  #32500 #32370 #WORKS
CALIBRATION_SUBSTRACTOR_2 = 32480 #32280 #32510 #WORKS
CALIBRATION_SUBSTRACTOR_3 = 32375 #32390 #32250
CALIBRATION_SUBSTRACTOR_4 = 0
CALIBRATION_MULTIPLIER_1 = 1 #0.93 #32525 #WORKS
CALIBRATION_MULTIPLIER_2 = 1 #32280 #32510 #WORKS
CALIBRATION_MULTIPLIER_3 = 0.80 #32250
CALIBRATION_MULTIPLIER_4 = 1



#--- Define how many erros can occur in a distance measurement before resetting ---#
MAX_MEASUREMENT_ERRORS = 10
MAX_DISTANCE_ERROR = 300 # 20

#--- Class to encapsulate a message frame or header with fixed-length fields ---#
class Frame(object):
	def __init__(self, fields, bytes=[]):
		self.fields 	= fields
		self.seqnum 	= 1
		class struct(Structure):
			_pack_ 		= 1
			_fields_ 	= fields
		class union(Union):
			_fields_ = [("values", struct), ("bytes", U8*sizeof(struct))]
		self.u = union()
		for n, b in enumerate(bytes[0:sizeof(struct)]):
			self.u.bytes[n] = b
		self.bytes, self.values = self.u.bytes, self.u.values 

	#--- return frame data ---#
	def data(self):
		self.values.seqnum = self.seqnum
		self.seqnum += 1
		return list(self.bytes)

	#--- return string with field values ---#
	def field_values(self, zeros = True):
		fids = [f[0] for f in self.fields]
		return " ".join([("%s:%x" % (f, getattr(self.values, f))) for f in fids])




#--- Controller class performing the UWB measurements ---#
class MultiUWBController:

	class UwbModule(DW1000):
		def __init__(self, SPI_interface, module_ID=None, blink_ID=None,  calibration_substractor = None, calibration_multiplier = None):
			if module_ID == None:
				print("No ID provided")
				sys.exit(1)
			if blink_ID == None:
				print("No blink_ID provided")
				sys.exit(1)
			#--- Save the device parameters else the device wont maintain ---#
			self.module_ID = module_ID
			self.calibration_substractor = calibration_substractor
			self.calibration_multiplier = calibration_multiplier

			#--- Initialise the SPI interface and initialise the  DW1000 parent object ---#
			self.SPI = Spi(SPI_interface, self.module_ID)
			DW1000.__init__(self, self.SPI)

			self.blink_message = Frame(BLINK_MSG)
			self.blink_message.framectrl = BLINK_FRAME_CTRL
			self.blink_message.tagid = blink_ID

			#--- Reset the module and initialise it ---#
			self.reset()
			if not self.test_irq():
				print("No interrupt from unit {}".format(self.module_ID))
				sys.exit(1)
			self.initialise()

		#--- Returns the blink frame associated with this module ---#
		def blinkMessage(self):
			return self.blink_message

		#--- Returns the calibration substractor associated with this module ---#
		def calibrationSubstractor(self):
			return self.calibration_substractor
		#--- Returns the calibration multiplier associated with this module ---#
		def calibrationMultiplier(self):
			return self.calibration_multiplier



	def __init__(self):

		verbose = False
		for arg in sys.argv[1:]:
			if arg.lower() == '-v':
				verbose = True

		self.uwb_tag = self.UwbModule(SPIF0, '1', BLINK_ADDRESSES[0])

		self.uwb_anchors = []
		self.uwb_anchors.append(	self.UwbModule(SPIF1, '2', BLINK_ADDRESSES[1], CALIBRATION_SUBSTRACTOR_1, CALIBRATION_MULTIPLIER_1))
		#self.uwb_anchors.append(	self.UwbModule(SPIF2, '3', BLINK_ADDRESSES[1], CALIBRATION_SUBSTRACTOR_2, CALIBRATION_MULTIPLIER_2))
		#self.uwb_anchors.append(	self.UwbModule(SPIF3, '4', BLINK_ADDRESSES[1], CALIBRATION_SUBSTRACTOR_3, CALIBRATION_MULTIPLIER_3))
		#self.uwb_anchors.append(	self.UwbModule(SPIF4, '5', BLINK_ADDRESSES[1], CALIBRATION_SUBSTRACTOR_4, CALIBRATION_MULTIPLIER_4))
		

	def getDistances(self):
		errors = count = 0
		distances_current = []
		times_current = []
		distances_all = []
		#--- CHANGE THIS TO USE ALL ANCHORS LATER ON ---#
		for index, anchor in enumerate(self.uwb_anchors):
			distances_current = []
			measurement_mnt = 0
			self.uwb_tag.softreset()
			self.uwb_tag.initialise(chan=5)
			anchor.softreset()
			anchor.initialise(chan=5)
			print("\tMEASURING ANCHOR: {}".format(index))
			while measurement_mnt < 20:
				errors += 1
				if errors >= 4:
					print("Resetting")
					self.uwb_tag.softreset()
					self.uwb_tag.initialise(chan=5)
					anchor.softreset()
					anchor.initialise(chan=5)

				#--- First message ---#
				blink_message = self.uwb_tag.blinkMessage()
				txdata =  blink_message.data()
				anchor.start_rx()
				self.uwb_tag.set_txdata(txdata)
				self.uwb_tag.start_tx()
				rxdata = anchor.get_rxdata()
				if not rxdata:
					print(anchor.sys_status())
					continue
				anchor.clear_irq()



				#--- Second message ---#
				blink_message = anchor.blinkMessage()
				txdata =  blink_message.data()
				self.uwb_tag.start_rx()
				anchor.set_txdata(txdata)
				anchor.start_tx()
				rxdata = self.uwb_tag.get_rxdata()
				if not rxdata:
					print(self.uwb_tag.sys_status())
					continue
				self.uwb_tag.clear_irq

				#--- Calculate second message timestamps ---#
				dt1 = self.uwb_tag.rx_time() - self.uwb_tag.tx_time()
				dt2 = anchor.tx_time() - anchor.rx_time()
				tx1, rx1 = self.uwb_tag.tx_time(), anchor.rx_time()
				tx2, rx2 = anchor.tx_time(), self.uwb_tag.rx_time()

				#--- Third message ---#
				blink_message = self.uwb_tag.blinkMessage()
				txdata =  blink_message.data()
				anchor.start_rx()
				self.uwb_tag.set_txdata(txdata)
				self.uwb_tag.start_tx()
				rxdata = anchor.get_rxdata()
				if not rxdata:
					print(anchor.sys_status())
					continue
				anchor.clear_irq()

				#--- Time calculations ---#
				tx3, rx3 = self.uwb_tag.tx_time(), anchor.rx_time()
				round1 = rx2 - tx1
				round2 = rx3 - tx2
				reply1 = tx2 - rx1
				reply2 = tx3 - rx2
				#t1 = ((dt1 - dt2) / 2)
				t2 = (((round1 * round2) - (reply1 * reply2)) / (round1 + round2 + reply1 + reply2) - anchor.calibrationSubstractor()) * anchor.calibrationMultiplier()
				measured_distance = t2 * TSTAMP_DIST
				print("%7.3f %7.3f" % (t2, t2*TSTAMP_DIST))
				#print("%7.3f" % (measured_distance))

				#--- The measurement is false if its below 0 or above MAX_DISTANCE_ERROR ---#
				if measured_distance > MAX_DISTANCE_ERROR or measured_distance < 0:
					print("INVALID MEASUREMENT: %7.3f" % (measured_distance))
					continue
				times_current.append(t2)
				distances_current.append(measured_distance)
				measurement_mnt += 1
				errors = 0



				#--- print message count ---#
				count += 1
				if count%100 == 0:
					sys.stderr.write(str(count)+ ' ' )
					sys.stderr.flush()
				#time.sleep(0.1)
			print("-------------------------\n")
			print("FINISHED: %3.7f %7.3f" % ((sum(times_current)/20), (sum(distances_current)/20)))
			distances_all.append(sum(distances_current) / 20)
		#print("FINISHED: {}".format(distances_all))
		return(distances_all)


if __name__ == '__main__':
	#--- Initialise the ros node ---#
	rospy.init_node('uwb_measurement_publisher', anonymous = True)
	pub = rospy.Publisher('uwb_data_topic', uwb_data_raw, queue_size = 10)
	r = rospy.Rate(10)
	time.sleep(0.5)

	#--- Initialise a UWB distance measurement controller ---#
	uwb_controller = MultiUWBController()

	#--- start publishing the UWB distance measurements ---#
	while not rospy.is_shutdown():
		distance_all = []
		destination_id_all = []
		distance_all = uwb_controller.getDistances()
		r.sleep()
	rospy.spin()

sys.exit()


