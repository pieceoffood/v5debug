/**
 * @Author: yan
 * @Date:   2018-10-14T14:25:38+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:20:17+08:00
 */
#include "main.h"
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
    userDisplay.delPages();
    if (userDisplay.confirmPage == nullptr)
        userDisplay.confirmPage = lv_obj_create(nullptr, nullptr);
    //显示自动赛选项
    lv_obj_t *autoinfoLab = lv_label_create(userDisplay.confirmPage, NULL);
    sprintf(autoInfo, " %s\n %s\n %s\n %s\n %s\n %s", side, fr, shootH_M, isShootMid, plat, bumper);
    lv_label_set_text(autoinfoLab, autoInfo);
    //TODO 传感器页面
    userDisplay.creartSensorsInfo(userDisplay.confirmPage, LV_HOR_RES - lv_obj_get_width(autoinfoLab)); //总宽度-对象宽度
    lv_obj_align(userDisplay.sensorsInfoPage, autoinfoLab, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);

    std::cout << "pressed" << std::endl;
    return LV_RES_OK;
}
/**
 * 标签栏按下后的动作
 * @param tab 标签
 * @param x   几号标签
 */
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
/**
*在初始化initialize()之后运行，并且在连接到场控之前自动运行
*管理系统或VEX竞争交换机。这是为了特定于竞争的初始化例程，例如自主选择器在液晶显示器上。
*此任务将在机器人启用和自动赛或手动赛时开始。
*选择自动赛 设置参数的地方
*经简易场控测试 是先接上场控,然后再开机,才会执行.已经开机再接场控 不会执行
 */
void competition_initialize()
{
    userDisplay.createCompPage();
    lv_obj_t *_confirmBtn;
    //创建标签栏
    lv_obj_t *tab = lv_tabview_create(userDisplay.competitionPage, NULL);
    userDisplay.theme->tabview.bg->body.main_color = LV_COLOR_RED; //进来后 默认设置成红色
    lv_obj_set_size(tab, LV_HOR_RES, LV_VER_RES);                  //设置位置
    lv_obj_t *redTab = lv_tabview_add_tab(tab, "红方");
    lv_obj_t *blueTab = lv_tabview_add_tab(tab, "蓝方");
    lv_obj_t *skillAutoTab = lv_tabview_add_tab(tab, "技能赛");

    /*当选项卡按下后进行的操作*/
    lv_tabview_set_tab_load_action(tab, tabChose);
    //创建选项
    frSw = lv_sw_create(userDisplay.competitionPage, NULL);         //创建前后场开关
    shootSw = lv_sw_create(userDisplay.competitionPage, NULL);      //创建射高中旗开关
    midShootSw = lv_sw_create(userDisplay.competitionPage, NULL);   //创建是否射中间杆子旗子开关
    platformSw = lv_sw_create(userDisplay.competitionPage, NULL);   //创建是否开台开关
    bumperFlagSw = lv_sw_create(userDisplay.competitionPage, NULL); //创建是否撞中间旗开关

    lv_obj_t *frLab = lv_label_create(userDisplay.competitionPage, NULL);          //创建前后场开关文本条
                                                                                   //    lv_label_set_style(frLab, &userDisplay.fontStyle);
    lv_obj_t *shootLab = lv_label_create(userDisplay.competitionPage, frLab);      //创建射高旗中旗开关文本条
    lv_obj_t *midShootLab = lv_label_create(userDisplay.competitionPage, frLab);   //创建是否射中间杆子旗子文本条
    lv_obj_t *platformLab = lv_label_create(userDisplay.competitionPage, frLab);   //创建是否开台开关文本条
    lv_obj_t *bumperFlagLab = lv_label_create(userDisplay.competitionPage, frLab); //创建是否撞中间旗开关文本条
    //
    lv_obj_t *confirmBtn = lv_btn_create(userDisplay.competitionPage, NULL);    //创建确认文本开关
    lv_obj_t *confirmLab = lv_label_create(userDisplay.competitionPage, frLab); //创建是否撞中间旗开关文本条

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
    //确认按钮的动作
    lv_btn_set_action(confirmBtn, LV_BTN_ACTION_PR, confirmBtnIncomp);

    //调用按钮页面
    //TODO 技能赛的动作
}
void UserDisplay::createCompPage()
{
    if (competitionPage == nullptr)
        competitionPage = lv_obj_create(nullptr, nullptr);
    lv_scr_load(competitionPage);
    std::cout << "create CompPage" << std::endl;
}
