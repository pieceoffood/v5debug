/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T17:26:54+08:00
 */

#ifndef LV_BAR_H
#define LV_BAR_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_BAR != 0

#include "display/lv_core/lv_obj.h"
#include "lv_btn.h"
#include "lv_cont.h"
#include "lv_label.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /*条形数据*/
    typedef struct
    {
        /*没有继承的ext */
        /* Ext。祖先*/
        /*此类型的新数据*/
        int16_t cur_value;       /*条的当前值*/
        int16_t min_value;       /*条的最小值*/
        int16_t max_value;       /*栏的最大值*/
        lv_style_t *style_indic; /*指标的样式*/
    } lv_bar_ext_t;

    typedef enum
    {
        LV_BAR_STYLE_BG,
        LV_BAR_STYLE_INDIC,
    } lv_bar_style_t;

    /**********************
 * 全局模型
 **********************/

    /**
    *创建一个条形对象
   * @param par指向一个对象的指针，它将是新条形图的父级
   * @param复制指向bar对象的指针，如果不是NULL，那么新对象将是
   *从中复制
   * @return指向创建栏的指针
 */
    lv_obj_t *lv_bar_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 *Setter功能
 *====================*/

    /**
    *在栏上设置新值
    * @param指向条形对象的指针
    * @param值新值
 */
    void lv_bar_set_value(lv_obj_t *bar, int16_t value);

    /**
    *在栏上设置动画的新值
    * @param指向条形对象的指针
    * @param值新值
    * @param anim_time动画时间，以毫秒为单位
 */
    void lv_bar_set_value_anim(lv_obj_t *bar, int16_t value, uint16_t anim_time);

    /**
    *设置条形的最小值和最大值
   * @param指向条形对象的指针
   * @param min最小值
   * @param max最大值
 */
    void lv_bar_set_range(lv_obj_t *bar, int16_t min, int16_t max);

    /**
    *设置一个酒吧的风格
     * @param指向条形对象的指针
     * @param类型应该设置哪种样式
     * @param样式指针指向一个样式
 */
    void lv_bar_set_style(lv_obj_t *bar, lv_bar_style_t type, lv_style_t *style);

    /*=====================
 * 吸气功能
 *====================*/

    /**
    *获得一个酒吧的价值
     * @param指向条形对象的指针
     * @return栏的值
 */
    int16_t lv_bar_get_value(lv_obj_t *bar);

    /**
    *获得一个酒吧的最小值
   * @param指向条形对象的指针
   * @return栏的最小值
 */
    int16_t lv_bar_get_min_value(lv_obj_t *bar);

    /**
    *获得酒吧的最大价值
   * @param指向条形对象的指针
   * @return栏的最大值
 */
    int16_t lv_bar_get_max_value(lv_obj_t *bar);

    /**
    *获得一个酒吧的风格
     * @param指向条形对象的指针
     * @param类型应该获得哪种风格
     * @return样式指针指向一个样式
 */
    lv_style_t *lv_bar_get_style(lv_obj_t *bar, lv_bar_style_t type);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_BAR*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_BAR_H*/
