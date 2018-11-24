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
void UserDisplay::createUserObj(obj_flag objname, bool isSrcLoad, const char *terminalText,
                                lv_obj_t *parent, const char *labText)
{
    if (displayObj[objname] == nullptr)
    {
        if (isSrcLoad)
        {
            displayObj[objname] = lv_obj_create(parent, nullptr);
            lv_scr_load(displayObj[objname]);
        }
        else
        {
            displayObj[objname] = lv_page_create(parent, nullptr);
            exitBtn = lv_btn_create(displayObj[objname], nullptr);
            lv_obj_set_pos(exitBtn, LV_HOR_RES - 80, LV_VER_RES - 50);
            lv_obj_set_size(exitBtn, 50, 25);
            lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
            lv_label_set_text(exitLab, "exit");
        }

        std::cout << "obj:" << terminalText << " create successful" << std::endl;
    }
    else
    {
        std::cerr << "obj:" << terminalText << " already exist" << std::endl;
    }

    if (labText != nullptr)
    {
        lv_obj_t *lab = lv_label_create(userDisplay->displayObj[objname], nullptr);
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
    unsigned int flag = 1;
    for (auto &it : userDisplay->displayTask)
    {
        if (it != nullptr)
        {
            lv_task_del(it);
            it = nullptr;
            std::cout << "del task:" << flag << std::endl;
            flag++;
        }
    }
}
void UserDisplay::delObjs()
{
    unsigned int flag = 1;
    for (auto &it : userDisplay->displayObj)
    {
        if (it != nullptr)
        {
            lv_obj_del(it);
            it = nullptr;
            std::cout << "del Obj:" << flag << std::endl;
            flag++;
        }
    }
}
