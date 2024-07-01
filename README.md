# Quick Start
Compiling tests passed on ubuntu 20.04** with ros2 installed.
You can just execute the following commands one by one.
```
git clone https://github.com/weiwei-dotcom/path_follow.git
cd path_follow
colcon build
source install/setup.bash
ros2 launch path_follow.launch.py
```
If you find this work useful or interesting, please kindly give us a star :star:, thanks!:grinning:

# Acknowledgements
- The Ceres solver we use is from [Ceres Solver](http://ceres-solver.org/installation.html), which is lightweight and easy to use. We use Ceres to solver the fit problem between CDCR(Cable-Driven Continuum Robot) and planner path.

# Related Paper
[连续体机器人路径跟随拟合算法[J]](https://s43.aconvert.com/convert/p3r68-cdx67/kxe2r-h2s3y.pdf).

# This is an Motion Planner for CDCR Path Follow Motion.
![连续体机器人跟随等曲率半圆圆弧路径](https://github.com/weiwei-dotcom/path_follow/assets/62756096/4741e273-21a1-4c4a-a7b6-80b8523ae1a5)
![连续体跟随避障路径](https://github.com/weiwei-dotcom/path_follow/assets/62756096/9742c10e-cb60-4d73-92d2-ffa9404b346a)
