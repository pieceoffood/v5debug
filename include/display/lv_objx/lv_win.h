/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-15T08:49:31+08:00
 */

#ifndef LV_WIN_H
#define LV_WIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_WIN != 0

/*依赖项测试*/
#if USE_LV_BTN == 0
#error "lv_win: lv_btn is required. Enable it in lv_conf.h (USE_LV_BTN  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_win: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#if USE_LV_IMG == 0
#error "lv_win: lv_img is required. Enable it in lv_conf.h (USE_LV_IMG  1) "
#endif

#if USE_LV_PAGE == 0
#error "lv_win: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_cont.h"
#include "display/lv_objx/lv_img.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_objx/lv_page.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /*窗口数据*/
    typedef struct
    {
        /*Ext. of ancestor*/
        /*此类型的新数据 */
        lv_obj_t *page;            /*指向保存内容的页面的指针*/
        lv_obj_t *header;          /*指向窗口标题容器的指针*/
        lv_obj_t *title;           /*指向窗口标题标签的指针*/
        lv_style_t *style_header;  /*标题容器的样式r*/
        lv_style_t *style_btn_rel; /*控制按钮释放样式*/
        lv_style_t *style_btn_pr;  /*控制按钮按下样式e*/
        lv_coord_t btn_size;       /*控制按钮的大小（方形）*/
    } lv_win_ext_t;

    typedef enum
    {
        LV_WIN_STYLE_BG,
        LV_WIN_STYLE_CONTENT_BG,
        LV_WIN_STYLE_CONTENT_SCRL,
        LV_WIN_STYLE_SB,
        LV_WIN_STYLE_HEADER,
        LV_WIN_STYLE_BTN_REL,
        LV_WIN_STYLE_BTN_PR,
    } lv_win_style_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *创建一个窗口对象
    * @param par指向一个对象的指针，它将是新窗口的父级
    * @param复制指向窗口对象的指针，如果不是NULL，则新对象将从中复制
    * @return指向创建窗口的指针
 */
    lv_obj_t *lv_win_create(lv_obj_t *par, lv_obj_t *copy);

    /*======================
 * 添加/删除功能
 *=====================*/

    /**
    *将控制按钮添加到窗口的标题
    * @param win指向窗口对象的指针
    * @param img_src图像源（'lv_img_t'变量，文件路径或符号）
    * @param rel_action释放按钮时调用的函数指针
    * @return指向创建的按钮对象的指针
 */
    lv_obj_t *lv_win_add_btn(lv_obj_t *win, const void *img_src,
                             lv_action_t rel_action);

    /*=====================
 * Setter functions
 *====================*/

    /**
    *可以分配给窗口控制按钮以关闭它的释放操作
    * @param btn指向已释放按钮的指针
    * @return总是LV_ACTION_RES_INV因为按钮被删除了窗口
 */
    lv_res_t lv_win_close_action(lv_obj_t *btn);

    /**
    *设置窗口的标题
    * @param win指向窗口对象的指针
    * @param新标题的标题字符串
 */
    void lv_win_set_title(lv_obj_t *win, const char *title);

    /**
    *设置窗口的控制按钮大小
    * @param win指向窗口对象的指针
    * @return控制按钮大小
 */
    void lv_win_set_btn_size(lv_obj_t *win, lv_coord_t size);

    /**
    *设置窗口的滚动条模式
    * @param win指向窗口对象的指针
    * @param sb_mode来自'lv_sb_mode_t'的新滚动条模式
 */
    void lv_win_set_sb_mode(lv_obj_t *win, lv_sb_mode_t sb_mode);

    /**
    *设置窗口的布局
    * @param win指向窗口对象的指针
    * @param布局'lv_layout_t'的布局
 */
    void lv_win_set_layout(lv_obj_t *win, lv_layout_t layout);

    /**
    *设置窗口的样式
    * @param win指向窗口对象的指针
    * @param类型应该设置哪种样式
    * @param样式指针指向一个样式
 */
    void lv_win_set_style(lv_obj_t *win, lv_win_style_t type, lv_style_t *style);

    /*=====================
 * Getter functions
 *====================*/

    /**
    *获取窗口的标题
    * @param win指向窗口对象的指针
    * @return窗口的标题字符串
 */
    const char *lv_win_get_title(lv_obj_t *win);

    /**
    *获取窗口的控制按钮大小
    * @param win指向窗口对象的指针
    * @return控制按钮大小
 */
    lv_coord_t lv_win_get_btn_size(lv_obj_t *win);

    /**
    *获取窗口的布局
    * @param win指向窗口对象的指针
    * @return窗口的布局（来自'lv_layout_t'）
 */
    lv_layout_t lv_win_get_layout(lv_obj_t *win);

    /**
    *获取窗口的滚动条模式
    * @param win指向窗口对象的指针
    * @return窗口的滚动条模式（来自'lv_sb_mode_t'）
 */
    lv_sb_mode_t lv_win_get_sb_mode(lv_obj_t *win);

    /**
    *获取窗口的内容区域（页面可滚动）的宽度
    * @param win指向窗口对象的指针
    * @return内容区域的宽度
 */
    lv_coord_t lv_win_get_width(lv_obj_t *win);

    /**
    *从其中一个控制按钮获取寡妇的指针。在只有按钮已知的控制按钮的操作中很有用。
    * @param ctrl_btn指向窗口的控制按钮
    * @return指向'ctrl_btn'窗口的指针
 */
    lv_obj_t *lv_win_get_from_btn(lv_obj_t *ctrl_btn);

    /**
    *获得一个窗口的风格
    * @param赢得指向按钮对象的指针
    * @param类型获取哪个样式窗口
    * @return样式指针指向一个样式
 */
    lv_style_t *lv_win_get_style(lv_obj_t *win, lv_win_style_t type);

    /*=====================
 * Other functions
 *====================*/

    /**
    *专注于一个物体。它确保对象在窗口中可见。
     * @param win指向窗口对象的指针
     * @param obj指向要聚焦的对象的指针（必须在窗口中）
     * @param anim_time以毫秒为单位滚动动画时间（0：无动画）
 */
    void lv_win_focus(lv_obj_t *win, lv_obj_t *obj, uint16_t anim_time);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_WIN*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_WIN_H*/
