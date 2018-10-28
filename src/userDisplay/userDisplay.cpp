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
void UserDisplay::createUserObj(obj_flag objname, const char *text)
{
    delObjs();
    if (displayObj[objname] == nullptr)
        displayObj[objname] = lv_obj_create(nullptr, nullptr);
    lv_scr_load(displayObj[objname]);
    if (text != nullptr)
    {
        lv_obj_t *lab = lv_label_create(userDisplay.displayObj[objname], nullptr);
        lv_label_set_text(lab, text);
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
            std::cout << "del Obj:" << taskFlag << std::endl;
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
