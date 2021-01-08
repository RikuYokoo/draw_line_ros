#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <geometry_msgs/Pose2D.h>

using namespace std;

cv::Mat output_image;

geometry_msgs::Pose2D ms;
class ros_image{
  ros::NodeHandle n;
  image_transport::ImageTransport it;
  image_transport::Subscriber image_sub;
  ros::Publisher pub;
public:
  ros_image()
    :it(n)
  {
    image_sub = it.subscribe("image", 1, &ros_image::imageCallback, this);
    pub = n.advertise<geometry_msgs::Pose2D>("detect_blue", 1);
  }
  ~ros_image()
  {
  }

  void imageCallback(const sensor_msgs::ImageConstPtr& msg){
    int before_x, before_y;
    double radius;
    cv_bridge::CvImagePtr cv_ptr;
    try{
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    output_image = cv_ptr->image;
    cv::Mat hsv_image, bin_image;

    /*---------------------------------------------------------------------*/
    cv::cvtColor(output_image, hsv_image, CV_BGR2HSV, 3);//bgr->hsvに変換
    cv::Scalar lower = cv::Scalar(100, 70, 70);//青
    cv::Scalar upper = cv::Scalar(130, 255, 255);
    cv::inRange(hsv_image, lower, upper, bin_image);//2値化?
    cv::erode(bin_image, bin_image, cv::Mat(), cv::Point(-1, -1), 3);
    vector<vector< cv::Point> > contours;
    cv::findContours(bin_image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//輪郭取得
    double max_area = 0;
    int max_area_contour =-1;

    if(contours.size() > 0){
      for (int j = 0; j < contours.size();j++){
        double area = contourArea(contours.at(j));
        if(max_area< area){
          max_area = area;
          max_area_contour= j;
        }
      }
      if(max_area_contour != -1){
        int count=contours.at(max_area_contour).size();
        double x=0;
        double y=0;
        for(int k=0;k<count;k++){
          x+=contours.at(max_area_contour).at(k).x;
          y+=contours.at(max_area_contour).at(k).y;
        }
        x/=count;
        y/=count;
        ms.x = x;
        ms.y = y;
        ms.theta = max_area;
        pub.publish(ms);
        cout << max_area << endl;
        radius = (double)count/2;
        cv::circle(output_image, cv::Point(x, y), 50, cv::Scalar(255, 0, 0), 3, 4);
      }
    }else{
      ms.theta = 0;
      pub.publish(ms);
    }
    /*---------------------------------------------------------------------*/
    //cv::imshow("detect_blue_image", output_image);
    cv::waitKey(1);
  }
};

int main(int argc, char** argv){
  ros::init (argc, argv, "detect_blue");
  ros_image ros_image;
  ros::spin();

  return 0;
}


