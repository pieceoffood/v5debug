/**
 * @Author: 陈昱安
 * @Date:   2018-10-22T22:01:37+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:09:02+08:00
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
void UserDisplay::createUserObj(obj_flag objname, const char *terminalText, const char *labText)
{
    delObjs();
    if (displayObj[objname] == nullptr)
    {
        displayObj[objname] = lv_obj_create(nullptr, nullptr);
        std::cout << "obj:" << terminalText << " create successful" << std::endl;
    }
    else
    {
        std::cout << "obj:" << terminalText << " already exist" << std::endl;
    }
    lv_scr_load(displayObj[objname]);
    if (labText != nullptr)
    {
        lv_obj_t *lab = lv_label_create(userDisplay.displayObj[objname], nullptr);
        lv_label_set_text(lab, labText);
    }
}
void UserDisplay::createUserTask(task_flag taskName, void (*task)(void *), uint32_t loopTime, const char *terminalText)
{
    if (displayTask[taskName] == nullptr)
    {
        displayTask[taskName] = lv_task_create(task, loopTime, LV_TASK_PRIO_LOW, nullptr);
        std::cout << "task:" << terminalText << " create successful" << std::endl;
    }
    else
    {
        std::cout << "task:" << terminalText << " already exist" << std::endl;
    }
}
void UserDisplay::delTasks()
{
    unsigned int taskFlag = 1;
    for (auto &it : userDisplay.displayTask)
    {
        if (it != nullptr)
        {
            lv_task_del(it);
            it = nullptr;
            std::cout << "del task:" << taskFlag << std::endl;
            taskFlag++;
        }
    }
}
void UserDisplay::delObjs()
{
    delTasks();
    unsigned int objFlag = 1;
    for (auto &it : userDisplay.displayObj)
    {
        if (it != nullptr)
        {
            lv_obj_del(it);
            it = nullptr;
            std::cout << "del Obj:" << objFlag << std::endl;
            objFlag++;
        }
    }
}
