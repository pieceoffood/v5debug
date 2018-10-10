/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-10T13:22:52+08:00
 */

/**
 * @file lv_sw.h
 *
 */

#ifndef LV_SW_H
#define LV_SW_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_SW != 0

/*Testing of dependencies*/
#if USE_LV_SLIDER == 0
#error "lv_sw: lv_slider is required. Enable it in lv_conf.h (USE_LV_SLIDER  1)"
#endif

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_slider.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/
    /*开关数据*/
    typedef struct
    {
        lv_slider_ext_t slider; /*Ext. of ancestor*/
        /*此类型的新数据 */
        lv_style_t *style_knob_off; /*开关关闭时旋钮的样式*/
        lv_style_t *style_knob_on;  /*开关打开时旋钮的样式（NULL为 使用与OFF相同*/
        uint8_t changed : 1;        /*表示拖动显式更改的开关*/
    } lv_sw_ext_t;

    typedef enum
    {
        LV_SW_STYLE_BG,
        LV_SW_STYLE_INDIC,
        LV_SW_STYLE_KNOB_OFF,
        LV_SW_STYLE_KNOB_ON,
    } lv_sw_style_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *创建一个开关对象
    * @param par指向一个对象的指针，它将是新开关的父指针
    * @param复制指向一个switch对象的指针，如果不是NULL那么新对象就会
    *从中复制
    * @return指向创建的开关的指针
 */
    lv_obj_t *lv_sw_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 * Setter functions
 *====================*/

    /**
    *打开开关
    * @param sw指向开关对象的指针
 */
    void lv_sw_on(lv_obj_t *sw);

    /**
    *关闭开关
    * @param sw指向开关对象的指针
 */
    void lv_sw_off(lv_obj_t *sw);

    /**
    *设置一个功能，当用户切换开关时将调用该功能
    * @param sw指向切换对象的指针
    * @param动作一个回调函数
 */
    static inline void lv_sw_set_action(lv_obj_t *sw, lv_action_t action)
    {
        lv_slider_set_action(sw, action);
    }

    /**
    *设置开关的样式
    * @param sw指向开关对象的指针
    * @param类型应该设置哪种样式
    * @param样式指针指向一个样式
 */
    void lv_sw_set_style(lv_obj_t *sw, lv_sw_style_t type, lv_style_t *style);

    /*=====================
 * Getter functions
 *====================*/

    /**
    *获取开关的状态
    * @param sw指向开关对象的指针
   * @return false：OFF; 是的：开
 */
    static inline bool lv_sw_get_state(lv_obj_t *sw)
    {
        return lv_bar_get_value(sw) == 0 ? false : true;
    }

    /**
    *获取开关动作功能
    * @param指向开关对象的滑块指针
    * @return回调函数
 */
    static inline lv_action_t lv_sw_get_action(lv_obj_t *slider)
    {
        return lv_slider_get_action(slider);
    }

    /**
    *获得一种开关风格
    * @param sw指向开关对象的指针
    * @param类型应该获得哪种风格
    * @return样式指针指向一个样式
 */
    lv_style_t *lv_sw_get_style(lv_obj_t *sw, lv_sw_style_t type);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_SW*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_SW_H*/
