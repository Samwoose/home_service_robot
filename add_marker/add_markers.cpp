#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <iostream>

using namespace std ;
double x, y ,w ; //position x, y , orientation w
double first_goal_x = -3.00; // check this value in pick_objects.cpp file
double first_goal_y = -1.3; //check this value in pick_objects.cpp file
int process = 1 ; // it indicates which process robot is in, 
//1=>going to first goal 
//2=>pick up the object
//3=>reach the dropoff zone
//4=>drop the object

void callbackFuc(const nav_msgs::Odometry::ConstPtr& msg){
   
  x = msg->pose.pose.position.x ;
  y = msg->pose.pose.position.y ; 
  w = msg->pose.pose.orientation.w ;

 
  ROS_INFO("message received") ;
  cout<<"process value: " << process << endl; 
  cout<<"x : " << x << endl;
  cout<<"y : " << y << endl;
  cout<<"w : " << w << endl;


}


int main( int argc, char** argv )
{
   ros::init(argc, argv, "basic_shapes");
   ros::NodeHandle n;
   ros::Rate r(1);
   ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
   //subscribe to odom
   ros::Subscriber odom_sub = n.subscribe("/odom", 1, callbackFuc);   
   
   
   // Set our initial shape type to be a cube
   uint32_t shape = visualization_msgs::Marker::CUBE;
 
   while (ros::ok())
   { 
     


     visualization_msgs::Marker marker;
     // Set the frame ID and timestamp.  See the TF tutorials for information on these.
     marker.header.frame_id = "map";
     marker.header.stamp = ros::Time::now();
 
     // Set the namespace and id for this marker.  This serves to create a unique ID
     // Any marker sent with the same namespace and id will overwrite the old one
     marker.ns = "basic_shapes";
     marker.id = 0;
 
     // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
     marker.type = shape;
 
     // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
     if(process == 1){
        ROS_INFO("Create a virtual object") ;
        marker.action = visualization_msgs::Marker::ADD;
 	
     }	
     
     if((x < 0.6 && x > -0.2) && (y < -2.2 && y > -2.8) && process == 1 ){
	ROS_INFO("arrived to the first goal") ; // x = 0.069 , y = -2.45
        marker.action = visualization_msgs::Marker::DELETE;
	process = 2 ;
     }
     if(process ==2){
       ROS_INFO("Carrying the object") ;
       marker.action = visualization_msgs::Marker::DELETE;

     }

     if((x < -1.3 && x > -1.8) && (y < -1.3 && y > -2.1) && process == 2 ){
       ROS_INFO("arrived to the drop off zone") ; // x = -1.57 , y = -1.50
       marker.action = visualization_msgs::Marker::ADD;
       process = 3 ;
     }


     if(process == 3){
        ROS_INFO("Drop the object") ;
        marker.action = visualization_msgs::Marker::ADD;
     }

// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
     if(process == 1){
        marker.pose.position.x = 0.58;
        marker.pose.position.y = -2.05;   ;
     }
     if(process == 3){
        marker.pose.position.x = -1.455;
        marker.pose.position.y = -1.845;
     }
          
     
     marker.pose.position.z = 0;
     marker.pose.orientation.x = 0.0;
     marker.pose.orientation.y = 0.0;
     marker.pose.orientation.z = 0.0;
     marker.pose.orientation.w = 1.0;

     // Set the scale of the marker -- 1x1x1 here means 1m on a side
     marker.scale.x = 0.3;
     marker.scale.y = 0.3;
     marker.scale.z = 0.3;
 
     // Set the color -- be sure to set alpha to something non-zero!
     marker.color.r = 0.0f;
     marker.color.g = 1.0f;
     marker.color.b = 0.0f;
     marker.color.a = 1.0;
 
     marker.lifetime = ros::Duration();
 
     ros::spinOnce();	
     // Publish the marker
     while (marker_pub.getNumSubscribers() < 1)
     {
       if (!ros::ok())
       {
         return 0;
       }
       //when this warning message appears, make sure to add Marker in rviz
       ROS_WARN_ONCE("Please create a subscriber to the marker");
       sleep(1);
     }
     
     
	
     marker_pub.publish(marker);
 
     
 
     r.sleep();
     
   }
 }
