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
#if defined(ROBOT_ALMIGHTY) //全能机
    sprintf(sensorsInfo, "GYRO:%.1f\n \
CHS_L: enc:%.1f\tTemper:%.1f\n \
CHS_R: enc:%.1f\tTemper:%.1f\n \
Shoot: enc:%.1f\tTemper:%.1f\tLimit:%d\n \
Lift : enc:%.1f\tTemper:%.1f\n \
Cap  : enc:%.1f\tTemper:%.1f\n ",
            chassis.getGyro(), chassis.getEncLeft(), chassis.getTemperatureLeft(), chassis.getEncRight(), chassis.getTemperatureRight(),
            shoot.getEnc(), shoot.getTemperature(), shoot.getLimit(), lift.getEnc(), lift.getTemperature(), capIntake.getEnc(), capIntake.getTemperature());
#elif defined(ROBOT_CAP) //盘子机
#else                    // 矮子机
    sprintf(sensorsInfo, "GYRO:%.1f\n \
L_enc:%.1f L_Temper:%.1f\n \
R_enc:%.1f R_Temper:%.1f\n \
Shoot_enc:%.1f shoot_Temper:%.1f\n ",
            chassis.getGyro(), chassis.getEncLeft(), chassis.getTemperatureLeft(), chassis.getEncRight(), chassis.getTemperatureRight(),
            shoot.getEnc(), shoot.getTemperature());
#endif
    lv_label_set_text(userDisplay.sensorsLab, sensorsInfo);
}

void UserDisplay::creartSensorsInfo(lv_obj_t *parent, int width)
{
    createUserTask(TASK_REFR, sensorsTask, 100, "sensorInfo");
    createUserObj(OBJ_SENSORSINFO, false, "sensorInfo", parent);

    lv_obj_set_size(displayObj[OBJ_SENSORSINFO], width, LV_VER_RES); //设置页面大小
    lv_obj_t *exitBtn = lv_btn_create(displayObj[OBJ_SENSORSINFO], nullptr);
    lv_obj_set_pos(exitBtn, width - 75, LV_VER_RES - 75);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
    lv_label_set_text(exitLab, "exit");
    sensorsLab = lv_label_create(displayObj[OBJ_SENSORSINFO], nullptr); //创建基于INFOObj的标签
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
    sensorsTask(nullptr); //刷新标签栏
}
