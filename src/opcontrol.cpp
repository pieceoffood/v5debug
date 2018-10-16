/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T12:51:50+08:00
 */

#include "main.h"
/**
*手动模式*/
using namespace okapi;
void opcontrol()
{
    userDisplay.createOpObj();
    unsigned long lastTime = pros::millis();
    auto chassis = ChassisControllerFactory::create(1_mtr, 3_rmtr, 4_rmtr, 2_mtr, AbstractMotor::gearset::green); //创建底盘构造函数 XDRIVE
    Controller controller;                                                                                        //创建遥控器构造函数
    while (true)
    {
        userDisplay.loopTime(pros::millis() - lastTime);
        double ch3 = controller.getAnalog(ControllerAnalog::leftY);
        double ch1 = controller.getAnalog(ControllerAnalog::rightX);
        // std::cout << "ch3:" << ch3 << " ch1:" << ch1 << std::endl;
        chassis.arcade(ch3, ch1, 0.1);
        // chassis.xArcade(controller.getAnalog(ControllerAnalog::leftX),
        //                 controller.getAnalog(ControllerAnalog::leftY),
        //                 controller.getAnalog(ControllerAnalog::rightX), 0.1);
        lastTime = pros::millis();
        pros::delay(20);
    }
}
void UserDisplay::loopTime(const int loopTime)
{
    if (loopTime > _maxLoopTime)
        _maxLoopTime = loopTime;
    if (loopTime < _minLoopTime)
        _minLoopTime = loopTime;
    sprintf(_buf_long, "loop:%d max:%d min:%d\n", loopTime, _maxLoopTime, _minLoopTime);
    lv_label_set_text(loopTimeLab, _buf_long);
}
void UserDisplay::createOpObj()
{
    delObjs();
    if (opcontrolObj == nullptr)
    {
        opcontrolObj = lv_obj_create(nullptr, nullptr);
        loopTimeLab = lv_label_create(opcontrolObj, nullptr);
    }
    lv_scr_load(opcontrolObj);
    std::cout << "create opObj" << std::endl;
    if (!pros::competition::is_connected()) //没插场控
        createStartObj();
    else
    {
        if (startBTNM != nullptr)
        {
            lv_obj_del(startBTNM);
            startBTNM = nullptr;
            std::cout << "del startBTNM" << std::endl;
        }
    }
}
