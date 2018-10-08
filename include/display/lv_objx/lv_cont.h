/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T17:58:15+08:00
 */

/**
 * @file lv_cont.h
 *
 */

#ifndef LV_CONT_H
#define LV_CONT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_CONT != 0

#include "display/lv_core/lv_obj.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /*布局选项*/
    typedef enum
    {
        LV_LAYOUT_OFF = 0,
        LV_LAYOUT_CENTER,
        LV_LAYOUT_COL_L,  /*列左对齐*/
        LV_LAYOUT_COL_M,  /*列中间对齐*/
        LV_LAYOUT_COL_R,  /*列右对齐*/
        LV_LAYOUT_ROW_T,  /*行顶对齐*/
        LV_LAYOUT_ROW_M,  /*行中间对齐*/
        LV_LAYOUT_ROW_B,  /*行底对齐*/
        LV_LAYOUT_PRETTY, /*在行中放置尽可能多的对象并开始新的对象行*/
        LV_LAYOUT_GRID,   /*将相同大小的对象对齐到网格中*/
    } lv_layout_t;

    typedef struct
    {
        /*从'base_obj'继承，所以没有继承的ext。 */ /*分机 祖先*/
        /*此类型的新数据 */
        uint8_t layout : 4;  /*来自'lv_cont_layout_t'枚举的布局*/
        uint8_t hor_fit : 1; /*1：启用水平适合所有孩子*/
        uint8_t ver_fit : 1; /* 1：启用水平冷杉让所有孩子参与*/
    } lv_cont_ext_t;

    /**********************
 * 全局模型
    *********************/

    /**
    *创建容器对象
    * @param par指向一个对象的指针，它将是新容器的父级
    * @param复制指向容器对象的指针，如果不是NULL则为新对象
    *将从中复制
    * @return指向创建的容器的指针
 */
    lv_obj_t *lv_cont_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 * Setter功能
 *====================*/

    /**
    *在容器上设置布局
    * @param cont指向容器对象的指针
    * @param布局'lv_cont_layout_t'的布局
 */
    void lv_cont_set_layout(lv_obj_t *cont, lv_layout_t layout);

    /**
    *启用水平或垂直配合。
    *容器尺寸将设置为水平或儿童
    * 垂直。
    * @param cont指向容器对象的指针
    * @param hor_en true：启用水平拟合
    * @param ver_en true：启用垂直拟合
 */
    void lv_cont_set_fit(lv_obj_t *cont, bool hor_en, bool ver_en);

    /**
    *设置容器的样式
 * @param cont指向容器对象的指针
 * @param样式指向新样式
 */
    static inline void lv_cont_set_style(lv_obj_t *cont, lv_style_t *style)
    {
        lv_obj_set_style(cont, style);
    }

    /*=====================
 *吸气功能
 *====================*/

    /**
    *获取容器的布局
     * @param cont指向容器对象的指针
     * @return'lv_cont_layout_t'的布局
 */
    lv_layout_t lv_cont_get_layout(lv_obj_t *cont);

    /**
    *获取容器的水平拟合启用属性
   * @param cont指向容器对象的指针
  * @return true：启用水平拟合; false：禁用
 */
    bool lv_cont_get_hor_fit(lv_obj_t *cont);

    /**
    *获取容器的垂直适合启用属性
   * @param cont指向容器对象的指针
  * @return true：启用垂直拟合; false：禁用
 */
    bool lv_cont_get_ver_fit(lv_obj_t *cont);

    /**
    *获得容器的风格
    * @param cont指向容器对象的指针
    * @return指向容器样式的指针
 */
    static inline lv_style_t *lv_cont_get_style(lv_obj_t *cont)
    {
        return lv_obj_get_style(cont);
    }

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_CONT*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_CONT_H*/
