# draw_line_ros
ロボットシステム学課題2
---
## 概要  
- ロボットシステム学の課題2で,ros,opencv,webカメラを使用し作成した.  
- ペンを用いなくても線が引けます.
---
## 環境  
- Ubuntu 18.04.5 LTS  
- ROS Melodic
- OpenCV 3.2.0  
- webカメラ 
  - [こちらの製品](http://www.sac-corp.jp/product/contents/actioncam/ac200.html)を使用しました.  
---
## 環境構築  
- ROSのインストール
  - [こちら](https://github.com/ryuichiueda/ros_setup_scripts_Ubuntu18.04_desktop)を利用しインストールさせていただきました.  
- opencvのインストール  
  - [公式サイト](https://opencv.org/)  
- パッケージのクローン
```sh
cd ~/catkin_ws/src  
git clone https://github.com/RikuYokoo/draw_line_ros.git  
(cd ~/catkin_ws && catkin_make)  
```
---
## 実行方法
- roscoreを立ち上げます.
  - `roscore`  
もう一つ端末を開きます.  
- パッケージを起動させます.
  - `roslaunch draw_line_ros draw_line_ros.launch`  
  - カメラ画像等が立ち上がります.  
---
## パッケージ概要
---
