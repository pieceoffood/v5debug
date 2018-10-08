/**
 * @Author: yan
 * @Date:   2018-10-08T10:28:31+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T15:39:46+08:00
 */

#ifndef LV_OBJ_H
#define LV_OBJ_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#include "display/lv_misc/lv_area.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_misc/lv_ll.h"
#include "display/lv_misc/lv_mem.h"
#include "lv_style.h"
#include <stdbool.h>
#include <stddef.h>

/*********************
 *      DEFINES
 *********************/

/* lv_conf.h的错误检查*/
#if LV_HOR_RES == 0 || LV_VER_RES == 0
#error "LittlevGL: LV_HOR_RES and LV_VER_RES must be greater then 0"
#endif

#if LV_ANTIALIAS > 1
#error "LittlevGL: LV_ANTIALIAS can be only 0 or 1"
#endif

#if LV_VDB_SIZE == 0 && LV_ANTIALIAS != 0
#error "LittlevGL: If LV_VDB_SIZE == 0 the anti-aliasing must be disabled"
#endif

#if LV_VDB_SIZE > 0 && LV_VDB_SIZE < LV_HOR_RES
#error \
    "LittlevGL: Small Virtual Display Buffer (lv_conf.h: LV_VDB_SIZE >= LV_HOR_RES)"
#endif

#if LV_VDB_SIZE == 0 && USE_LV_REAL_DRAW == 0
#error \
    "LittlevGL: If LV_VDB_SIZE = 0 Real drawing function are required (lv_conf.h: USE_LV_REAL_DRAW 1)"
#endif

#define LV_ANIM_IN 0x00       /*动画来展示对象。'或'与lv_anim_builtin_t*/
#define LV_ANIM_OUT 0x80      /*动画隐藏的对象。'或'与lv_anim_builtin_t*/
#define LV_ANIM_DIR_MASK 0x80 /*ANIM_IN / ANIM_OUT面*/

#define LV_MAX_ANCESTOR_NUM 8
    /**********************
 *      TYPEDEFS
 **********************/

    struct _lv_obj_t;

    typedef enum
    {
        LV_DESIGN_DRAW_MAIN,
        LV_DESIGN_DRAW_POST,
        LV_DESIGN_COVER_CHK,
    } lv_design_mode_t;

    typedef bool (*lv_design_func_t)(struct _lv_obj_t *obj, const lv_area_t *mask_p, lv_design_mode_t mode);

    typedef enum
    {
        LV_RES_INV = 0, /**通常表示该对象被删除（变为无效）在动作函数*/
        LV_RES_OK,      /*对象在动作后有效（没有删除）*/
    } lv_res_t;

    typedef enum
    {
        /*一般信号*/
        LV_SIGNAL_CLEANUP,
        LV_SIGNAL_CHILD_CHG,
        LV_SIGNAL_CORD_CHG,
        LV_SIGNAL_STYLE_CHG,
        LV_SIGNAL_REFR_EXT_SIZE,
        LV_SIGNAL_GET_TYPE,

        /*输入设备相关*/
        LV_SIGNAL_PRESSED,
        LV_SIGNAL_PRESSING,
        LV_SIGNAL_PRESS_LOST,
        LV_SIGNAL_RELEASED,
        LV_SIGNAL_LONG_PRESS,
        LV_SIGNAL_LONG_PRESS_REP,
        LV_SIGNAL_DRAG_BEGIN,
        LV_SIGNAL_DRAG_END,

        /*集团相关*/
        LV_SIGNAL_FOCUS,
        LV_SIGNAL_DEFOCUS,
        LV_SIGNAL_CONTROLL,
    } lv_signal_t;

    typedef lv_res_t (*lv_signal_func_t)(struct _lv_obj_t *obj, lv_signal_t sign, void *param);

    typedef struct _lv_obj_t
    {
        struct _lv_obj_t *par;        /*指向父对象的指针*/
        lv_ll_t child_ll;             /*用于存储子对象的链接列表*/
        lv_area_t coords;             /*对象的坐标（x1，y1，x2，y2）*/
        lv_signal_func_t signal_func; /*对象类型特定信号函数*/
        lv_design_func_t design_func; /*对象类型特定设计功能*/
        void *ext_attr;               /*对象类型特定的扩展数据*/
        lv_style_t *style_p;          /*指向对象样式的指针*/

#if LV_OBJ_FREE_PTR != 0
        void *free_ptr; /*应用程序特定指针（自由设置）*/
#endif

#if USE_LV_GROUP != 0
        void *group_p; /*指向对象组的指针*/
#endif
        /*属性和状态*/
        uint8_t click : 1;       /*1: 可以通过输入设备按下*/
        uint8_t drag : 1;        /*1: 启用拖动*/
        uint8_t drag_throw : 1;  /*1: 使用拖动启用投掷*/
        uint8_t drag_parent : 1; /*1: 将拖动父级*/
        uint8_t hidden : 1;      /*1: 对象被隐藏*/
        uint8_t top : 1;         /*1: 如果单击对象或其子对象，则转到前景*/
        uint8_t reserved : 1;
        uint8_t protect;     /*可以防止自动发生的操作。“或运算来自lv_obj_prot_t的值*/
        lv_coord_t ext_size; /*EXTtend在每个方向上的对象大小。例如 阴影画*/
#ifdef LV_OBJ_FREE_NUM_TYPE
        LV_OBJ_FREE_NUM_TYPE free_num; /*应用程序特定标识符（自由设置）*/
#endif
    } lv_obj_t;

    typedef lv_res_t (*lv_action_t)(struct _lv_obj_t *obj);

    /*保护一些属性（最多8位）*/
    typedef enum
    {
        LV_PROTECT_NONE = 0x00,
        LV_PROTECT_CHILD_CHG = 0x01,  /*禁用子更改信号。由图书馆使用*/
        LV_PROTECT_PARENT = 0x02,     /*防止自动父更改（例如在lv_page中）*/
        LV_PROTECT_POS = 0x04,        /*防止自动定位（例如在lv_cont布局中*/
        LV_PROTECT_FOLLOW = 0x08,     /*防止自动跟踪对象 订购（例如在lv_cont PRETTY布局中）*/
        LV_PROTECT_PRESS_LOST = 0x10, /*TODO */
    } lv_protect_t;

    /*由`lv_obj_get_type（）`使用。存储对象及其祖先类型*这里*/
    typedef struct
    {
        const char *type[LV_MAX_ANCESTOR_NUM]; /*[0]：实际类型，[1]：祖先，[2] ＃1的祖先... [x]：“lv_obj” */
    } lv_obj_type_t;

    typedef enum
    {
        LV_ALIGN_CENTER = 0,
        LV_ALIGN_IN_TOP_LEFT,
        LV_ALIGN_IN_TOP_MID,
        LV_ALIGN_IN_TOP_RIGHT,
        LV_ALIGN_IN_BOTTOM_LEFT,
        LV_ALIGN_IN_BOTTOM_MID,
        LV_ALIGN_IN_BOTTOM_RIGHT,
        LV_ALIGN_IN_LEFT_MID,
        LV_ALIGN_IN_RIGHT_MID,
        LV_ALIGN_OUT_TOP_LEFT,
        LV_ALIGN_OUT_TOP_MID,
        LV_ALIGN_OUT_TOP_RIGHT,
        LV_ALIGN_OUT_BOTTOM_LEFT,
        LV_ALIGN_OUT_BOTTOM_MID,
        LV_ALIGN_OUT_BOTTOM_RIGHT,
        LV_ALIGN_OUT_LEFT_TOP,
        LV_ALIGN_OUT_LEFT_MID,
        LV_ALIGN_OUT_LEFT_BOTTOM,
        LV_ALIGN_OUT_RIGHT_TOP,
        LV_ALIGN_OUT_RIGHT_MID,
        LV_ALIGN_OUT_RIGHT_BOTTOM,
    } lv_align_t;

    typedef enum
    {
        LV_ANIM_NONE = 0,
        LV_ANIM_FLOAT_TOP,    /*浮动自/到顶部*/
        LV_ANIM_FLOAT_LEFT,   /*从/向左浮动*/
        LV_ANIM_FLOAT_BOTTOM, /*从底部浮动*/
        LV_ANIM_FLOAT_RIGHT,  /*从/向右浮动*/
        LV_ANIM_GROW_H,       /*水平增长/收缩*/
        LV_ANIM_GROW_V,       /*垂直增长/缩小*/
    } lv_anim_builtin_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
 * Init. the 'lv' library.
 */
    void lv_init(void);

    /*--------------------
 * 创建和删除
 *-------------------*/

    /**
    * 创建一个基本对象
    * @param指向父对象的父指针。如果为NULL，则将创建一个屏幕
    * @param复制指向基础对象的指针，如果不是NULL，那么新对象将是从中复制
    * @return 指向新对象的指针
    */
    lv_obj_t *lv_obj_create(lv_obj_t *parent, lv_obj_t *copy);

    /**
    * 删除'obj'及其所有子女
    * @param obj指向要删除的对象的指针
    * @return LV_RES_INV因为该对象已被删除
    */
    lv_res_t lv_obj_del(lv_obj_t *obj);

    /**
    *删除对象的所有子项
    * @param obj指向对象的指针
 */
    void lv_obj_clean(lv_obj_t *obj);

    /**
    *将对象标记为无效，因此其当前位置将被重绘 'lv_refr_task'
    * @param obj指向对象的指针
 */
    void lv_obj_invalidate(lv_obj_t *obj);

    /*=====================
 * Setter functions
 *====================*/

    /*--------------
 * Screen set
 *--------------*/

    /**
    *加载新屏幕
    * @param scr指向屏幕的指针
 */
    void lv_scr_load(lv_obj_t *scr);

    /*--------------------
 * Parent/children set
 *--------------------*/

    /**
    *为对象设置新父级。它的相对位置是一样的。
     * @param obj指向对象的指针
     * @param指向新父对象的父指针
 */
    void lv_obj_set_parent(lv_obj_t *obj, lv_obj_t *parent);

    /*--------------------
 * Coordinate set
 * ------------------*/

    /**
    *设置相对位置的相对位置（相对于父级）
    * @param obj指向对象的指针
    * @param x距离父母左侧的新距离
    * @param与父母顶部的新距离
 */
    void lv_obj_set_pos(lv_obj_t *obj, lv_coord_t x, lv_coord_t y);

    /**
    *设置对象的x坐标
    * @param obj指向对象的指针
    * @param x距父母左侧的新距离
 */
    void lv_obj_set_x(lv_obj_t *obj, lv_coord_t x);

    /**
    *设置对象的y坐标
    * @param obj指向对象的指针
    * @param与父母顶部的新距离
 */
    void lv_obj_set_y(lv_obj_t *obj, lv_coord_t y);

    /**
    *设置对象的大小
    * @param obj指向对象的指针
    * @param w新宽度
    * @param h新高度
 */
    void lv_obj_set_size(lv_obj_t *obj, lv_coord_t w, lv_coord_t h);

    /**
    *设置对象的宽度
    * @param obj指向对象的指针
    * @param w新宽度
 */
    void lv_obj_set_width(lv_obj_t *obj, lv_coord_t w);

    /**
    *设置对象的高度
    * @param obj指向对象的指针
    * @param h新高度
 */
    void lv_obj_set_height(lv_obj_t *obj, lv_coord_t h);

    /**
    *将对象与其他对象对齐。
    * @param obj指向要对齐的对象的指针
    * @param指向对象的基指针（如果使用NULL则为NULL）。'obj'会与之对齐。
    * @param对齐类型（参见'lv_align_t'枚举）
    * @param x_mod x对齐后的坐标移位
    * @param y_mod y对齐后的坐标移位
 */
    void lv_obj_align(lv_obj_t *obj, lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod);

    /*---------------------
 * 外观设定
 *--------------------*/

    /**
    *为对象设置新样式
    * @param obj指向对象的指针
    * @param style_p指向新样式的指针
 */
    void lv_obj_set_style(lv_obj_t *obj, lv_style_t *style);

    /**
    *通知对象有关其样式的修改
    * @param obj指向对象的指针
 */
    void lv_obj_refresh_style(lv_obj_t *obj);

    /**
    *如果修改了样式，则通知所有对象
   * @param样式指针指向一个样式。只有具有此样式的对象才会出现通知
    *（NULL表示通知所有对象）)
 */
    void lv_obj_report_style_mod(lv_style_t *style);

    /*-----------------
 * 属性集
 *----------------*/

    /**
    *隐藏一个对象。它不可见且可点击。
     * @param obj指向对象的指针
     * @param zh_cn：隐藏对象
 */
    void lv_obj_set_hidden(lv_obj_t *obj, bool en);

    /**
    *   启用或禁用对象的单击
     * @param obj指向对象的指针
     * @param zh_cn：使对象可单击
 */
    void lv_obj_set_click(lv_obj_t *obj, bool en);

    /**
    *启用此选项可将此对象置于前台或点击其任何子女
     * @param obj指向对象的指针
     * @param zh_cn：启用自动顶部功能
 */
    void lv_obj_set_top(lv_obj_t *obj, bool en);

    /**
    *启用拖动对象
    * @param obj指向对象的指针
    * @param zh_cn：使对象可拖动
 */
    void lv_obj_set_drag(lv_obj_t *obj, bool en);

    /**
    *拖动后启用抛出对象
    * @param obj指向对象的指针
    * @param zh_cn：启用拖动投掷
 */
    void lv_obj_set_drag_throw(lv_obj_t *obj, bool en);

    /**
    *允许使用父级进行与拖动相关的操作。如果尝试拖动对象，则会移动父对象
    * @param obj指向对象的指针
    * @param zh_cn：为对象启用“拖动父级”
 */
    void lv_obj_set_drag_parent(lv_obj_t *obj, bool en);

    /**
    *在保护字段中设置一个或多个位
    * @param obj指向对象的指针
    *来自lv_obj_prot_t的@param prot'OR'-ed值
 */
    void lv_obj_set_protect(lv_obj_t *obj, uint8_t prot);

    /**
    *清除保护字段中的一个或多个位
    * @param obj指向对象的指针
    *来自lv_obj_prot_t的@param prot'OR'-ed值
 */
    void lv_obj_clear_protect(lv_obj_t *obj, uint8_t prot);

    /**
    *设置对象的信号功能。始终调用新的前一个信号功能。
    * @param obj指向对象的指针
    * @param fp新的信号功能
 */
    void lv_obj_set_signal_func(lv_obj_t *obj, lv_signal_func_t fp);

    /**
    *为对象设置新的设计功能
    * @param obj指向对象的指针
    * @param fp新的设计功能
 */
    void lv_obj_set_design_func(lv_obj_t *obj, lv_design_func_t fp);

    /*----------------
 * Other set
 *--------------*/

    /**
    *分配一个新的分机。对象的数据
     * @param obj指向对象的指针
    * @param ext_size新ext的大小。数据
     * @return指向分配的ext的正常指针
 */
    void *lv_obj_allocate_ext_attr(lv_obj_t *obj, uint16_t ext_size);

    /**
    *向对象发送'LV_SIGNAL_REFR_EXT_SIZE'信号
    * @param obj指向对象的指针
 */
    void lv_obj_refresh_ext_size(lv_obj_t *obj);

#ifdef LV_OBJ_FREE_NUM_TYPE
    /**
    *为对象设置特定于应用程序的编号。它可以帮助识别应用程序中的对象。
    * @param obj指向对象的指针
    * @param free_num新的免费号码
 */
    void lv_obj_set_free_num(lv_obj_t *obj, LV_OBJ_FREE_NUM_TYPE free_num);
#endif

#if LV_OBJ_FREE_PTR != 0
    /**
    *为对象设置特定于应用程序的指针。它可以帮助识别应用程序中的对象。
    * @param obj指向对象的指针
    * @param free_p新的免费品特
 */
    void lv_obj_set_free_ptr(lv_obj_t *obj, void *free_p);
#endif

#if USE_LV_ANIMATION
    /**
    *为对象设置动画
    * @param obj指向要设置动画的对象的指针来自'lv_anim_builtin_t'的@param类型的动画。'或'与ANIM_IN或ANIM_OUT
    * @param动画的时间，以毫秒为单位
    * @param在动画之前延迟延迟，以毫秒为单位
    * @param cb动画准备就绪时调用的函数
 */
    void lv_obj_animate(lv_obj_t *obj, lv_anim_builtin_t type, uint16_t time,
                        uint16_t delay, void (*cb)(lv_obj_t *));
#endif

    /*=======================
 * Getter functions
 *======================*/

    /*------------------
 * Screen get
 *-----------------*/

    /**
    *返回指向活动屏幕的指针
    * @return指向活动屏幕对象的指针（由'lv_scr_load（）'加载）
 */
    lv_obj_t *lv_scr_act(void);

    /**
    *返回顶层。（在每个屏幕上都相同，它高于正常值屏幕层）
     * @return指向顶层对象的指针（透明屏幕大小为lv_obj）
 */
    lv_obj_t *lv_layer_top(void);

    /**
    *返回系统层。（在每个屏幕上都相同，它在所有屏幕之上其他层）它用于例如光标
     * @return指向系统层对象的指针（透明屏幕大小为lv_obj）
 */
    lv_obj_t *lv_layer_sys(void);

    /**
    *返回对象的屏幕
    * @param obj指向对象的指针
    * @return指向屏幕的指针
 */
    lv_obj_t *lv_obj_get_screen(lv_obj_t *obj);

    /*---------------------
 * Parent/children get
 *--------------------*/

    /**
    *返回对象的父级
    * @param obj指向对象的指针
    * @return指向'obj'的父级
 */
    lv_obj_t *lv_obj_get_parent(lv_obj_t *obj);

    /**
    *迭代一个物体的孩子（从“最年轻的，最后的创建“）
    * @param obj指向对象的指针
    * @param child NULL在第一次调用时获取下一个孩子和之前的返回值
    * @在'act_child'之后返回孩子，如果没有更多孩子，则返回NULL
 */
    lv_obj_t *lv_obj_get_child(lv_obj_t *obj, lv_obj_t *child);

    /**
    *通过对象的子项进行迭代（首先从“最老的”开始已创建）
    * @param obj指向对象的指针
    * @param child NULL在第一次调用时获取下一个孩子和之前的返回值
    * @在'act_child'之后返回孩子，如果没有更多孩子，则返回NULL
 */
    lv_obj_t *lv_obj_get_child_back(lv_obj_t *obj, lv_obj_t *child);

    /**
    *计算一个物体的孩子（只有孩子直接在'obj'）
    * @param obj指向对象的指针
    * @return儿童号'obj'
 */
    uint16_t lv_obj_count_children(lv_obj_t *obj);

    /*---------------------
 * Coordinate get
 *--------------------*/

    /**
    *将对象的坐标复制到某个区域
    * @param obj指向对象的指针
    * @param cords_p指向存储坐标的区域的指针
 */
    void lv_obj_get_coords(lv_obj_t *obj, lv_area_t *cords_p);

    /**
    *获取对象的x坐标
    * @param obj指向对象的指针
    * @ obj'从其父级左侧返回距离
 */
    lv_coord_t lv_obj_get_x(lv_obj_t *obj);

    /**
    *获取对象的y坐标
    * @param obj指向对象的指针
    * @ obj'从其父级顶部返回距离
 */
    lv_coord_t lv_obj_get_y(lv_obj_t *obj);

    /**
    *获取对象的宽度
    * @param obj指向对象的指针
    * @return宽度
 */
    lv_coord_t lv_obj_get_width(lv_obj_t *obj);

    /**
    *获取物体的高度
    * @param obj指向对象的指针
    * @return高度
 */
    lv_coord_t lv_obj_get_height(lv_obj_t *obj);

    /**
    *获取对象的扩展大小属性
    * @param obj指向对象的指针
    * @return扩展大小属性
 */
    lv_coord_t lv_obj_get_ext_size(lv_obj_t *obj);

    /*-----------------
 * 外观得到
 *---------------*/

    /**
    *获取对象的样式指针（如果NULL获取父项的样式）
    * @param obj指向对象的指针
    * @return指向一个样式
 */
    lv_style_t *lv_obj_get_style(lv_obj_t *obj);

    /*-----------------
*属性获取
 *----------------*/

    /**
    *获取对象的隐藏属性
    * @param obj指向对象的指针
    * @return true：隐藏对象
 */
    bool lv_obj_get_hidden(lv_obj_t *obj);

    /**
    *获取对象的单击启用属性
    * @param obj指向对象的指针
    * @return true：对象是可点击的
 */
    bool lv_obj_get_click(lv_obj_t *obj);

    /**
    *获取对象的top enable属性
    * @param obj指向对象的指针
    * @return true：启用自动顶部胎儿
 */
    bool lv_obj_get_top(lv_obj_t *obj);

    /**
    *获取对象的拖动启用属性
    * @param obj指向对象的指针
    * @return true：对象是可拖动的
 */
    bool lv_obj_get_drag(lv_obj_t *obj);

    /**
    *获取对象的drag thow enable属性
    * @param obj指向对象的指针
    * @return true：启用拖动抛出
 */
    bool lv_obj_get_drag_throw(lv_obj_t *obj);

    /**
    *获取对象的拖动父属性
    * @param obj指向对象的指针
    * @return true：启用拖动父级
 */
    bool lv_obj_get_drag_parent(lv_obj_t *obj);

    /**
    *获取对象的保护字段
    * @param obj指向对象的指针
    * @return保护字段（'OR'值lv_obj_prot_t）
 */
    uint8_t lv_obj_get_protect(lv_obj_t *obj);

    /**
    *检查给定保护位域的至少一位是否已设置
    * @param obj指向对象的指针
    * @param prot保护要测试的位（'或'lv_obj_prot_t的值）
    * @return false：没有设置给定的位，为true：至少设置一位
 */
    bool lv_obj_is_protected(lv_obj_t *obj, uint8_t prot);

    /**
    *获取对象的信号功能
    * @param obj指向对象的指针
    * @return信号功能
 */
    lv_signal_func_t lv_obj_get_signal_func(lv_obj_t *obj);

    /**
    *获取对象的设计功能
    * @param obj指向对象的指针
    * @return设计功能
 */
    lv_design_func_t lv_obj_get_design_func(lv_obj_t *obj);

    /*------------------
 * Other get
 *-----------------*/

    /**
    *获取ext指针
    * @param obj指向对象的指针
    * @return ext指针但不是动态版本
    *将它用作ext-> data1，而不是da（ext） - > data1
 */
    void *lv_obj_get_ext_attr(lv_obj_t *obj);

    /**
    *获取对象及其祖先类型。把他们的名字放在`type_buf`开头与当前类型。
     *例如buf.type [0] =“lv_btn”，buf.type [1] =“lv_cont”，buf.type [2] =“lv_obj”
     * @param obj指向应该获取类型的对象的指针
     * @param buf指向`lv_obj_type_t`缓冲区以存储类型
 */
    void lv_obj_get_type(lv_obj_t *obj, lv_obj_type_t *buf);

#ifdef LV_OBJ_FREE_NUM_TYPE
    /**
    *获取免费电话号码
    * @param obj指向对象的指针
    * @return免费号码
 */
    LV_OBJ_FREE_NUM_TYPE lv_obj_get_free_num(lv_obj_t *obj);
#endif

#if LV_OBJ_FREE_PTR != 0
    /**
    *获取免费指针
    * @param obj指向对象的指针
    * @return自由指针
 */
    void *lv_obj_get_free_ptr(lv_obj_t *obj);
#endif

#if USE_LV_GROUP
    /**
    *获取对象的组
    * @param obj指向对象的指针
    * @return指向对象组的指针t
 */
    void *lv_obj_get_group(lv_obj_t *obj);
#endif

/**********************
 *      MACROS
 **********************/
#define LV_SCALE(x) (x << LV_ANTIALIAS)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_OBJ_H*/
