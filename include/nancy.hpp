#pragma once
#include "ncrapi/ncrapi.hpp"
#include <cstdint>
#include <string>
#include <valarray>

//DEMO FOR NANCY
//用户设置
const std::string robotInfo = "flipper 35216B";
//端口配置
//马达
const uint8_t LF = 1;
const bool LF_REVERSE = 0;
const uint8_t LB = 2;
const bool LB_REVERSE = 1;
const uint8_t RF = 3;
const bool RF_REVERSE = 1;
const uint8_t RB = 4;
const bool RB_REVERSE = 0;

const uint8_t LIFT_LEFT = 11;
const bool LIFT_LEFT_REVERSE = 1;
const uint8_t LIFT_RIGHT = 12;
const bool LIFT_RIGHT_REVERSE = 0;
const uint8_t FLIPPER = 8;
const bool FLIPPER_REVERSE = 0;

const int JOY_THRESHOLD = 10; //deadzone for Controller 遥控器矫正阀值
const int ROTATE_SPEED = 127; //maxium speed 底盘最大旋转速度

extern pros::Controller *joy1;
extern pros::Controller *joy2;
<<<<<<< HEAD
extern ncrapi::Chassis<4> *chassis;
extern ncrapi::Generic<2> *lift;
extern ncrapi::Generic<1> *flipper;
//demo for nancy
=======
extern ncrapi::Chassis *chassis;
extern ncrapi::Generic *lift;
extern ncrapi::Generic *flipper;
//demo for nancy
>>>>>>> upstream/master
