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

#endif /* end of include guard: GAOZIEXAMPLE_HPP_ */
