/**
 * @file lv_theme_alien.h
 *
 */

#ifndef LV_THEME_ALIEN_H
#define LV_THEME_ALIEN_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"

#if USE_LV_THEME_ALIEN

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *初始化外星人主题
    * @param hue [0..360]来自HSV色彩空间的色调值，用于定义主题的基础
    *颜色
    * @param指向字体的字体指针（NULL使用默认值）
    * @return指向初始化主题的指针
 */
    lv_theme_t *lv_theme_alien_init(uint16_t hue, lv_font_t *font);
    /**
    *获取指向主题的指针
    * @return指向主题的指针
 */
    lv_theme_t *lv_theme_get_alien(void);

    /**********************
 *      MACROS
 **********************/

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_THEME_ALIEN_H*/
