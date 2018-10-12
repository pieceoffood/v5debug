/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-12T17:20:50+08:00
 */

/**
 * @file lv_font.h
 *
 */

#ifndef LV_FONT_H
#define LV_FONT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"

#include <stddef.h>
#include <stdint.h>

#include "lv_fonts/lv_symbol_def.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    typedef struct
    {
        uint32_t w_px : 8;
        uint32_t glyph_index : 24;
    } lv_font_glyph_dsc_t;

    typedef struct
    {
        uint32_t unicode : 21;
        uint32_t glyph_dsc_index : 11;
    } lv_font_unicode_map_t;

    typedef struct _lv_font_struct
    {
        uint32_t unicode_first;
        uint32_t unicode_last;
        uint8_t h_px;
        const uint8_t *glyph_bitmap;
        const lv_font_glyph_dsc_t *glyph_dsc;
        const uint32_t *unicode_list;
        const uint8_t *(*get_bitmap)(const struct _lv_font_struct *, uint32_t); /*从字体中获取字形的位图*/
        const int16_t (*get_width)(const struct _lv_font_struct *, uint32_t);   /*使用给定字体获取字形*/
        struct _lv_font_struct *next_page;                                      /**指向字体扩展名的指针*/
        uint32_t bpp : 4;                                                       /*每像素位数：1,2或4*/
    } lv_font_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
 *初始化内置字体
 */
    void lv_font_init(void);

    /**
    *从字体名称和字体dsc创建一对。获得功能。'font_get'之后
     *可用于此字体
     * @param子指针指向要加入'父级'的字体
    * @param指向字体的父指针。'孩子'将加入这里
 */
    void lv_font_add(lv_font_t *child, lv_font_t *parent);

    /**
    *返回字体的位图。
    * @param font_p指向字体的指针
    * @param写了一封信
    * @return指向该字母位图的指针
 */
    const uint8_t *lv_font_get_bitmap(const lv_font_t *font_p, uint32_t letter);

    /**
    *获取字体的高度
    * @param font_p指向字体的指针
    * @return字体的高度
 */
    static inline uint8_t lv_font_get_height(const lv_font_t *font_p)
    {
        return font_p->h_px;
    }

    /**
    *获取字体的宽度
    * @param font_p指向字体的指针
    * @param写了一封信
    * @return一个字母的宽度
 */
    uint8_t lv_font_get_width(const lv_font_t *font_p, uint32_t letter);

    /**
    *获取字体的每像素位数
    * @param字体指向字体
    * @param写一封来自字体的字母（字体扩展名可以有不同的bpp）
    * @return bpp的字体（或字体扩展名）
 */
    uint8_t lv_font_get_bpp(const lv_font_t *font, uint32_t letter);

    /**
    *字体包含时，'font-> get_bitmap'中使用的通用位图获取函数
    *范围内的所有字符
    * @param字体指向字体
    * @param unicode_letter一个应该得到位图的unicode字母
    * @return指向位图的指针，如果没有找到则返回NULL
 */
    const uint8_t *lv_font_get_bitmap_continuous(const lv_font_t *font,
                                                 uint32_t unicode_letter);

    /**
    *字体NOT时，'font-> get_bitmap'中使用的通用位图获取函数
    *包含范围内的所有字符（稀疏）
    * @param字体指向字体
    * @param unicode_letter一个应该得到位图的unicode字母
    * @return指向位图的指针，如果没有找到则返回NULL
 */
    const uint8_t *lv_font_get_bitmap_sparse(const lv_font_t *font,
                                             uint32_t unicode_letter);
    /**
    *字体时，'font-> get_width'中使用的通用字形宽度获取函数
    *包含范围内的所有字符
    * @param字体指向字体
    * @param unicode_letter一个宽度应该得到的unicode字母
    * @return gylph的宽度或-1如果没有找到
 */
    const int16_t lv_font_get_width_continuous(const lv_font_t *font,
                                               uint32_t unicode_letter);

    /**
    *字体NOT时，'font-> get_bitmap'中使用的通用字形宽度get函数
    *包含范围内的所有字符（稀疏）
    * @param字体指向字体
    * @param unicode_letter一个宽度应该得到的unicode字母
    * @return字形宽度，如果没有找到-1
 */
    const int16_t lv_font_get_width_sparse(const lv_font_t *font,
                                           uint32_t unicode_letter);

/**********************
 *      MACROS
 **********************/
#define LV_FONT_DECLARE(font_name) extern lv_font_t font_name;

/******************************
 *  FONT DECLARATION INCLUDES
 *****************************/

/*10 px */
#if USE_LV_FONT_DEJAVU_10
    LV_FONT_DECLARE(lv_font_dejavu_10)
#endif

#if USE_LV_FONT_DEJAVU_10_LATIN_SUP
    LV_FONT_DECLARE(lv_font_dejavu_10_latin_sup)
#endif

#if USE_LV_FONT_DEJAVU_10_CYRILLIC
    LV_FONT_DECLARE(lv_font_dejavu_10_cyrillic)
#endif

#if USE_LV_FONT_SYMBOL_10
    LV_FONT_DECLARE(lv_font_symbol_10)
#endif

/*20 px */
#if USE_LV_FONT_DEJAVU_20
    LV_FONT_DECLARE(lv_font_dejavu_20)
#endif

#if USE_LV_FONT_DEJAVU_20_LATIN_SUP
    LV_FONT_DECLARE(lv_font_dejavu_20_latin_sup)
#endif

#if USE_LV_FONT_DEJAVU_20_CYRILLIC
    LV_FONT_DECLARE(lv_font_dejavu_20_cyrillic)
#endif

#if USE_LV_FONT_SYMBOL_20
    LV_FONT_DECLARE(lv_font_symbol_20)
#endif

/*30 px */
#if USE_LV_FONT_DEJAVU_30
    LV_FONT_DECLARE(lv_font_dejavu_30)
#endif

#if USE_LV_FONT_DEJAVU_30_LATIN_SUP
    LV_FONT_DECLARE(lv_font_dejavu_30_latin_sup)
#endif

#if USE_LV_FONT_DEJAVU_30_CYRILLIC
    LV_FONT_DECLARE(lv_font_dejavu_30_cyrillic)
#endif

#if USE_LV_FONT_SYMBOL_30
    LV_FONT_DECLARE(lv_font_symbol_30)
#endif

/*40 px */
#if USE_LV_FONT_DEJAVU_40
    LV_FONT_DECLARE(lv_font_dejavu_40)
#endif

#if USE_LV_FONT_DEJAVU_40_LATIN_SUP
    LV_FONT_DECLARE(lv_font_dejavu_40_latin_sup)
#endif

#if USE_LV_FONT_DEJAVU_40_CYRILLIC
    LV_FONT_DECLARE(lv_font_dejavu_40_cyrillic)
#endif

#if USE_PROS_FONT_DEJAVU_MONO_10
    LV_FONT_DECLARE(pros_font_dejavu_mono_10)
#endif
#if USE_PROS_FONT_DEJAVU_MONO_10_LATIN_SUP
    LV_FONT_DECLARE(pros_font_dejavu_mono_10_latin_sup)
#endif
#if USE_PROS_FONT_DEJAVU_MONO_20
    LV_FONT_DECLARE(pros_font_dejavu_mono_20)
#endif
#if USE_PROS_FONT_DEJAVU_MONO_20_LATIN_SUP
    LV_FONT_DECLARE(pros_font_dejavu_mono_20_latin_sup)
#endif
#if USE_PROS_FONT_DEJAVU_MONO_30
    LV_FONT_DECLARE(pros_font_dejavu_mono_30)
#endif
#if USE_PROS_FONT_DEJAVU_MONO_30_LATIN_SUP
    LV_FONT_DECLARE(pros_font_dejavu_mono_30_latin_sup)
#endif
#if USE_PROS_FONT_DEJAVU_MONO_40
    LV_FONT_DECLARE(pros_font_dejavu_mono_40)
#endif
#if USE_PROS_FONT_DEJAVU_MONO_40_LATIN_SUP
    LV_FONT_DECLARE(pros_font_dejavu_mono_40_latin_sup)
#endif

#if USE_LV_FONT_SYMBOL_40
    LV_FONT_DECLARE(lv_font_symbol_40)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*USE_FONT*/
