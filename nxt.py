#!/usr/bin/env python3

import rospy
from std_msgs.msg import Bool, String
from drobot_comm.msg import Task

class TaskManager:
    def __init__(self):
        rospy.init_node('task_manager', anonymous=True)
        self.task_input_bool = False
        self.task = ""
        self.station = ""
        self.bool_pub = rospy.Publisher('trig_topic', Bool, queue_size=10)
        self.string_pub = rospy.Publisher('task_topic', String, queue_size=10)
        rospy.Subscriber('/task', Task, self.task_callback)
        self.rate = rospy.Rate(50) 

    def task_callback(self, msg):
        if msg.created_time:
            self.task_input_bool = True
            self.task = msg.task_type
            self.station = msg.task_station
            rospy.loginfo(f"Task received: {self.task} at station {self.station}")
        else:
            rospy.logwarn("Received task with no created_time.")

    def publish_messages(self):
        while not rospy.is_shutdown():
            bool_msg = Bool(data=self.task_input_bool)
            self.bool_pub.publish(bool_msg)
            rospy.loginfo(f"Publishing Boolean: {bool_msg.data}")
            
            if self.task_input_bool:
                user_input_string = f"{self.task},nort,,70,1"
                string_msg = String(data=user_input_string)
                self.string_pub.publish(string_msg)
                rospy.loginfo(f"Publishing String: {user_input_string}")
            else:
                rospy.loginfo("No valid task to publish.")

            self.rate.sleep()

    def spin(self):
        self.publish_messages()
        rospy.spin()

if __name__ == '__main__':
    try:
        task_manager = TaskManager()
        task_manager.spin()
    except rospy.ROSInterruptException:
        pass
