/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:54:23+08:00
 */

#include "main.h"

void opcontrol()
{
    userDisplay->delTasks();
    userDisplay->delObjs();
    userDisplay->createOpObj();
    uint32_t nowTime = pros::millis();
    uint32_t lastTime = pros::millis();

    while (true)
    {
        nowTime = pros::millis();
        userDisplay->loopTime = nowTime - lastTime;
        if (userDisplay->loopTime > userDisplay->maxLoopTime)
            userDisplay->maxLoopTime = userDisplay->loopTime;
        if (userDisplay->loopTime < userDisplay->minLoopTime)
            userDisplay->minLoopTime = userDisplay->loopTime;
        //TODO
        lastTime = nowTime;
        pros::c::task_delay_until(&nowTime, 10);
    }
}
static void loopTask(void *param)
{
    (void)param; /*Unused*/
    char loopInfo[256];
    sprintf(loopInfo, "loop:%u max:%u min:%u\n",
            userDisplay->loopTime, userDisplay->maxLoopTime, userDisplay->minLoopTime);
    lv_label_set_text(userDisplay->loopLab, loopInfo);
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
