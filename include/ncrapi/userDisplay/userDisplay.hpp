/**
 * @Author: 陈昱安
 * @Date:   2018-10-11T21:09:49+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T21:54:48+08:00
 */

#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include <array>
extern lv_font_t myfont;
typedef enum obj_flag
{
    OBJ_COMPETITION,
    OBJ_DISABLED,
    OBJ_AUTONOMOUS,
    OBJ_OPCONTROL,
    OBJ_CONFIRM,     //从这里开始下面都无法lv_load_src(),因为是依附状态
    OBJ_SENSORSINFO, //传感器页面
    BTNM_START,      //按钮阵列
    LAB_SENSORS,
    LAB_LOOP
} obj_flag;

typedef enum task_flag
{
    TASK_REFR, //传感器页面的TASK
    TASK_LOOP  //记录遥控模式下LOOP的TASK
} task_flag;

class UserDisplay
{
  public:
    //样式
    lv_theme_t *theme;
    std::array<lv_obj_t *, 7> displayObj = {nullptr};   //对象
    std::array<lv_task_t *, 2> displayTask = {nullptr}; //线程
    //标题栏
    lv_obj_t *sensorsLab = nullptr;
    lv_obj_t *loopLab = nullptr;
    //时间变量
    uint32_t loopTime = 0;
    uint32_t maxLoopTime = 0;
    uint32_t minLoopTime = 20;
    UserDisplay();
    void delObjs();
    void delTasks();
    void createUserObj(obj_flag objname, bool isSrcLoad, const char *terminalText, const char *labText = nullptr);
    void createUserTask(task_flag taskName, void (*task)(void *), uint32_t loopTime, const char *terminalText);
    void createOpObj();
    void createStartObj();
    void creartSensorsInfo(lv_obj_t *parent, int width);
};
extern UserDisplay userDisplay;

#endif /* end of include guard: USERDISPLAY_HPP_ */
