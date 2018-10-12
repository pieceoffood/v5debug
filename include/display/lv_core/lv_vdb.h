/**
 * @file lv_vdb.h
 *
 */

#ifndef LV_VDB_H
#define LV_VDB_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"

#if LV_VDB_SIZE != 0

#include "display/lv_misc/lv_area.h"
#include "display/lv_misc/lv_color.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/

    typedef struct
    {
        lv_area_t area;
        lv_color_t *buf;
    } lv_vdb_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
*获取'vdb'变量或在LV_VDB_DOUBLE模式下分配一个变量
* @return指向'vdb'变量的指针
 */
    lv_vdb_t *lv_vdb_get(void);

    /**
 *刷新vdb的内容
 */
    void lv_vdb_flush(void);

    /**
    *在'disp_map（）'时必须调用'LV_VDB_DOUBLE'模式已准备好将地图复制到帧缓冲区。.
 */
    void lv_flush_ready(void);

    /**********************
 *      MACROS
 **********************/

#else /*LV_VDB_SIZE != 0*/

/*Just for compatibility*/
void lv_flush_ready(void);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_VDB_H*/
