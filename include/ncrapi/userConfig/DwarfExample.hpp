
#ifndef DWARFEXAMPLE_HPP_ //这里要改
#define DWARFEXAMPLE_HPP_ //这里要改
#define ROBOT_DWARF       //矮子机
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
//场地配置
static constexpr int SITE_SIZE = 3573;         //场地边长
static constexpr int MAT_SIZE = SITE_SIZE / 6; //一个垫子的长度 = 场地长度 / 6
//底盘
const int JOY_THRESHOLD = 10; //遥控器矫正阀值
const int ROTATE_SPEED = 90;  //底盘旋转速度
//射球系统
// const int SHOOT_GEAR_VAL = 360; //驱动齿轮转多少度 编码器清零
const int SHOOT_HOLDING = 15;
const int SHOOT_READY_VAL = 120;
const int SHOOT_SHOOT_VAL = 180;
const int SHOOT_MAX_TIME = 500; //弹射最大允许的连续驱动时间
const int SHOOT_WAITING_TIME = 500;

#endif /* end of include guard: EXAMPLE_HPP_ */
