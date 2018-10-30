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
    lv_obj_t *exitBtn = lv_btn_create(displayObj[OBJ_VERSION], NULL);
    lv_obj_set_pos(exitBtn, LV_HOR_RES - 100, LV_VER_RES - 50);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, NULL);
    lv_label_set_text(exitLab, "exit");
    std::array<lv_obj_t *, 4> verLab; //三行版本号
    //创建LAB条
    for (auto &it : verLab)
        it = lv_label_create(displayObj[OBJ_VERSION], nullptr); //创建基于INFOObj的标签
    // const char *pros = "pros_version:" + PROS_VERSION_STRING;
    lv_label_set_text(verLab[PROS], "pros_version:PROS_VERSION_STRING");
    lv_label_set_text(verLab[OKLIB], "oklib_version:3.3.5");
    lv_label_set_text(verLab[LVGL], "lvgl_version:, LVGL_VERSION_MAJOR. LVGL_VERSION_MINOR. LVGL_VERSION_PATCH");
    lv_label_set_text(verLab[NCR], "ncr_version:NCR_VERSION_STRING");

    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
}
