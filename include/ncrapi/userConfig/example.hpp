/**
 * @Author: yan
 * @Date:   2018-10-14T12:18:39+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:50:52+08:00
 */
#ifndef EXAMPLE_HPP_ //这里要改
#define EXAMPLE_HPP_ //这里要改
//端口配置
//adi
const unsigned int GYRO_PORT = 1;        //陀螺仪端口号
const unsigned int SHOOT_LIMIT_PORT = 2; //射球行程开关端口号
//马达
const int LF = 1;
const int LB = 2;
const int RF = 3;
const int RB = 4;
const int SHOOT_L = 5;
const int SHOOT_R = 6;
const int INTAKE_L = 7;
const int INTAKE_R = 8;
const int VISION = 9; //视觉传感器
//底盘
const int JOY_THRESHOLD = 10; //遥控器矫正阀值
//射球系统
const int SHOOT_HOLDING = 15;
const int SHOOT_READY_VAL = 120;
const int SHOOT_SHOOT_VAL = 180;
const int SHOOT_WAITING_TIME = 500;
#endif /* end of include guard: EXAMPLE_HPP_ */
