#include <ros/ros.h>
#include "std_msgs/String.h" // Для приема и отправки текста
#include <sstream>

#include "../include/list_names.h" // Тут лежит инфа и конструкторы названий

ros::Subscriber dino_subscriber; // Объявляем подписчика

std::string input_topic_name;

void callback(const std_msgs::String msg)
{
  if (msg.data == "0")
  {
    ROS_INFO_STREAM("You have entered nothing");
  }
  else
    ROS_INFO_STREAM(msg.data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dino"); // инициализация ROS
  ros::NodeHandle n;             // Создание дескриптора узла
  n.param<std::string>("input_dino_topic", input_topic_name, "dino_beginning");

  dino_subscriber = n.subscribe(input_topic_name, 1, callback);

  ros::spin();

  return 0;
}
