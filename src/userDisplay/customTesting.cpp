#include "main.h"
/**
 *  画一个矩形 
 * @param parent 父对象
 * @param x 矩形X轴位置
 * @param y 矩形Y轴位置 
 * @param width 矩形宽
 * @param height 矩形高
 * @param color  矩形颜色
 * @return lv_obj_t* 返回OBJ 对象
 */

static lv_res_t btn_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay->displayObj[OBJ_CUSTOMTEST]);
    userDisplay->displayObj[OBJ_CUSTOMTEST] = nullptr;
    return LV_RES_INV;
}
void UserDisplay::creartCustomTest(lv_obj_t *parent)
{
    createUserObj(OBJ_CUSTOMTEST, false, "customTestPage", parent);
    // if (displayObj[OBJ_VISION] == nullptr)
    //     displayObj[OBJ_VISION] = lv_obj_create(parent, nullptr);
    lv_obj_set_size(displayObj[OBJ_CUSTOMTEST], LV_HOR_RES, LV_VER_RES); //设置页面大小

    //TODO
    //关闭按钮
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, btn_close_action);
}