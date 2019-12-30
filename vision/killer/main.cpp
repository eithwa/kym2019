#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <signal.h>
#include "ros/this_node.h" 
 #include "ros/master.h"
using namespace cv;
using namespace std;

void SigintHandler(int sig){
	ROS_INFO("shutting down!");
	ros::shutdown();
}

Mat image;
void imageCb(const sensor_msgs::ImageConstPtr &msg){
	cv_bridge::CvImagePtr cv_ptr;
	try{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8); //convert image data

		Mat Source = cv_ptr->image.clone();
		//cv::flip(Source, Source, 1); // reverse image
		if(!cv_ptr->image.empty()){
            image = cv_ptr->image.clone();
			//cv::imshow("Image window", cv_ptr->image);
			//cv::waitKey(1);
		}
	}
	catch (cv_bridge::Exception &e){
		ROS_ERROR("Could not convert to image!");
		return;
	}
}

int main(int argc,char **argv){
	ros::init(argc, argv, "killer");
	ros::NodeHandle h_node;
	signal(SIGINT, SigintHandler);
	//==============================
    const char* env_p = std::getenv("ROBOT_NS");
    std::string topicname = "/camera/image_raw";
    std::string nodename = "/prosilica_driver";
    /*if(env_p){
        std::string env_(env_p);
        topicname = env_+"/camera/image_raw";
        nodename = env_+"/prosilica_driver";
    }
    else{
        topicname = "/camera/image_raw";
        nodename = "/prosilica_driver";
    }*/
    //==============================
	ros::Subscriber image_sub = h_node.subscribe(topicname, 1, imageCb);
	ros::Rate loop_rate(60); //60hz
    double StartTime = ros::Time::now().toSec();
    vector<string> node_name;
    //v_string.push_back("/monitor");
    bool get_node = false;
	while (ros::ok()){
        double sec = ros::Time::now().toSec() - StartTime;
        node_name.clear();
        if(ros::master::getNodes(node_name)){
            for(int i=0; i<node_name.size(); i++){
                if(node_name[i] == nodename){
                    if(get_node == false){
                        cout<<"open\n";
                        get_node = true;
                        StartTime = ros::Time::now().toSec();
                    }
                }
            }
        }
        if(!get_node){
            StartTime = ros::Time::now().toSec();
        }
        if(sec>2&&get_node){
            if(!image.empty()){
                image.release();
                StartTime = ros::Time::now().toSec();
                
            }else{
                //cout<<"kill\n";
                std::string system_="rosnode kill "+nodename;
                system(system_.c_str());
                get_node = false;
            }
        }

		ros::spinOnce();
		loop_rate.sleep();
	}
	ROS_INFO("Node exit");
	printf("Process exit\n");
	return 0;
}
