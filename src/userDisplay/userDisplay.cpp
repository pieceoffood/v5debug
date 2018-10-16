/**
 * @Author: yan
 * @Date:   2018-10-16T10:25:11+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T11:06:11+08:00
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

void UserDisplay::delPages()
{
    if (sensorsInfoPage != nullptr)
    {
        lv_obj_del(sensorsInfoPage);
        sensorsInfoPage = nullptr;
        std::cout << "del SensorsInfoWin" << std::endl;
    }
    if (refr_task != nullptr)
    {
        lv_task_del(refr_task);
        refr_task = nullptr;
        std::cout << "del SensorsInfoTask" << std::endl;
    }

    if (disabledPage != nullptr)
    {
        lv_obj_del(disabledPage);
        disabledPage = nullptr;
        std::cout << "del disabledPage" << std::endl;
    }
    if (competitionPage != nullptr)
    {
        lv_obj_del(competitionPage);
        competitionPage = nullptr;
        std::cout << "del competitionPage" << std::endl;
    }
    if (confirmPage != nullptr)
    {
        lv_obj_del(confirmPage);
        confirmPage = nullptr;
        std::cout << "del confirmPage" << std::endl;
    }
}
void UserDisplay::delAutoPages()
{
    delPages();
    if (opcontrolPage != nullptr)
    {
        lv_obj_del(opcontrolPage);
        opcontrolPage = nullptr;
        loopTimeLab = nullptr;
        std::cout << "del autoPage" << std::endl;
    }
}
void UserDisplay::delOpPages()
{
    delPages();
    if (autonomousPage != nullptr)
    {
        lv_obj_del(autonomousPage);
        autonomousPage = nullptr;
        std::cout << "del opPage" << std::endl;
    }
}
