#ifndef QUANNENGEXAMPLE_HPP_
#define QUANNENGEXAMPLE_HPP_
#define ROBOT_ALMIGHTY //全能机
#include <cstdint>
//端口配置
//adi
const uint8_t GYRO_PORT = 1;        //陀螺仪端口号
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

//场地配置
static constexpr int SITE_SIZE = 3573;         //场地边长
static constexpr int MAT_SIZE = SITE_SIZE / 6; //一个垫子的长度 = 场地长度 / 6
//底盘
const int JOY_THRESHOLD = 15; //遥控器矫正阀值
const int ROTATE_SPEED = 127; //底盘旋转速度
//射球系统
const int SHOOT_GEAR_VAL = 900;  //驱动齿轮转多少度 编码器清零
const int SHOOT_HOLDING = 15;    //悬停马达力度
const int SHOOT_READY_VAL = 360; //悬停准备值
const int SHOOT_SHOOT_VAL = 460; //发射值
// const int SHOOT_MAX_TIME = 700;  //弹射最大允许的连续驱动时间
const int SHOOT_WAITING_TIME = 500;
//升降系统
const int LIFT_UP_VAL = 1270;
//吸吐系统

//盘子夹系统
const int CAPINTAKE_UP_VAL = 261;
const int CAPINTAKE_HOLDING = 15;

#endif /* end of include guard: QUANNENGEXAMPLE_HPP_ */
