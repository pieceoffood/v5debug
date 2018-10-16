/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T16:40:52+08:00
 */

#include "main.h"
/**
*手动模式*/
void opcontrol()
{
    userDisplay.createOpObj();
    unsigned long lastTime = pros::millis();
    // auto chassis = ChassisControllerFactory::create(1_mtr, 3_rmtr, 4_rmtr, 2_mtr, AbstractMotor::gearset::green); //创建底盘构造函数 XDRIVE
    // Controller controller;
    pros::Motor motor(1);
    // pros::Controller joy(CONTROLLER_MASTER);
    Chassis chassis({pros::Motor(1), pros::Motor(2), pros::Motor(3), pros::Motor(4)});
    while (true)
    {
        userDisplay.loopTime = pros::millis() - lastTime;
        if (userDisplay.loopTime > userDisplay.maxLoopTime)
            userDisplay.maxLoopTime = userDisplay.loopTime;
        if (userDisplay.loopTime < userDisplay.minLoopTime)
            userDisplay.minLoopTime = userDisplay.loopTime;
        chassis.forward(127);
        // double ch3 = controller.getAnalog(ControllerAnalog::leftY);
        // double ch1 = controller.getAnalog(ControllerAnalog::rightX);
        //std::cout << "ch3:" << joy.get_analog(ANALOG_LEFT_X) << " ch1:" << joy.get_analog(ANALOG_RIGHT_Y) << std::endl;
        //    motor.move(joy.get_analog(ANALOG_LEFT_X));
        // chassis.arcade(ch3, ch1, 0.1);
        // chassis.xArcade(controller.getAnalog(ControllerAnalog::leftX),
        //                 controller.getAnalog(ControllerAnalog::leftY),
        //                 controller.getAnalog(ControllerAnalog::rightX), 0.1);
        lastTime = pros::millis();
        pros::delay(20);
    }
}
static void loopTask(void *param)
{
    (void)param; /*Unused*/
    char loopInfo[256];
    sprintf(loopInfo, "loop:%ld max:%d min:%d\n", userDisplay.loopTime, userDisplay.maxLoopTime, userDisplay.minLoopTime);
    lv_label_set_text(userDisplay.loopLab, loopInfo);
}

void UserDisplay::createOpObj()
{
    delObjs();
    if (loop_task == nullptr)
    {
        loop_task = lv_task_create(loopTask, 100, LV_TASK_PRIO_LOW, nullptr);
        std::cout << "creart loop task" << std::endl;
    }
    if (opcontrolObj == nullptr)
        opcontrolObj = lv_obj_create(nullptr, nullptr);
    lv_scr_load(opcontrolObj);
    std::cout << "create opObj" << std::endl;
    if (!pros::competition::is_connected()) //没插场控
        createStartObj();
    loopLab = lv_label_create(opcontrolObj, nullptr);
    loopTask(nullptr);
}
