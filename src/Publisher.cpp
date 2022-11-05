#include <ros/ros.h>
#include "std_msgs/String.h"            // Для приема и отправки текста
#include <sstream>

#include "../include/List_Names.h"  // Тут лежит инфа и конструкторы названий

// Объявляем издетеля и подписчика

ros::Subscriber subscriber;

// Переменные для записи параметров

std::string input_topic_name;


int citation_number = -1;       // Номер публикуемой цитаты
bool get_new_citation = false;  // Флаг для публикации цитаты
const double frecuency = 10.0;  // Частота работы узла в Гц

// Функция установки номера отправляемой цитаты
void citation_number_callback(const std_msgs::Int8::ConstPtr& msg){
  citation_number = msg->data;
  get_new_citation = true;
}

int main(int argc, char **argv){
ros::init(argc,argv,"dino");   //      инициализация ROS                                          
  ros::NodeHandle n;                        // Создание дескриптора узла
  ROS_INFO("Starting..");             
  n.param<std::string>("input_dino_topic", input_topic_name, "dino");// Записываем значение параметра в переменную. Если значение не задано - будет значение по-умолчанию
  citation_number_subscriber = n.subscribe(input_topic_name,1,&citation_number_callback);      // Определение подписчика
  ros::Rate loop_rate(frecuency);

  ROS_INFO_STREAM("To get Bender's wisdom, send a number from 0 to 10 inclusively to the topic " <<
                  n.getNamespace() << "/" << input_topic_name);
 
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
