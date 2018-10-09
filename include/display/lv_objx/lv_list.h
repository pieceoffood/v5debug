
#ifndef LV_LIST_H
#define LV_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_LIST != 0

/*依赖项测试*/
#if USE_LV_PAGE == 0
#error "lv_list: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#if USE_LV_BTN == 0
#error "lv_list: lv_btn is required. Enable it in lv_conf.h (USE_LV_BTN  1) "
#endif

#if USE_LV_LABEL == 0
#error \
    "lv_list: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_img.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_objx/lv_page.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/
    /*清单数据*/
    typedef struct
    {
        lv_page_ext_t page; /*Ext. of ancestor*/
        /*New data for this type */
        uint16_t anim_time;                       /*滚动动画时间*/
        lv_style_t *styles_btn[LV_BTN_STATE_NUM]; /*列表元素按钮的样式*/
        lv_style_t *style_img;                    /*按钮上列表元素图像的样式*/
    } lv_list_ext_t;

    typedef enum
    {
        LV_LIST_STYLE_BG,
        LV_LIST_STYLE_SCRL,
        LV_LIST_STYLE_SB,
        LV_LIST_STYLE_BTN_REL,
        LV_LIST_STYLE_BTN_PR,
        LV_LIST_STYLE_BTN_TGL_REL,
        LV_LIST_STYLE_BTN_TGL_PR,
        LV_LIST_STYLE_BTN_INA,
    } lv_list_style_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *创建一个列表对象
    * @param par指向一个对象的指针，它将是新列表的父指针
    * @param复制指向列表对象的指针，如果不是NULL，那么新对象将是
    *从中复制
    * @return指向创建列表的指针
 */
    lv_obj_t *lv_list_create(lv_obj_t *par, lv_obj_t *copy);

    /*======================
 * *添加/删除功能
 *=====================*/

    /**
     * 将列表元素添加到列表中
    * @param列表指向列表对象的指针
    * @param img_fn文本前图像的文件名（如果未使用，则为NULL）
    * @param txt list元素的文本（如果未使用则为NULL）
    * @param rel_action指向释放动作函数（与lv_btn一样）
    * @return指向可以自定义的新列表元素（一个按钮）
 */
    lv_obj_t *lv_list_add(lv_obj_t *list, const void *img_src, const char *txt, lv_action_t rel_action);

    /*=====================
 * Setter functions
 *====================*/

    /**
    *在'list_up（）''list_down（）''list_focus（）'上设置滚动动画持续时间
    * @param列表指向列表对象的指针
    * @param anim_time动画持续时间[ms]
 */
    void lv_list_set_anim_time(lv_obj_t *list, uint16_t anim_time);

    /**
    *设置列表的滚动条模式
    * @param列表指向列表对象的指针
    * @param sb_mode来自'lv_page_sb_mode_t'枚举的新模式
 */
    static inline void lv_list_set_sb_mode(lv_obj_t *list, lv_sb_mode_t mode)
    {
        lv_page_set_sb_mode(list, mode);
    }

    /**
    *设置列表样式
    * @param列表指向列表对象的指针
    * @param类型应该设置哪种样式
    * @param样式指针指向一个样式
 */
    void lv_list_set_style(lv_obj_t *list, lv_list_style_t type, lv_style_t *style);

    /*=====================
 * Getter functions
 *====================*/

    /**
    *获取列表元素的文本
    * @param btn指向列表元素的指针
    * @return指向文本的指针
 */
    const char *lv_list_get_btn_text(lv_obj_t *btn);
    /**
    *从列表元素中获取标签对象
    * @param btn指向列表元素的指针（按钮）
    * @return指向list元素中标签的指针，如果没有找到则返回NULL
 */
    lv_obj_t *lv_list_get_btn_label(lv_obj_t *btn);

    /**
    *从列表元素中获取图像对象
    * @param btn指向列表元素的指针（按钮）
    * @return指向列表元素中图像的指针，如果未找到则返回NULL
 */
    lv_obj_t *lv_list_get_btn_img(lv_obj_t *btn);

    /**
    *获取滚动动画持续时间
    * @param列表指向列表对象的指针
    * @return动画持续时间[ms]
 */
    uint16_t lv_list_get_anim_time(lv_obj_t *list);

    /**
    *获取列表的滚动条模式
    * @param列表指向列表对象的指针
    * @return滚动条模式来自'lv_page_sb_mode_t'枚举
 */
    static inline lv_sb_mode_t lv_list_get_sb_mode(lv_obj_t *list)
    {
        return lv_page_get_sb_mode(list);
    }

    /**
    *获得列表样式
    * @param列表指向列表对象的指针
    * @param类型应该获得哪种风格
    * @return样式指针指向一个样式
 *  */
    lv_style_t *lv_list_get_style(lv_obj_t *list, lv_list_style_t type);

    /*=====================
 * Other functions
 *====================*/

    /**
    *将列表元素向上移动一个
    * @param列表指针列表对象
 */
    void lv_list_up(lv_obj_t *list);
    /**
    *将列表元素向下移动一个
    * @param列表指向列表对象的指针
 */
    void lv_list_down(lv_obj_t *list);

    /**
    *专注于列表按钮。它确保按钮在。上可见清单。
     * @param btn指向要关注的列表按钮
     * @param anim_en true：滚动动画，false：没有动画
 */
    void lv_list_focus(lv_obj_t *btn, bool anim_en);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_LIST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_LIST_H*/
