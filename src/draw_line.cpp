#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <geometry_msgs/Pose2D.h>

int blue_x, blue_y, b_blue_x, b_blue_y, green_x, green_y, b_green_x, b_green_y;

cv::Mat draw = cv::Mat::zeros(720, 1280, CV_8UC3);
void drawgreenCallback(const geometry_msgs::Pose2D& msg){
  double area;
  green_x = msg.x;
  green_y = msg.y;
  area = msg.theta;

  if(area > 1500){
    cv::line(draw, cv::Point(b_green_x, b_green_y), cv::Point(green_x, green_y), cv::Scalar(0, 255, 0), 3, CV_AA);
  }
  b_green_x = green_x;
  b_green_y = green_y;

  cv::imshow("draw", draw);
  cv::waitKey(1);
}
void drawblueCallback(const geometry_msgs::Pose2D& msg){
  double area;
  blue_x = msg.x;
  blue_y = msg.y;
  area = msg.theta;

  if(area > 1500){
    cv::line(draw, cv::Point(b_blue_x, b_blue_y), cv::Point(blue_x, blue_y), cv::Scalar(255, 144, 30), 3, CV_AA);
  }
  b_blue_x = blue_x;
  b_blue_y = blue_y;

  cv::imshow("draw", draw);
  cv::waitKey(1);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "draw_line");
  ros::NodeHandle n;
  ros::Subscriber sub_green = n.subscribe("detect_green", 1, drawgreenCallback);
  ros::Subscriber sub_blue = n.subscribe("detect_blue", 1, drawblueCallback);

  ros::spin();

  return 0;
}

