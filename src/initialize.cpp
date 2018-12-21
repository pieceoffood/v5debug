/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:49:50+08:00
 */

#include "main.hpp"
//全局变量和类
ncrapi::SystemData *sysData;      //系统数据类
ncrapi::UserDisplay *userDisplay; //图像数据类

//全局初始化构造函数

/**
 * 初始化函数
 */

void initialize()
{

    lv_obj_t *initObj = lv_obj_create(nullptr, nullptr);
    lv_scr_load(initObj);
    lv_obj_t *img = lv_img_create(initObj, nullptr);
    lv_img_set_src(img, &logo); //将创建的文件设置为图像
    lv_obj_align(img, initObj, LV_ALIGN_CENTER, 0, -20);
    lv_obj_animate(img, LV_ANIM_FLOAT_TOP, 3000, 100, nullptr);
    lv_obj_t *lab1 = lv_label_create(img, nullptr);
    lv_obj_align(lab1, img, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    //系统初始化
    lv_label_set_text(lab1, "系统初始化中...");
    sysData = new ncrapi::SystemData();
    lv_label_set_text(lab1, "文件读取中...");
    //显示初始化
    lv_label_set_text(lab1, "图形界面初始化中...");
    userDisplay = new ncrapi::UserDisplay;
    userDisplay->createMbox(initObj, "请选择红蓝方(默认红方)", "红方", "蓝方", ncrapi::UserDisplay::choseSideAction);

    lv_label_set_text(lab1, "机器人初始化完毕...");
    lv_obj_del(initObj);
}
