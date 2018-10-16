/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T12:50:56+08:00
 */

#include "main.h"
//全局变量和类
systemData sysData;      //系统数据类
UserDisplay userDisplay; //图像数据类

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
    lv_label_set_text(lab1, "机器人初始化中...");
    lv_label_set_text(lab2, "陀螺仪初始化中");
    okapi::ADIGyro gyro(GYRO_PORT);
    gyro.reset();
    if (gyro.get() == PROS_ERR)
    {
        lv_label_set_text(lab2, "警告!!!陀螺仪初始化失败");
        while (1)
            ;
    }
    else
        lv_label_set_text(lab2, "陀螺仪初始化完毕");
    lv_label_set_text(lab1, "机器人初始化完毕...");
    lv_obj_del(initObj);
    initObj = nullptr;
}
