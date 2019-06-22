#!/usr/bin/env python
# -*- coding: utf-8 -*-+

import roslib
roslib.load_manifest('strategy')
import rospy

# rostopic msg
from std_msgs.msg import Int32,Bool
from geometry_msgs.msg import Twist

class NodeHandle(object):
	def __init__(self):
		self._moving = False
		self.sub_moving = rospy.Subscriber("FIRA/Moving",Bool,self.Set_moving)
		self.pub_vel = rospy.Publisher('motion/cmd_vel',Twist, queue_size = 1)
	def Set_moving(self,msg):
		self._moving = msg.data
	def Set_stop(self):
		twist = Twist()
		twist.linear.x = 0
		twist.linear.y = 0
		twist.angular.z = 0
		self.pub_vel.publish(twist)
def main():
	rospy.init_node('moving_detection', anonymous=True)
	node = NodeHandle()
	# 30 hz
	rate = rospy.Rate(2)
	i = 0
	
	while not rospy.is_shutdown():
			if(not node._moving):        
				node.Set_stop()
				print('stop')
			else:
				node._moving = False
				print('moving')
			rate.sleep()
	try:
		print("stop")
		rospy.spin()
	except KeyboardInterrupt:
		print("Shutting down")

if __name__ == "__main__":
	main()
