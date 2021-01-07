#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  ros::init (argc, argv, "web_camera");
  ros::NodeHandle n;

  image_transport::ImageTransport it(n);
  image_transport::Publisher image_pub = it.advertise("image", 1);

  cv::Mat image;
  cv::VideoCapture camera(2);//usb接続カメラ使用,パソコン内蔵を使用する場合は0にする
  //cv::VideoCapture camera(0);//usb接続カメラ使用,パソコン内蔵を使用する場合は0にする
  if(!camera.isOpened()){
    ROS_INFO("failed to open camera.");
    return -1;
  }
  ros::Rate looprate (50);
  while(ros::ok()){
    camera >> image;
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
    image_pub.publish(msg);
    ros::spinOnce();
    looprate.sleep();
  }
  return 0;
}
