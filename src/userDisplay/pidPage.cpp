#include "ncrapi/system/systemData.hpp"
#include "ncrapi/userDisplay/userDisplay.hpp"
/**
 * 标签栏按下后的动作
 * @param tab 标签
 * @param x   几号标签
 */
static void tabChose(lv_obj_t *tab, uint16_t x)
{
}
namespace ncrapi
{
void UserDisplay::creartPid(lv_obj_t *parent)
{
    if (displayObj[OBJ_BTNM_SON] == nullptr)
        displayObj[OBJ_BTNM_SON] = lv_tabview_create(parent, nullptr);
    lv_tabview_set_style(displayObj[OBJ_BTNM_SON], LV_TABVIEW_STYLE_BTN_REL, &style); //设置样式
    lv_obj_t *frTab = lv_tabview_add_tab(displayObj[OBJ_BTNM_SON], "前后PID调试");
    lv_obj_t *rotateTab = lv_tabview_add_tab(displayObj[OBJ_BTNM_SON], "左右PID调试");
    /*当选项卡按下后进行的操作*/
    lv_tabview_set_tab_load_action(displayObj[OBJ_BTNM_SON], tabChose);
}

} // namespace ncrapi