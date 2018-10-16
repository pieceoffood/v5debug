/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:27:48+08:00
 */
#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_
#include "display/lv_conf.h"
#include "display/lvgl.h"
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
    lv_obj_t *disabledPage = nullptr;
    lv_obj_t *autonomousPage = nullptr;
    lv_obj_t *confirmPage = nullptr;
    lv_obj_t *sensorsInfoPage = nullptr;
    //按钮阵列
    lv_obj_t *startBTNM = nullptr;
    //标题栏
    lv_obj_t *loopTimeLab = nullptr;
    lv_obj_t *sensorsLab = nullptr;
    //线程
    lv_task_t *refr_task = nullptr;
    //临时char型存储

    UserDisplay();

    void loopTime(const int loopTime);
    void delPages();
    void delAutoPages();
    void delOpPages();
    void createAutoPage();
    void createCompPage();
    void createDisPage();
    void createOpPage();
    void createStartPage();
    void creartSensorsInfo(lv_obj_t *parent, int width);
};
extern UserDisplay userDisplay;

#endif /* end of include guard: USERDISPLAY_HPP_ */
