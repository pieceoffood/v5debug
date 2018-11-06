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
    size_t _safeModeFlags = 0;

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
     * 获取速度
     * @return 返回速度
     */
    virtual double getSpeed()
    {
        double temp = 0;
        for (auto &it : _motorList)
            temp += it.get_actual_velocity();
        return temp / _nums;
    }
    /**
     * 获取电机瓦数
     * @return 返回电机瓦数
     */
    virtual double getPower()
    {
        double temp = 0;
        for (auto &it : _motorList)
            temp += it.get_power();
        return temp / _nums;
    }
    /**
     * 获取电机以mA为单位的电流。
     * @return 获取电机以mA为单位的电流。
     */
    virtual int getCurrent()
    {
        double temp = 0;
        for (auto &it : _motorList)
            temp += it.get_current_draw();
        return temp / _nums;
    }
    /**
     * 获取电机效率
     * @return 以百分比形式返回电机效率
     */
    virtual double getEfficiency()
    {
        double temp = 0;
        for (auto &it : _motorList)
            temp += it.get_efficiency();
        return temp / _nums;
    }
    /**
     * 获取电机扭矩
     * @return 返回电机扭矩
     */
    virtual double getTorque()
    {
        double temp = 0;
        for (auto &it : _motorList)
            temp += it.get_torque();
        return temp / _nums;
    }
    /**
     * 获取电机平均温度
     * @return 返回电机平均温度
     */
    virtual double getTemperature()
    {
        double temp = 0;
        for (auto &it : _motorList)
            temp += it.get_temperature();
        return temp / _nums;
    }
    /**
     * 检测部件是否堵转
     * @return 返回false 没有堵转,返回true 堵转了
     */
    virtual bool isSafeMode()
    {
        if (getSpeed() == 0 && !getPower())
        {
            _safeModeFlags++;
            if (_safeModeFlags > 10)
                return true;
            else
                return false;
        }
        else
        {
            _safeModeFlags = 0;
            return false;
        }
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
