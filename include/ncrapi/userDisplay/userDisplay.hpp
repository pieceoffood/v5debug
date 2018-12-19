#pragma once
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include <array>
#include <iostream>
#include <sstream>
extern lv_font_t ncrfont10;
// extern lv_img_t field;
LV_IMG_DECLARE(field); //声明一个场地图像变量
typedef enum obj_flag
{
    OBJ_BTNM_SON, //起始页面下的选项
    BTNM_START,   //按钮阵列 为了防止重复删除 这个也要放前面

    OBJ_COMPETITION,
    OBJ_DISABLED,
    OBJ_AUTONOMOUS,
    OBJ_OPCONTROL,
    OBJ_CONFIRM, //从这里开始下面都无法lv_load_src(),因为是依附状态
} obj_flag;

typedef enum task_flag
{
    TASK_LOOP, //记录遥控模式下LOOP的TASK
    TASK_OTHER //其他模式下的线程
} task_flag;
namespace ncrapi
{

class UserDisplay
{
  public:
    //样式
    lv_theme_t *theme;
    lv_style_t style;
    std::array<lv_obj_t *, 8> displayObj = {nullptr};   //对象
    std::array<lv_task_t *, 2> displayTask = {nullptr}; //线程
    //标题栏
    lv_obj_t *otherLab = nullptr;
    lv_obj_t *loopLab = nullptr;
    //退出按钮
    lv_obj_t *exitBtn = nullptr;
    //时间变量
    uint32_t loopTime = 0;
    uint32_t maxLoopTime = 0;
    uint32_t minLoopTime = 20;
    UserDisplay();
    void delObjs();
    void delTasks();
    void createUserObj(obj_flag objname, bool isSrcLoad, const char *terminalText, lv_obj_t *parent = nullptr, const char *labText = nullptr);
    void createUserTask(task_flag taskName, void (*task)(void *), uint32_t loopTime, const char *terminalText);
    void createOpObj();
    void createStartObj();
    void creartVersion(lv_obj_t *parent);
    void creartConfig(lv_obj_t *parent);
    void creartVision(lv_obj_t *parent);
    void creartCustomTest(lv_obj_t *parent);
    void creartSysInfo(lv_obj_t *parent);
    void creartPid(lv_obj_t *parent);
    void creartOdom(lv_obj_t *parent);
    void creartDebug(lv_obj_t *parent);
    static lv_res_t closeAction(lv_obj_t *btn); //退出按钮的动作

    std::ostringstream ostr;
};
} // namespace ncrapi
extern ncrapi::UserDisplay *userDisplay;
