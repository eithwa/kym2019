/**
 * @file BaseNode.h
 *
 * @brief Ros communication central!
 *
 * @date February 2014
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef Strategy_nodeHandle_HPP_
#define Strategy_nodeHandle_HPP_




/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include <string>
#include <iostream>
#include "../common/defend_Env.h"
#include "../common/BaseNode.h"

//message include
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include "vision/Object.h"
#include "vision/Two_point.h"
#include "fira_status_plugin/RobotSpeedMsg.h"
#include "fira_status_plugin/ModelMsg.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "gazebo_msgs/ModelStates.h"
#include "std_msgs/Int32MultiArray.h"

/*****************************************************************************
** Define
*****************************************************************************/
#define Ball_Topic_Name         "/FIRA/Strategy/WorldMap/soccer"
#define ModelState_Topic_Name  "/gazebo/model_states"
//robot prefix
#define Robot_Topic_Prefix "/FIRA/R"
#define RobotOpt_Topic_Prefix "/FIRA/Opt_R"
#define GameState_Topic "/FIRA/GameState"
#define TeamColor_Topic "/FIRA/TeamColor"
#define Vision_Topic "/vision/object"
#define Vision_Two_point_Topic "/interface/Two_point"
#define SAVEPARAM_TOPIC "/FIRA/SaveParam"
//BlackObject_distance
#define  BlackObject_Topic "/vision/BlackRealDis"
//one_Robot speed
#define Robot_Topic_Speed "/motion/cmd_vel"
//robot suffix
#define Robot_Position_Topic_Suffix "/Strategy/WorldMap/RobotPos"
#define Robot_Role_Topic_Suffix "/Strategy/Coach/role"
#define RobotSpeed_Topic_Suffix "/Strategy/PathPlan/RobotSpeed"

#define Node_Name "PersonalStrategy"

//RobotNumber
#define RobotNumber_Topic "/FIRA/RobotNumber"

#define VectorMax 1.42
#define VectorMin 0.05
/*****************************************************************************
** Class
*****************************************************************************/

class Strategy_nodeHandle :public BaseNode {
public:
    Strategy_nodeHandle(int argc, char** argv);

    virtual ~Strategy_nodeHandle(){}

    void pubGrpSpeed();

    void setEnv(Environment *inEnv){
        global_env = inEnv;

    }
    // shoot signal
    ros::Publisher shoot;
    // pub shoot signal
    void pubShoot(int shoot_value){
        ros::Time current = ros::Time::now();
        static double current_time =10000;
        static double record_time;
        double time = current_time-record_time;
        if(time>1){
            std_msgs::Int32 shoot_signal;
            shoot_signal.data = shoot_value;
            shoot.publish(shoot_signal);
            record_time = current_time;
        }
        current_time = (double)(current.sec+(double)current.nsec/1000000000);

    }
    struct SaveAry{
            int distance;
            int location;
            int counter;
        };
    struct SaveAry Save[20];
    struct New_SaveAry{
            int distance;
            int location;
            int counter;
            int middle;
            int middle_place;
        };
    struct New_SaveAry New_Save[20];

    int* getRoleAry(){
        return roleAry;
    }

    void setOpponent(bool inBool){opponent = inBool;}

    ros::NodeHandle* getNodeHandle(){return n;}
    long getGameState(){return gamestate;}
    std::string getTeamColor(){return teamcolor;}
    int getIsSimulator(){return IsSimulator;}

    //BlackObject
    int Blackangle;
    int *blackobject;
    void loadParam(ros::NodeHandle *n);
    int* getBlackObject(){return blackobject;}
protected:
    void ros_comms_init();

private:
    int roleAry[PLAYERS_PER_SIDE];
    std::string model_array[11];
    bool opponent;

    Environment *global_env;


    ros::NodeHandle *n;
    long gamestate;
    std::string teamcolor;

    //gazebo_ModelStates subscriber
    ros::Subscriber Gazebo_Model_Name_sub;

    //ball subscriber
    ros::Subscriber ball_sub;

    //robot subscriber
    ros::Subscriber robot_1_pos_sub  ;
    ros::Subscriber robot_2_pos_sub  ;
    ros::Subscriber robot_3_pos_sub  ;
    ros::Subscriber robotOpt_1_pos_sub  ;
    ros::Subscriber robotOpt_2_pos_sub  ;
    ros::Subscriber robotOpt_3_pos_sub  ;

    ros::Subscriber GameState;
    ros::Subscriber TeamColor;
    ros::Subscriber Vision;
    ros::Subscriber Vision_Two_point;

    //BlackObject
    ros::Subscriber BlackObject;

    //robot role publisher
    //no robot_1_role_sub, because robot_1 is always goal keeper
    ros::Subscriber robot_1_role_sub;
    ros::Subscriber robot_2_role_sub;
    ros::Subscriber robot_3_role_sub;
    ros::Subscriber SAVEPARAM;

    //robot speed publisher
    ros::Publisher robot_1_speed_pub;
    ros::Publisher robot_2_speed_pub;
    ros::Publisher robot_3_speed_pub;
    ros::Publisher robotOpt_1_speed_pub;
    ros::Publisher robotOpt_2_speed_pub;
    ros::Publisher robotOpt_3_speed_pub;

    //one_robot speed
    ros::Publisher robot_speed_pub;

    /// load param begin
    std::vector<double> SPlanning_Velocity;
    std::vector<double> Distance_Settings;
    int IsSimulator;
    /// load param end

    bool run_one = false;

    void Transfer(int);

    double c_v_x,c_v_y;

    void rotateXY(double rotate,double inX,double inY,double &newX,double &newY);
    void pubSpeed(ros::Publisher *puber,double v_x,double v_y,double v_yaw,double robot_rot);
    void velocity_S_planning(geometry_msgs::Twist *msg);

    //find Gazebo_msgs::ModelStates name
    void find_gazebo_model_name_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){//----------------------------------printf here is ok, but printf next row will crash if i open over one robot map
        if(run_one) return;
        int model_length;
        model_length = msg->name.size();
        for(int i = 0; i<model_length;i++){
            model_array[i] = msg->name[i];
        }
        run_one = true;
    }
    int get_model_num(const std::string ModelName){
        int send_back_num;
        for(int i =0; i< 11; i++){
            if(model_array[i] == ModelName) return i;
        }
    }

//Use_topic_gazebo_msgs_Model_States to get model position
    void  ball_sub_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){
        int model_num;
        model_num = get_model_num("soccer");
        geometry_msgs::Pose tPose = msg->pose[model_num];
        global_env->currentBall.pos.x = tPose.position.x;
        global_env->currentBall.pos.y = tPose.position.y;
    }
    void robot_1_pos_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){
        int model_num;
        model_num = get_model_num("R1");
        geometry_msgs::Pose tPose = msg->pose[model_num];
        global_env->home[0].pos.x = tPose.position.x;
        global_env->home[0].pos.y = tPose.position.y;
        Transfer(0);

        double w = tPose.orientation.w;
        double x = tPose.orientation.x;
        double y = tPose.orientation.y;
        double z = tPose.orientation.z;
        double yaw = atan2(  2*(w*z+x*y),  1-2*(y*y+z*z)  )*rad2deg;
        global_env->home[0].rotation = yaw;
    }
    void robot_2_pos_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){
        int model_num;
        model_num = get_model_num("R2");
        geometry_msgs::Pose tPose = msg->pose[model_num];
        global_env->home[1].pos.x = tPose.position.x;
        global_env->home[1].pos.y = tPose.position.y;
        Transfer(1);

        double w = tPose.orientation.w;
        double x = tPose.orientation.x;
        double y = tPose.orientation.y;
        double z = tPose.orientation.z;
        double yaw = atan2(  2*(w*z+x*y),  1-2*(y*y+z*z)  )*rad2deg;
        global_env->home[1].rotation = yaw;

    }
    void  robot_3_pos_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){
        int model_num;
        model_num = get_model_num("R3");
        geometry_msgs::Pose tPose = msg->pose[model_num];
        global_env->home[2].pos.x = tPose.position.x;
        global_env->home[2].pos.y = tPose.position.y;
        Transfer(2);

        double w = tPose.orientation.w;
        double x = tPose.orientation.x;
        double y = tPose.orientation.y;
        double z = tPose.orientation.z;
        double yaw = atan2(  2*(w*z+x*y),  1-2*(y*y+z*z)  )*rad2deg;
        global_env->home[2].rotation = yaw;

    }


    void  robotOpt_1_pos_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){
        int model_num;
        model_num = get_model_num("FIRA_Opt_1");
        geometry_msgs::Pose tPose = msg->pose[model_num];
        global_env->opponent[0].pos.x = tPose.position.x;
        global_env->opponent[0].pos.y = tPose.position.y;

        double w = tPose.orientation.w;
        double x = tPose.orientation.x;
        double y = tPose.orientation.y;
        double z = tPose.orientation.z;
        double yaw = atan2(  2*(w*z+x*y),  1-2*(y*y+z*z)  )*rad2deg;
        global_env->opponent[0].rotation = yaw;
    }


    void  robotOpt_2_pos_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){
        int model_num;
        model_num = get_model_num("FIRA_Opt_2");
        geometry_msgs::Pose tPose = msg->pose[model_num];
        global_env->opponent[1].pos.x = tPose.position.x;
        global_env->opponent[1].pos.y = tPose.position.y;

        double w = tPose.orientation.w;
        double x = tPose.orientation.x;
        double y = tPose.orientation.y;
        double z = tPose.orientation.z;
        double yaw = atan2(  2*(w*z+x*y),  1-2*(y*y+z*z)  )*rad2deg;
        global_env->opponent[1].rotation = yaw;
    }


    void  robotOpt_3_pos_fun(const gazebo_msgs::ModelStates::ConstPtr &msg){
        int model_num;
        model_num = get_model_num("FIRA_Opt_3");
        geometry_msgs::Pose tPose = msg->pose[model_num];
        global_env->opponent[2].pos.x = tPose.position.x;
        global_env->opponent[2].pos.y = tPose.position.y;

        double w = tPose.orientation.w;
        double x = tPose.orientation.x;
        double y = tPose.orientation.y;
        double z = tPose.orientation.z;
        double yaw = atan2(  2*(w*z+x*y),  1-2*(y*y+z*z)  )*rad2deg;
        global_env->opponent[2].rotation = yaw;
    }

    void  robot_1_role_fun(const std_msgs::Int32::ConstPtr &msg){
        roleAry[0] = msg->data;
    }

    void  robot_2_role_fun(const std_msgs::Int32::ConstPtr &msg){
        roleAry[1] = msg->data;
    }

    void  robot_3_role_fun(const std_msgs::Int32::ConstPtr &msg){
        roleAry[2] = msg->data;
    }
    void subGameState(const std_msgs::Int32::ConstPtr &msg){
        gamestate=msg->data;
    }
    void subTeamColor(const std_msgs::String::ConstPtr &msg){
        teamcolor= msg->data;
    }

    void subVision(const vision::Object::ConstPtr &msg){
        double ball_distance,yellow_distance,blue_distance;
	//std::cout << "ball_dis_msg = " << msg->ball_dis << std::endl;
        yellow_distance = msg->yellow_dis;
        blue_distance = msg->blue_dis;
        if(global_env->teamcolor == "Blue"){
            global_env->home[global_env->RobotNumber].op_goal.distance= blue_distance/100;
            global_env->home[global_env->RobotNumber].op_goal.angle = msg->blue_ang;
            global_env->home[global_env->RobotNumber].goal.distance = yellow_distance/100;
            global_env->home[global_env->RobotNumber].goal.angle = msg->yellow_ang;

        }else if(global_env->teamcolor == "Yellow"){
            global_env->home[global_env->RobotNumber].op_goal.distance= yellow_distance/100;
            global_env->home[global_env->RobotNumber].op_goal.angle = msg->yellow_ang;
            global_env->home[global_env->RobotNumber].goal.distance= blue_distance/100;
            global_env->home[global_env->RobotNumber].goal.angle = msg->blue_ang;
        }

        ball_distance = msg->ball_dis;
        global_env->home[global_env->RobotNumber].ball.distance = ball_distance/100;
        global_env->home[global_env->RobotNumber].ball.angle = msg->ball_ang;
        global_env->home[global_env->RobotNumber].ball_fly = msg->ball_fly;                
    }

/*****/    //for goalkeeper on 5th robot with ros  //front = 45
    void subVision_Two_point(const vision::Two_point::ConstPtr &msg){
        if(global_env->teamcolor == "Blue"){
            int ang_max = msg->blue_ang_max;
            int ang_min = msg->blue_ang_min;
            // ang_max = two_point_angle_fix(ang_max);
            // ang_min = two_point_angle_fix(ang_min);
            //angle cannot scan fix
//                if(ang_max > - 56){
//                    ang_max = ang_min - 160;
//                }else if(ang_min < 57){
//                    ang_min = ang_max + 160;
//                }
//            ang_max = angle_fix(ang_max);
//            ang_min = angle_fix(ang_min);
            global_env->home[global_env->RobotNumber].opgoal_edge.angle_max = ang_max;
            global_env->home[global_env->RobotNumber].opgoal_edge.angle_min = ang_min;
            double opgoal_left = msg->blue_left,opgoal_right = msg->blue_right;
            global_env->home[global_env->RobotNumber].opgoal_edge.left_dis = opgoal_left/100;
            global_env->home[global_env->RobotNumber].opgoal_edge.right_dis = opgoal_right/100;
        }else if(global_env->teamcolor == "Yellow"){
            int ang_max = msg->yellow_ang_max;
            int ang_min = msg->yellow_ang_min;
            // ang_max = two_point_angle_fix(ang_max);
            // ang_min = two_point_angle_fix(ang_min);
            //angle cannot scan fix
//                if(ang_max > - 56){
//                    ang_max = ang_min - 160;
//                }else if(ang_min < 57){
//                    ang_min = ang_max + 160;
//                }
//            ang_max = angle_fix(ang_max);
//            ang_min = angle_fix(ang_min);
            global_env->home[global_env->RobotNumber].opgoal_edge.angle_max = ang_max;
            global_env->home[global_env->RobotNumber].opgoal_edge.angle_min = ang_min;
            double opgoal_left = msg->yellow_left,opgoal_right = msg->yellow_right;
            global_env->home[global_env->RobotNumber].opgoal_edge.left_dis = opgoal_left/100;
            global_env->home[global_env->RobotNumber].opgoal_edge.right_dis = opgoal_right/100;
        }
    }

    // int two_point_angle_fix(int angle){
    //     int front = 46;
    //     if(angle <= 225){
    //         angle = angle - front;
    //     }else{
    //         angle = angle -(360+front);
    //     }
    //     return angle;
    // }
//    int angle_fix(int angle){
//        if(angle > 180){
//            angle = angle -360;
//        }else if(angle < -180){
//       angle = angle +360;
//        }
//        return angle;
//    }
/*****/

    void subBlackObject(const std_msgs::Int32MultiArray::ConstPtr &msg){
        static int counter=0;
        int All_Line_distance[360];
        int angle[360];
        int place;

        for(int i=0; i<360/Blackangle-23; i++){
            All_Line_distance[i] = msg -> data[i];
        }
        global_env->mindis[0] = All_Line_distance[0];
        for(int i=1; i<360/Blackangle-23; i++){
            if(All_Line_distance[i] < global_env->mindis[0]){
				if(All_Line_distance[i]>25 &&All_Line_distance[i]<1000){						
					global_env->mindis[0] = All_Line_distance[i];
					place = i;
				}
			}
        }

     global_env->blackangle[0] = place*3;
     if(global_env->blackangle[0] > 180){
        global_env->blackangle[0] = -(360 - global_env->blackangle[0]);
     }


    }
     void getSaveParam(const std_msgs::Int32::ConstPtr &msg){
         global_env->SaveParam = msg->data;
     }
};

#endif /* NODE_HPP_ */
