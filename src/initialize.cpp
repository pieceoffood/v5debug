/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:49:50+08:00
 */

#include "main.hpp"
//全局变量和类
ncrapi::SystemData *sysData;      //系统数据类
ncrapi::UserDisplay *userDisplay; //图像数据类

//全局初始化构造函数
//部件类初始化
//demo for nancy
pros::Controller *joy1; // master Controller 主遥控器
pros::Controller *joy2; //partner Controller 副遥控器

ncrapi::Chassis<4> *chassis; //底盘
ncrapi::Generic<2> *lift;    //lift arm 升降臂
ncrapi::Generic<1> *flipper; //旋转器

//demo for nancy

/**
 * 初始化函数
 */

void initialize()
{ //系统初始化
    sysData = new ncrapi::SystemData();
    //显示初始化
    userDisplay = new ncrapi::UserDisplay;
    userDisplay->createMbox(OBJ_BTNM_SON, "select red/blue (default red)", "red", "blue", ncrapi::UserDisplay::choseSideAction);
    lv_obj_t *lab1 = lv_label_create(userDisplay->displayObj[OBJ_BTNM_SON], nullptr);
    //遥控器初始化
    lv_label_set_text(lab1, "Controller initialize ...");
    joy1 = new pros::Controller(CONTROLLER_MASTER);  //主遥控器
    joy2 = new pros::Controller(CONTROLLER_PARTNER); //副遥控器
    //显示用户信息
    lv_obj_t *lab2 = lv_label_create(userDisplay->displayObj[OBJ_BTNM_SON], nullptr);
    lv_obj_set_y(lab2, 30);
    std::string temp = robotInfo;
    temp += " version:";
    temp += NCR_VERSION_STRING;
    lv_label_set_text(lab2, temp.c_str());

    //demo for nancy
    lv_label_set_text(lab1, "chassis initialize ...");
    chassis = new ncrapi::Chassis<4>({pros::Motor(LF, pros::E_MOTOR_GEARSET_18, LF_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                                      pros::Motor(LB, pros::E_MOTOR_GEARSET_18, LB_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                                      pros::Motor(RF, pros::E_MOTOR_GEARSET_18, RF_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                                      pros::Motor(RB, pros::E_MOTOR_GEARSET_18, RB_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)});
    pros::delay(1000);
    lv_label_set_text(lab1, "lift initialize...");
    lift = new ncrapi::Generic<2>({pros::Motor(LIFT_LEFT, pros::E_MOTOR_GEARSET_18, LIFT_LEFT_REVERSE, pros::E_MOTOR_ENCODER_DEGREES),
                                   pros::Motor(LIFT_RIGHT, pros::E_MOTOR_GEARSET_18, LIFT_RIGHT_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)},
                                  "升降", 10);
    pros::delay(1000);

    lv_label_set_text(lab1, "flipper initialize ...");
    flipper = new ncrapi::Generic<1>({pros::Motor(FLIPPER, pros::E_MOTOR_GEARSET_18, FLIPPER_REVERSE, pros::E_MOTOR_ENCODER_DEGREES)}, "旋转器", 10); //旋转器
    pros::delay(1000);
    //demo for nancy
    lv_label_set_text(lab1, "robot initialize done ...");
    lv_obj_del(userDisplay->displayObj[OBJ_BTNM_SON]);
    userDisplay->displayObj[OBJ_BTNM_SON] = nullptr;
}
