/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:49:50+08:00
 */

#include "main.h"
//全局变量和类
systemData sysData;      //系统数据类
UserDisplay userDisplay; //图像数据类

//全局初始化构造函数
Config config("/usd/configUTF8.txt");
//视觉参数配置
//视觉定义 这里有问题 官方说下个版本修复
// pros::vision_signature_s_t BALL = {1, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t RED_CAP = {2, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t BLUE_CAP = {3, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t RED_FALG = {4, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t BLUE_FALG = {5, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t RED_PLAT = {6, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t BLUE_PLAT = {7, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t CENTRAL_PLAT = {8, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t HIGH_COLUMN = {9, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
// pros::vision_signature_s_t LOW_COLUMN = {10, {255, 255, 255}, 8755, 9319, 9036, 1269, 1943, 1606, 3, 0};
//部件类初始化
pros::Controller joy1(CONTROLLER_MASTER); //主遥控器
pros::Controller joy2(CONTROLLER_MASTER); //副遥控器
pros::Vision visionF(VISON_F,pros::E_VISION_ZERO_CENTER); //前部视觉传感器,中心点坐标
#if defined(ROBOT_ALMIGHTY)
Chassis chassis({pros::Motor(LF, pros::E_MOTOR_GEARSET_18, LF_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                 pros::Motor(LB, pros::E_MOTOR_GEARSET_18, LB_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                 pros::Motor(RF, pros::E_MOTOR_GEARSET_18, RF_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                 pros::Motor(RB, pros::E_MOTOR_GEARSET_18, RB_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)},
                pros::ADIGyro(GYRO_PORT)); //底盘累初始化;
Shoot<1> shoot({pros::Motor(SHOOT, pros::E_MOTOR_GEARSET_36, SHOOT_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)},
               pros::ADIDigitalIn(SHOOT_LIMIT_PORT), SHOOT_READY_VAL, SHOOT_SHOOT_VAL, SHOOT_WAITING_TIME, SHOOT_GEAR_VAL, SHOOT_HOLDING);          //发射器类初始化                                                                           //发射器类初始化
Lift<1> lift({pros::Motor(LIFT, pros::E_MOTOR_GEARSET_18, LIFT_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)}, LIFT_UP_VAL);                                         //升降
Generic<1> intake({pros::Motor(INTAKE, pros::E_MOTOR_GEARSET_18, INTAKE_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)});                                          //吸吐初始化
CapIntake<1> capIntake({pros::Motor(INTAKE_CAP, pros::E_MOTOR_GEARSET_18, CAP_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)}, CAPINTAKE_UP_VAL, CAPINTAKE_HOLDING); //盘子夹
pros::Task _shootTask((pros::task_fn_t)taskShoot, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "task_shoot");
#elif defined(ROBOT_CAP)

#else

Chassis chassis({pros::Motor(LF, pros::E_MOTOR_GEARSET_18, LF_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                 pros::Motor(LB, pros::E_MOTOR_GEARSET_18, LB_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                 pros::Motor(RF, pros::E_MOTOR_GEARSET_18, RF_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                 pros::Motor(RB, pros::E_MOTOR_GEARSET_18, RB_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)},
                pros::ADIGyro(GYRO_PORT)); //底盘累初始化;
Shoot<2> shoot({pros::Motor(SHOOT_L, pros::E_MOTOR_GEARSET_18, SHOOT_L_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                pros::Motor(SHOOT_R, pros::E_MOTOR_GEARSET_18, SHOOT_R_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)},
               pros::ADIDigitalIn(SHOOT_LIMIT_PORT), SHOOT_READY_VAL, SHOOT_SHOOT_VAL, SHOOT_WAITING_TIME, SHOOT_GEAR_VAL, SHOOT_HOLDING); //发射器类初始化
Generic<1> intake({pros::Motor(INTAKE, pros::E_MOTOR_GEARSET_18, INTAKE_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)}); //吸吐类初始化
Head<1> head({pros::Motor(HEAD, pros::E_MOTOR_GEARSET_36, HEAD_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)}); //云台类
pros::Task _shootTask((pros::task_fn_t)taskShoot, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "task_shoot");
#endif

template <size_t nums>
void initGeneric(Generic<nums> *generic, lv_obj_t *lab, const char *str, const int isReverse = 1)
{
    lv_label_set_text(lab, str);
    generic->set(15 * isReverse);
    pros::delay(500);
    while (generic->getSpeed() != 0)
        pros::delay(20);
    generic->set(0);
    generic->resetEnc();
}
/**
 * 初始化函数
 */



void initialize()
{
    _shootTask.suspend();

    lv_obj_t *initObj = lv_obj_create(nullptr, nullptr);
    lv_scr_load(initObj);
    lv_obj_t *lab1 = lv_label_create(initObj, nullptr);
    lv_obj_t *lab2 = lv_label_create(initObj, nullptr);
    lv_obj_set_y(lab2, 20);
    lv_label_set_text(lab1, "机器人初始化中...");
    //底盘初始化
    lv_label_set_text(lab2, "底盘校准中...");
    chassis.resetEnc();
    chassis.resetGyro();
    //弹射初始化
    initGeneric(&shoot, lab2, "弹射校准中...");
#if defined(ROBOT_ALMIGHTY)
    //升降初始化
    initGeneric(&lift, lab2, "升降校准中...",-1);
    //盘子夹初始化
    initGeneric(&capIntake, lab2, "夹子校准中...",-1);
#endif
    lv_label_set_text(lab1, "机器人初始化完毕...");
    lv_obj_del(initObj);
}
