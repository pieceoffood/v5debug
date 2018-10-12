/**
 * @file lv_indev_proc.h
 *
 */

#ifndef LV_INDEV_H
#define LV_INDEV_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_core/lv_group.h"
#include "display/lv_hal/lv_hal_indev.h"
#include "lv_obj.h"

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
 * 初始化显示输入设备子系统
 */
    void lv_indev_init(void);

    /**
    *获取当前处理的输入设备。也是可用于动作功能。
     * @return指向当前处理的输入设备的指针，如果没有输入则为NULL
     *现在设备处理
 */
    lv_indev_t *lv_indev_get_act(void);

    /**
    *重置一个或所有输入设备
    * @param indev指向要重置的输入设备的指针或NULL以重置所有这些指针
 */
    void lv_indev_reset(lv_indev_t *indev);

    /**
    *重置输入设备的长按状态
    * @param indev_proc指向输入设备的指针
 */
    void lv_indev_reset_lpr(lv_indev_t *indev);

    /**
    *按类型启用输入设备设备
    * @param type输入设备类型
   * @param enable true：启用此类型; false：禁用此类型
 */
    void lv_indev_enable(lv_hal_indev_type_t type, bool enable);

    /**
    *设置指针输入设备的光标（对于LV_INPUT_TYPE_POINTER和LV_INPUT_TYPE_BUTTON）
    * @param指向输入设备的indev指针
    * @param cur_obj指向要用作游标的对象的指针
 */
    void lv_indev_set_cursor(lv_indev_t *indev, lv_obj_t *cur_obj);

#if USE_LV_GROUP
    /**
    *为键盘输入设备设置目标组（对于LV_INDEV_TYPE_KEYPAD）
    * @param指向输入设备的indev指针
    * @param组指向一个组
 */
    void lv_indev_set_group(lv_indev_t *indev, lv_group_t *group);
#endif

    /**
    *为LV_INDEV_TYPE_BUTTON设置一个点数组。这些点将分配给按钮以按下特定点屏幕
    * @param指向输入设备的indev指针
    * @param组指向一个组
 */
    void lv_indev_set_button_points(lv_indev_t *indev, lv_point_t *points);

    /**
    *获取输入设备的最后一点（对于LV_INDEV_TYPE_POINTER和 LV_INDEV_TYPE_BUTTON）
    * @param指向输入设备的indev指针
    * @param指向存储结果的点的指针
 */
    void lv_indev_get_point(lv_indev_t *indev, lv_point_t *point);

    /**
    *检查是否有输入设备拖动（for LV_INDEV_TYPE_POINTER和LV_INDEV_TYPE_BUTTON）
    * @param指向输入设备的indev指针
    * @return true：拖动正在进行中
 */
    bool lv_indev_is_dragging(lv_indev_t *indev);

    /**
    *获取拖动输入设备的向量（对于LV_INDEV_TYPE_POINTER和LV_INDEV_TYPE_BUTTON）
    * @param指向输入设备的indev指针
    * @param指向存储向量的点的指针r
 */
    void lv_indev_get_vect(lv_indev_t *indev, lv_point_t *point);
    /**
    *获取自上次按下后经过的时间
    * @param指向输入设备的indev指针（NULL表示整体最小不活动）
    * @return自上次按下后经过的刻度（毫秒）
 */
    uint32_t lv_indev_get_inactive_time(lv_indev_t *indev);

    /**
    *在下一个版本之前不做任何事情
    *@param指向输入设备的indev指针
 */
    void lv_indev_wait_release(lv_indev_t *indev);

    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_INDEV_H*/
