/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-10T10:57:04+08:00
 */

/**
 * @file math_base.h
 *
 */

#ifndef LV_MATH_H
#define LV_MATH_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>

    /*********************
 *      DEFINES
 *********************/

#define LV_MATH_MIN(a, b) (a < b ? a : b)
#define LV_MATH_MAX(a, b) (a > b ? a : b)
#define LV_MATH_ABS(x) ((x) > 0 ? (x) : (-(x)))

    /**********************
 *      TYPEDEFS
 **********************/

    /**********************
 * GLOBAL PROTOTYPES
 **********************/
    /**
    *将数字转换为字符串
    *@param num .一个数字
    *@param buf 指针指向' char '缓冲区。结果将存储在这里(最多10个元素)
    *@return   与' buf '相同(只是为了方便)
 */
    char *lv_math_num_to_str(int32_t num, char *buf);

    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
