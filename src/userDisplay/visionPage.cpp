#include "main.h"

static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay->displayObj[OBJ_VISION]);
    userDisplay->displayObj[OBJ_VISION] = nullptr;
    lv_task_del(userDisplay->displayTask[TASK_VISON]);
    userDisplay->displayTask[TASK_VISON] = nullptr;
    return LV_RES_INV;
}

static void visionTask(void *param)
{
    (void)param; /*Unused*/
                 // userDisplay->ostr.clear(); //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
                 // userDisplay->ostr.str(""); //2：调用str("")将缓冲区清零，清除脏数据
    std::string str;

    uint16_t temp = lv_tabview_get_tab_act(userDisplay->displayObj[OBJ_VISION]);

    if (temp == 0)
        ;
    else if (temp == 1)
        ;
    else if (temp == 2)
        ;
    else if (temp == 3)
        ;
    else if (temp == 4)
        ;
    lv_label_set_text(userDisplay->visionLab, str.c_str());
}

void UserDisplay::creartVision(lv_obj_t *parent)
{
    createUserTask(TASK_VISON, visionTask, 100, "vision");
    //createUserObj(OBJ_VISION, false, "vision", parent);
    if (displayObj[OBJ_VISION] == nullptr)
        displayObj[OBJ_VISION] = lv_tabview_create(parent, nullptr);
    lv_obj_t *builtInSigTab = lv_tabview_add_tab(displayObj[OBJ_VISION], "内置签名");

    lv_obj_t *getSigTab = lv_tabview_add_tab(displayObj[OBJ_VISION], "按签名");
    lv_obj_t *getSizeTab = lv_tabview_add_tab(displayObj[OBJ_VISION], "按尺寸");
    lv_obj_t *getCodeTab = lv_tabview_add_tab(displayObj[OBJ_VISION], "按代码");
    lv_obj_t *drawTab = lv_tabview_add_tab(displayObj[OBJ_VISION], "图像显示");

    visionLab = lv_label_create(displayObj[OBJ_VISION], nullptr); //创建基于INFOObj的标签
    lv_obj_set_y(visionLab, 60);

    //退出按钮
    exitBtn = lv_btn_create(displayObj[OBJ_VISION], nullptr);
    lv_obj_set_pos(exitBtn, LV_HOR_RES - 80, LV_VER_RES - 50);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
    lv_label_set_text(exitLab, "exit");
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
    visionTask(nullptr); //刷新标签栏
}
