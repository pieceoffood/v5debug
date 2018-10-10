/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-10T10:57:48+08:00
 */
#include "api.h"
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include <cstdio>

class UserDisplay
{
  private:
    //页
    lv_obj_t *_initPage = nullptr;
    lv_obj_t *_disabledPage = nullptr;
    lv_obj_t *_autonomousPage = nullptr;
    lv_obj_t *_opcontrolPage = nullptr;
    lv_obj_t *_competitionPage = nullptr;
    //标题
    lv_obj_t *_loopTimeLab = nullptr; //循环标题栏
    //样式
    lv_theme_t *_theme; //全局主题
    lv_style_t _redStyle;
    lv_style_t _blueStyle;

    char _buf_long[256];
    int _maxLoopTime = 0;
    int _minLoopTime = 20;
    //自动赛按钮
    void createSkillAutoTab(lv_obj_t *parent)
    {
    }
    void createRedTab(lv_obj_t *parent)
    {
    }
    void createBlueTab(lv_obj_t *parent)
    {
    }

  public:
    UserDisplay()
    {
        /*初始化外星人主题
        * 210：绿色色调值
        * NULL: 使用默认字体 (LV_FONT_DEFAULT)*/
        _theme = lv_theme_alien_init(210, NULL);
        /*设置Surand系统主题*/
        lv_theme_set_current(_theme);
        //创建页面
        //    startPage = lv_page_create(nullptr, nullptr);
        _initPage = lv_obj_create(nullptr, nullptr);
        _disabledPage = lv_obj_create(nullptr, nullptr);
        _autonomousPage = lv_obj_create(nullptr, nullptr);
        _opcontrolPage = lv_obj_create(nullptr, nullptr);
        _competitionPage = lv_obj_create(nullptr, nullptr);
        //创建标题栏
        _loopTimeLab = lv_label_create(_opcontrolPage, nullptr);
        lv_obj_align(_loopTimeLab, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
    }
    void initialize()
    {
        lv_scr_load(_initPage);
        lv_obj_t *lab = lv_label_create(_initPage, nullptr);
        lv_label_set_text(lab, "robot Initialization...");
    }

    void disabled()
    {
        lv_scr_load(_disabledPage);
        lv_obj_t *lab = lv_label_create(_disabledPage, nullptr);
        lv_label_set_text(lab, "competition disabled...");
    }

    void competition_initialize()
    {
        lv_scr_load(_competitionPage);
        lv_obj_t *lab = lv_label_create(_competitionPage, nullptr);
        lv_label_set_text(lab, "competition Initialization...");
        //创建标签栏
        lv_obj_t *tab = lv_tabview_create(_competitionPage, NULL);
        lv_obj_set_size(tab, LV_HOR_RES, LV_VER_RES); //设置位置
        lv_obj_t *redTab = lv_tabview_add_tab(tab, "red");
        lv_obj_t *blueTab = lv_tabview_add_tab(tab, "blue");
        lv_obj_t *skillAutoTab = lv_tabview_add_tab(tab, "skillAuto");
        //设置样式
        lv_style_copy(&_redStyle, &lv_style_plain);  /*复制内置样式作为起点*/
        lv_style_copy(&_blueStyle, &lv_style_plain); /*复制内置样式作为起点*/
        _redStyle.body.main_color = LV_COLOR_RED;    /*红色主题*/
        _blueStyle.body.main_color = LV_COLOR_BLUE;  /*蓝色主色*/
        lv_obj_set_style(redTab, &_redStyle);        //应用红色样式
        lv_obj_set_style(blueTab, &_blueStyle);      //应用蓝色样式

        //调用按钮页面
        createRedTab(redTab);
        createBlueTab(blueTab);
        createSkillAutoTab(skillAutoTab);
    }

    void autonomous()
    {
        lv_scr_load(_autonomousPage);
        lv_obj_t *lab = lv_label_create(_autonomousPage, nullptr);
        lv_label_set_text(lab, "robot autonomousing...");
    }

    void opcontrol()
    {
        lv_scr_load(_opcontrolPage);
        if (!pros::competition::is_connected())
        {
            startP(_opcontrolPage);
        }
        else

        {

            lv_obj_t *lab = lv_label_create(_opcontrolPage, nullptr);
            lv_label_set_text(lab, "robot opcontroling...");
        }
    }
    void loopTime(const int loopTime)
    {
        if (loopTime > _maxLoopTime)
            _maxLoopTime = loopTime;
        if (loopTime < _minLoopTime)
            _minLoopTime = loopTime;
        sprintf(_buf_long, "loop:%d max:%d min:%d\n", loopTime, _maxLoopTime, _minLoopTime);
        lv_label_set_text(_loopTimeLab, _buf_long);
    }
    void startP(lv_obj_t *para)
    {
        /****************
     *添加标题
     ****************/
        /*创建标签栏 */
        lv_obj_t *tab = lv_tabview_create(para, NULL);
        lv_obj_t *onlineTab = lv_tabview_add_tab(tab, "onlineTest\n");
        lv_obj_t *robotTab = lv_tabview_add_tab(tab, "robotTest\n");
        lv_obj_t *autoTab = lv_tabview_add_tab(tab, "autonomous\n");
        lv_obj_t *opctlTab = lv_tabview_add_tab(tab, "opcontrol\n");
        lv_obj_t *frTab = lv_tabview_add_tab(tab, "frPid\n");
        lv_obj_t *rotateTab = lv_tabview_add_tab(tab, "rotatePid\n");
        lv_obj_t *odomTab = lv_tabview_add_tab(tab, "odomTest\n");
        lv_obj_t *customTab = lv_tabview_add_tab(tab, "customTest\n");
        //设置标题栏风格
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_BG, &style_tv_btn_bg);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_INDIC, &lv_style_plain);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_REL, &style_tv_btn_rel);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_PR, &style_tv_btn_pr);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_REL, &style_tv_btn_rel);
        // lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_PR, &style_tv_btn_pr);
    }
};
