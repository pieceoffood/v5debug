/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:32:37+08:00
 */

#include "main.h"
/**
 * 自动赛
 */

void autonomous()
{
    userDisplay.createAutoPage();
    lv_obj_t *lab = lv_label_create(userDisplay.autonomousPage, nullptr);
    lv_label_set_text(lab, "自动赛进行中");
}
void UserDisplay::createAutoPage()
{
    delAutoPages();
    if (autonomousPage == nullptr)
        autonomousPage = lv_obj_create(nullptr, nullptr);
    lv_scr_load(autonomousPage);
    std::cout << "create autoPage" << std::endl;
}
