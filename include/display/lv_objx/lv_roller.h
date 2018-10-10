/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-10T15:18:25+08:00
 */

#ifndef LV_ROLLER_H
#define LV_ROLLER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_ROLLER != 0

/*依赖项测试*/
#if USE_LV_DDLIST == 0
#error \
    "lv_roller: lv_ddlist is required. Enable it in lv_conf.h (USE_LV_DDLIST  1) "
#endif

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_ddlist.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/
    /*Data of roller*/
    typedef struct
    {
        lv_ddlist_ext_t ddlist; /*Ext. of ancestor*/
                                /*New data for this type */
    } lv_roller_ext_t;

    typedef enum
    {
        LV_ROLLER_STYLE_BG,
        LV_ROLLER_STYLE_SEL,
    } lv_roller_style_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *创建一个滚轴对象
    * @param par指向一个对象的指针，它将是新滚子的父指针
    * @param复制指向滚子对象的指针，如果不是NULL，则新对象将从中复制
    * @return指向创建的滚轮的指针
 */
    lv_obj_t *lv_roller_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 * Setter functions
 *====================*/

    /**
    *在滚筒上设置选项
    * @param滚轮指针指向滚轮对象
   * @param选项包含'\ n'分隔选项的字符串。例如“One \ nTwo \ nThree”
 */
    static inline void lv_roller_set_options(lv_obj_t *roller, const char *options)
    {
        lv_ddlist_set_options(roller, options);
    }

    /**
    *设置所选选项
    * @param滚轮指针指向滚轮对象
    * @param sel_opt所选选项的id（0 ...选项数 -  1）;
   * @param anim_en true：设置动画; 假立即设置
 */
    void lv_roller_set_selected(lv_obj_t *roller, uint16_t sel_opt, bool anim_en);

    /**
    *设置要在选择新选项时调用的函数
    * @param滚轮指针指向滚轮
    * @param动作指向回调函数
    */
    static inline void lv_roller_set_action(lv_obj_t *roller, lv_action_t action)
    {
        lv_ddlist_set_action(roller, action);
    }

    /**
    *设置高度以显示给定的行数（选项）
    * @param滚轮指针指向滚轮对象
    * @param row_cnt所需可见行数
 */
    void lv_roller_set_visible_row_count(lv_obj_t *roller, uint8_t row_cnt);

    /**
    *启用或禁用内容的水平拟合
    * @param滚轮指针指向滚轮
   * @param fit en true：启用自动适应; false：禁用自动适合
 */
    static inline void lv_roller_set_hor_fit(lv_obj_t *roller, bool fit_en)
    {
        lv_ddlist_set_hor_fit(roller, fit_en);
    }

    /**
    *设置打开/关闭动画时间。
    * @param滚轮指针指向滚轮对象
    * @param anim_time：打开/关闭动画时间[ms]
 */
    static inline void lv_roller_set_anim_time(lv_obj_t *roller, uint16_t anim_time)
    {
        lv_ddlist_set_anim_time(roller, anim_time);
    }

    /**
    *设置滚筒的风格
    * @param滚轮指针指向滚轮对象
    * @param类型应该设置哪种样式
    * @param样式指针指向一个样式
 */
    void lv_roller_set_style(lv_obj_t *roller, lv_roller_style_t type, lv_style_t *style);

    /*=====================
 * Getter functions
 *====================*/

    /**
    *获得滚轮选项
    * @param滚轮指针指向滚轮对象
    * @return由'\ n'-s分隔的选项（例如“Option1 \ nOption2 \ nOption3”）
 */
    static inline const char *lv_roller_get_options(lv_obj_t *roller)
    {
        return lv_ddlist_get_options(roller);
    }

    /**
    *获取所选选项的ID
    * @param滚轮指针指向滚轮对象
    *所选选项的@return id（0 ...选项数 -  1）;
 */
    static inline uint16_t lv_roller_get_selected(lv_obj_t *roller)
    {
        return lv_ddlist_get_selected(roller);
    }

    /**
    *将当前选定的选项作为字符串
    * @param滚轮指针指向滚轮对象
    * @param buf指向存储字符串的数组的指针
 */
    static inline void lv_roller_get_selected_str(lv_obj_t *roller, char *buf)
    {
        lv_ddlist_get_selected_str(roller, buf);
    }

    /**
    *获取“选项选择”回调功能
    * @param滚轮指针指向滚轮
    * @return指向回调函数的指针
 */
    static inline lv_action_t lv_roller_get_action(lv_obj_t *roller)
    {
        return lv_ddlist_get_action(roller);
    }

    /**
    *获取开放/关闭动画时间。
    * @param滚轮指针指向滚轮
    * @return开启/关闭动画时间[ms]
 */
    static inline uint16_t lv_roller_get_anim_time(lv_obj_t *roller)
    {
        return lv_ddlist_get_anim_time(roller);
    }

    /**
    *获取自动宽度设置属性
    * @param滚轮指针指向滚轮对象
   * @return true：启用自动尺寸; false：启用手动宽度设置
 */
    bool lv_roller_get_hor_fit(lv_obj_t *roller);

    /**
    *获得一种滚动的风格
    * @param滚轮指针指向滚轮对象
    * @param类型应该获得哪种风格
    * @return样式指针指向一个样式
 *  */
    lv_style_t *lv_roller_get_style(lv_obj_t *roller, lv_roller_style_t type);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_ROLLER*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_ROLLER_H*/
