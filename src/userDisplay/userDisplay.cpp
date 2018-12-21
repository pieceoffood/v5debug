/**
 * @Author: 陈昱安
 * @Date:   2018-10-22T22:01:37+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:09:02+08:00
 */

#include "api.h"
#include "nancy.hpp"
#include "ncrapi/ncrapi.hpp"

namespace ncrapi
{
/**
 *构造函数初始化 
 */
UserDisplay::UserDisplay()
{
    //增加自定义字库
    lv_font_add(&ncrfont10, nullptr);

    /*初始化外星人主题*/
    theme = lv_theme_alien_init(100, &ncrfont10);
    /*设置Surand系统主题*/
    lv_theme_set_current(theme);
    lv_style_copy(&style, &lv_style_btn_rel); //拷贝当前按钮样式
    style.text.font = &ncrfont10;             //重新设置字体

    //释放按钮的垂直填充应用于所有按钮
    style.body.padding.ver = 5;
}
/**
 *自定义类创建 
 * @param 页面名称 
 * @param 是否重新绘制新屏幕 
 * @param 控制台字符串 
 * @param parent 父对象
 * @param labText  页面名称
 */
void UserDisplay::createUserObj(obj_flag objname, bool isSrcLoad, const char *terminalText, lv_obj_t *parent, const char *labText)
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
            displayObj[objname] = lv_obj_create(parent, nullptr);

            lv_obj_set_style(displayObj[objname], &style);
            displayObj[objname]->style_p->body.main_color = LV_COLOR_BLACK;
            displayObj[objname]->style_p->body.grad_color = LV_COLOR_BLACK;
            lv_obj_set_size(displayObj[objname], LV_HOR_RES, LV_VER_RES - 10); //设置页面大小

            //退出按钮
            createExitBtn(objname);
        }

        std::cout << "obj:" << terminalText << " create successful" << std::endl;
    }
    else
        std::cerr << "obj:" << terminalText << " already exist" << std::endl;

    if (labText != nullptr)
    {
        lv_obj_t *lab = lv_label_create(userDisplay->displayObj[objname], nullptr);
        lv_label_set_text(lab, labText);
    }
}
/**
 * 使用LVGLTASK函数创建一个线程
 * @param taskName 线程名称
 * @param task 线程函数
 * @param loopTime  循环时间
 * @param terminalText 线程名称
 */
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
/**
 * 删除所有线程 
 */
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
/**
 * 删除所有对象 
 */
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
/**
 * 用于获取系统LOOP时间的静态函数 
 * @param param 
 */
static void loopTask(void *param)
{
    (void)param;               /*Unused*/
    userDisplay->ostr.clear(); //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
    userDisplay->ostr.str(""); //2：调用str("")将缓冲区清零，清除脏数据
    userDisplay->ostr << "loop:" << userDisplay->loopTime << "max:" << userDisplay->maxLoopTime << "min:" << userDisplay->minLoopTime << std::endl;
    std::string temp = userDisplay->ostr.str();
    lv_label_set_text(userDisplay->loopLab, temp.c_str());
}
/**
 * 创建遥控模块页面 
 */
void UserDisplay::createOpObj()
{
    delTasks();
    createUserTask(TASK_LOOP, loopTask, 100, "loopLab");
    delObjs();
    createUserObj(OBJ_OPCONTROL, true, "opControl");
    if (!pros::competition::is_connected()) //没插场控
        createStartObj();

    lv_obj_t *robotInfoLab = lv_label_create(displayObj[OBJ_OPCONTROL], nullptr);
    lv_obj_set_x(robotInfoLab, LV_HOR_RES / 2 - 30);
    lv_label_set_text(robotInfoLab, robotInfo.c_str());

    loopLab = lv_label_create(displayObj[OBJ_OPCONTROL], nullptr);
    loopTask(nullptr);
}
lv_res_t UserDisplay::closeAction(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    if (userDisplay->displayObj[OBJ_BTNM_SON] != nullptr)
    {
        lv_obj_del(userDisplay->displayObj[OBJ_BTNM_SON]);
        userDisplay->displayObj[OBJ_BTNM_SON] = nullptr;
    }
    if (userDisplay->displayTask[TASK_OTHER] != nullptr)
    {
        lv_task_del(userDisplay->displayTask[TASK_OTHER]);
        userDisplay->displayTask[TASK_OTHER] = nullptr;
    }
    return LV_RES_INV;
}
lv_res_t UserDisplay::resetAction(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    for (auto &it : sysData->obj)
        it->resetAllSensors();
    return LV_RES_INV;
}
//消息框动作函数
lv_res_t UserDisplay::choseSideAction(lv_obj_t *mbox, const char *txt)
{
    printf("Mbox button: %s\n", txt);
    if (!strcmp(txt, "红方"))
    {
        sysData->autoIsMode = 0; //普通自动赛模式
        sysData->autoSide = 0;   //红方0
        userDisplay->theme->tabview.bg->body.main_color = LV_COLOR_RED;
    }
    if (!strcmp(txt, "蓝方"))
    {
        sysData->autoIsMode = 0; //普通自动赛模式
        sysData->autoSide = 360; //蓝方360
        userDisplay->theme->tabview.bg->body.main_color = LV_COLOR_BLUE;
    }
    return LV_RES_OK; /*Return OK if the message box is not deleted*/
}
void UserDisplay::createMbox(lv_obj_t *parent, const char *txt1, const char *txt2, const char *txt3, lv_btnm_action_t action) //创建一个消息框
{
    lv_obj_t *mbox = lv_mbox_create(parent, nullptr);
    lv_mbox_set_text(mbox, txt1);
    static const char *btns[] = {txt2, txt3, ""}; /*Button description. '\221' lv_btnm like control char*/
    lv_mbox_add_btns(mbox, btns, nullptr);
    lv_obj_set_width(mbox, 250);
    lv_obj_align(mbox, parent, LV_ALIGN_IN_TOP_LEFT, 10, 10); /*Align to the corner*/
    lv_mbox_set_action(mbox, action);
}

void UserDisplay::createExitBtn(obj_flag objname, const int x, const int y, const int width, const int high) //创建退出按钮
{
    lv_obj_t *exitBtn = lv_btn_create(displayObj[objname], nullptr);
    lv_obj_set_pos(exitBtn, x, y);
    lv_obj_set_size(exitBtn, width, high);
    lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
    lv_label_set_text(exitLab, "exit");
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, closeAction);
}

void UserDisplay::createResetBtn(obj_flag objname, const int x, const int y, const int width, const int high)
{
    //退出重制传感器按钮
    lv_obj_t *resetBtn = lv_btn_create(displayObj[objname], nullptr);
    lv_obj_set_pos(resetBtn, x, y);
    lv_obj_set_size(resetBtn, width, high);
    lv_obj_t *resetLab = lv_label_create(resetBtn, nullptr);
    lv_label_set_text(resetLab, "reset");
    lv_btn_set_action(resetBtn, LV_BTN_ACTION_CLICK, resetAction);
}
} // namespace ncrapi