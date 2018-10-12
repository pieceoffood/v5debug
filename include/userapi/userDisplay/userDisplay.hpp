/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-12T12:34:46+08:00
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
    lv_style_t *nowStyle = &redStyle;
    //标题栏
    lv_obj_t *loopTimeLab = nullptr;
    //弹窗
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
extern UserDisplay userDisplay;

/**
 * 自动赛选择时候的确认按钮的动作
 * @param  btn 要实现动作的按钮的指针
 * @return     返回不知道啥....
 */
static lv_res_t confirmBtnIncomp(lv_obj_t *btn)
{
    char autoInfo[256];
    const char *side;
    const char *fr;
    const char *shootH_M;
    const char *isShootMid;
    const char *plat;
    const char *bumper;
    sysData.autoSide == 0 ? side = "red" : side = "blue";
    sysData.autoIsFR == 0 ? fr = "front" : fr = "back";
    sysData.autoIsFlag == 0 ? shootH_M = "high" : shootH_M = "middle";
    sysData.autoIsShootFlag == 0 ? isShootMid = "don't shoot mid flag!" : isShootMid = "shoot mid flag";
    sysData.autoIsRunPlat == 0 ? plat = "dont' run to plat" : plat = "run to plat";
    sysData.autoIsBumperFlag == 0 ? bumper = "dont't bumper flag" : bumper = " bumper flag";

    lv_obj_del(userDisplay.competitionPage);
    userDisplay.tempPage = lv_obj_create(nullptr, nullptr);
    lv_page_set_style(userDisplay.tempPage, LV_PAGE_STYLE_BG, userDisplay.nowStyle); //指针传不过去啊...
    //显示自动赛选项
    lv_obj_t *autoinfoLab = lv_label_create(userDisplay.tempPage, NULL);
    sprintf(autoInfo, ":%s\n%s\n%s\n%s\n%s\n%s", side, fr, shootH_M, isShootMid, plat, bumper);
    lv_label_set_text(autoinfoLab, autoInfo);
    // lv_obj_t *sensorsLab = lv_label_create(userDisplay.tempPage, NULL);
    // lv_label_set_text(sensorsLab, "gyro:");
    //TODO 传感器都放上

    std::cout << "pressed" << std::endl;
    return LV_RES_OK;
}
#endif /* end of include guard: USERDISPLAY_HPP_ */
