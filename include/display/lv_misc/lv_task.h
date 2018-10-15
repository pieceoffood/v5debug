/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-15T08:41:08+08:00
 */

#ifndef LV_TASK_H
#define LV_TASK_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_ll.h"
#include "lv_mem.h"
#include <stdbool.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/
#ifndef LV_ATTRIBUTE_TASK_HANDLER
#define LV_ATTRIBUTE_TASK_HANDLER
#endif
    /**********************
 *      TYPEDEFS
 **********************/
    /**
 * lv_tasks的可能优先级
 */
    typedef enum
    {
        LV_TASK_PRIO_OFF = 0,
        LV_TASK_PRIO_LOWEST,
        LV_TASK_PRIO_LOW,
        LV_TASK_PRIO_MID,
        LV_TASK_PRIO_HIGH,
        LV_TASK_PRIO_HIGHEST,
        LV_TASK_PRIO_NUM,
    } lv_task_prio_t;

    /**
 * lv_task的描述符
 */
    typedef struct
    {
        uint32_t period;
        uint32_t last_run;
        void (*task)(void *);
        void *param;
        uint8_t prio : 3;
        uint8_t once : 1;
    } lv_task_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
 *初始化lv_task模块
 */
    void lv_task_init(void);

    /**
 *定期调用它来处理lv_tasks。
 */
    LV_ATTRIBUTE_TASK_HANDLER void lv_task_handler(void);

    /**
    *创建一个新的lv_task
    * @param任务是一个任务本身的函数
    * @param周期呼叫周期以ms为单位
    * @param prio任务的优先级（LV_TASK_PRIO_OFF表示任务已停止）
    * @param param free参数
    * @return指向新任务的指针
 */
    lv_task_t *lv_task_create(void (*task)(void *), uint32_t period,
                              lv_task_prio_t prio, void *param);

    /**
    *删除lv_task
    * @param lv_task_p指向由lv_task_p创建的任务的指针
 */
    void lv_task_del(lv_task_t *lv_task_p);

    /**
    *为lv_task设置新的优先级
    * @param lv_task_p指向lv_task的指针
    * @param prio新的优先事项
 */
    void lv_task_set_prio(lv_task_t *lv_task_p, lv_task_prio_t prio);

    /**
    *为lv_task设置新的时间段
    * @param lv_task_p指向lv_task的指针
    * @param期间的新时期
 */
    void lv_task_set_period(lv_task_t *lv_task_p, uint32_t period);

    /**
    *准备一个lv_task。它不会等待它的时期。
     * @param lv_task_p指向lv_task的指针。
 */
    void lv_task_ready(lv_task_t *lv_task_p);

    /**
    *一次通话后删除lv_task
    * @param lv_task_p指向lv_task的指针。
 */
    void lv_task_once(lv_task_t *lv_task_p);

    /**
    *重置lv_task。
    *它将在几毫秒之后被称为先前设定的时间段。
    * @param lv_task_p指向lv_task的指针。
 */
    void lv_task_reset(lv_task_t *lv_task_p);

    /**
    *启用或禁用整个lv_task处理
    * @param en：true：lv_task正在运行，false：lv_task正在处理暂停
 */
    void lv_task_enable(bool en);

    /**
    *获得空闲百分比
    * @return lv_task空闲百分比
 */
    uint8_t lv_task_get_idle(void);

    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
