/**
 * @Author: 陈昱安
 * @Date:   2018-10-23T22:43:01+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-27T22:25:03+08:00
 */

#ifndef GENERIC_HPP_
#define GENERIC_HPP_

#include "api.h"
#include <array>
#include <memory>

/**
 * 机器人功能基础类 开环控制
 * @param a    马达对象
 * @param hold 悬停值
 */
template <size_t _nums>
class Generic
{
  protected:
    const std::array<pros::Motor, _nums> _motorList;
    const int _holdVal;
    int _holdingFlag = 0;
    int _pwm = 0;

  public:
    Generic(const std::array<pros::Motor, _nums> &motorList, const int hold = 0) : _motorList(motorList), _holdVal(hold)
    {
        resetEnc();
    }
    virtual void set(const int pwm)
    {
        for (auto &it : _motorList)
            it.move(pwm);
    }
    virtual void stop()
    {
        for (auto &it : _motorList)
            it.move(0);
    }
    virtual void holding()
    {
        set(_holdVal * _holdingFlag);
    }

    virtual void joyControl(const bool up, const bool down)
    {
        if (up)
        {
            set(127);
            _holdingFlag = 1;
        }
        else if (down)
        {
            set(-127);
            _holdingFlag = -1;
        }
        else
            holding();
    }
    /**
    * 重置马达编码器
    */
    virtual void resetEnc()
    {
        for (auto &it : _motorList)
            it.tare_position();
    }
    /**
     * 获取编码器值
     * @return 弹射编码器的值
     */
    virtual double getEnc()
    {
        double temp = 0;
        for (auto &it : _motorList)
            temp += it.get_position();
        return temp / _nums;
    }
    /**
     * 设置马达制动模式
     * @param mode 马达制动的模式
     */
    virtual void setBrakeMode(pros::motor_brake_mode_e_t mode)
    {
        for (auto &it : _motorList)
            it.set_brake_mode(mode);
    }
};
#endif
