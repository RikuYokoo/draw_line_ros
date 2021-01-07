#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <geometry_msgs/Pose2D.h>

int x, y, before_x, before_y;

cv::Mat draw = cv::Mat::zeros(720, 1280, CV_8UC3);
void drawCallback(const geometry_msgs::Pose2D& msg){
  //int x, y, before_x, before_y;
  double area;
  x = msg.x;
  y = msg.y;
  area = msg.theta;

  if(area > 1500){
    cv::line(draw, cv::Point(before_x, before_y), cv::Point(x, y), cv::Scalar(0, 255, 0), 1, CV_AA);
  }
  before_x = x;
  before_y = y;

  cv::imshow("draw", draw);
  cv::waitKey(1);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "draw_line");
  ros::NodeHandle n;
  ros::Subscriber sub_green = n.subscribe("detect_green", 1, drawCallback);
  //ros::Subscriber sub_blue = n.subscribe("detect_blue", 1, drawCallback);

  ros::spin();

  return 0;
}

