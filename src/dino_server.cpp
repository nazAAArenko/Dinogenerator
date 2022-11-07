#include "ros/ros.h"
#include "dino/GenerateName.h"
#include <ros/console.h>
#include "std_msgs/String.h"
#include "../include/list_names.h"
#include <string>
#include <random>
#include <time.h>

ros::Publisher dino_publisher;

std::string output_topic_name;

int length;

bool get_beginning(dino::GenerateName::Request &req,
                   dino::GenerateName::Response &resp)
{
   if (req.word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") != std::string::npos)
   {
      ROS_INFO_STREAM("Input only Latin symbols");
      return false;
   }

   if (req.word.empty())
   {
      resp.name.data = "0";
      dino_publisher.publish(resp.name);
      return false;
   }

   length = req.word.size();
   for (int i = 1; i < length; i++)
   {
      req.word[i] = tolower(req.word[i]);
   }
   req.word[0] = toupper(req.word[0]);
   resp.name.data = req.word + dino_facts[rand() % 10];
   dino_publisher.publish(resp.name);
   return true;
}

int main(int argc, char **argv)
{
   srand(time(0));
   ros::init(argc, argv, "generate_name_server");
   ros::NodeHandle n;
   n.param<std::string>("outpit_dino_topic", output_topic_name, "dino_beginning");
   dino_publisher = n.advertise<std_msgs::String>(output_topic_name, 1);

   ros::ServiceServer service = n.advertiseService("get_beginning", get_beginning);
   ROS_INFO("Ready to know some facts about dinosaurs and get his full name. Please, enter the beginning of dinosaur name.");

   ros::spin();

   return 0;
}
