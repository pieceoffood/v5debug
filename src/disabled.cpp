/**
 * @Author: yan
 * @Date:   2018-10-14T15:44:39+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T12:51:06+08:00
 */
#include "main.h"
/**
 * 场控没开自动赛 没开手动 完全禁止的时候使用的函数
  */
void disabled()
{
    userDisplay.createUserObj(OBJ_DISABLED, "场控关闭状态");
}
// void UserDisplay::createDisObj()
// {
//     userDisplay.delObjs();
//     if (displayObj[OBJ_DISABLED] == nullptr)
//         displayObj[OBJ_DISABLED] = lv_obj_create(nullptr, nullptr);
//     lv_scr_load(displayObj[OBJ_DISABLED]);
//     lv_obj_t *lab = lv_label_create(userDisplay.displayObj[OBJ_DISABLED], nullptr);
//     lv_label_set_text(lab, "场控关闭状态...");
//     std::cout << "create DisableObj" << std::endl;
// }
