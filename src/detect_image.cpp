#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <geometry_msgs/Pose2D.h>

using namespace std;

int blue_x, blue_y, blue_area, green_x, green_y, green_area;

cv::Mat detect_image;

geometry_msgs::Pose2D ms;
class ros_image{
  ros::NodeHandle n;
  image_transport::ImageTransport it;
  image_transport::Subscriber image_sub;
  ros::Publisher pub;
  ros::Subscriber green_sub, blue_sub;
public:
  ros_image()
    :it(n)
  {
    image_sub = it.subscribe("image", 1, &ros_image::imageCallback, this);
    //green_sub = n.subscribe("detect_green", 1, &ros_image::posegreenCallback, this);
    blue_sub = n.subscribe("detect_blue", 1, &ros_image::poseblueCallback,this);
    green_sub = n.subscribe("detect_green", 1, &ros_image::posegreenCallback, this);
  }
  ~ros_image()
  {
  }
  void poseblueCallback(const geometry_msgs::Pose2D& msg){
    blue_x = msg.x;
    blue_y = msg.y;
    blue_area = msg.theta;
  }
  void posegreenCallback(const geometry_msgs::Pose2D& msg){
    green_x = msg.x;
    green_y = msg.y;
    green_area = msg.theta;
  }

  void imageCallback(const sensor_msgs::ImageConstPtr& msg){
    //green_sub = n.subscribe("detect_green", 1, posegreenCallback);
    //blue_sub = n.subscribe("detect_blue", 1, poseblueCallback);
    int before_x, before_y;
    cv_bridge::CvImagePtr cv_ptr;
    try{
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    detect_image = cv_ptr->image;
    if(blue_area > 0)
      cv::circle(detect_image, cv::Point(blue_x, blue_y), 50, cv::Scalar(255, 0, 0), 3, 4);
    if(green_area > 0)
      cv::circle(detect_image, cv::Point(green_x, green_y), 50, cv::Scalar(0, 255, 0), 3, 4);

    cv::imshow("detect_image", detect_image);
    cv::waitKey(1);
  }
};

int main(int argc, char** argv){
  ros::init (argc, argv, "detect_image");
  ros_image ros_image;
  ros::spin();

  return 0;
}
