/**
 * @Author: yan
 * @Date:   2018-10-11T10:05:04+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-11T10:29:08+08:00
 */
#ifndef COMPDSP_HPP_
#define COMPDSP_HPP_
#include "userapi/userDisplay/userDisplay.hpp"

class CompDsp
{
  private:
    UserDisplay *_data;

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
        lv_style_copy(&_data->redStyle, &lv_style_plain);  /*复制内置样式作为起点*/
        lv_style_copy(&_data->blueStyle, &lv_style_plain); /*复制内置样式作为起点*/
        _data->redStyle.body.main_color = LV_COLOR_RED;    /*红色主题*/
        _data->blueStyle.body.main_color = LV_COLOR_BLUE;  /*蓝色主色*/
        lv_obj_set_style(redTab, &_data->redStyle);        //应用红色样式
        lv_obj_set_style(blueTab, &_data->blueStyle);      //应用蓝色样式

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
};
#endif /* end of include guard: COMPDSP_HPP_ */
