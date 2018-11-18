#include "main.h"

static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay.displayObj[OBJ_VISION]);
    userDisplay.displayObj[OBJ_VISION] = nullptr;
    lv_task_del(userDisplay.displayTask[TASK_VISON]);
    userDisplay.displayTask[TASK_VISON] = nullptr;
    return LV_RES_INV;
}

static void visionTask(void *param)
{
    (void)param; /*Unused*/
    char visionInfo[256];

    lv_label_set_text(userDisplay.visionLab, visionInfo);
}

void UserDisplay::creartVision(lv_obj_t *parent)
{
    createUserTask(TASK_VISON, visionTask, 100, "vision");
    createUserObj(OBJ_VISION, false, "vision", parent);

    lv_obj_set_size(displayObj[OBJ_VISION], LV_HOR_RES, LV_VER_RES);    //设置页面大小
    lv_obj_t *exitBtn = lv_btn_create(displayObj[OBJ_VISION], nullptr); //创建退出按钮
    lv_obj_set_pos(exitBtn, LV_HOR_RES - 75, LV_VER_RES - 75);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
    lv_label_set_text(exitLab, "exit");
    visionLab = lv_label_create(displayObj[OBJ_VISION], nullptr); //创建基于INFOObj的标签
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
    visionTask(nullptr); //刷新标签栏
}
