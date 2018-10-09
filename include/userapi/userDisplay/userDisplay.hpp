/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T15:54:22+08:00
 */
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include <cstdio>
class UserDisplay
{
  private:
    lv_obj_t *startPage = nullptr;
    lv_obj_t *initPage = nullptr;
    lv_obj_t *disabledPage = nullptr;
    lv_obj_t *autonomousPage = nullptr;
    lv_obj_t *opcontrolPage = nullptr;
    lv_obj_t *competitionPage = nullptr;

    lv_obj_t *loopTimeLab; //循环标题栏
    char _buf_long[256];
    int _maxLoopTime = 0;
    int _minLoopTime = 20;

  public:
    UserDisplay()
    {
        startPage = lv_page_create(nullptr, nullptr);
        initPage = lv_obj_create(nullptr, nullptr);
        disabledPage = lv_obj_create(nullptr, nullptr);
        autonomousPage = lv_obj_create(nullptr, nullptr);
        opcontrolPage = lv_obj_create(nullptr, nullptr);
        competitionPage = lv_obj_create(nullptr, nullptr);

        loopTimeLab = lv_label_create(opcontrolPage, nullptr);
        lv_obj_align(loopTimeLab, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
    }
    void initialize()
    {
        lv_scr_load(initPage);
        lv_obj_t *lab = lv_label_create(initPage, nullptr);
        lv_label_set_text(lab, "robot Initialization...");
    }

    void disabled()
    {
        lv_scr_load(disabledPage);
        lv_obj_t *lab = lv_label_create(disabledPage, nullptr);
        lv_label_set_text(lab, "competition disabled...");
    }

    void competition_initialize()
    {
        lv_scr_load(competitionPage);
        lv_obj_t *lab = lv_label_create(competitionPage, nullptr);
        lv_label_set_text(lab, "competition Initialization...");
    }
    void autonomous()
    {
        lv_scr_load(autonomousPage);
        lv_obj_t *lab = lv_label_create(autonomousPage, nullptr);
        lv_label_set_text(lab, "robot autonomousing...");
    }

    void opcontrol()
    {
        lv_scr_load(opcontrolPage);
        lv_obj_t *lab = lv_label_create(opcontrolPage, nullptr);
        lv_label_set_text(lab, "robot opcontroling...");
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
    void startP()
    {
        /*创建新的屏幕并加载它
      *可以从任何类型的对象类型创建屏幕
      *现在使用一个页面，它是一个滚动内容的对象*/
        lv_scr_load(startPage);
        /****************
     *添加标题
     ****************/
        lv_obj_t *label = lv_label_create(startPage, nullptr); /*第一个参数 (scr) 是父类 */
        lv_label_set_text(label, "please chose");              /*设置标题文本*/
        lv_obj_set_x(label, 10);                               /*设置X轴的位置*/
        /***********************
        * 创建两个按钮对象
        ***********************/
        /*创建按钮*/
        lv_obj_t *btn1 = lv_btn_create(startPage, nullptr); /*在当前加载的屏幕上创建按钮*/
        //lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_rel_action); /*在按钮释放时调用SET函数*/
        lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20); /*标签下方对齐*/

        /*在按钮上创建标签（“标签”变量可以重复使用）*/
        label = lv_label_create(btn1, nullptr);
        lv_label_set_text(label, "onlineTest");

        /*复制前一个按钮*/
        lv_obj_t *btn2 = lv_btn_create(startPage, btn1);         /*第二个参数是要复制的对象。*/
        lv_obj_align(btn2, btn1, LV_ALIGN_OUT_RIGHT_MID, 50, 0); /*对齐PREV.按钮。*/

        /*在按钮上创建标签*/
        label = lv_label_create(btn2, nullptr);
        lv_label_set_text(label, "autonomous");
    }
};
