/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T17:36:20+08:00
 */

/**
 * @file lv_btnm.h
 *
 */

#ifndef LV_BTNM_H
#define LV_BTNM_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_BTNM != 0

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_label.h"

/*********************
 *      DEFINES
 *********************/

/*控制字节*/
#define LV_BTNM_CTRL_CODE \
    0x80 /*The control byte has to begin (if present) with 0b10xxxxxx*/
#define LV_BTNM_CTRL_MASK 0xC0
#define LV_BTNM_WIDTH_MASK 0x07
#define LV_BTNM_HIDE_MASK 0x08
#define LV_BTNM_REPEAT_DISABLE_MASK 0x10
#define LV_BTNM_INACTIVE_MASK 0x20

    /**********************
 *      TYPEDEFS
 **********************/

    /*释放按钮或长按时调用的回调函数的类型
 *按下按钮矩阵
 *参数：按钮矩阵，已释放按钮的文本
 *如果按钮矩阵被删除，则返回LV_ACTION_RES_INV
*LV_ACTION_RES_OK*/
 typedef lv_res_t (*lv_btnm_action_t)(lv_obj_t *, const char *txt);

/*按钮矩阵的数据*/
    typedef struct
    {
        /*没有继承的ext。*/ /*分机 祖先*/
        /*此类型的新数据 */
        const char **map_p;                       /*指向当前地图的指针*/
        lv_area_t *button_areas;                  /*按钮区域数组*/
        lv_btnm_action_t action;                  /*释放按钮时调用的函数*/
        lv_style_t *styles_btn[LV_BTN_STATE_NUM]; /*每个州的按钮样式*/
        uint16_t btn_cnt;                         /*'map_p'中的按钮数量（由库处理）*/
        uint16_t btn_id_pr;                       /*当前按下的按钮的索引（in`button_areas`）或LV_BTNM_PR_NONE */
        uint16_t btn_id_tgl;                      /*当前切换按钮的索引（in`button_areas`）或LV_BTNM_PR_NONE */
        uint8_t toggle : 1;                       /*启用切换*/
    } lv_btnm_ext_t;

    typedef enum
    {
        LV_BTNM_STYLE_BG,
        LV_BTNM_STYLE_BTN_REL,
        LV_BTNM_STYLE_BTN_PR,
        LV_BTNM_STYLE_BTN_TGL_REL,
        LV_BTNM_STYLE_BTN_TGL_PR,
        LV_BTNM_STYLE_BTN_INA,
    } lv_btnm_style_t;

    /**********************
 * 全局模型
 **********************/

    /**
    *创建一个按钮矩阵对象
     * @param par指向一个对象的指针，它将是新按钮的父指针
     *矩阵
     * @param复制指针到一个按钮矩阵对象，如果不是NULL那么新的
     *对象将从中复制
     * @return指向创建的按钮矩阵的指针
 */
    lv_obj_t *lv_btnm_create(lv_obj_t *par, lv_obj_t *copy);

    /*=====================
 *  Setter功能
 *====================*/

    /**
    *设置一张新地图。将根据地图创建/删除按钮。
     * @param btnm指向按钮矩阵对象的指针
    * @param map指针一个字符串数组。最后一个字符串必须是：“”。
     *使用“\ n”开始新行。
     *第一个字节可以是控制数据：
     *  - 第7位：始终为1
     *  - 第6位：始终为0
     *  - 第5位：无效（禁用）
     *  - 第4位：不重复（长按）
     *  - 第3位：隐藏
     *  - 位2..0：按钮相对宽度
     *示例（实际使用八进制数）：“\ 224abc”：“abc”文本
     * 4宽，无长按
 */
    void lv_btnm_set_map(lv_obj_t *btnm, const char **map);

    /**
    *为按钮设置一个新的回调函数（当按钮时会调用它
    * 发行了）
    * @param btnm：指向按钮矩阵对象的指针
    * @param动作指向回调函数
 */
    void lv_btnm_set_action(lv_obj_t *btnm, lv_btnm_action_t action);

    /**
    *启用或禁用按钮切换
   * @param btnm指向按钮矩阵对象的指针
  * @param zh_cn：启用切换; false：禁用切换
   * @param id当前切换按钮的索引（如果'en'== false则忽略）
 */
    void lv_btnm_set_toggle(lv_obj_t *btnm, bool en, uint16_t id);

    /**
    *设置按钮矩阵的样式
   * @param btnm指向按钮矩阵对象的指针
   * @param类型应该设置哪种样式
   * @param样式指针指向一个样式
 */
    void lv_btnm_set_style(lv_obj_t *btnm, lv_btnm_style_t type, lv_style_t *style);

    /*=====================
 * 吸气功能
 *====================*/

    /**
    *获取按钮矩阵的当前地图
     * @param btnm指向按钮矩阵对象的指针
     * @return当前地图
 */
    const char **lv_btnm_get_map(lv_obj_t *btnm);

    /**
    *获取按钮矩阵上按钮的回调函数
   * @param btnm：指向按钮矩阵对象的指针
   * @return指向回调函数的指针
 */
    lv_btnm_action_t lv_btnm_get_action(lv_obj_t *btnm);

    /**
    *获取切换按钮
    * @param btnm指向按钮矩阵对象的指针
    *当前切换按钮的@return索引（0：如果未设置）
 */
    uint16_t lv_btnm_get_toggled(lv_obj_t *btnm);

    /**
    *获得按钮矩阵的样式
    * @param btnm指向按钮矩阵对象的指针
    * @param类型应该获得哪种风格
    * @return样式指针指向一个样式
 */
    lv_style_t *lv_btnm_get_style(lv_obj_t *btnm, lv_btnm_style_t type);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_BTNM*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_BTNM_H*/
