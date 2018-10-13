/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-13T11:03:43+08:00
 */
#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_

#include "api.h"
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include "userapi\systemData.hpp"

class UserDisplay
{
  public:
    //样式
    lv_theme_t *_theme;
    //页面
    lv_obj_t *competitionPage = nullptr;
    lv_obj_t *opcontrolPage = nullptr;
    lv_obj_t *initPage = nullptr;
    lv_obj_t *disabledPage = nullptr;
    lv_obj_t *autonomousPage = nullptr;
    lv_obj_t *tempPage = nullptr;
    //样式
    lv_style_t redStyle;
    lv_style_t blueStyle;
    lv_style_t fontStyle; //字体样式
    lv_style_t *nowStyle = &redStyle;

    //标题栏
    lv_obj_t *loopTimeLab = nullptr;
    //弹窗
    UserDisplay()
    {
        /*初始化外星人主题
        * 210：绿色色调值
        * NULL: 使用默认字体 (LV_FONT_DEFAULT)*/
        _theme = lv_theme_alien_init(100, NULL);
        /*设置Surand系统主题*/
        lv_theme_set_current(_theme);
        //增加自定义字库
        lv_font_add(&myfont, NULL);
        lv_style_copy(&fontStyle, &lv_style_plain);
        fontStyle.text.font = &myfont;
        //创建页面
        initPage = lv_obj_create(nullptr, nullptr);
        disabledPage = lv_obj_create(nullptr, nullptr);
        autonomousPage = lv_obj_create(nullptr, nullptr);
        opcontrolPage = lv_obj_create(nullptr, nullptr);
        competitionPage = lv_obj_create(nullptr, nullptr);
        //创建标题栏
        loopTimeLab = lv_label_create(opcontrolPage, nullptr);
        lv_obj_align(loopTimeLab, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
    }
};
extern UserDisplay userDisplay;

#endif /* end of include guard: USERDISPLAY_HPP_ */
