/**
 * @file lv_tabview.h
 *
 */

#ifndef LV_TABVIEW_H
#define LV_TABVIEW_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_TABVIEW != 0

/*Testing of dependencies*/
#if USE_LV_BTNM == 0
#error                                                                         \
    "lv_tabview: lv_btnm is required. Enable it in lv_conf.h (USE_LV_BTNM  1) "
#endif

#if USE_LV_PAGE == 0
#error                                                                         \
    "lv_tabview: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_page.h"
#include "display/lv_objx/lv_win.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*参数：指向tabview对象的指针，tab_id */
typedef void (*lv_tabview_action_t)(lv_obj_t *, uint16_t);

/*标签数据*/
typedef struct {
  /*Ext. of ancestor*/
  /*此类型的新数据 */
  lv_obj_t *btns;
  lv_obj_t *indic;
  lv_obj_t *content; /*显示当前标签的矩形*/
  const char **tab_name_ptr;
  lv_point_t point_last;
  uint16_t tab_cur;
  uint16_t tab_cnt;
  uint16_t anim_time;
  uint8_t slide_enable : 1; /*1: 通过触摸板启用水平滑动*/
  uint8_t draging : 1;
  uint8_t drag_hor : 1;
  lv_tabview_action_t tab_load_action;
} lv_tabview_ext_t;

typedef enum {
  LV_TABVIEW_STYLE_BG,
  LV_TABVIEW_STYLE_INDIC,
  LV_TABVIEW_STYLE_BTN_BG,
  LV_TABVIEW_STYLE_BTN_REL,
  LV_TABVIEW_STYLE_BTN_PR,
  LV_TABVIEW_STYLE_BTN_TGL_REL,
  LV_TABVIEW_STYLE_BTN_TGL_PR,
} lv_tabview_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
* @param par指向对象的指针，它将是新选项卡的父级
* @param复制指向选项卡对象的指针，如果不是NULL，那么新对象将是从中复制
* @return指向创建的选项卡的指针
 */
lv_obj_t *lv_tabview_create(lv_obj_t *par, lv_obj_t *copy);

/*======================
 * Add/remove functions
 *=====================*/

/**
*添加具有给定名称的新选项卡
* @param tabview指向Tab视图对象的位置，以指向新选项卡
* @param命名选项卡按钮上的文本
* @return指向创建的页面对象（lv_page）的指针。你可以创建你的内容在这里
 */
lv_obj_t *lv_tabview_add_tab(lv_obj_t *tabview, const char *name);

/*=====================
 * Setter functions
 *====================*/

/**
*设置新标签
* @param tabview指向Tab视图对象的指针
* @param id要加载的选项卡的索引
* @param anim_en true：设置滑动动画; false：立即设置
 */
void lv_tabview_set_tab_act(lv_obj_t *tabview, uint16_t id, bool anim_en);

/**
*设置加载选项卡时要调用的操作（只有在创建内容时才有效*必填）
* lv_tabview_get_act（）仍然提供当前（旧）选项卡（以删除内容从这里）
* @param tabview指向tabview对象的指针
* @param动作指向加载选项卡时要调用的函数的指针
 */
void lv_tabview_set_tab_load_action(lv_obj_t *tabview,  lv_tabview_action_t action);

/**
*启用触摸板水平滑动
* @param tabview指向Tab视图对象的指针
* @param zh_cn：启用滑动; false：禁用滑动
 */
void lv_tabview_set_sliding(lv_obj_t *tabview, bool en);

/**
*加载新选项卡时，设置选项卡视图的动画时间
* @param tabview指向Tab视图对象的指针
* @param anim_time动画时间，以毫秒为单位
 */
void lv_tabview_set_anim_time(lv_obj_t *tabview, uint16_t anim_time);

/**
*设置选项卡视图的样式
* @param tabview指向tan视图对象的指针
* @param类型应该设置哪种样式
* @param样式指向新样式
 */
void lv_tabview_set_style(lv_obj_t *tabview, lv_tabview_style_t type,
                          lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
*获取当前活动选项卡的索引
* @param tabview指向Tab视图对象的指针
* @return活动标签索引
 */
uint16_t lv_tabview_get_tab_act(lv_obj_t *tabview);

/**
*获取标签数量
* @param tabview指向Tab视图对象的指针
* @return tab count
 */
uint16_t lv_tabview_get_tab_count(lv_obj_t *tabview);
/**
*获取选项卡的页面（内容区域）
* @param tabview指向Tab视图对象的指针
*选项卡的@param id索引（> = 0）
* @return指向页面（lv_page）对象的指针
 */
lv_obj_t *lv_tabview_get_tab(lv_obj_t *tabview, uint16_t id);

/**
*获取标签加载操作
* @param tabview指向tabview对象的指针
* @param返回当前标签加载操作
 */
lv_tabview_action_t lv_tabview_get_tab_load_action(lv_obj_t *tabview);

/**
*是否启用水平滑动
* @param tabview指向Tab视图对象的指针
* @return true：启用滑动; false：禁用滑动
 */
bool lv_tabview_get_sliding(lv_obj_t *tabview);

/**
*加载新选项卡时，获取选项卡视图的动画时间
* @param tabview指向Tab视图对象的指针
* @return动画时间，以毫秒为单位
 */
uint16_t lv_tabview_get_anim_time(lv_obj_t *tabview);

/**
*获得标签视图的样式
* @param tabview指向ab视图对象的指针
* @param类型应该获得哪种风格
* @return样式指针指向一个样式
 */
lv_style_t *lv_tabview_get_style(lv_obj_t *tabview, lv_tabview_style_t type);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_TABVIEW*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TABVIEW_H*/
