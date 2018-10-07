/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-24T22:52:49+08:00
 */

#include "main.h"
/**
*手动模式*/
using namespace okapi;
void opcontrol()
{
    auto chassis = ChassisControllerFactory::create(1, -2, -3, 4, AbstractMotor::gearset::green,
                                                    {4.00_in, 11.5_in}); //创建底盘构造函数 XDRIVE
    Controller controller;                                               //创建遥控器构造函数
    UserDisplay display;
    display.lv_tutorial_styles();
    while (true)
    {

        chassis.arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightX)); //普通ARCAD控制
        pros::delay(20);
    }
}
