/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T17:48:43+08:00
 */

/**
 * @file lv_chart.h
 *
 */

#ifndef LV_CHART_H
#define LV_CHART_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_CHART != 0

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_line.h"

    /*********************
 *      DEFINES
 *********************/

    /**********************
 *      TYPEDEFS
 **********************/
    typedef struct
    {
        lv_coord_t *points;
        lv_color_t color;
    } lv_chart_series_t;

    /*图表数据 */
    typedef struct
    {
        /*没有继承的ext*/ /*Ext。祖先*/
        /*此类型的新数据 */
        lv_ll_t series_ll;  /*数据行指针的链接列表（商店lv_chart_dl_t）*/
        lv_coord_t ymin;    /* y min值（用于缩放数据）*/
        lv_coord_t ymax;    /*y max value（用于缩放数据）*/
        uint8_t hdiv_cnt;   /*水平分割线数量*/
        uint8_t vdiv_cnt;   /*垂直分割线数量*/
        uint16_t point_cnt; /*数据行中的点号*/
        uint8_t type : 3;   /*行，列或点图表（来自'lv_chart_type_t'）*/
        struct
        {
            lv_coord_t width; /*线宽或点半径*/
            uint8_t num;      /*dl_ll中的数据行数*/
            lv_opa_t opa;     /*数据线的不透明度*/
            lv_opa_t dark;    /*点/柱底的暗层*/
        } series;
    } lv_chart_ext_t;

    /*图表类型*/
    typedef enum
    {
        LV_CHART_TYPE_LINE = 0x01,
        LV_CHART_TYPE_COLUMN = 0x02,
        LV_CHART_TYPE_POINT = 0x04,
    } lv_chart_type_t;

    /**********************
 * 全局模型
 **********************/

    /**
    *创建图表背景对象
   * @param par指向一个对象的指针，它将是新图表的父级
   * 背景
   * @param复制指向图表背景对象的指针，如果不是NULL那么新的
   *对象将从中复制
   * @return指向创建的图表背景的指针
 */
    lv_obj_t *lv_chart_create(lv_obj_t *par, lv_obj_t *copy);

    /*======================
*添加/删除功能
 *=====================*/

    /**
    *为图表分配并添加数据系列
     * @param图表指向图表对象的指针
     *数据系列的@param颜色
     * @return指向已分配数据系列的指针
 */
    lv_chart_series_t *lv_chart_add_series(lv_obj_t *chart, lv_color_t color);

    /*=====================
 * Setter功能
 *====================*/

    /**
    *设置水平和垂直分割线的数量
   * @param图表指向图形背景对象的指针
   * @param hdiv水平分割线的数量
   * @param vdiv垂直分割线数
 */
    void lv_chart_set_div_line_count(lv_obj_t *chart, uint8_t hdiv, uint8_t vdiv);

    /**
    *设置最小和最大y值
   * @param图表指向图形背景对象的指针
   * @param ymin y最小值
   * @param ymax y最大值
 */
    void lv_chart_set_range(lv_obj_t *chart, lv_coord_t ymin, lv_coord_t ymax);

    /**
    *为图表设置新类型
   * @param图表指向图表对象的指针
   * @param键入新类型的图表（来自'lv_chart_type_t'枚举）
 */
    void lv_chart_set_type(lv_obj_t *chart, lv_chart_type_t type);

    /**
    *设置图表数据行上的点数
    * @param图表指针r到图表对象
    * @param point_cnt数据行上的新点数
 */
    void lv_chart_set_point_count(lv_obj_t *chart, uint16_t point_cnt);

    /**
    *设置数据系列的不透明度
     * @param图表指向图表对象的指针
     * @param opa数据系列的不透明度
 */
    void lv_chart_set_series_opa(lv_obj_t *chart, lv_opa_t opa);

    /**
    *使用值初始化所有数据点
    * @param图表指向图表对象
    * @param ser指向“图表”上数据系列的指针
    * @param y所有积分的新值
 */
    void lv_chart_set_series_width(lv_obj_t *chart, lv_coord_t width);

    /**
    *在点或列的底部设置暗效果
   * @param图表指向图表对象的指针
   * @param dark_eff暗效电平（LV_OPA_TRANSP关闭）
 */
    void lv_chart_set_series_darking(lv_obj_t *chart, lv_opa_t dark_eff);

    /**
    *使用值初始化所有数据点
   * @param图表指向图表对象
   * @param ser指向“图表”上数据系列的指针
   * @param y所有积分的新值
 */
    void lv_chart_init_points(lv_obj_t *chart, lv_chart_series_t *ser,
                              lv_coord_t y);

    /**
    *设置数组中点的值s
    * @param图表指向图表对象
    * @param ser指向“图表”上数据系列的指针
    * @param y_array'lv_coord_t'点数组（带'点数'元素）
 */
    void lv_chart_set_points(lv_obj_t *chart, lv_chart_series_t *ser,
                             lv_coord_t *y_array);

    /**
    *正确移位所有数据并在数据线上设置最正确的数据
    * @param图表指向图表对象
    * @param ser指向“图表”上数据系列的指针
    * @param y最正确数据的新值
 */
    void lv_chart_set_next(lv_obj_t *chart, lv_chart_series_t *ser, lv_coord_t y);

    /**
    *设置图表的样式
   * @param图表指向图表对象的指针
   * @param样式指针指向一个样式
 */
    static inline void lv_chart_set_style(lv_obj_t *chart, lv_style_t *style)
    {
        lv_obj_set_style(chart, style);
    }

    /*=====================
 * 吸气功能
 *====================*/

    /**
    *获取图表的类型
   * @param图表指向图表对象
   * @return类型的图表（来自'lv_chart_t'枚举）
 */
    lv_chart_type_t lv_chart_get_type(lv_obj_t *chart);

    /**
    *获取图表上每条数据线的数据点数
    * @param图表指向图表对象
    * @return点数在每条数据线上
 */
    uint16_t lv_chart_get_point_cnt(lv_obj_t *chart);

    /**
    *获取数据系列的不透明度
   * @param图表指向图表对象
   * @return数据系列的不透明度
 */
    lv_opa_t lv_chart_get_series_opa(lv_obj_t *chart);

    /**
    *获取数据系列宽度
    * @param图表指向图表对象
    * @return数据系列的宽度（线或点）
 */
    lv_coord_t lv_chart_get_series_width(lv_obj_t *chart);

    /**
    *在点或列的底部获得暗效果级别
   * @param图表指向图表对象
   * @return暗效果等级（LV_OPA_TRANSP关闭）
 */
    lv_opa_t lv_chart_get_series_darking(lv_obj_t *chart);

    /**
    *获取图表对象的样式
    * @param图表指向图表对象的指针
    * @return指向图表样式的指针
 */
    static inline lv_style_t *lv_chart_get_style(lv_obj_t *chart)
    {
        return lv_obj_get_style(chart);
    }

    /*=====================
 *其他功能
 *====================*/

    /**
    *如果数据行已更改，请刷新图表
     * @param图表指向图表对象
 */
    void lv_chart_refresh(lv_obj_t *chart);

    /**********************
 *      MACROS
 **********************/

#endif /*USE_LV_CHART*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_CHART_H*/
