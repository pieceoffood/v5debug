#ifndef XUANXUAN_HPP_
#define XUANXUAN_HPP_

#define ROBOT_DWARF //矮子机
#include <cstdint>
//端口配置
//adi
const std::uint8_t GYRO_PORT = 1;   //陀螺仪端口号
const uint8_t SHOOT_LIMIT_PORT = 2; //射球行程开关端口号
//马达
const uint8_t LF = 1;
const bool LF_REVERSE = 0;
const uint8_t LB = 2;
const bool LB_REVERSE = 1;
const uint8_t RF = 3;
const bool RF_REVERSE = 1;
const uint8_t RB = 4;
const bool RB_REVERSE = 0;
const uint8_t SHOOT_L = 5;
const bool SHOOT_L_REVERSE = 1;
const uint8_t SHOOT_R = 6;
const bool SHOOT_R_REVERSE = 0;
const uint8_t INTAKE = 7;
const bool INTAKE_REVERSE = 0;
const uint8_t HEAD = 8; //云台
const bool HEAD_REVERSE = 1;
//视觉传感器
const uint8_t VISON_F = 10;
//场地配置
static constexpr int SITE_SIZE = 3573;         //场地边长
static constexpr int MAT_SIZE = SITE_SIZE / 6; //一个垫子的长度 = 场地长度 / 6
//底盘
//自定义马达对应值
constexpr int userSpeed[128] = {
    0, 18, 21, 21, 22, 23, 24, 24, 24, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29,
    30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 33, 33, 40, 40, 40, 40, 40, 40, 40, 40, 42, 44, 46, 48,
    50, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127};
const int JOY_THRESHOLD = 10;   //遥控器矫正阀值
const int ROTATE_SPEED = 90;    //底盘旋转速度
                                //射球系统
const int SHOOT_GEAR_VAL = 360; //驱动齿轮转多少度 编码器清零
const int SHOOT_HOLDING = 15;
const int SHOOT_READY_VAL = 120;
const int SHOOT_SHOOT_VAL = 210;
const int SHOOT_MAX_TIME = 500; //弹射最大允许的连续驱动时间
const int SHOOT_WAITING_TIME = 500;

#endif /* end of include guard: XUANXUAN_HPP_ */
