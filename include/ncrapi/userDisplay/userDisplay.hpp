/**
 * @Author: 陈昱安
 * @Date:   2018-10-11T21:09:49+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-23T23:42:59+08:00
 */

#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_
#include "display/lv_conf.h"
#include "display/lvgl.h"
extern lv_font_t myfont;
class UserDisplay
{
  public:
    //样式
    lv_theme_t *theme;
    //对象
    lv_obj_t *competitionObj = nullptr;
    lv_obj_t *opcontrolObj = nullptr;
    lv_obj_t *disabledObj = nullptr;
    lv_obj_t *autonomousObj = nullptr;
    lv_obj_t *confirmObj = nullptr;
    lv_obj_t *sensorsInfoObj = nullptr;
    //按钮阵列
    lv_obj_t *startBTNM = nullptr;
    //标题栏
    lv_obj_t *sensorsLab = nullptr;
    lv_obj_t *loopLab = nullptr;
    //线程
    lv_task_t *refr_task = nullptr;
    lv_task_t *loop_task = nullptr;
    //时间变量
    uint32_t loopTime = 0;
    uint32_t maxLoopTime = 0;
    uint32_t minLoopTime = 20;
    UserDisplay();

    void delObjs();
    void createAutoObj();
    void createCompObj();
    void createDisObj();
    void createOpObj();
    void createStartObj();
    void creartSensorsInfo(lv_obj_t *parent, int width);
};
extern UserDisplay userDisplay;

#endif /* end of include guard: USERDISPLAY_HPP_ */
