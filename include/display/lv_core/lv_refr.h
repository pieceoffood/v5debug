/**
 * @file lv_refr.h
 *
 */

#ifndef LV_REFR_H
#define LV_REFR_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_obj.h"
#include <stdbool.h>

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    /**********************
 *  STATIC PROTOTYPES
 **********************/

    /**********************
 *  STATIC VARIABLES
 **********************/

    /**********************
 *      MACROS
 **********************/

    /**********************
 *   GLOBAL FUNCTIONS
 **********************/

    /**
 *初始化屏幕刷新子系统
 */
    void lv_refr_init(void);

    /**
    *使区域无效
    * @param area_p指向应该无效的区域的指针d
 */
    void lv_inv_area(const lv_area_t *area_p);

    /**
    *设置每次刷新后调用的函数，以宣布刷新时间和
    *刷新像素数
    * @param cb指向回调函数的指针（void my_refr_cb（uint32_t time_ms， uint32_t px_num））
 */
    void lv_refr_set_monitor_cb(void (*cb)(uint32_t, uint32_t));

    /**
    *当区域无效时调用以修改区域的坐标。特殊显示控制器可能需要特殊的坐标舍入
    * @param cb指向将修改区域的函数的指针
 */
    void lv_refr_set_round_cb(void (*cb)(lv_area_t *));

    /**
    *获取缓冲区中的区域数量
    * @return无效区域的数量
 */
    uint16_t lv_refr_get_buf_size(void);

    /**
    *从缓冲区弹出（删除）最后'num'个无效区域
    * @param num要删除的区域数
 */
    void lv_refr_pop_from_buf(uint16_t num);
    /**********************
 *   STATIC FUNCTIONS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_REFR_H*/
