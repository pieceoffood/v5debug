/**
 * @Author: yan
 * @Date:   2018-10-08T10:28:31+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T16:52:53+08:00
 */
#ifndef LV_BTN_H
#define LV_BTN_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_BTN != 0

/*依赖项测试*/
#if USE_LV_CONT == 0
#error "lv_btn: lv_cont is required. Enable it in lv_conf.h (USE_LV_CONT  1) "
#endif

#include "display/lv_core/lv_indev.h"
#include "display/lv_objx/lv_cont.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /*按钮状态*/
    typedef enum
    {
        LV_BTN_STATE_REL,
        LV_BTN_STATE_PR,
        LV_BTN_STATE_TGL_REL,
        LV_BTN_STATE_TGL_PR,
        LV_BTN_STATE_INA,
        LV_BTN_STATE_NUM,
    } lv_btn_state_t;

    typedef enum
    {
        LV_BTN_ACTION_CLICK,
        LV_BTN_ACTION_PR,
        LV_BTN_ACTION_LONG_PR,
        LV_BTN_ACTION_LONG_PR_REPEAT,
        LV_BTN_ACTION_NUM,
    } lv_btn_action_t;

    /*按钮数据*/
    typedef struct
    {
        lv_cont_ext_t cont; /*Ext。祖先*/
        /*此类型的新数据 */
        lv_action_t actions[LV_BTN_ACTION_NUM];
        lv_style_t *styles[LV_BTN_STATE_NUM]; /*每个州的风格*/

        lv_btn_state_t
            state;          /*来自'lv_btn_state_t'枚举的按钮的当前状态*/
        uint8_t toggle : 1; /*1：启用切换*/
        uint8_t
            long_pr_action_executed : 1; /*1：执行长按动作（由...处理图书馆）*/
    } lv_btn_ext_t;

    /*样式*/
    typedef enum
    {
        LV_BTN_STYLE_REL,
        LV_BTN_STYLE_PR,
        LV_BTN_STYLE_TGL_REL,
        LV_BTN_STYLE_TGL_PR,
        LV_BTN_STYLE_INA,
    } lv_btn_style_t;

    /**********************
 * 全局变量
 **********************/

    /**
    *创建一个按钮对象
     * @param par指向一个对象的指针，它将是新按钮的父指针
     * @param复制指向按钮对象的指针，如果不是NULL，则新对象将
     *从中复制
     * @return指向创建按钮的指针
 */
    lv_obj_t *lv_btn_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 * Setter功能
 *====================*/

    /**
    *启用切换状态。在释放时，按钮将从/更改为切换
     *国家。
     * @param btn指向按钮对象的指针
     * @param tgl true：启用切换状态，false：禁用
 */
    void lv_btn_set_toggle(lv_obj_t *btn, bool tgl);

    /**
    *设置按钮的状态
   * @param btn指向按钮对象的指针
   * @param说明按钮的新状态（来自lv_btn_state_t枚举）
 */
    void lv_btn_set_state(lv_obj_t *btn, lv_btn_state_t state);

    /**
    *切换按钮的状态（ON-> OFF，OFF-> ON）
    * @param btn指向按钮对象的指针
 */
    void lv_btn_toggle(lv_obj_t *btn);

    /**
    *设置按钮事件发生时调用的函数
    * @param btn指向按钮对象的指针
    * @param动作类型的事件形式'lv_action_t'（按，发布，长按,长按重复）
 */
    void lv_btn_set_action(lv_obj_t *btn, lv_btn_action_t type, lv_action_t action);

    /**
    *在按钮上设置布局
    * @param btn指向按钮对象的指针
    * @param布局'lv_cont_layout_t'的布局
 */
    static inline void lv_btn_set_layout(lv_obj_t *btn, lv_layout_t layout)
    {
        lv_cont_set_layout(btn, layout);
    }

    /**
    *启用水平或垂直配合。
     *按钮大小将设置为水平或儿童
     * 垂直。
     * @param btn指向按钮对象的指针
     * @param hor_en true：启用水平拟合
     * @param ver_en true：启用垂直拟合
 */
    static inline void lv_btn_set_fit(lv_obj_t *btn, bool hor_en, bool ver_en)
    {
        lv_cont_set_fit(btn, hor_en, ver_en);
    }

    /**
    *设置按钮的样式。
   * @param btn指向按钮对象的指针
   * @param类型应该设置哪种样式
   * @param样式指针指向一个样式
 *  */
    void lv_btn_set_style(lv_obj_t *btn, lv_btn_style_t type, lv_style_t *style);

    /*=====================
 *吸气功能
 *====================*/

    /**
    *获取按钮的当前状态
    * @param btn指向按钮对象的指针
    * @return按钮的状态（来自lv_btn_state_t枚举）
 */
    lv_btn_state_t lv_btn_get_state(lv_obj_t *btn);

    /**
    *获取按钮的切换启用属性
     * @param btn指向按钮对象的指针
     * @return ture：启用切换，false：禁用
 */
    bool lv_btn_get_toggle(lv_obj_t *btn);

    /**
    *获取按钮的释放动作
    * @param btn指向按钮对象的指针
    * @return指向释放动作功能的指针
 */
    lv_action_t lv_btn_get_action(lv_obj_t *btn, lv_btn_action_t type);

    /**
    *获取按钮的布局
    * @param btn指向按钮对象的指针
    * @return'lv_cont_layout_t'的布局
 */
    static inline lv_layout_t lv_btn_get_layout(lv_obj_t *btn)
    {
        return lv_cont_get_layout(btn);
    }

    /**
    *获取按钮的水平拟合启用属性
   * @param btn指向按钮对象的指针
  * @return true：启用水平拟合; false：禁用
 */
    static inline bool lv_btn_get_hor_fit(lv_obj_t *btn)
    {
        return lv_cont_get_hor_fit(btn);
    }

    /**
    *获取容器的垂直适合启用属性
   * @param btn指向按钮对象的指针
  * @return true：启用垂直拟合; false：禁用
 */
    static inline bool lv_btn_get_ver_fit(lv_obj_t *btn)
    {
        return lv_cont_get_ver_fit(btn);
    }

    /**
    *获得按钮的风格。
    * @param btn指向按钮对象的指针
    * @param类型应该获得哪种风格
    * @return样式指针的样式
 *  */
    lv_style_t *lv_btn_get_style(lv_obj_t *btn, lv_btn_style_t type);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_BUTTON*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_BTN_H*/
