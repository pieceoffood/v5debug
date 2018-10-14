/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-14T11:54:51+08:00
 */

#include "main.h"
/**
 * 初始化函数
 */
void initialize()
{
    InitDsp initDsp(&userDisplay);
    while (1)
        pros::delay(20);
}
/**
* 场控没开自动赛 没开手动 完全禁止的时候使用的函数
 */
void disabled()
{
    DisabledDsp disabledDsp(&userDisplay);
}

/**
*在初始化initialize()之后运行，并且在连接到场控之前自动运行
*管理系统或VEX竞争交换机。这是为了特定于竞争的初始化例程，例如自主选择器在液晶显示器上。
*此任务将在机器人启用和自动赛或手动赛时开始。
*选择自动赛 设置参数的地方
*经简易场控测试 是先接上场控,然后再开机,才会执行.已经开机再接场控 不会执行
 */
void competition_initialize()
{
    CompDsp comDsp(&userDisplay);
}
systemData sysData;      //系统数据类
UserDisplay userDisplay; //图像数据类
