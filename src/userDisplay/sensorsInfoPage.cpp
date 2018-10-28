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
    lv_obj_del(userDisplay.displayObj[OBJ_SENSORSINFO]);
    userDisplay.displayObj[OBJ_SENSORSINFO] = nullptr;
    lv_task_del(userDisplay.displayTask[TASK_REFR]);
    userDisplay.displayTask[TASK_REFR] = nullptr;
    return LV_RES_INV;
}

static void sensorsTask(void *param)
{
    (void)param; /*Unused*/
    char sensorsInfo[256];
    sprintf(sensorsInfo, "GYRO:%.1f enc_L:%.1f enc_R:%.1f \nlimit_Shoot:%u enc_Shoot:%.1f \nlimit_Lift: enc_Lift: \n ",
            chassis.getGyro(), chassis.getEncLeft(), chassis.getEncRight(),
            shoot.getLimit(), shoot.getEnc());
    lv_label_set_text(userDisplay.sensorsLab, sensorsInfo);
}

void UserDisplay::creartSensorsInfo(lv_obj_t *parent, int width)
{
    if (displayTask[TASK_REFR] == nullptr)
    {
        displayTask[TASK_REFR] = lv_task_create(sensorsTask, 100, LV_TASK_PRIO_LOW, nullptr);
        std::cout << "creart Sensors Info task" << std::endl;
    }
    if (displayObj[OBJ_SENSORSINFO] == nullptr)
        displayObj[OBJ_SENSORSINFO] = lv_obj_create(parent, nullptr);
    lv_obj_set_size(displayObj[OBJ_SENSORSINFO], width, LV_VER_RES); //设置页面大小
    std::cout << "creart Sensors Info Obj" << std::endl;

    lv_obj_t *exitBtn = lv_btn_create(displayObj[OBJ_SENSORSINFO], NULL);
    lv_obj_set_pos(exitBtn, width - 100, LV_VER_RES - 50);
    lv_obj_set_size(exitBtn, 75, 50);
    lv_obj_t *exitLab = lv_label_create(exitBtn, NULL);
    lv_label_set_text(exitLab, "exit");
    sensorsLab = lv_label_create(displayObj[OBJ_SENSORSINFO], nullptr); //创建基于INFOObj的标签
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
    sensorsTask(nullptr); //刷新标签栏
}
