/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-13T14:24:59+08:00
 */

#ifndef LV_STYLE_H
#define LV_STYLE_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_misc/lv_anim.h"
#include "display/lv_misc/lv_area.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_misc/lv_font.h"
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#define LV_RADIUS_CIRCLE (LV_COORD_MAX) /*一个非常大的半径，总是绘制为圆*/

    /**********************
 *      TYPEDEFS
 **********************/

    /**边框类型（使用'或'值）*/
    typedef enum
    {
        LV_BORDER_NONE = 0x00,
        LV_BORDER_BOTTOM = 0x01,
        LV_BORDER_TOP = 0x02,
        LV_BORDER_LEFT = 0x04,
        LV_BORDER_RIGHT = 0x08,
        LV_BORDER_FULL = 0x0F,
    } lv_border_part_t;

    /*暗影类型*/
    typedef enum
    {
        LV_SHADOW_BOTTOM = 0,
        LV_SHADOW_FULL,
    } lv_shadow_type_t;

    typedef struct
    {
        uint8_t glass : 1; /*1: 1：不要继承这种风*/

        struct
        {
            lv_color_t main_color; //主要颜色（顶部颜色）
            lv_color_t grad_color; //渐变色（底色）
            lv_coord_t radius;     //转角半径。（设置为LV_RADIUS_CIRCLE绘制圆圈）
            lv_opa_t opa;          //Opacity（0..255或LV_OPA_TRANSP，LV_OPA_10，LV_OPA_20 ...... LV_OPA_COVER）

            struct
            {
                lv_color_t color;      //边框颜色
                lv_coord_t width;      //边框宽度
                lv_border_part_t part; //t边框部分（LV_BORDER_LEFT / RIGHT / TOP / BOTTOM / FULL或'OR'ed值）
                lv_opa_t opa;          //边界不透明度
            } border;                  //边框

            struct
            {
                lv_color_t color; //阴影颜色
                lv_coord_t width; //阴影宽度
                uint8_t type;     //阴影类型（LV_SHADOW_BOTTOM或LV_SHADOW_FULL）
            } shadow;             //印象

            struct
            {
                lv_coord_t ver;   //垂直填充
                lv_coord_t hor;   //水平填充
                lv_coord_t inner; //内部填充
            } padding;

            uint8_t empty : 1; /*透明背景（仍绘制边框）*/
        } body;                //身体风格属性

        struct
        {
            lv_color_t color;        //文字颜色
            const lv_font_t *font;   //指向字体的指针
            lv_coord_t letter_space; //字母空间
            lv_coord_t line_space;   //行间距
            lv_opa_t opa;            //文本不透明度（0..255或LV_OPA_TRANSP，LV_OPA_10，LV_OPA_20 ... LV_OPA_COVER）
        } text;                      //文本样式属性

        struct
        {
            lv_color_t color; //基于像素亮度的图像重新着色的颜色
            lv_opa_t intense; //重色强度（0..255或LV_OPA_TRANSP，LV_OPA_10，LV_OPA_20 ...... LV_OPA_COVER）
            lv_opa_t opa;     //图像不透明度（0..255或LV_OPA_TRANSP，LV_OPA_10，LV_OPA_20 ... LV_OPA_COVER）
        } image;              //图像样式属性

        struct
        {
            lv_color_t color; //线条颜色
            lv_coord_t width; //线宽
            lv_opa_t opa;     //线不透明度（0..255或LV_OPA_TRANSP，LV_OPA_10，LV_OPA_20 ...... LV_OPA_COVER）
        } line;               //线条样式属性
    } lv_style_t;

#if USE_LV_ANIMATION
    typedef struct
    {
        const lv_style_t *style_start; /*指向起始样式*/
        const lv_style_t *style_end;   /*指向目标样式的指针*/
        lv_style_t *style_anim;        /*指向动画样式的指针*/
        lv_anim_cb_t end_cb;           /*在动画准备就绪时调用它（如果未使用则为NULL）*/
        int16_t time;                  /*以ms为单位的动画时间*/
        int16_t act_time;              /*动画中的当前时间。设为负值以延迟*/
        uint16_t playback_pause;       /*等待回放*/
        uint16_t repeat_pause;         /*等待重复*/
        uint8_t playback : 1;          /*动画准备好后再播放*/
        uint8_t repeat : 1;            /*无限重复动画*/
    } lv_style_anim_t;                 //风格动画

/* 示例初始化
lv_style_anim_t a;
a.style_anim = &style_to_anim;
a.style_start = &style_1;
a.style_end = &style_2;
a.act_time = 0;
a.time = 1000;
a.playback = 0;
a.playback_pause = 0;
a.repeat = 0;
a.repeat_pause = 0;
a.end_cb = NULL;
lv_style_anim_create(&a);
 */
#endif

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
 *  初始化基本款式
 */
    void lv_style_init(void);

    /**
    *将样式复制到另一个
    * @param dest指向目标样式的指针
    * @param src指向源样式的指针
 */
    void lv_style_copy(lv_style_t *dest, const lv_style_t *src);

#if USE_LV_ANIMATION
    /**
    *从预先配置的'lv_style_anim_t'变量创建动画
    * @param anim指向预先配置的'lv_style_anim_t'变量的指针（将是
    *复制）
 */
    void lv_style_anim_create(lv_style_anim_t *anim);
#endif

    /*************************
 *    GLOBAL VARIABLES
 *************************/
    extern lv_style_t lv_style_scr;
    extern lv_style_t lv_style_transp;
    extern lv_style_t lv_style_transp_fit;
    extern lv_style_t lv_style_transp_tight;
    extern lv_style_t lv_style_plain;
    extern lv_style_t lv_style_plain_color;
    extern lv_style_t lv_style_pretty;
    extern lv_style_t lv_style_pretty_color;
    extern lv_style_t lv_style_btn_rel;
    extern lv_style_t lv_style_btn_pr;
    extern lv_style_t lv_style_btn_tgl_rel;
    extern lv_style_t lv_style_btn_tgl_pr;
    extern lv_style_t lv_style_btn_ina;

    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_STYLE_H*/
