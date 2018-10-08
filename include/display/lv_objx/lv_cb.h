/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T17:40:47+08:00
 */

/**
 * @file lv_cb.h
 *
 */

#ifndef LV_CB_H
#define LV_CB_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_CB != 0

/*依赖项测试*/
#if USE_LV_BTN == 0
#error "lv_cb: lv_btn is required. Enable it in lv_conf.h (USE_LV_BTN  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_cb: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_label.h"

    /*********************
 *      定义
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /*复选框数据*/
    typedef struct
    {
        lv_btn_ext_t bg_btn; /*Ext。祖先*/
        /*此类型的新数据 */
        lv_obj_t *bullet; /*指针按钮*/
        lv_obj_t *label;  /*标签指针*/
    } lv_cb_ext_t;

    typedef enum
    {
        LV_CB_STYLE_BG,
        LV_CB_STYLE_BOX_REL,
        LV_CB_STYLE_BOX_PR,
        LV_CB_STYLE_BOX_TGL_REL,
        LV_CB_STYLE_BOX_TGL_PR,
        LV_CB_STYLE_BOX_INA,
    } lv_cb_style_t;

    /**********************
 * 全局模型
 **********************/

    /**
    *创建一个复选框对象
    * @param par指向一个对象的指针，它将是新复选框的父级
    * @param复制指向一个复选框对象的指针，如果不是NULL则为新对象
    *将从中复制
    * @return指向创建的复选框的指针
 */
    lv_obj_t *lv_cb_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 * Setter功能
 *====================*/

    /**
    *设置复选框的文本
   * @param cb指向一个复选框的指针
   * @param txt复选框的文本
 */
    void lv_cb_set_text(lv_obj_t *cb, const char *txt);

    /**
    *设置复选框的状态
     * @param cb指向一个复选框对象的指针
    * @param选中true：选中复选框; false：取消选中
 */
    static inline void lv_cb_set_checked(lv_obj_t *cb, bool checked)
    {
        lv_btn_set_state(cb, checked ? LV_BTN_STATE_TGL_REL : LV_BTN_STATE_REL);
    }

    /**
    *使复选框处于非活动状态（禁用）
     * @param cb指向一个复选框对象的指针
 */
    static inline void lv_cb_set_inactive(lv_obj_t *cb)
    {
        lv_btn_set_state(cb, LV_BTN_STATE_INA);
    }

    /**
    *设置单击复选框时要调用的函数
   * @param cb指向一个复选框对象的指针
 */
    static inline void lv_cb_set_action(lv_obj_t *cb, lv_action_t action)
    {
        lv_btn_set_action(cb, LV_BTN_ACTION_CLICK, action);
    }

    /**
    *设置复选框的样式
    * @param cb指向复选框对象的指针
    * @param类型应该设置哪种样式
    * @param样式指针指向一个样式
 *  */
    void lv_cb_set_style(lv_obj_t *cb, lv_cb_style_t type, lv_style_t *style);

    /*=====================
 * 吸气功能
 *====================*/

    /**
    *获取复选框的文本
   * @param cb指向复选框对象的指针
   * @return指向复选框文本的指针
 */
    const char *lv_cb_get_text(lv_obj_t *cb);

    /**
    *获取复选框的当前状态
    * @param cb指向一个复选框对象的指针
   * @return true：已检查; false：未选中
 */
    static inline bool lv_cb_is_checked(lv_obj_t *cb)
    {
        return lv_btn_get_state(cb) == LV_BTN_STATE_REL ? false : true;
    }

    /**
    *获取复选框的操作
    * @param cb指向按钮对象的指针
    * @return指向动作功能的指针
 */
    static inline lv_action_t lv_cb_get_action(lv_obj_t *cb)
    {
        return lv_btn_get_action(cb, LV_BTN_ACTION_CLICK);
    }

    /**
    *获得一个按钮的样式
    * @param cb指向复选框对象的指针
    * @param类型应该获得哪种风格
    * @return样式指针的样式
 *  */
    lv_style_t *lv_cb_get_style(lv_obj_t *cb, lv_cb_style_t type);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_CB*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_CB_H*/
