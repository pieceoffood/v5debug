/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:49:50+08:00
 */

#include "main.h"
//全局变量和类
systemData *sysData;      //系统数据类
UserDisplay *userDisplay; //图像数据类

//全局初始化构造函数
Config config("/usd/configUTF8.txt");

template <size_t nums>
void initGeneric(Generic<nums> *generic, lv_obj_t *lab, const char *str, const int isReverse = 1)
{
    lv_label_set_text(lab, str);
    generic->set(15 * isReverse);
    pros::delay(500);
    while (generic->getSpeed() != 0)
        pros::delay(20);
    generic->set(0);
    generic->resetEnc();
}
/**
 * 初始化函数
 */

void initialize()
{

    lv_obj_t *initObj = lv_obj_create(nullptr, nullptr);
    lv_scr_load(initObj);
    lv_obj_t *lab1 = lv_label_create(initObj, nullptr);
    lv_obj_t *lab2 = lv_label_create(initObj, nullptr);
    lv_obj_set_y(lab2, 20);

    //系统初始化
    lv_label_set_text(lab2, "系统初始化中...");

    //显示初始化
    userDisplay = new UserDisplay;

    lv_label_set_text(lab1, "机器人初始化完毕...");
    lv_obj_del(initObj);
}
