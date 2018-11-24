/**
 * @Author: 陈昱安
 * @Date:   2018-10-22T22:01:37+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T21:57:01+08:00
 */

#include "main.h"

static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay->displayObj[OBJ_SENSORSINFO]);
    userDisplay->displayObj[OBJ_SENSORSINFO] = nullptr;
    lv_task_del(userDisplay->displayTask[TASK_REFR]);
    userDisplay->displayTask[TASK_REFR] = nullptr;
    return LV_RES_INV;
}

static void sensorsTask(void *param)
{
    (void)param; /*Unused*/
    // char sensorsInfo[256];
    userDisplay->ostr.clear();                                               //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
    userDisplay->ostr.str("");                                               //2：调用str("")将缓冲区清零，清除脏数据
    userDisplay->ostr << std::fixed << std::setprecision(1) << std::setw(6); //流操纵算子

    //这里添加类的显示函数

    std::string temp = userDisplay->ostr.str();
    lv_label_set_text(userDisplay->sensorsLab, temp.c_str());
}

void UserDisplay::creartSensorsInfo(lv_obj_t *parent, int width)
{
    createUserTask(TASK_REFR, sensorsTask, 100, "sensorInfo");
    createUserObj(OBJ_SENSORSINFO, false, "sensorInfo", parent);

    lv_obj_set_size(displayObj[OBJ_SENSORSINFO], width, LV_VER_RES); //设置页面大小

    sensorsLab = lv_label_create(displayObj[OBJ_SENSORSINFO], nullptr); //创建基于INFOObj的标签
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
    sensorsTask(nullptr); //刷新标签栏
}
