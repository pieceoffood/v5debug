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
    pros::Controller controller(CONTROLLER_MASTER);
    Chassis chassis({pros::Motor(LF), pros::Motor(LB), pros::Motor(RF, 1), pros::Motor(RB, 1)});
    Generic<2> shoot({pros::Motor(SHOOT_L), pros::Motor(SHOOT_R, 1)}, SHOOT_HOLDING);
    Generic<2> intake({pros::Motor(INTAKE_L), pros::Motor(INTAKE_R, 1)});
    while (true)
    {
        userDisplay.loopTime = pros::millis() - lastTime;
        if (userDisplay.loopTime > userDisplay.maxLoopTime)
            userDisplay.maxLoopTime = userDisplay.loopTime;
        if (userDisplay.loopTime < userDisplay.minLoopTime)
            userDisplay.minLoopTime = userDisplay.loopTime;
        chassis.arcade(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_X), JOY_THRESHOLD);
        shoot.joyControl(controller.get_digital(DIGITAL_L1), controller.get_digital(DIGITAL_L2));
        intake.joyControl(controller.get_digital(DIGITAL_R1), controller.get_digital(DIGITAL_R2));
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
