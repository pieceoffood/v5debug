#pragma once
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
    //机器人初始参数
    const std::string robotStyle;
    const std::string userName;
    const std::string teamNum;
    std::string robotInfo = "型号:";
    //自动赛参数
    bool autoIsMode = 0; //自动赛模式 普通自动0 纯自动1
    int autoSide = 0;    //红方 0 蓝方360
    std::array<bool, AUTO_NUMS> autoFlags;
    //传感器数据
    //构造函数
    systemData(const std::string style, const std::string name, const std::string num) : robotStyle(style), userName(name), teamNum(num)
    {
        // Config config("/usd/configUTF8.txt");
        robotInfo.append(robotStyle);
        robotInfo.append(" 用户:");
        robotInfo.append(userName);
        robotInfo.append(" ");
        robotInfo.append(teamNum);
    }
};
extern systemData *sysData;
