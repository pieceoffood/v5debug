/**
 * @Author: yan
 * @Date:   2018-10-14T15:44:39+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:06:18+08:00
 */
#include "main.hpp"
/**
 * 场控没开自动赛 没开手动 完全禁止的时候使用的函数
  */
void disabled()
{
    userDisplay->delTasks();
    userDisplay->delObjs();
    userDisplay->createUserObj(OBJ_DISABLED, true, "obj_disabled", nullptr, "场控关闭状态");
}
