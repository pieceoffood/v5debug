/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-14T16:15:36+08:00
 */
#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_

#include "api.h"
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include "userapi\systemData.hpp"

class UserDisplay
{
  private:
    int _maxLoopTime = 0;
    int _minLoopTime = 20;
    char _buf_long[256];

  public:
    //样式
    lv_theme_t *theme;
    //页面
    lv_obj_t *competitionPage = nullptr;
    lv_obj_t *opcontrolPage = nullptr;
    lv_obj_t *initPage = nullptr;
    lv_obj_t *disabledPage = nullptr;
    lv_obj_t *autonomousPage = nullptr;
    lv_obj_t *tempPage = nullptr;

    //标题栏
    lv_obj_t *loopTimeLab = nullptr;
    //弹窗
    UserDisplay()
    {
        //增加自定义字库
        lv_font_add(&myfont, NULL);
        /*初始化外星人主题*/
        theme = lv_theme_alien_init(100, &myfont);
        /*设置Surand系统主题*/
        lv_theme_set_current(theme);
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
    void startPage(lv_obj_t *para)
    {
        static const char *btnm_map[] = {"在线检测", "机器人检测", "\n",
                                         "自动赛", "手动赛", "\n",
                                         "前后PID", "旋转PID", "\n",
                                         "ODOM测试", "自定义测试", ""};

        lv_obj_t *btnm = lv_btnm_create(para, NULL); //创建按钮集群
        lv_btnm_set_map(btnm, btnm_map);
        lv_obj_set_size(btnm, LV_HOR_RES, LV_VER_RES - 30);
        lv_obj_set_y(btnm, 30);
    }
    void loopTime(const int loopTime)
    {
        if (loopTime > _maxLoopTime)
            _maxLoopTime = loopTime;
        if (loopTime < _minLoopTime)
            _minLoopTime = loopTime;
        sprintf(_buf_long, "loop:%d max:%d min:%d\n", loopTime, _maxLoopTime, _minLoopTime);
        lv_label_set_text(loopTimeLab, _buf_long);
    }
};

extern UserDisplay userDisplay;
#endif /* end of include guard: USERDISPLAY_HPP_ */
