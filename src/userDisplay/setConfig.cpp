#include "main.h"
static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay->displayObj[OBJ_CONFIG]);
    userDisplay->displayObj[OBJ_CONFIG] = nullptr;
    return LV_RES_INV;
}
void UserDisplay::creartConfig(lv_obj_t *parent)
{

    createUserObj(OBJ_CONFIG, false, "configPage", parent);
    lv_obj_set_size(displayObj[OBJ_CONFIG], LV_HOR_RES, LV_VER_RES);        //设置页面大小
    lv_obj_t *configLab = lv_label_create(displayObj[OBJ_CONFIG], nullptr); //创建LAB条

    userDisplay->ostr.clear(); //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
    userDisplay->ostr.str(""); //2：调用str("")将缓冲区清零，清除脏数据
    config->showConfig();
    std::string temp = userDisplay->ostr.str();
    lv_label_set_text(configLab, temp.c_str());
    //创建保存按钮

    //读取SD卡内容

    //设置SD卡内容 需要创建一系列按钮

    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
}
