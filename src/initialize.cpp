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
pros::Task _shootTask((pros::task_fn_t)taskLinearShoot, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "task_shoot");
//部件类初始化
pros::Controller joy1(CONTROLLER_MASTER); //主遥控器
pros::Controller joy2(CONTROLLER_MASTER); //副遥控器
//1反转,0正转
Chassis chassis({pros::Motor(LF, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_COUNTS),
                 pros::Motor(LB, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_COUNTS),
                 pros::Motor(RF, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_COUNTS),
                 pros::Motor(RB, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_COUNTS)},
                pros::ADIGyro(GYRO_PORT)); //底盘累初始化
LinearShoot<2> shoot({pros::Motor(SHOOT_L, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_COUNTS),
                      pros::Motor(SHOOT_R, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_COUNTS)},
                     pros::ADIDigitalIn(SHOOT_LIMIT_PORT),
                     SHOOT_READY_VAL, SHOOT_SHOOT_VAL, SHOOT_WAITING_TIME, SHOOT_HOLDING); //发射器类初始化
Generic<2> intake({pros::Motor(INTAKE_L, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_COUNTS),
                   pros::Motor(INTAKE_R, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_COUNTS)}); //吸吐类初始化

/**
 * 初始化函数
 */
void initialize()
{
    lv_obj_t *initObj = lv_obj_create(nullptr, nullptr);
    lv_scr_load(initObj);
    lv_obj_t *lab1 = lv_label_create(initObj, nullptr);
    lv_obj_t *lab2 = lv_label_create(initObj, nullptr);
    lv_obj_set_y(lab2, 20);
    lv_label_set_text(lab1, "机器人初始化中...");
    //底盘初始化
    chassis.resetEnc();
    chassis.resetGyro();
    //弹射初始化
    // shoot.resetEnc();
    lv_label_set_text(lab1, "机器人初始化完毕...");
    lv_obj_del(initObj);
    initObj = nullptr;
}
