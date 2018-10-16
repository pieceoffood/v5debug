/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:30:30+08:00
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
void UserDisplay::createOpPage()
{
    delOpPages();
    if (opcontrolPage == nullptr)
    {
        opcontrolPage = lv_obj_create(nullptr, nullptr);
        loopTimeLab = lv_label_create(opcontrolPage, nullptr);
        lv_obj_align(loopTimeLab, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
    }
    lv_scr_load(opcontrolPage);
    std::cout << "create opPage" << std::endl;
    if (!pros::competition::is_connected()) //没插场控
        createStartPage();
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
