/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-11T10:52:29+08:00
 */
#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_

#include "api.h"
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include <cstdio>

class UserDisplay
{
  private:
    //样式
    lv_theme_t *_theme;

  public:
    //页面
    lv_obj_t *competitionPage = nullptr;
    lv_obj_t *opcontrolPage = nullptr;
    lv_obj_t *initPage = nullptr;
    lv_obj_t *disabledPage = nullptr;
    lv_obj_t *autonomousPage = nullptr;
    //样式
    lv_style_t redStyle;
    lv_style_t blueStyle;
    //标题栏
    lv_obj_t *loopTimeLab = nullptr;
    UserDisplay()
    {
        /*初始化外星人主题
        * 210：绿色色调值
        * NULL: 使用默认字体 (LV_FONT_DEFAULT)*/
        _theme = lv_theme_alien_init(210, NULL);
        /*设置Surand系统主题*/
        lv_theme_set_current(_theme);
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
#endif /* end of include guard: USERDISPLAY_HPP_ */
