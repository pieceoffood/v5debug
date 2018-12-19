
#include "ncrapi/system/systemData.hpp"

namespace ncrapi
{
void UserDisplay::creartVision(lv_obj_t *parent)
{

    if (displayObj[OBJ_BTNM_SON] == nullptr)
        displayObj[OBJ_BTNM_SON] = lv_tabview_create(parent, nullptr);
    lv_tabview_set_style(displayObj[OBJ_BTNM_SON], LV_TABVIEW_STYLE_BTN_REL, &style); //设置样式
    lv_obj_t *builtInSigTab = lv_tabview_add_tab(displayObj[OBJ_BTNM_SON], "内置签名");

    lv_obj_t *getSigTab = lv_tabview_add_tab(displayObj[OBJ_BTNM_SON], "按数据0");
    lv_obj_t *getSizeTab = lv_tabview_add_tab(displayObj[OBJ_BTNM_SON], "按数据1");
    lv_obj_t *getCodeTab = lv_tabview_add_tab(displayObj[OBJ_BTNM_SON], "按数据2");
    /*当选项卡按下后进行的操作*/

    //退出按钮
    exitBtn = lv_btn_create(displayObj[OBJ_BTNM_SON], nullptr);
    lv_obj_set_pos(exitBtn, LV_HOR_RES - 80, LV_VER_RES - 50);
    lv_obj_set_size(exitBtn, 50, 25);
    lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
    lv_label_set_text(exitLab, "exit");
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, closeAction);
}
} // namespace ncrapi