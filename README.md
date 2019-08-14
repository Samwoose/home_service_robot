# home_service_robot

How to run the program

1. Open a new terminal
2. $conda init bash
3. Close the terminal
4. Open a new terminal
5. $cd /home/workspace/catkin_ws
6. $pip install catkin_pkg
7. $catkin_make
8. $source devel/setup.bash
9. $cd src/scripts
10.$conda activate /opt/robond/py2
11.$chmod +x home_service.sh
12. $./home_service.sh


#Purposes of packages
#Used directories, packages and launch file
1. turtlebot_simulator -> turtlebot_gazebo(package) -> launch -> turtlebot_world.launch(launch file)
Purpose: create world and robot that will perform home service task( pick up object and deliver it to the drop off zone)

2. turtlebot_interactions -> turtlebot_rviz_launchers(package) ->  launch -> view_navigation.launch(launch file)
Purpose: call the rviz configuration that is required in this project. 

3. turtlebot_simulator -> turtlebot_gazebo(package) -> launch -> amcl_demo.launch(launch file)
Purpose: perform localization and help navigation task from pick up zone to drop off zone.
(playground.pgm and playground.yaml are in turtlebot_simulator/turtlebot_gazebo/map directory )
Map image is created by SLAM. ( turtlebot_simulator -> turtlebot_gazebo(package)->launch->gmapping_demo.launch(launch file) )

4. add_markers(package) -> launch -> add_markers.launch(launch file)
Purpose: perform the task that adds and deletes depending on our robot’s location. When the robot is around pick-up area, it delete a virtual object. When the robot has arrived around drop-off zone, it add the virtual object marker on rviz. 

5. pick_objects(package) -> launch -> pick_objects.launch(launch file)
Purpose: perform the task that move the robot to pick-up zone, wait for 5 seconds ,and again move the robot to drop-off zone.


