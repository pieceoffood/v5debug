/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T12:51:39+08:00
 */

#include "main.h"
/**
 * 自动赛
 */

void autonomous()
{
    userDisplay.createAutoObj();
}
void UserDisplay::createAutoObj()
{
    delObjs();
    if (autonomousObj == nullptr)
        autonomousObj = lv_obj_create(nullptr, nullptr);
    lv_scr_load(autonomousObj);
    lv_obj_t *lab = lv_label_create(userDisplay.autonomousObj, nullptr);
    lv_label_set_text(lab, "自动赛进行中");
    std::cout << "create autoObj" << std::endl;
}
