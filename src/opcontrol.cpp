/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:54:23+08:00
 */

#include "main.h"
//任务通知测试
// void my_task_fn(void *ign)
// {
//     while (pros::c::task_notify_take(true, TIMEOUT_MAX))
//     {
//         puts("I was unblocked!");
//     }
// }
/**
 * 手动模块
 */
void opcontrol()
{
    userDisplay.delTasks();
    userDisplay.delObjs();
    userDisplay.createOpObj();
    uint32_t nowTime = pros::millis();
    uint32_t lastTime = pros::millis();
    //任务通知测试
    //    pros::task_t my_task = pros::c::task_create(my_task_fn, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Notify me! Task");
    while (true)
    {
        nowTime = pros::millis();
        userDisplay.loopTime = nowTime - lastTime;
        if (userDisplay.loopTime > userDisplay.maxLoopTime)
            userDisplay.maxLoopTime = userDisplay.loopTime;
        if (userDisplay.loopTime < userDisplay.minLoopTime)
            userDisplay.minLoopTime = userDisplay.loopTime;
        chassis.arcade(joy1.get_analog(ANALOG_LEFT_Y), joy1.get_analog(ANALOG_RIGHT_X), JOY_THRESHOLD);
        // shoot.joyControl(joy1.get_digital(DIGITAL_L1), joy1.get_digital(DIGITAL_L2), joy1.get_digital(DIGITAL_A));
        intake.joyControl(joy1.get_digital(DIGITAL_R1), joy1.get_digital(DIGITAL_R2));
        //多线程测试
        // if (pros::c::joy1_get_digital(joy1_MASTER, DIGITAL_L1))
        // {
        //     pros::c::task_notify(my_task);
        // }
        lastTime = nowTime;
        pros::c::task_delay_until(&nowTime, 20);
    }
}
static void loopTask(void *param)
{
    (void)param; /*Unused*/
    char loopInfo[256];
    sprintf(loopInfo, "loop:%u max:%u min:%u\n", userDisplay.loopTime, userDisplay.maxLoopTime, userDisplay.minLoopTime);
    lv_label_set_text(userDisplay.loopLab, loopInfo);
}

void UserDisplay::createOpObj()
{
    delTasks();
    createUserTask(TASK_LOOP, loopTask, 100, "loopLab");
    delObjs();
    createUserObj(OBJ_OPCONTROL, true, "opControl");
    if (!pros::competition::is_connected()) //没插场控
        createStartObj();
    loopLab = lv_label_create(displayObj[OBJ_OPCONTROL], nullptr);
    loopTask(nullptr);
}
