#include "main.h"

static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay->displayObj[OBJ_CHECKLIST]);
    userDisplay->displayObj[OBJ_CHECKLIST] = nullptr;
    return LV_RES_INV;
}
void UserDisplay::creartCheckList(lv_obj_t *parent)
{

    createUserObj(OBJ_CHECKLIST, false, "checkListPage", parent);
    lv_obj_set_size(displayObj[OBJ_CHECKLIST], LV_HOR_RES, LV_VER_RES); //设置页面大小

    //创建LAB条

    //设置文本行内容
    //    lv_label_set_text(verLab[], pros_ver.c_str());

    //TODO:文本条位置设置

    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
}
