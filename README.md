# TKURoboSot
TKU Team participate in FIRA RoboSot league.

## Packages Required
```bash
$ sudo apt-get install ros-kinetic-prosilica-camera
# camera ip is 192.168.16.100
$ sudo apt-get install ros-kinetic-rosbridge-server
$ sudo apt-get install ros-kinetic-web-video-server
```
## Build

Need to build package `imu_3d` and `vision` first, because there are some `msg` need to build first.
After that, build all
```bash
$ cd fira_ws/
$ catkin_make --pkg imu_3d
$ catkin_make --pkg vision
$ catkin_make
```

## Quickly start Robot 

```bash
$ roslaunch fira_launch main_launch.launch

Set robot's vision parameter. When you parameter setting has been completed,you might close this command on terminal.
$ rosrun vision interface_node

$ rosrun strategy teamStrategy
$ rosrun strategy FIRA_strategy
```

## Step-by-step setting guide
```bash
1.Open the roscore. 
$ roscore
2.Load parameter.
$ rosparam load src/fira_launch/default_config/vision_better.yaml
    * NB: If you want to load camera parameter only, using following command.
    $ rosparam load src/vision/prosilica_parameter /prosilica_driver
3.Start motion node.
$ rosrun motion Attack_motion
    * NB: You can testing the motion of robot by publishing /motion/cmd_vel topic
4.Using mjpeg_server to stream image topic.
$ rosrun mjpeg_server mjpeg_server 
5.Start user interface node. 
$ rosrun vision interface_node 
6.Start image processing node.
$ rosrun vision monitor
7.Start rosbridge node.
$ roslaunch rosbridge_server rosbridge_websocket.launch
8.Run the FIRA strategy include two nodes.
   i.  Team strategy
   $ rosrun strategy teamStrategy
   ii. Personal strategy
   $ rosrun strategy FIRA_strategy
```
