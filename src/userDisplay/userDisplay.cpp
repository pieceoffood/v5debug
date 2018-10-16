/**
 * @Author: yan
 * @Date:   2018-10-16T10:25:11+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T12:56:28+08:00
 */
#include "main.h"

UserDisplay::UserDisplay()
{
    //增加自定义字库
    lv_font_add(&myfont, nullptr);
    /*初始化外星人主题*/
    theme = lv_theme_alien_init(100, &myfont);
    /*设置Surand系统主题*/
    lv_theme_set_current(theme);
}

void UserDisplay::delObjs()
{
    if (sensorsInfoObj != nullptr)
    {
        lv_obj_del(sensorsInfoObj);
        sensorsInfoObj = nullptr;
        std::cout << "del SensorsInfoWin" << std::endl;
    }
    if (refr_task != nullptr)
    {
        lv_task_del(refr_task);
        refr_task = nullptr;
        std::cout << "del SensorsInfoTask" << std::endl;
    }

    if (disabledObj != nullptr)
    {
        lv_obj_del(disabledObj);
        disabledObj = nullptr;
        std::cout << "del disabledObj" << std::endl;
    }
    if (competitionObj != nullptr)
    {
        lv_obj_del(competitionObj);
        competitionObj = nullptr;
        std::cout << "del competitionObj" << std::endl;
    }
    if (confirmObj != nullptr)
    {
        lv_obj_del(confirmObj);
        confirmObj = nullptr;
        std::cout << "del confirmObj" << std::endl;
    }
    if (opcontrolObj != nullptr)
    {
        lv_obj_del(opcontrolObj);
        opcontrolObj = nullptr;
        loopTimeLab = nullptr;
        std::cout << "del autoObj" << std::endl;
    }
    if (autonomousObj != nullptr)
    {
        lv_obj_del(autonomousObj);
        autonomousObj = nullptr;
        std::cout << "del opObj" << std::endl;
    }
}
