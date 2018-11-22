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
    lv_obj_t *exitBtn = lv_btn_create(displayObj[OBJ_CHECKLIST], NULL);
    lv_obj_set_pos(exitBtn, LV_HOR_RES - 75, LV_VER_RES - 75);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, NULL);
    lv_label_set_text(exitLab, "exit");

    //创建LAB条
    std::array<lv_obj_t *, 8> checkListLab;
    for (auto &it : checkListLab)
        it = lv_label_create(displayObj[OBJ_CHECKLIST], nullptr); //创建基于INFOObj的标签
    //字符串添加版本号
    std::string pros_ver = "pros_version:";
    pros_ver.append(PROS_VERSION_STRING);

    //设置文本行内容
    //    lv_label_set_text(verLab[], pros_ver.c_str());

    //TODO:文本条位置设置

    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
}
