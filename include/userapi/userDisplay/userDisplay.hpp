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
        /*初始化外星人主题
        * 210：绿色色调值
        * NULL: 使用默认字体 (LV_FONT_DEFAULT)*/
        lv_theme_t *th = lv_theme_alien_init(210, NULL);
        /*设置Surand系统主题*/
        lv_theme_set_current(th);
        //创建页面
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
        /*创建标签栏 */
        lv_obj_t *tab = lv_tabview_create(startPage, NULL);
        lv_obj_t *onlineTab = lv_tabview_add_tab(tab, "onlineTest");
        lv_obj_t *robotTab = lv_tabview_add_tab(tab, "robotTest");
        lv_obj_t *autoTab = lv_tabview_add_tab(tab, "autonomous");
        lv_obj_t *opctlTab = lv_tabview_add_tab(tab, "opcontrol");
        lv_obj_t *frTab = lv_tabview_add_tab(tab, "frPid");
        lv_obj_t *rotateTab = lv_tabview_add_tab(tab, "rotatePid");
        lv_obj_t *odomTab = lv_tabview_add_tab(tab, "odomTest");
        lv_obj_t *customTab = lv_tabview_add_tab(tab, "customTest");
        //设置标题栏风格
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_BG, &style_tv_btn_bg);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_INDIC, &lv_style_plain);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_REL, &style_tv_btn_rel);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_PR, &style_tv_btn_pr);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_REL, &style_tv_btn_rel);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_PR, &style_tv_btn_pr);
    }
};
