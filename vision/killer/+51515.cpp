#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <signal.h>

using namespace cv;
using namespace std;

void SigintHandler(int sig){
	ROS_INFO("shutting down!");
	ros::shutdown();
}

double Rate(){	
	double ALPHA = 0.5;
	double dt;
	static double FrameRate = 0.0;
	static int frame_counter = 0;
	static double StartTime = ros::Time::now().toNSec();
	double EndTime;

	frame_counter++;
	if (frame_counter == 10){
		EndTime = ros::Time::now().toNSec();
		dt = (EndTime - StartTime) / frame_counter;
		StartTime = EndTime;
		if (dt != 0){
			FrameRate = (1000000000.0 / dt) * ALPHA + FrameRate * (1.0 - ALPHA);
			cout << "FPS: " << FrameRate << endl;
		}
		frame_counter = 0;
	}
        return FrameRate;
}

void imageCb(const sensor_msgs::ImageConstPtr &msg){
	cv_bridge::CvImagePtr cv_ptr;
	try{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8); //convert image data

		Mat Source = cv_ptr->image.clone();
		//cv::flip(Source, Source, 1); // reverse image
		if(!cv_ptr->image.empty()){
			cv::imshow("Subsriber window", cv_ptr->image);
			cv::waitKey(1);
		}
		Rate();
	}
	catch (cv_bridge::Exception &e){
		ROS_ERROR("Could not convert to image!");
		return;
	}
}

int main(int argc,char **argv){
	ros::init(argc, argv, "image_subscriber");
	ros::NodeHandle h_node;
	signal(SIGINT, SigintHandler);
	
	ros::Subscriber image_sub = h_node.subscribe("/camera/image_raw", 1, imageCb);
	ros::Rate loop_rate(60); //60hz
	while (ros::ok()){
		ros::spinOnce();
		loop_rate.sleep();
	}
	ROS_INFO("Node exit");
	printf("Process exit\n");
	return 0;
}


