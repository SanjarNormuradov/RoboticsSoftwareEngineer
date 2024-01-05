#!/bin/sh
terminator -e "bash -c 'source ~/RoboticsSoftwareEngineer/project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=~/RoboticsSoftwareEngineer/project5/catkin_ws/src/worlds/office; exec bash'" &
sleep 10
terminator -e "bash -c 'source ~/RoboticsSoftwareEngineer/project5/catkin_ws/devel/setup.bash; roslaunch gmapping slam_gmapping_pr2.launch; exec bash'" &
sleep 10
terminator -e "bash -c 'source ~/RoboticsSoftwareEngineer/project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch; exec bash'" &
sleep 10
terminator -e "bash -c 'source ~/RoboticsSoftwareEngineer/project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch; exec bash'"
