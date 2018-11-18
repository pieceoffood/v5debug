#include "main.h"
typedef enum verlab_flag
{
    PROS,
    OKLIB,
    LVGL,
    NCR
} verlab_flag;
static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay.displayObj[OBJ_VERSION]);
    userDisplay.displayObj[OBJ_VERSION] = nullptr;
    return LV_RES_INV;
}
void UserDisplay::creartVersion(lv_obj_t *parent)
{

    createUserObj(OBJ_VERSION, false, "versionPage", parent);
    lv_obj_set_size(displayObj[OBJ_VERSION], LV_HOR_RES, LV_VER_RES); //设置页面大小
    lv_obj_t *exitBtn = lv_btn_create(displayObj[OBJ_VERSION], NULL);
    lv_obj_set_pos(exitBtn, LV_HOR_RES - 75, LV_VER_RES - 75);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, NULL);
    lv_label_set_text(exitLab, "exit");
    std::array<lv_obj_t *, 4> verLab; //三行版本号
    //创建LAB条
    for (auto &it : verLab)
        it = lv_label_create(displayObj[OBJ_VERSION], nullptr); //创建基于INFOObj的标签
    //字符串添加版本号
    std::string pros_ver = "pros_version:";
    pros_ver.append(PROS_VERSION_STRING);
    std::string oklib_ver = "oklib_version:3.3.7";
    std::string lvgl_ver = "lvgl_version:";
    lvgl_ver.append(LVGL_VERSION_INFO);
    std::string ncr_ver = "ncr_version:";
    ncr_ver.append(NCR_VERSION_STRING);
    //设置文本行内容
    lv_label_set_text(verLab[PROS], pros_ver.c_str());
    lv_label_set_text(verLab[OKLIB], oklib_ver.c_str());
    lv_label_set_text(verLab[LVGL], lvgl_ver.c_str());
    lv_label_set_text(verLab[NCR], ncr_ver.c_str());
    //TODO:文本条位置设置
    int yFlag = 20;
    for (auto &it : verLab)
    {
        lv_obj_set_y(it, yFlag);
        yFlag += 30;
    }

    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
}
