/**
 * @Author: yan
 * @Date:   2018-10-14T15:44:39+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-15T11:23:01+08:00
 */
#include "main.h"
/**
 * 场控没开自动赛 没开手动 完全禁止的时候使用的函数
  */
void disabled()
{
    userDisplay.delPages();
    userDisplay.createDisPage();
    lv_obj_t *lab = lv_label_create(userDisplay.disabledPage, nullptr);
    lv_label_set_text(lab, "场控关闭状态...");
}
