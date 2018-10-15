/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-15T15:33:00+08:00
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
    auto chassis = ChassisModelFactory::create(Motor(1), Motor(2), Motor(3), Motor(4), 200.0, 12000.0); //创建底盘构造函数 XDRIVE
    Controller controller;                                                                              //创建遥控器构造函数
    while (true)
    {
        userDisplay.loopTime(pros::millis() - lastTime);
        chassis.xArcade(controller.getAnalog(ControllerAnalog::leftX),
                        controller.getAnalog(ControllerAnalog::leftY),
                        controller.getAnalog(ControllerAnalog::rightX));
        chassis.left(0);
        lastTime = pros::millis();
        pros::delay(20);
    }
}
