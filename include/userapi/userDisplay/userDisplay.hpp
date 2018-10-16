/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T13:41:34+08:00
 */
#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_
#include "display/lv_conf.h"
#include "display/lvgl.h"
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
    unsigned long loopTime = 0;
    int maxLoopTime = 0;
    int minLoopTime = 20;
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
