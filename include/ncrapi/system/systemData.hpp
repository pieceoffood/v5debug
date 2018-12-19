#pragma once

#include "configSet.hpp"
#include "object.hpp"
#include <array>

#define AUTO_NUMS 5
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
namespace ncrapi
{
struct SystemData
{
    //机器人初始参数
    std::vector<std::pair<std::string, std::string>> _pidData;
    std::vector<std::pair<std::string, std::string>> _robotData;
    const std::string robotStyle;
    const std::string userName;
    const std::string teamNum;
    std::vector<Obj *> obj; //存储机器人部件的名字
    std::string robotInfo = "型号:";
    //自动赛参数
    bool autoIsMode = 0; //自动赛模式 普通自动0 纯自动1
    int autoSide = 0;    //红方 0 蓝方360
    std::array<bool, AUTO_NUMS> autoFlags;
    //传感器数据
    //构造函数
    SystemData(const std::string style, const std::string name, const std::string num) : robotStyle(style), userName(name), teamNum(num)
    {
        Config config(&_pidData, "/usd/pid.txt"); //读取PID配置
        robotInfo.append(robotStyle);
        robotInfo.append(" 用户:");
        robotInfo.append(userName);
        robotInfo.append(" ");
        robotInfo.append(teamNum);
    }
    /**
    *增加部件名字 
    * @param str 部件的名字
    */
    void addObj(Obj *generic)
    {
        obj.push_back(generic);
    }
    /**
     *获取当前机器人部件总数 
     * @return size_t 部件总数
     */
    size_t getObjNums()
    {
        return obj.size();
    }
};
} // namespace ncrapi
extern ncrapi::SystemData *sysData;
