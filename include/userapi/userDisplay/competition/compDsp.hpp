/**
 * @Author: yan
 * @Date:   2018-10-11T10:05:04+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-12T12:35:19+08:00
 */
#ifndef COMPDSP_HPP_
#define COMPDSP_HPP_
#include "userapi/userDisplay/userDisplay.hpp"

#include <memory>

static lv_obj_t *frSw;         //创建前后场开关
static lv_obj_t *shootSw;      //创建射高中旗开关
static lv_obj_t *midShootSw;   //创建是否射中间杆子旗子开关
static lv_obj_t *platformSw;   //创建是否开台开关
static lv_obj_t *bumperFlagSw; //创建是否撞中间旗开关
static void tabChose(lv_obj_t *tab, uint16_t x)
{

    if (x == 1)
    {
        sysData.autoIsMode = 0; //普通自动赛模式
        sysData.autoSide = 360; //蓝方360
        userDisplay.nowStyle = &userDisplay.blueStyle;
    }
    else if (x == 2)
    {
        sysData.autoIsMode = 1; //纯自动
        sysData.autoSide = 0;   //技能赛默认红方
    }
    else
    {
        sysData.autoIsMode = 0; //普通自动赛模式
        sysData.autoSide = 0;   //红方0
        userDisplay.nowStyle = &userDisplay.redStyle;
    }
}
class CompDsp
{
  private:
    UserDisplay *_data;
    lv_obj_t *_confirmBtn;

  public:
    CompDsp(UserDisplay *data) : _data(data)
    {
        lv_scr_load(_data->competitionPage);
        //创建标签栏
        lv_obj_t *tab = lv_tabview_create(_data->competitionPage, NULL);
        lv_obj_set_size(tab, LV_HOR_RES, LV_VER_RES); //设置位置
        lv_obj_t *redTab = lv_tabview_add_tab(tab, "red");
        lv_obj_t *blueTab = lv_tabview_add_tab(tab, "blue");
        lv_obj_t *skillAutoTab = lv_tabview_add_tab(tab, "skillAuto");

        //设置样式
        lv_style_copy(&_data->redStyle, &lv_style_plain);   /*复制内置样式作为起点*/
        lv_style_copy(&_data->blueStyle, &lv_style_plain);  /*复制内置样式作为起点*/
        _data->redStyle.body.border.color = LV_COLOR_RED;   //边框颜色
        _data->blueStyle.body.border.color = LV_COLOR_BLUE; //边框颜色
        _data->redStyle.body.main_color = LV_COLOR_RED;     /*红色主题*/
        _data->blueStyle.body.main_color = LV_COLOR_BLUE;   /*蓝色主色*/

        lv_obj_set_style(redTab, &_data->redStyle);   //应用红色样式
        lv_obj_set_style(blueTab, &_data->blueStyle); //应用蓝色样式
        /*当选项卡按下后进行的操作*/
        lv_tabview_set_tab_load_action(tab, tabChose);
        //调用按钮页面
        createTab(redTab);
        createTab(blueTab);
        createSkillAutoTab(skillAutoTab);
    }
    ~CompDsp()
    {
        std::cout << "compDsp destructor" << std::endl;
        //缺少释放
    }
    void createSkillAutoTab(lv_obj_t *parent)
    {
    }

    void createTab(lv_obj_t *parent)
    {
        //创建选项
        lv_obj_t *frSw = lv_sw_create(parent, NULL);         //创建前后场开关
        lv_obj_t *shootSw = lv_sw_create(parent, NULL);      //创建射高中旗开关
        lv_obj_t *midShootSw = lv_sw_create(parent, NULL);   //创建是否射中间杆子旗子开关
        lv_obj_t *platformSw = lv_sw_create(parent, NULL);   //创建是否开台开关
        lv_obj_t *bumperFlagSw = lv_sw_create(parent, NULL); //创建是否撞中间旗开关

        lv_obj_t *frLab = lv_label_create(parent, NULL);         //创建前后场开关文本条
        lv_obj_t *shootLab = lv_label_create(parent, NULL);      //创建射高旗中旗开关文本条
        lv_obj_t *midShootLab = lv_label_create(parent, NULL);   //创建是否射中间杆子旗子文本条
        lv_obj_t *platformLab = lv_label_create(parent, NULL);   //创建是否开台开关文本条
        lv_obj_t *bumperFlagLab = lv_label_create(parent, NULL); //创建是否撞中间旗开关文本条

        lv_obj_t *confirmBtn = lv_btn_create(parent, NULL);   //创建确认文本开关
        lv_obj_t *confirmLab = lv_label_create(parent, NULL); //创建是否撞中间旗开关文本条

        lv_label_set_text(frLab, "front_back");
        lv_label_set_text(shootLab, "high_mid");
        lv_label_set_text(midShootLab, "isShootFlag");
        lv_label_set_text(platformLab, "isRunToPlat");
        lv_label_set_text(bumperFlagLab, "isBumperFlag");
        lv_label_set_text(confirmLab, "confirm");
        //设置按钮样式
        lv_btn_set_style(confirmBtn, LV_BTN_STYLE_REL, lv_obj_get_style(parent));
        //大小设置
        lv_obj_set_size(confirmBtn, 200, 50);
        //位置设置
        lv_obj_align(shootSw, frSw, LV_ALIGN_CENTER, 0, 50);
        lv_obj_align(midShootSw, shootSw, LV_ALIGN_CENTER, 0, 50);
        lv_obj_align(platformSw, frSw, LV_ALIGN_OUT_RIGHT_MID, 120, 0);
        lv_obj_align(bumperFlagSw, platformSw, LV_ALIGN_CENTER, 0, 50);
        lv_obj_align(frLab, frSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);       //前后 文本框对齐开关
        lv_obj_align(shootLab, shootSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0); //高中旗 文本框对齐开关
        lv_obj_align(midShootLab, midShootSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(platformLab, platformSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(bumperFlagLab, bumperFlagSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(confirmBtn, bumperFlagLab, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
        lv_obj_align(confirmLab, confirmBtn, LV_ALIGN_IN_BOTTOM_MID, 0, -15);
        //获取开关状态
        sysData.autoIsFR = lv_sw_get_state(frSw);                 //前场后场
        sysData.autoIsFlag = lv_sw_get_state(shootSw);            //高旗中旗
        sysData.autoIsShootFlag = lv_sw_get_state(midShootSw);    //是否射中间旗子
        sysData.autoIsRunPlat = lv_sw_get_state(platformSw);      //是否开台
        sysData.autoIsBumperFlag = lv_sw_get_state(bumperFlagSw); //是否撞旗
        //确认按钮的动作
        lv_btn_set_action(confirmBtn, LV_BTN_ACTION_PR, confirmBtnIncomp);
    }
};

#endif /* end of include guard: COMPDSP_HPP_ */
