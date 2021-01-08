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
- ノードを起動させます.
  - `roslaunch draw_line_ros draw_line_ros.launch`  
  - カメラ画像等が立ち上がります.  
---
## ノード概要
|ソースファイル|ノード名|概要|
|:--:|:--:|:--|
|[web_camera.cpp](https://github.com/RikuYokoo/draw_line_ros/blob/main/src/web_camera.cpp)|web_camera|webカメラからの映像をPublishします.|
|[detect_blue.cpp](https://github.com/RikuYokoo/draw_line_ros/blob/main/src/detect_blue.cpp)|detect_blue|web_cameraから映像をSubscribeし青色を検出し座標をPublishする.|
|[detect_green.cpp](https://github.com/RikuYokoo/draw_line_ros/blob/main/src/detect_green.cpp)|detect_green|web_cameraから映像をSubscribeし緑色を検出し座標をPublishする.|
|[draw_line.cpp](https://github.com/RikuYokoo/draw_line_ros/blob/main/src/draw_line.cpp)|draw_line|detect_blue,detect_green から座標を受け取り線を引く.|
|[detect_image.cpp](https://github.com/RikuYokoo/draw_line_ros/blob/main/src/detect_image.cpp)|detect_image|web_cameraから映像を,detect_blue,detect_greenからx,y座標をSubscribeします.|

---
## 動画
[動画のリンク](https://www.youtube.com/watch?v=3omE_8d17WQ)
 - 動画が横長で画質が悪くなっています

---
## ライセンス
[BSD 3-Clause "New" or "Revised" License](https://github.com/RikuYokoo/draw_line_ros/blob/main/LICENSE)
