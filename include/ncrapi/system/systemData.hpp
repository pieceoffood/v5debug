/**
 * @Author: yan
 * @Date:   2018-10-11T13:18:43+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:28:17+08:00
 */

#ifndef SYSTEMDATA_HPP_
#define SYSTEMDATA_HPP_
#define AUTO_NUMS 5
#include "configSet.hpp"
#include <array>

typedef enum auto_flag
{
    AUTO_FR,        //前场0 后场1
    AUTO_SHOOT,     //射高旗0 射中旗1
    AUTO_MID_SHOOT, //是否射中间的旗子 0不射 1射
    AUTO_PLATFORM,  //0不开台 1 开台
    AUTO_BUMPERFLAG //0不撞中间旗 1 撞中间旗子
} auto_flag;
//旗子枚举
typedef enum flagPosName
{
    leftHighFlag = 0,
    leftMiddleFlag,
    leftLowFlag,
    middleHighFlag,
    middleMiddleFlag,
    middleLowFlag,
    rightHighFlag,
    rightMiddleFlag,
    rightLowFlag
} flagPosName;
/**
  * 普通自动赛的旗子坐标 和 纯自动的旗子的坐标 两者不同
  * X =autoMode 普通自动赛=0,纯自动=1
  * y = flagPosName
  */
struct flagCoordinate
{
    int x, y, z;
};
//盘子的坐标 红方基准
struct capCoordinate
{
    int x, y;
};
struct systemData
{
    //自动赛参数
    bool autoIsMode = 0; //自动赛模式 普通自动0 纯自动1
    int autoSide = 0;    //红方 0 蓝方360
    std::array<bool, AUTO_NUMS> autoFlags;
    //传感器数据
};
extern systemData sysData;

#endif /* end of include guard: SYSTEMDATA_HPP_ */
