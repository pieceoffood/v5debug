/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:54:23+08:00
 */

#include "main.hpp"

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
    (void)param;               /*Unused*/
    userDisplay->ostr.clear(); //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
    userDisplay->ostr.str(""); //2：调用str("")将缓冲区清零，清除脏数据
    userDisplay->ostr << "loop:" << userDisplay->loopTime << "max:" << userDisplay->maxLoopTime << "min:" << userDisplay->minLoopTime << std::endl;
    std::string temp = userDisplay->ostr.str();
    lv_label_set_text(userDisplay->loopLab, temp.c_str());
}
