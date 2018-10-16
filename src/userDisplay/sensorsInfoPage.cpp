/**
 * @Author: yan
 * @Date:   2018-10-16T10:02:14+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:32:20+08:00
 */
#include "main.h"

static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay.sensorsInfoPage);
    userDisplay.sensorsInfoPage = nullptr;
    lv_task_del(userDisplay.refr_task);
    userDisplay.refr_task = nullptr;
    return LV_RES_INV;
}

static void sensorsTask(void *param)
{
    (void)param; /*Unused*/
    char sensorsInfo[256];
    okapi::ADIGyro gyro(GYRO_PORT);
    sprintf(sensorsInfo, "GYRO:%d enc_L: enc_R: \nlimit_Shoot: enc_Shoot: \nlimit_Lift: enc_Lift: \n ",
            static_cast<int>(gyro.get()));
    lv_label_set_text(userDisplay.sensorsLab, sensorsInfo);
}

void UserDisplay::creartSensorsInfo(lv_obj_t *parent, int width)
{
    if (refr_task == nullptr)
    {
        refr_task = lv_task_create(sensorsTask, 100, LV_TASK_PRIO_LOW, nullptr);
        std::cout << "creart Sensors Info task" << std::endl;
    }
    if (sensorsInfoPage == nullptr)
    {
        sensorsInfoPage = lv_page_create(parent, nullptr);
        std::cout << "creart Sensors Info page" << std::endl;
    }
    lv_obj_set_size(sensorsInfoPage, width, LV_VER_RES); //设置页面大小
    lv_obj_t *exitBtn = lv_btn_create(sensorsInfoPage, NULL);
    lv_obj_set_x(exitBtn, lv_page_get_scrl_width(sensorsInfoPage) - 50);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, NULL);
    lv_label_set_text(exitLab, "exit");
    sensorsLab = lv_label_create(sensorsInfoPage, nullptr); //创建基于INFOPAGE的标签
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
    sensorsTask(nullptr); //刷新标签栏
}
