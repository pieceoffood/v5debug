#include "main.h"

std::array<lv_obj_t *, AUTO_NUMS> compSw;
/**
 * 自动赛选择时候的确认按钮的动作
 * @param  btn 要实现动作的按钮的指针
 * @return     返回不知道啥....
 */
static lv_res_t confirmBtnIncomp(lv_obj_t *btn)
{
    int i = 0;
    //获取开关状态
    for (auto &it : sysData->autoFlags)
    {
        it = lv_sw_get_state(compSw[i]);
        i++;
    }
    char autoInfo[256];
    const char *side, *fr, *shootH_M, *isShootMid, *plat, *bumper;
    sysData->autoSide == 0 ? side = "红方" : side = "蓝方";
    sysData->autoFlags[AUTO_FR] == 0 ? fr = "前场" : fr = "后场";
    sysData->autoFlags[AUTO_SHOOT] == 0 ? shootH_M = "射高旗" : shootH_M = "射中旗";
    sysData->autoFlags[AUTO_MID_SHOOT] == 0 ? isShootMid = "不二次射旗" : isShootMid = "二次射旗";
    sysData->autoFlags[AUTO_PLATFORM] == 0 ? plat = "不开台" : plat = "开台";
    sysData->autoFlags[AUTO_BUMPERFLAG] == 0 ? bumper = "不二次撞旗" : bumper = "二次撞旗";
    //创建确认页面
    userDisplay->delTasks();
    userDisplay->delObjs();
    userDisplay->createUserObj(OBJ_CONFIRM, false, "obj_confirmPage");
    // //显示自动赛选项
    lv_obj_t *autoinfoLab = lv_label_create(userDisplay->displayObj[OBJ_CONFIRM], nullptr);
    sprintf(autoInfo, " %s\n %s\n %s\n %s\n %s\n %s", side, fr, shootH_M, isShootMid, plat, bumper);
    lv_label_set_text(autoinfoLab, autoInfo);
    // 传感器页面创建
    userDisplay->creartSensorsInfo(userDisplay->displayObj[OBJ_CONFIRM], LV_HOR_RES - lv_obj_get_width(autoinfoLab)); //总宽度-对象宽度
    lv_obj_align(userDisplay->displayObj[OBJ_SENSORSINFO], autoinfoLab, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
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
        sysData->autoIsMode = 0; //普通自动赛模式
        sysData->autoSide = 0;   //红方0
        userDisplay->theme->tabview.bg->body.main_color = LV_COLOR_RED;
    }
    else if (x == 1)
    {
        sysData->autoIsMode = 0; //普通自动赛模式
        sysData->autoSide = 360; //蓝方360
        userDisplay->theme->tabview.bg->body.main_color = LV_COLOR_BLUE;
    }
    else if (x == 2)
    {
        sysData->autoIsMode = 1; //纯自动
        sysData->autoSide = 0;   //技能赛默认红方
        userDisplay->theme->tabview.bg->body.main_color = LV_COLOR_BLACK;
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
    userDisplay->delTasks();
    userDisplay->delObjs();
    userDisplay->createUserObj(OBJ_COMPETITION, true, "obj_competition");
    //创建标签栏
    lv_obj_t *tab = lv_tabview_create(userDisplay->displayObj[OBJ_COMPETITION], NULL);
    userDisplay->theme->tabview.bg->body.main_color = LV_COLOR_RED; //进来后 默认设置成红色
    lv_obj_set_size(tab, LV_HOR_RES, LV_VER_RES);                   //设置位置
    lv_obj_t *redTab = lv_tabview_add_tab(tab, "红方");
    lv_obj_t *blueTab = lv_tabview_add_tab(tab, "蓝方");
    lv_obj_t *skillAutoTab = lv_tabview_add_tab(tab, "技能赛");

    /*当选项卡按下后进行的操作*/
    lv_tabview_set_tab_load_action(tab, tabChose);
    //创建各种开关
    for (auto &it : compSw)
        it = lv_sw_create(userDisplay->displayObj[OBJ_COMPETITION], nullptr);
    //创建开关后面的文本条
    std::array<lv_obj_t *, AUTO_NUMS> compLab;
    for (auto &it : compLab)
        it = lv_label_create(userDisplay->displayObj[OBJ_COMPETITION], nullptr);
    //确认按钮
    lv_obj_t *confirmBtn = lv_btn_create(userDisplay->displayObj[OBJ_COMPETITION], nullptr); //创建确认开关
    lv_obj_t *confirmLab = lv_label_create(confirmBtn, nullptr);                             //创建确认开关文本 这里设置按钮为父级

    lv_label_set_text(compLab[AUTO_FR], "前场&后场");
    lv_label_set_text(compLab[AUTO_SHOOT], "高旗&中旗");
    lv_label_set_text(compLab[AUTO_MID_SHOOT], "是否二次射旗");
    lv_label_set_text(compLab[AUTO_PLATFORM], "是否开台");
    lv_label_set_text(compLab[AUTO_BUMPERFLAG], "是否二次撞旗");
    lv_label_set_text(confirmLab, "确认");
    //大小设置
    lv_obj_set_size(confirmBtn, 200, 50);
    //位置设置
    int xFlag = 10, yFlag = 80, countForSw = 1, countForLab = 0;
    //设置开关和匹配文本的位置
    for (auto &it : compSw)
    {
        lv_obj_set_pos(it, xFlag, yFlag);
        lv_obj_align(compLab[countForLab], it, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        yFlag += 50;
        countForSw++;
        countForLab++;
        if (countForSw >= 4)
        {
            xFlag = 250;
            yFlag = 80;
            countForSw = 0;
        }
    }
    //设置确定按钮和其文本框的位置
    lv_obj_set_pos(confirmBtn, LV_HOR_RES - 200, LV_VER_RES - 50);
    //确认按钮的动作
    lv_btn_set_action(confirmBtn, LV_BTN_ACTION_PR, confirmBtnIncomp);

    //调用按钮页面
    //TODO 技能赛的动作
}
