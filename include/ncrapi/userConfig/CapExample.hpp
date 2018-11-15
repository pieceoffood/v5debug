#ifndef CAPEXAMPLE_HPP_
#define CAPEXAMPLE_HPP_

#define ROBOT_CAP //盘子机
#include <cstdint>
//端口配置
//adi
const std::uint8_t GYRO_PORT = 1;   //陀螺仪端口号
const uint8_t SHOOT_LIMIT_PORT = 2; //射球行程开关端口号
//马达
const uint8_t LF = 1;
const uint8_t LB = 2;
const uint8_t RF = 3;
const uint8_t RB = 4;
const uint8_t SHOOT_L = 9;
const uint8_t SHOOT_R = 5;
const uint8_t LIFT = 6;
const uint8_t INTAKE_BALL = 7;
const uint8_t INTAKE_CAP = 8;
//视觉传感器
const uint8_t VISON_F = 10;
//自定义马达对应值
constexpr int userSpeed[128] = {
    0, 18, 21, 21, 22, 23, 24, 24, 24, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29,
    30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 33, 33, 40, 40, 40, 40, 40, 40, 40, 40, 42, 44, 46, 48,
    50, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127};

#endif /* end of include guard: GAOZIEXAMPLE_HPP_ */
