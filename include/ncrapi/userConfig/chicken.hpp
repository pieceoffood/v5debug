#ifndef CHICKEN
#define CHICKEN

#define ROBOT_ALMIGHTY //全能机
#include <cstdint>

//端口配置
//adi
const uint8_t GYRO_PORT = 1;        //陀螺仪端口号
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
const uint8_t SHOOT = 5;
const bool SHOOT_REVERSE = 0;
const uint8_t LIFT = 6;
const bool LIFT_REVERSE = 0;
const uint8_t INTAKE = 7;
const bool INTAKE_REVERSE = 1;
const uint8_t INTAKE_CAP = 8;
const bool CAP_REVERSE = 1;
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

const int JOY_THRESHOLD = 10; //遥控器矫正阀值
const int ROTATE_SPEED = 127; //底盘旋转速度
//射球系统
const int SHOOT_GEAR_VAL = 900;  //驱动齿轮转多少度 编码器清零
const int SHOOT_HOLDING = 15;    //悬停马达力度
const int SHOOT_READY_VAL = 390; //悬停准备值
const int SHOOT_SHOOT_VAL = 470; //发射值
const int SHOOT_WAITING_TIME = 500;
//升降系统
const int LIFT_UP_VAL = 1270;
//吸吐系统

//盘子夹系统
const int CAPINTAKE_UP_VAL = 261;
const int CAPINTAKE_HOLDING = 15;

#endif /* end of include guard: CHICKEN */
