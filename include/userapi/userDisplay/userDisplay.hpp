/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-10T17:10:52+08:00
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
    lv_obj_t *_loopTimeLab = nullptr;
    //样式
    lv_theme_t *_theme;
    lv_style_t _redStyle;
    lv_style_t _blueStyle;

    char _buf_long[256];
    int _maxLoopTime = 0;
    int _minLoopTime = 20;
    //自动赛按钮
    void createSkillAutoTab(lv_obj_t *parent)
    {
    }
    void createTab(lv_obj_t *parent)
    {
        //创建选项
        lv_obj_t *frRoller = lv_roller_create(parent, NULL);    //创建前后场选项卡
        lv_obj_t *shootRoller = lv_roller_create(parent, NULL); //创建射高中旗选项卡

        lv_obj_t *midShootSw = lv_sw_create(parent, NULL);   //创建是否射中间杆子旗子开关
        lv_obj_t *platformSw = lv_sw_create(parent, NULL);   //创建是否开台开关
        lv_obj_t *bumperFlagSw = lv_sw_create(parent, NULL); //创建是否撞中间旗开关

        lv_obj_t *midShootLab = lv_label_create(parent, NULL);   //创建是否射中间杆子旗子文本条
        lv_obj_t *platformLab = lv_label_create(parent, NULL);   //创建是否开台开关文本条
        lv_obj_t *bumperFlagLab = lv_label_create(parent, NULL); //创建是否撞中间旗开关文本条

        lv_roller_set_options(frRoller, "the front\nthe back");
        lv_roller_set_options(shootRoller, "high flag\nmid flag");
        lv_label_set_text(midShootLab, "isShootFlag");
        lv_label_set_text(platformLab, "isRunToPlat");
        lv_label_set_text(bumperFlagLab, "isBumperFlag");

        //大小设置
        // lv_roller_set_visible_row_count(frRoller, 1);
        // lv_roller_set_visible_row_count(shootRoller, 1);没鸟用 骗人的
        lv_obj_set_size(frRoller, 80, 140);
        lv_obj_set_size(shootRoller, 80, 140);
        //位置设置
        lv_obj_align(shootRoller, frRoller, LV_ALIGN_OUT_RIGHT_TOP, 15, 0);
        lv_obj_align(midShootSw, shootRoller, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);
        lv_obj_align(platformSw, shootRoller, LV_ALIGN_OUT_RIGHT_MID, 10, 2);
        lv_obj_align(bumperFlagSw, shootRoller, LV_ALIGN_OUT_RIGHT_MID, 10, 50);
        lv_obj_align(midShootLab, midShootSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(platformLab, platformSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(bumperFlagLab, bumperFlagSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
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
        createTab(redTab);
        createTab(blueTab);
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
        static const char *btnm_map[] = {"onlineTest", "robotTest", "\n",
                                         "autonomous", "opcontorl", "\n",
                                         "frPid", "rotatePid", "\n",
                                         "odomTest", "customTest", ""};

        lv_obj_t *btnm = lv_btnm_create(para, NULL); //创建按钮集群
        lv_btnm_set_map(btnm, btnm_map);
        lv_obj_set_size(btnm, LV_HOR_RES, LV_VER_RES);
    }
};
