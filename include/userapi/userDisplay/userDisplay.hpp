/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-15T11:43:53+08:00
 */
#ifndef USERDISPLAY_HPP_
#define USERDISPLAY_HPP_

#include "api.h"
#include "display/lv_conf.h"
#include "display/lvgl.h"
#include "userapi/systemData.hpp"
#include "userapi/userapi.hpp"
static void sensorsTask(void *param);
static lv_res_t win_close_action(lv_obj_t *btn);

class UserDisplay
{
  private:
    int _maxLoopTime = 0;
    int _minLoopTime = 20;
    char _buf_long[256];

  public:
    //样式
    lv_theme_t *theme;
    //窗口
    lv_obj_t *win = nullptr;
    //页面
    lv_obj_t *competitionPage = nullptr;
    lv_obj_t *opcontrolPage = nullptr;
    lv_obj_t *disabledPage = nullptr;
    lv_obj_t *autonomousPage = nullptr;
    lv_obj_t *confirmPage = nullptr;
    //按钮阵列
    lv_obj_t *startBTNM = nullptr;
    //标题栏
    lv_obj_t *loopTimeLab = nullptr;
    lv_obj_t *sensorsLab = nullptr;
    //线程
    lv_task_t *refr_task = nullptr;
    //临时char型存储

    UserDisplay()
    {
        //增加自定义字库
        lv_font_add(&myfont, nullptr);
        /*初始化外星人主题*/
        theme = lv_theme_alien_init(100, &myfont);
        /*设置Surand系统主题*/
        lv_theme_set_current(theme);
    }
    void createStartPage()
    {
        static const char *btnm_map[] = {"传感器信息", "机器人检测", "\n",
                                         "自动赛", "手动赛", "\n",
                                         "前后PID", "旋转PID", "\n",
                                         "ODOM测试", "自定义测试", ""};
        if (startBTNM == nullptr)
            startBTNM = lv_btnm_create(opcontrolPage, nullptr); //创建按钮集群
        lv_btnm_set_map(startBTNM, btnm_map);
        lv_obj_set_size(startBTNM, LV_HOR_RES, LV_VER_RES - 30);
        lv_obj_set_y(startBTNM, 30);
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
    void delPages()
    {
        if (win != nullptr)
        {
            lv_obj_del(win);
            win = nullptr;
            std::cout << "del SensorsInfoWin" << std::endl;
        }
        if (refr_task != nullptr)
        {
            lv_task_del(refr_task);
            refr_task = nullptr;
            std::cout << "del SensorsInfoTask" << std::endl;
        }

        if (disabledPage != nullptr)
        {
            lv_obj_del(disabledPage);
            disabledPage = nullptr;
            std::cout << "del disabledPage" << std::endl;
        }
        if (competitionPage != nullptr)
        {
            lv_obj_del(competitionPage);
            competitionPage = nullptr;
            std::cout << "del competitionPage" << std::endl;
        }
        if (confirmPage != nullptr)
        {
            lv_obj_del(confirmPage);
            confirmPage = nullptr;
            std::cout << "del confirmPage" << std::endl;
        }
    }
    void delAutoPages()
    {
        delPages();
        if (opcontrolPage != nullptr)
        {
            lv_obj_del(opcontrolPage);
            opcontrolPage = nullptr;
            std::cout << "del autoPage" << std::endl;
        }
    }
    void delOpPages()
    {
        delPages();
        if (autonomousPage != nullptr)
        {
            lv_obj_del(autonomousPage);
            autonomousPage = nullptr;
            std::cout << "del opPage" << std::endl;
        }
    }
    void createAutoPage()
    {
        delAutoPages();
        if (autonomousPage == nullptr)
            autonomousPage = lv_obj_create(nullptr, nullptr);
        lv_scr_load(autonomousPage);
        std::cout << "create autoPage" << std::endl;
    }
    void createCompPage()
    {
        if (competitionPage == nullptr)
            competitionPage = lv_obj_create(nullptr, nullptr);
        lv_scr_load(competitionPage);
        std::cout << "create CompPage" << std::endl;
    }
    void createDisPage()
    {
        if (disabledPage == nullptr)
            disabledPage = lv_obj_create(nullptr, nullptr);
        lv_scr_load(disabledPage);
        std::cout << "create DisablePage" << std::endl;
    }
    void createOpPage()
    {
        delOpPages();
        if (opcontrolPage == nullptr)
        {
            opcontrolPage = lv_obj_create(nullptr, nullptr);
            loopTimeLab = lv_label_create(opcontrolPage, nullptr);
            lv_obj_align(loopTimeLab, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
        }
        lv_scr_load(opcontrolPage);
        std::cout << "create opPage" << std::endl;
        if (!pros::competition::is_connected()) //没插场控
            createStartPage();
        else
        {
            if (startBTNM != nullptr)
            {
                lv_obj_del(startBTNM);
                startBTNM = nullptr;
                std::cout << "del startBTNM" << std::endl;
            }
        }
    }
    void creartSensorsInfo(lv_obj_t *parent)
    {
        if (refr_task == nullptr)
        {
            refr_task = lv_task_create(sensorsTask, 100, LV_TASK_PRIO_LOW, nullptr);
            std::cout << "creart Sensors Info task" << std::endl;
        }
        if (win == nullptr)
        {
            win = lv_win_create(parent, nullptr);
            std::cout << "creart Sensors Info win" << std::endl;
        }
        lv_win_set_layout(win, LV_LAYOUT_COL_L);             //设置布局
        lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action); //添加删除功能
        lv_win_set_title(win, "传感器信息");
        sensorsLab = lv_label_create(win, nullptr); //创建基于WIN的标签
        sensorsTask(nullptr);                       //刷新标签栏
    }
};
extern UserDisplay userDisplay;
static void sensorsTask(void *param)
{
    (void)param; /*Unused*/
    char sensorsInfo[256];
    okapi::ADIGyro gyro(GYRO_PORT);
    sprintf(sensorsInfo, "gyro:%d\n", static_cast<int>(gyro.get()));
    lv_label_set_text(userDisplay.sensorsLab, sensorsInfo);
}
static lv_res_t win_close_action(lv_obj_t *btn)
{
    (void)btn; /*Unused*/
    lv_obj_del(userDisplay.win);
    userDisplay.win = nullptr;

    lv_task_del(userDisplay.refr_task);
    userDisplay.refr_task = nullptr;
    return LV_RES_INV;
}
#endif /* end of include guard: USERDISPLAY_HPP_ */
