/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T12:51:39+08:00
 */

#include "main.hpp"
/**
 * 自动赛
 */

void autonomous()
{
    userDisplay->delTasks();
    userDisplay->delObjs();
    userDisplay->createUserObj(OBJ_AUTONOMOUS, true, "obj_auto", nullptr, "自动赛进行中");
}
