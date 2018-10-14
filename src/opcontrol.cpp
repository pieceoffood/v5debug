/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-14T16:17:04+08:00
 */

#include "main.h"
/**
*手动模式*/
using namespace okapi;
void opcontrol()
{
    userDisplay.createOpPage();
    unsigned long lastTime = pros::millis();
    lv_obj_t *lab = lv_label_create(userDisplay.opcontrolPage, nullptr);
    lv_label_set_text(lab, "遥控程序执行中");
    // auto chassis = ChassisControllerFactory::create(1, -2, -3, 4, AbstractMotor::gearset::green,
    //                                                 {4.00_in, 11.5_in}); //创建底盘构造函数 XDRIVE
    // Controller controller;                                               //创建遥控器构造函数
    while (true)
    {
        userDisplay.loopTime(pros::millis() - lastTime);
        // chassis.arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightX)); //普通ARCAD控制
        lastTime = pros::millis();
        pros::delay(20);
    }
}
