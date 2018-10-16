/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-15T16:57:45+08:00
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
    auto chassis = ChassisControllerFactory::create(1_mtr, 3_rmtr, 4_rmtr, 2_mtr, AbstractMotor::gearset::green); //创建底盘构造函数 XDRIVE
    Controller controller;                                                                                        //创建遥控器构造函数
    chassis.forward(0.01);
    pros::delay(10000);
    chassis.stop();
    while (true)
    {
        userDisplay.loopTime(pros::millis() - lastTime);
        double ch3 = controller.getAnalog(ControllerAnalog::leftY);
        double ch1 = controller.getAnalog(ControllerAnalog::rightX);
        std::cout << "ch3:" << ch3 << " ch1:" << ch1 << std::endl;
        chassis.arcade(ch3, ch1, 0.1);
        // chassis.xArcade(controller.getAnalog(ControllerAnalog::leftX),
        //                 controller.getAnalog(ControllerAnalog::leftY),
        //                 controller.getAnalog(ControllerAnalog::rightX), 0.1);
        lastTime = pros::millis();
        pros::delay(20);
    }
}
