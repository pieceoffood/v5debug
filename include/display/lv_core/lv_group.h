#ifndef LV_GROUP_H
#define LV_GROUP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#include "lv_obj.h"

/*********************
 *      DEFINES
 *********************/
/*通过lv_group_send控制聚焦对象的预定义键（group，c）*/
/*为了兼容信号功能定义键，无论LV_GROUP*/
#define LV_GROUP_KEY_UP 17    /*0x11*/
#define LV_GROUP_KEY_DOWN 18  /*0x12*/
#define LV_GROUP_KEY_RIGHT 19 /*0x13*/
#define LV_GROUP_KEY_LEFT 20  /*0x14*/
#define LV_GROUP_KEY_ESC 27   /*0x1B*/
#define LV_GROUP_KEY_ENTER 10 /*0x0A, '\n'*/
#define LV_GROUP_KEY_NEXT 9   /*0x09, '\t'*/
#define LV_GROUP_KEY_PREV 11  /*0x0B, '*/

#define LV_GROUP_KEY_ENTER_LONG 14 /*0x0E, Sent by the library if ENTER is long pressed*/

#if USE_LV_GROUP != 0
    /**********************
 *      TYPEDEFS
 **********************/
    struct _lv_group_t;

    typedef void (*lv_group_style_mod_func_t)(lv_style_t *);
    typedef void (*lv_group_focus_cb_t)(struct _lv_group_t *);

    typedef struct _lv_group_t
    {
        lv_ll_t obj_ll;                      /*用于存储组中对象的链接列表 */
        lv_obj_t **obj_focus;                /*焦点对象*/
        lv_group_style_mod_func_t style_mod; /*修改焦点对象样式的函数*/
        lv_group_focus_cb_t focus_cb;        /*聚焦新对象时调用的函数（可选）*/
        lv_style_t style_tmp;                /*存储焦点对象的修改样式 */
        uint8_t frozen : 1;                  /*1: 无法关注新对象*/
    } lv_group_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *创建一个新的对象组
    * @return指向新对象组的指针
 */
    lv_group_t *lv_group_create(void);

    /**
    *将对象添加到组
    * @param组指针指向一个组
    * @param obj指向要添加的对象的指针
 */
    void lv_group_add_obj(lv_group_t *group, lv_obj_t *obj);

    /**
    *从组中删除对象
    * @param obj指向要删除的对象的指针
 */
    void lv_group_remove_obj(lv_obj_t *obj);

    /**
    *专注于物体（散焦电流）
    * @param obj指向要关注的对象的指针
 */
    void lv_group_focus_obj(lv_obj_t *obj);

    /**
    *将下一个对象聚焦在一个组中（使当前散焦）
    * @param组指针指向一个组
 */
    void lv_group_focus_next(lv_group_t *group);

    /**
    *将上一个对象聚焦在一个组中（使当前散焦）
    * @param组指针指向一个组
 */
    void lv_group_focus_prev(lv_group_t *group);

    /**
    *不要让焦点从当前对象改变
   * @param组指针指向一个组
   * @param zh_cn true：freeze，false：释放冻结（正常模式）
 */
    void lv_group_focus_freeze(lv_group_t *group, bool en);

    /**
    *将控制字符发送到组的焦点对象
    * @param组指针指向一个组
    * @param ca字符（使用LV_GROUP_KEY_ ..导航）
 */
    void lv_group_send_data(lv_group_t *group, uint32_t c);

    /**
    *为一个组设置一个函数，如果它在，它将修改对象的样式
    *专注
    * @param组指针指向一个组
    * @param style_mod_func样式修饰符函数指针
 */
    void lv_group_set_style_mod_cb(lv_group_t *group,
                                   lv_group_style_mod_func_t style_mod_func);

    /**
    *为聚焦新对象时将调用的组设置一个函数
    * @param组指针指向一个组
    * @param focus_cb回调函数，如果未使用则为NULL
 */
    void lv_group_set_focus_cb(lv_group_t *group, lv_group_focus_cb_t focus_cb);

    /**
    *使用设置'style_mod'功能修改样式。输入样式仍然存在
     *不变。
     * @param组指针指向组
     * @param样式指针指向要修改的样式
     * @return输入样式的副本，但使用'style_mod'函数进行修改
 */
    lv_style_t *lv_group_mod_style(lv_group_t *group, const lv_style_t *style);

    /**
    *获取焦点对象或NULL（如果没有）
    * @param组指针指向一个组
    * @return指向焦点对象的指针
 */
    lv_obj_t *lv_group_get_focused(lv_group_t *group);

    /**
    *获取组的样式修饰符功能
    * @param组指针指向一个组
    * @return指向样式修饰符函数的指针
 */
    lv_group_style_mod_func_t lv_group_get_style_mod_cb(lv_group_t *group);

    /**
    *获取组的焦点回调功能
    * @param组指针指向一个组
    * @return回调函数或NULL如果没有设置et
 */
    lv_group_focus_cb_t lv_group_get_focus_cb(lv_group_t *group);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_GROUP != 0*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_GROUP_H*/
