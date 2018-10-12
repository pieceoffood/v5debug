/**
 * @file hal_disp.h
 *
 * @description Display Driver HAL interface header file
 *
 */

#ifndef HAL_DISP_H
#define HAL_DISP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_misc/lv_color.h"
#include "lv_hal.h"
#include <stdbool.h>
#include <stdint.h>

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /**
 * Display Driver structure to be registered by HAL
 */
    typedef struct _disp_drv_t
    {
        /*将内部缓冲区（VDB）写入显示屏。'lv_flush_ready（）'必须是完成时调用*/
        void (*disp_flush)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t *color_p);

        /*在显示屏上填充一个颜色的区域*/
        void (*disp_fill)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);

        /*将像素图（例如图像）写入显示屏*/
        void (*disp_map)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t *color_p);

#if USE_LV_GPU
        /*Blend two memories using opacity (GPU only)*/
        void (*mem_blend)(lv_color_t *dest, const lv_color_t *src, uint32_t length,
                          lv_opa_t opa);

        /*Fill a memory with a color (GPU only)*/
        void (*mem_fill)(lv_color_t *dest, uint32_t length, lv_color_t color);
#endif

    } lv_disp_drv_t;

    typedef struct _disp_t
    {
        lv_disp_drv_t driver;
        struct _disp_t *next;
    } lv_disp_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *使用默认值初始化显示驱动程序。它用于在字段中存在已知值而不是内存垃圾。之后你可以设置字段。
    * @param驱动程序指针指向驱动程序变量以进行初始化
 */
    void lv_disp_drv_init(lv_disp_drv_t *driver);

    /**
    *注册初始化的显示驱动程序。自动将第一个显示设置为活动。
    * @param驱动程序指向初始化的'lv_disp_drv_t'变量（可以是局部变量）
    * @return指向新显示的指针或错误时为NULL
 */
    lv_disp_t *lv_disp_drv_register(lv_disp_drv_t *driver);

    /**
    *设置活动显示
    * @param disp指向显示的指针（返回值'lv_disp_register'）
 */
    void lv_disp_set_active(lv_disp_t *disp);

    /**
    *获取指向活动显示的指针
    * @return指向活动显示的指
 */
    lv_disp_t *lv_disp_get_active(void);

    /**
    *获取下一个显示。
   * @param disp指向当前显示的指针。NULL表示初始化。
   * @return下一个显示，如果没有，则返回NULL。当时给出第一个显示参数为NULL
 */
    lv_disp_t *lv_disp_next(lv_disp_t *disp);

    /**
    *在活动显示屏上填充颜色的矩形区域
    * @param x1矩形的左坐标
    * @param x2矩形的右坐标
    * @param y1矩形的顶部坐标
    * @param y2矩形的底部坐标
    * @param color_p指向颜色数组的指针
 */
    void lv_disp_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2,
                       lv_color_t *color_p);

    /**
    *在活动显示屏上填充颜色的矩形区域
    * @param x1矩形的左坐标
    * @param x2矩形的右坐标
    * @param y1矩形的顶部坐标
    * @param y2矩形的底部坐标
    * @param颜色填充颜色
 */
    void lv_disp_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2,
                      lv_color_t color);

    /**
    *将颜色贴图放在活动显示屏上的矩形区域
    * @param x1矩形的左坐标
    * @param x2矩形的右坐标
    * @param y1矩形的顶部坐标
    * @param y2矩形的底部坐标
    * @param color_map指向颜色数组的指针
 */
    void lv_disp_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2,
                     const lv_color_t *color_map);

#if USE_LV_GPU
    /**
 * Blend pixels to a destination memory from a source memory
 * In 'lv_disp_drv_t' 'mem_blend' is optional. (NULL if not available)
 * @param dest a memory address. Blend 'src' here.
 * @param src pointer to pixel map. Blend it to 'dest'.
 * @param length number of pixels in 'src'
 * @param opa opacity (0, LV_OPA_TRANSP: transparent ... 255, LV_OPA_COVER,
 * fully cover)
 */
    void lv_disp_mem_blend(lv_color_t *dest, const lv_color_t *src, uint32_t length,
                           lv_opa_t opa);

    /**
 * Fill a memory with a color (GPUs may support it)
 * In 'lv_disp_drv_t' 'mem_fill' is optional. (NULL if not available)
 * @param dest a memory address. Copy 'src' here.
 * @param src pointer to pixel map. Copy it to 'dest'.
 * @param length number of pixels in 'src'
 * @param opa opacity (0, LV_OPA_TRANSP: transparent ... 255, LV_OPA_COVER,
 * fully cover)
 */
    void lv_disp_mem_fill(lv_color_t *dest, uint32_t length, lv_color_t color);
    /**
 * Shows if memory blending (by GPU) is supported or not
 * @return false: 'mem_blend' is not supported in the driver; true: 'mem_blend'
 * is supported in the driver
 */
    bool lv_disp_is_mem_blend_supported(void);

    /**
 * Shows if memory fill (by GPU) is supported or not
 * @return false: 'mem_fill' is not supported in the drover; true: 'mem_fill' is
 * supported in the driver
 */
    bool lv_disp_is_mem_fill_supported(void);
#endif
    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
