/**
 * @Author: 陈昱安
 * @Date:   2018-10-22T22:01:37+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-25T08:59:44+08:00
 */

#include "main.h"

static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay.sensorsInfoObj);
    userDisplay.sensorsInfoObj = nullptr;
    lv_task_del(userDisplay.refr_task);
    userDisplay.refr_task = nullptr;
    return LV_RES_INV;
}

static void sensorsTask(void *param)
{
    (void)param; /*Unused*/
    char sensorsInfo[256];
    // sprintf(sensorsInfo, "GYRO:%.1f enc_L:%.1f enc_R:%.1f \nlimit_Shoot: enc_Shoot: \nlimit_Lift: enc_Lift: \n ",
    //         gyro.get_value(), chassis.getEncLeft(), chassis.getEncRight());
    lv_label_set_text(userDisplay.sensorsLab, sensorsInfo);
}

void UserDisplay::creartSensorsInfo(lv_obj_t *parent, int width)
{
    if (refr_task == nullptr)
    {
        refr_task = lv_task_create(sensorsTask, 100, LV_TASK_PRIO_LOW, nullptr);
        std::cout << "creart Sensors Info task" << std::endl;
    }
    if (sensorsInfoObj == nullptr)
        sensorsInfoObj = lv_obj_create(parent, nullptr);
    lv_obj_set_size(sensorsInfoObj, width, LV_VER_RES); //设置页面大小
    std::cout << "creart Sensors Info Obj" << std::endl;

    lv_obj_t *exitBtn = lv_btn_create(sensorsInfoObj, NULL);
    lv_obj_set_pos(exitBtn, width - 100, LV_VER_RES - 50);
    lv_obj_set_size(exitBtn, 75, 50);
    lv_obj_t *exitLab = lv_label_create(exitBtn, NULL);
    lv_label_set_text(exitLab, "exit");
    sensorsLab = lv_label_create(sensorsInfoObj, nullptr); //创建基于INFOObj的标签
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
    sensorsTask(nullptr); //刷新标签栏
}
