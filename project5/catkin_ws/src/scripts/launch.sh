#!/bin/sh
terminator -e "gazebo" &
sleep 5
terminator -e "bash -c 'source /opt/ros/kinetic/setup.bash; roscore'" &
sleep 5
terminator -e "rviz"
