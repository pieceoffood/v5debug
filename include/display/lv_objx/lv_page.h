/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T16:40:52+08:00
 */

#ifndef LV_PAGE_H
#define LV_PAGE_H

#ifdef __cplusplus
extern "C"
{
#endif
/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_PAGE != 0

/*依赖项测试*/
#if USE_LV_CONT == 0
#error "lv_page: lv_cont is required. Enable it in lv_conf.h (USE_LV_CONT  1) "
#endif

#include "display/lv_core/lv_indev.h"
#include "display/lv_objx/lv_cont.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /*滚动条模式：显示滚动条何时可见*/
    typedef enum
    {
        LV_SB_MODE_OFF,  /*从不显示滚动条*/
        LV_SB_MODE_ON,   /*始终显示滚动条*/
        LV_SB_MODE_DRAG, /*在拖动页面时显示滚动条*/
        LV_SB_MODE_AUTO, /*当可滚动容器很大时显示滚动条足以滚动*/
    } lv_sb_mode_t;

    /*页面数据*/
    typedef struct
    {
        lv_cont_ext_t bg; /*Ext。祖先*/
        /*此类型的新数据*/
        lv_obj_t *scrl;         /*背景上的可滚动对象*/
        lv_action_t rel_action; /*发布页面时调用的函数*/
        lv_action_t pr_action;  /*按下页面时调用的函数*/
        struct
        {
            lv_style_t *style;    /*滚动条样式*/
            lv_area_t hor_area;   /*相对于页面的水平滚动条区域（由图书馆处理）*/
            lv_area_t ver_area;   /*相对于页面的垂直滚动条区域（已处理由图书馆）*/
            uint8_t hor_draw : 1; /*1：水平滚动条现在可见（处理方式图书馆）*/
            uint8_t ver_draw : 1; /* 1：垂直滚动条现在可见（由。处理）图书馆）*/
            uint8_t mode : 3;     /*来自'lv_page_sb_mode_t'的滚动条可见性*/
        } sb;
    } lv_page_ext_t;

    typedef enum
    {
        LV_PAGE_STYLE_BG,
        LV_PAGE_STYLE_SCRL,
        LV_PAGE_STYLE_SB,
    } lv_page_style_t;

    /**********************
 * 全球原型
 **********************/

    /**
 * 创建页面对象
 *  @param par指向一个对象的指针，它将是新页面的父指针
 * @param复制指向页面对象的指针，如果不是NULL，那么新对象将是
 * 从中复制
 * @return指向创建页面的指针
 */
    lv_obj_t *lv_page_create(lv_obj_t *par, lv_obj_t *copy);

    /**
 * 获取页面的可滚动对象
 * @param页面指向页面对象的指针
 * @return指向容器的指针，该容器是页面的可滚动部分
 */
    lv_obj_t *lv_page_get_scrl(lv_obj_t *page);

    /*=====================
 * Setter功能
 *====================*/

    /**
 * 为页面设置发布操作
 * @param页面指向页面对象的指针
 * @param rel_action一个在页面释放时调用的函数
 */
    void lv_page_set_rel_action(lv_obj_t *page, lv_action_t rel_action);

    /**
 * 为页面设置按下操作
 * @param页面指向页面对象的指针
 * @param pr_action按下页面时调用的函数
 */
    void lv_page_set_pr_action(lv_obj_t *page, lv_action_t pr_action);

    /**
 * 在页面上设置滚动条模式
 * @param页面指向页面对象的指针
 * @param sb.mode来自'lv_page_sb.mode_t'枚举的新模式
 */
    void lv_page_set_sb_mode(lv_obj_t *page, lv_sb_mode_t sb_mode);

    /**
 * 设置页面可滚动部分的fit属性。
 * 这意味着它可以自动设置其大小以让所有孩子都参与进来。
 * （可以水平和垂直分别设置）
 * @param页面指向页面对象的指针
 * @param hor_en true：启用水平拟合
 * @param ver_en true：启用垂直拟合
 */
    static inline void lv_page_set_scrl_fit(lv_obj_t *page, bool hor_en,
                                            bool ver_en)
    {
        lv_cont_set_fit(lv_page_get_scrl(page), hor_en, ver_en);
    }

    /**
 * 设置页面可滚动部分的宽度
 * @param页面指向页面对象的指针
 * @param w可滚动的新宽度（没有效果是水平适合已启用）
 */
    static inline void lv_page_set_scrl_width(lv_obj_t *page, lv_coord_t w)
    {
        lv_obj_set_width(lv_page_get_scrl(page), w);
    }

    /**
 * 设置页面可滚动部分的高度
 * @param页面指向页面对象的指针
 * @param h可滚动的新高度（它没有效果是垂直拟合是启用）
 */
    static inline void lv_page_set_scrl_height(lv_obj_t *page, lv_coord_t h)
    {
        lv_obj_set_height(lv_page_get_scrl(page), h);
    }

    /**
* 设置页面可滚动部分的布局
* @param页面指向页面对象的指针
* @param布局'lv_cont_layout_t'的布局
*/
    static inline void lv_page_set_scrl_layout(lv_obj_t *page, lv_layout_t layout)
    {
        lv_cont_set_layout(lv_page_get_scrl(page), layout);
    }

    /**
 * 设置页面样式
 * @param页面指向页面对象的指针
 * @param类型应该设置哪种样式
 * @param样式指针指向一个样式
 *  */
    void lv_page_set_style(lv_obj_t *page, lv_page_style_t type, lv_style_t *style);

    /*=====================
 * 吸气功能
 *====================*/

    /**
 * 在页面上设置滚动条模式
 * @param页面指向页面对象的指针
 * @return来自'lv_page_sb.mode_t'枚举的模式
 */
    lv_sb_mode_t lv_page_get_sb_mode(lv_obj_t *page);

    /**
    *获取页面可滚动部分的宽度
    * @param页面指向页面对象的指针
    * @return可滚动的宽度
 */
    static inline lv_coord_t lv_page_get_scrl_width(lv_obj_t *page)
    {
        return lv_obj_get_width(lv_page_get_scrl(page));
    }

    /**
    *获取页面可滚动部分的高度
    * @param页面指向页面对象的指针
    * @return可滚动的高度
 */
    static inline lv_coord_t lv_page_get_scrl_height(lv_obj_t *page)
    {
        return lv_obj_get_height(lv_page_get_scrl(page));
    }

    /**
    *获取页面可滚动部分的布局
    * @param页面指向页面对象的指针
    * @return'lv_cont_layout_t'的布局
*/
    static inline lv_layout_t lv_page_get_scrl_layout(lv_obj_t *page)
    {
        return lv_cont_get_layout(lv_page_get_scrl(page));
    }

    /**
    *获取页面可滚动部分的水平拟合属性
    * @param页面指向页面对象的指针
    * @return true：启用水平拟合; false：禁用
*/
    static inline bool lv_page_get_scrl_hor_fit(lv_obj_t *page)
    {
        return lv_cont_get_hor_fit(lv_page_get_scrl(page));
    }

    /**
    *获取页面可滚动部分的垂直拟合属性
    * @param页面指向页面对象的指针
    * @return true：启用垂直拟合; false：禁用
*/
    static inline bool lv_page_get_scrl_fit_ver(lv_obj_t *page)
    {
        return lv_cont_get_ver_fit(lv_page_get_scrl(page));
    }

    /**
    *获得一种页面风格
 * @param页面指向页面对象的指针
 * @param类型应该获得哪种风格
 * @return样式指针指向一个样式
   */
    lv_style_t *lv_page_get_style(lv_obj_t *page, lv_page_style_t type);

    /*=====================
 * 其他功能
 *====================*/

    /**
    *将对象粘贴到页面。之后，页面可以移动（拖动）
    *这个对象也是。
    * @param obj指向页面上对象的指针
    * @param glue true：启用胶水，假：禁用胶水
 */
    void lv_page_glue_obj(lv_obj_t *obj, bool glue);

    /**
    *专注于一个物体。它确保对象在页面上可见。
     * @param页面指向页面对象的指针
     * @param obj指向要聚焦的对象的指针（必须在页面上）
     * @param anim_time以毫秒为单位滚动动画时间（0：无动画）
 */
    void lv_page_focus(lv_obj_t *page, lv_obj_t *obj, uint16_t anim_time);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_PAGE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_PAGE_H*/
