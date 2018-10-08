/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T17:22:28+08:00
 */

#ifndef LV_DDLIST_H
#define LV_DDLIST_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_DDLIST != 0

/*Testing of dependencies*/
#if USE_LV_PAGE == 0
#error \
    "lv_ddlist: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#if USE_LV_LABEL == 0
#error \
    "lv_ddlist: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_objx/lv_page.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/
    /*下拉列表数据*/
    typedef struct
    {
        lv_page_ext_t page; /* Ext。祖先*/
        /*此类型的新数据 */
        lv_obj_t *label;         /*选项的标签*/
        lv_style_t *sel_style;   /*所选选项的样式*/
        lv_action_t action;      /*选择选项时调用的指针*/
        uint16_t option_cnt;     /*选项数量*/
        uint16_t sel_opt_id;     /*当前选项的索引*/
        uint16_t sel_opt_id_ori; /*将原始索引存储在焦点上*/
        uint16_t anim_time;      /*打开/关闭动画时间[ms]*/
        uint8_t opened : 1;      /*1：列表打开*/
        lv_coord_t fix_height;   /*如果打开ddlist，则为高度。（0：自动尺寸）*/
    } lv_ddlist_ext_t;

    typedef enum
    {
        LV_DDLIST_STYLE_BG,
        LV_DDLIST_STYLE_SEL,
        LV_DDLIST_STYLE_SB,
    } lv_ddlist_style_t;

    /**********************
 * 全局模型
 **********************/
    /**
    *创建下拉列表对象
     * @param par指向一个对象的指针，它将是新下拉列表的父指针
     *清单
     * @param复制指向下拉列表对象的指针，如果不是NULL那么新的
     *对象将从中复制
     * @return指向创建的下拉列表的指针
 */
    lv_obj_t *lv_ddlist_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 * Setter功能
 *====================*/

    /**
    *在字符串的下拉列表中设置选项
   * @param ddlist指向下拉列表对象的指针
  * @param选项包含'\ n'分隔选项的字符串。例如“One \ nTwo \ nThree”
 */
    void lv_ddlist_set_options(lv_obj_t *ddlist, const char *options);

    /**
    *设置所选选项
    * @param ddlist指向下拉列表对象的指针
    * @param sel_opt所选选项的id（0 ...选项数 -  1）;
 */
    void lv_ddlist_set_selected(lv_obj_t *ddlist, uint16_t sel_opt);

    /**
    *设置要在选择新选项时调用的函数
    * @param ddlist指向下拉列表的指针
    * @param动作指向回调函数
 */
    void lv_ddlist_set_action(lv_obj_t *ddlist, lv_action_t action);

    /**
    *设置下拉列表的修复高度
   *如果为0则打开的ddlist将为auto。否则设定的高度将是
    *已申请。
    * @param ddlist指向下拉列表的指针
    * @param h列表打开时的高度（0：自动大小）
 */
    void lv_ddlist_set_fix_height(lv_obj_t *ddlist, lv_coord_t h);

    /**
    *启用或禁用内容的水平拟合
    * @param ddlist指向下拉列表的指针
   * @param fit en true：启用自动适应; false：禁用自动适合
 */
    void lv_ddlist_set_hor_fit(lv_obj_t *ddlist, bool fit_en);

    /**
    *设置下拉列表的滚动条模式
    * @param ddlist指向下拉列表对象的指针
    * @param sb_mode来自'lv_page_sb_mode_t'枚举的新模式
 */
    static inline void lv_ddlist_set_sb_mode(lv_obj_t *ddlist, lv_sb_mode_t mode)
    {
        lv_page_set_sb_mode(ddlist, mode);
    }

    /**
    *设置打开/关闭动画时间。
   * @param ddlist指向下拉列表的指针
   * @param anim_time：打开/关闭动画时间[ms]
 */
    void lv_ddlist_set_anim_time(lv_obj_t *ddlist, uint16_t anim_time);

    /**
    *设置下拉列表的样式
    * @param ddlist指向下拉列表对象的指针
    * @param类型应该设置哪种样式
    * @param样式指针指向一个样式
 *  */
    void lv_ddlist_set_style(lv_obj_t *ddlist, lv_ddlist_style_t type,
                             lv_style_t *style);

    /*=====================
 * 吸气功能
 *====================*/

    /**
    *获取下拉列表的选项
   * @param ddlist指向下拉列表对象的指针
   * @return由'\ n'-s分隔的选项（例如“Option1 \ nOption2 \ nOption3”）
 */
    const char *lv_ddlist_get_options(lv_obj_t *ddlist);

    /**
    *获取所选选项
    * @param ddlist指向下拉列表对象的指针
    *所选选项的@return id（0 ...选项数 -  1）;
 */
    uint16_t lv_ddlist_get_selected(lv_obj_t *ddlist);

    /**
    *将当前选定的选项作为字符串
   * @param ddlist指向ddlist对象的指针
   * @param buf指向存储字符串的数组的指针
 */
    void lv_ddlist_get_selected_str(lv_obj_t *ddlist, char *buf);

    /**
    *获取“选项选择”回调功能
    * @param ddlist指向下拉列表的指针
    * @return指向回调函数的指针
 */
    lv_action_t lv_ddlist_get_action(lv_obj_t *ddlist);

    /**
    *获取修复高度值。
    * @param ddlist指向下拉列表对象的指针
    *如果打开ddlist，则@return高度（0：自动大小）
 */
    lv_coord_t lv_ddlist_get_fix_height(lv_obj_t *ddlist);

    /**
    *获取下拉列表的滚动条模式
    * @param ddlist指向下拉列表对象的指针
    * @return滚动条模式来自'lv_page_sb_mode_t'枚举
 */
    static inline lv_sb_mode_t lv_ddlist_get_sb_mode(lv_obj_t *ddlist)
    {
        return lv_page_get_sb_mode(ddlist);
    }

    /**
    *获取开放/关闭动画时间。
   * @param ddlist指向下拉列表的指针
   * @return开启/关闭动画时间[ms]
 */
    uint16_t lv_ddlist_get_anim_time(lv_obj_t *ddlist);

    /**
    *获取下拉列表的样式
    * @param ddlist指向下拉列表对象的指针
    * @param类型应该获得哪种风格
    * @return样式指针指向一个样式
 */
    lv_style_t *lv_ddlist_get_style(lv_obj_t *ddlist, lv_ddlist_style_t type);

    /*=====================
 * 其他功能
 *====================*/

    /**
    *打开带或不带动画的下拉列表
    * @param ddlist指向下拉列表对象的指针
   * @param anim_en true：使用动画; false：不使用动画
 */
    void lv_ddlist_open(lv_obj_t *ddlist, bool anim);

    /**
    *关闭（折叠）下拉列表
    * @param ddlist指向下拉列表对象的指针
   * @param anim true：使用动画; false：不使用动画
 */
    void lv_ddlist_close_en(lv_obj_t *ddlist, bool anim);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_DDLIST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DDLIST_H*/
