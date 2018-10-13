/**
 * @Author: yan
 * @Date:   2018-10-11T10:05:04+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-13T15:26:45+08:00
 */
#ifndef COMPDSP_HPP_
#define COMPDSP_HPP_
#include "userapi/userDisplay/userDisplay.hpp"

static lv_obj_t *frSw;         //创建前后场开关
static lv_obj_t *shootSw;      //创建射高中旗开关
static lv_obj_t *midShootSw;   //创建是否射中间杆子旗子开关
static lv_obj_t *platformSw;   //创建是否开台开关
static lv_obj_t *bumperFlagSw; //创建是否撞中间旗开关
/**
 * 自动赛选择时候的确认按钮的动作
 * @param  btn 要实现动作的按钮的指针
 * @return     返回不知道啥....
 */
static lv_res_t confirmBtnIncomp(lv_obj_t *btn)
{
    //获取开关状态
    sysData.autoIsFR = lv_sw_get_state(frSw);                 //前场后场
    sysData.autoIsFlag = lv_sw_get_state(shootSw);            //高旗中旗
    sysData.autoIsShootFlag = lv_sw_get_state(midShootSw);    //是否射中间旗子
    sysData.autoIsRunPlat = lv_sw_get_state(platformSw);      //是否开台
    sysData.autoIsBumperFlag = lv_sw_get_state(bumperFlagSw); //是否撞旗
    char autoInfo[256];
    const char *side;
    const char *fr;
    const char *shootH_M;
    const char *isShootMid;
    const char *plat;
    const char *bumper;
    sysData.autoSide == 0 ? side = "红方" : side = "蓝方";
    sysData.autoIsFR == 0 ? fr = "前场" : fr = "后场";
    sysData.autoIsFlag == 0 ? shootH_M = "射高旗" : shootH_M = "射中旗";
    sysData.autoIsShootFlag == 0 ? isShootMid = "不二次射旗" : isShootMid = "二次射旗";
    sysData.autoIsRunPlat == 0 ? plat = "不开台" : plat = "开台";
    sysData.autoIsBumperFlag == 0 ? bumper = "不二次撞旗" : bumper = "二次撞旗";
    lv_obj_del(userDisplay.competitionPage);
    userDisplay.tempPage = lv_obj_create(nullptr, nullptr);
    //显示自动赛选项
    lv_obj_t *autoinfoLab = lv_label_create(userDisplay.tempPage, NULL);
    sprintf(autoInfo, " %s\n %s\n %s\n %s\n %s\n %s", side, fr, shootH_M, isShootMid, plat, bumper);
    lv_label_set_text(autoinfoLab, autoInfo);
    // lv_obj_t *sensorsLab = lv_label_create(userDisplay.tempPage, NULL);
    // lv_label_set_text(sensorsLab, "gyro:");
    //TODO 传感器都放上

    std::cout << "pressed" << std::endl;
    return LV_RES_OK;
}
static void tabChose(lv_obj_t *tab, uint16_t x)
{
    if (x == 0)
    {
        sysData.autoIsMode = 0; //普通自动赛模式
        sysData.autoSide = 0;   //红方0
        userDisplay.theme->tabview.bg->body.main_color = LV_COLOR_RED;
    }
    else if (x == 1)
    {
        sysData.autoIsMode = 0; //普通自动赛模式
        sysData.autoSide = 360; //蓝方360
        userDisplay.theme->tabview.bg->body.main_color = LV_COLOR_BLUE;
    }
    else if (x == 2)
    {
        sysData.autoIsMode = 1; //纯自动
        sysData.autoSide = 0;   //技能赛默认红方
        userDisplay.theme->tabview.bg->body.main_color = LV_COLOR_BLACK;
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
        userDisplay.theme->tabview.bg->body.main_color = LV_COLOR_RED; //进来后 默认设置成红色
        lv_obj_set_size(tab, LV_HOR_RES, LV_VER_RES);                  //设置位置
        lv_obj_t *redTab = lv_tabview_add_tab(tab, "红方");
        lv_obj_t *blueTab = lv_tabview_add_tab(tab, "蓝方");
        lv_obj_t *skillAutoTab = lv_tabview_add_tab(tab, "技能赛");

        /*当选项卡按下后进行的操作*/
        lv_tabview_set_tab_load_action(tab, tabChose);
        //创建选项
        frSw = lv_sw_create(_data->competitionPage, NULL);         //创建前后场开关
        shootSw = lv_sw_create(_data->competitionPage, NULL);      //创建射高中旗开关
        midShootSw = lv_sw_create(_data->competitionPage, NULL);   //创建是否射中间杆子旗子开关
        platformSw = lv_sw_create(_data->competitionPage, NULL);   //创建是否开台开关
        bumperFlagSw = lv_sw_create(_data->competitionPage, NULL); //创建是否撞中间旗开关

        lv_obj_t *frLab = lv_label_create(_data->competitionPage, NULL);          //创建前后场开关文本条
                                                                                  //    lv_label_set_style(frLab, &_data->fontStyle);
        lv_obj_t *shootLab = lv_label_create(_data->competitionPage, frLab);      //创建射高旗中旗开关文本条
        lv_obj_t *midShootLab = lv_label_create(_data->competitionPage, frLab);   //创建是否射中间杆子旗子文本条
        lv_obj_t *platformLab = lv_label_create(_data->competitionPage, frLab);   //创建是否开台开关文本条
        lv_obj_t *bumperFlagLab = lv_label_create(_data->competitionPage, frLab); //创建是否撞中间旗开关文本条
        //
        lv_obj_t *confirmBtn = lv_btn_create(_data->competitionPage, NULL);    //创建确认文本开关
        lv_obj_t *confirmLab = lv_label_create(_data->competitionPage, frLab); //创建是否撞中间旗开关文本条

        lv_label_set_text(frLab, "前场&后场");
        lv_label_set_text(shootLab, "高旗&中旗");
        lv_label_set_text(midShootLab, "是否二次射旗");
        lv_label_set_text(platformLab, "是否开台");
        lv_label_set_text(bumperFlagLab, "是否二次撞旗");
        lv_label_set_text(confirmLab, "确认");
        //大小设置
        lv_obj_set_size(confirmBtn, 200, 50);
        //位置设置
        lv_obj_align(frSw, tab, LV_ALIGN_IN_TOP_LEFT, 10, 70);
        lv_obj_align(shootSw, frSw, LV_ALIGN_OUT_TOP_LEFT, 0, 100);
        lv_obj_align(midShootSw, shootSw, LV_ALIGN_OUT_TOP_LEFT, 0, 100);
        lv_obj_align(frLab, frSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);       //前后 文本框对齐开关
        lv_obj_align(shootLab, shootSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0); //高中旗 文本框对齐开关
        lv_obj_align(midShootLab, midShootSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

        lv_obj_align(platformSw, frLab, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(bumperFlagSw, platformSw, LV_ALIGN_OUT_TOP_LEFT, 0, 100);
        lv_obj_align(platformLab, platformSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(bumperFlagLab, bumperFlagSw, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_obj_align(confirmBtn, bumperFlagLab, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
        lv_obj_align(confirmLab, confirmBtn, LV_ALIGN_IN_BOTTOM_MID, 0, -15);
        //设置样式
        // lv_btn_set_style(confirmBtn, LV_BTN_STYLE_REL, lv_obj_get_style(parent));
        //确认按钮的动作
        lv_btn_set_action(confirmBtn, LV_BTN_ACTION_PR, confirmBtnIncomp);

        //调用按钮页面
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
};

#endif /* end of include guard: COMPDSP_HPP_ */
