#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <signal.h>
#include <std_msgs/Int32.h>
#include "ros/this_node.h"
#include "ros/master.h"
using namespace cv;
using namespace std;

void SigintHandler(int sig)
{
    ROS_INFO("shutting down!");
    ros::shutdown();
}

double LastTime = 0;
int gamestate = 0;
int pre_state = 0;
double sec = 0;
bool restart_flag = false;
void imageCb(const sensor_msgs::ImageConstPtr &msg)
{
    LastTime = ros::Time::now().toSec();
}
void gamestate_call(const std_msgs::Int32 &msg)
{
    gamestate = msg.data;
    if (sec < 0.5 && gamestate == 0 && restart_flag == false)
    {
        pre_state = 0;
    }
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "strategy_controler");
    ros::NodeHandle h_node;
    signal(SIGINT, SigintHandler);
    //==============================
    std::string topicname = "/camera/image_raw";
    std::string nodename = "/prosilica_driver";
    const char *env_p = std::getenv("ROBOT_NS");
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
    ros::Subscriber gamestate_sub = h_node.subscribe("/FIRA/GameState", 1, gamestate_call);
    ros::Publisher gamestate_pub = h_node.advertise<std_msgs::Int32>("/FIRA/GameState", 1);
    ros::Rate loop_rate(60); //60hz

    while (ros::ok())
    {
        double sec = ros::Time::now().toSec() - LastTime;
        cout<<sec<<" "<<gamestate<<endl;
        if (sec > 0.5)
        {
            if (gamestate == 9)
            {
                pre_state = 9;
                std_msgs::Int32 msg;
                msg.data = 0;
                gamestate_pub.publish(msg);
                restart_flag = true;
                cout<<"stop\n";
            }
        }
        else
        {
            cout<<"pre_State "<<pre_state<<" restart_flag"<<restart_flag<<endl;
            if (pre_state == 9 && restart_flag)
            {
                std_msgs::Int32 msg;
                msg.data = 9;
                gamestate_pub.publish(msg);
                restart_flag = false;
                cout<<"restrart\n";
            }
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("Node exit");
    printf("Process exit\n");
    return 0;
}
