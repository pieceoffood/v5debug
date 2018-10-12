/**
 * @file lv_draw.h
 *
 */

#ifndef LV_DRAW_H
#define LV_DRAW_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_core/lv_style.h"
#include "display/lv_misc/lv_txt.h"

/*********************
 *      DEFINES
 *********************/
/*如果图像像素包含alpha，我们需要知道像素是多少字节*/
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
#define LV_IMG_PX_SIZE_ALPHA_BYTE 2
#elif LV_COLOR_DEPTH == 16
#define LV_IMG_PX_SIZE_ALPHA_BYTE 3
#elif LV_COLOR_DEPTH == 24
#define LV_IMG_PX_SIZE_ALPHA_BYTE 4
#endif

    /**********************
 *      TYPEDEFS
 **********************/

    /* 与之兼容的图像标题结果图像转换器实用程序*/
    typedef struct
    {
        union {
            struct
            {
                uint32_t chroma_keyed : 1; /*1：图像包含透明像素 LV_COLOR_TRANSP颜色*/
                uint32_t alpha_byte : 1;   /*每个像素都用8位alpha通道扩展*/
                uint32_t format : 6;       /*见：lv_img_px_format t*/
                uint32_t w : 12;           /*图像映射的宽度*/
                uint32_t h : 12;           /*图像地图的高度*/
            } header;
            uint8_t src_type;
        };

        union {
            const uint8_t *pixel_map; /*用于内部图像（c数组）指针像素阵列*/
            uint8_t first_pixel;      /*对于外部图像（二进制）的第一个字节像素（只是为了方便）*/
        };
    } lv_img_t;

    typedef enum
    {
        LV_IMG_FORMAT_UNKOWN = 0,
        LV_IMG_FORMAT_INTERNAL_RAW,    /*'lv_img_t' variable compiled with the code*/
        LV_IMG_FORMAT_FILE_RAW_RGB332, /*8 bit*/
        LV_IMG_FORMAT_FILE_RAW_RGB565, /*16 bit*/
        LV_IMG_FORMAT_FILE_RAW_RGB888, /*24 bit (stored on 32 bit)*/
    } lv_img_format_t;

    typedef enum
    {
        LV_IMG_SRC_VARIABLE,
        LV_IMG_SRC_FILE,
        LV_IMG_SRC_SYMBOL,
        LV_IMG_SRC_UNKNOWN,
    } lv_img_src_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *画一个矩形
    * @param cords_p矩形的坐标
    * @param mask_p矩形将仅在此蒙版中绘制
    * @param style_p指向样式的指针
 */
    void lv_draw_rect(const lv_area_t *cords_p, const lv_area_t *mask_p,
                      const lv_style_t *style_p);

/*3D建模的实验用途*/
#define USE_LV_TRIANGLE 0
#if USE_LV_TRIANGLE != 0
    /**
 * @param指向一个有3个点的数组的指针
 * @param mask_p三角形将仅在此蒙版中绘制
 * @param三角形的颜色
 */
    void lv_draw_triangle(const lv_point_t *points, const lv_area_t *mask_p,
                          lv_color_t color);
#endif

    /**
    *写一个文字
    * @param cords_p标签的坐标
    * @param mask_p标签仅在此区域绘制
    * @param style_p指向样式的指针
    * @param txt 0终止要写入的文本
    * @param标记来自'txt_flag_t'枚举的文本的设置
    * @param在x和y方向偏移文本偏移量（如果未使用则为NULL）
 */
    void lv_draw_label(const lv_area_t *cords_p, const lv_area_t *mask_p, const lv_style_t *style_p, const char *txt, lv_txt_flag_t flag, lv_point_t *offset);

#if USE_LV_IMG
    /**
    / * *
     *画一幅图像
     * @param cords_p图像的坐标
     * @param mask_p仅在此区域绘制图像
     * @param map_p指向包含像素的lv_color_t数组图片
 */
    void lv_draw_img(const lv_area_t *coords, const lv_area_t *mask, const lv_style_t *style, const void *src);
#endif

    /**
    * 画一条线
    * @param p1第一点
    * @param p2第二点
    * @param mask_pt该行仅在此区域绘制
    * @param style_p指向样式的指针
 */
    void lv_draw_line(const lv_point_t *p1, const lv_point_t *p2,
                      const lv_area_t *mask_p, const lv_style_t *style_p);

    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_H*/
