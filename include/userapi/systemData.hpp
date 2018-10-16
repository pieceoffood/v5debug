/**
 * @Author: yan
 * @Date:   2018-10-11T13:18:43+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:28:17+08:00
 */
#ifndef SYSTEMDATA_HPP_
#define SYSTEMDATA_HPP_
struct systemData
{
    //自动赛参数
    bool autoIsMode = 0;       //自动赛模式 普通自动0 纯自动1
    int autoSide = 0;          //红方 0 蓝方360
    bool autoIsFR = 0;         //前场0 后场1
    bool autoIsFlag = 0;       //射高旗0 射中旗1
    bool autoIsShootFlag = 0;  //是否射中间的旗子 0不射 1射
    bool autoIsRunPlat = 0;    //0不开台 1 开台
    bool autoIsBumperFlag = 0; //0不撞中间旗 1 撞中间旗子
    //传感器数据
};
extern systemData sysData;

#endif /* end of include guard: SYSTEMDATA_HPP_ */
