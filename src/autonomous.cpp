/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-14T16:11:04+08:00
 */

#include "main.h"
/**
 * 自动赛
 */
void autonomous()
{
    lv_scr_load(userDisplay.autonomousPage);
    lv_obj_t *lab = lv_label_create(userDisplay.autonomousPage, nullptr);
    lv_label_set_text(lab, "自动赛进行中");
    if (userDisplay.tempPage != nullptr)
    {
        lv_obj_del(userDisplay.tempPage);
        userDisplay.tempPage = nullptr;
        std::cout << "delete tempPage!" << std::endl;
    }
}
