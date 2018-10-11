/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-11T16:44:02+08:00
 */

#include "main.h"
/**
 * 自动赛
 */
void autonomous()
{
    AutoDsp autoDsp(&userDisplay);
    if (userDisplay.tempPage != nullptr)
    {
        lv_obj_del(userDisplay.tempPage);
        userDisplay.tempPage = nullptr;
        std::cout << "delete tempPage!" << std::endl;
    }
}
