/**
 * @Author: 陈昱安
 * @Date:   2018-10-23T21:46:55+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:56:41+08:00
 */

#ifndef SHOOT_HPP_
#define SHOOT_HPP_
#include "generic.hpp"
/**
 * 撞针式弹射
 */

template <size_t _nums>
class Shoot : public Generic<_nums>
{
  private:
    const pros::ADIDigitalIn _limit;
    const int _shootReadyVal;
    const int _shootShootVal;
    const uint32_t _waittingTime;
    const uint32_t _maxTime; //弹射驱动允许最大时间
    uint32_t _time = 0;
    int _state;                 //状态 -1发射中 0:发射结束状态 1:准备状态
    bool _mode;                 //模式 false 手动模式 true 自动模式
    bool _shootBtnFlag = false; //    volatile
    int _shootMode;             // 驱动轴转一圈重置度数
  public:
    Shoot(const std::array<pros::Motor, _nums> &motorList, const pros::ADIDigitalIn &limit, const int shootReadyVal, const int shootShootVal, const uint32_t waittingTime, const uint32_t maxTime, const int shootMode, const int hold)
        : Generic<_nums>(motorList, hold), _limit(limit), _shootReadyVal(shootReadyVal), _shootShootVal(shootShootVal), _waittingTime(waittingTime), _maxTime(maxTime), _shootMode(shootMode)
    {
        Generic<_nums>::resetEnc();
        _state = 0;
        _mode = true;
    }
    /**
     * 获取行程开关当前值
     * @return 返回行程开关值
     */
    std::int32_t getLimit()
    {
        return _limit.get_value();
    }
    /**
    * 射球
    * @param x true发射
    */
    void shootingSet(bool x)
    {
        _mode = true;
        _shootBtnFlag = x;
    }
    double getSensors()
    {
        double temp = Generic<_nums>::getEnc();
        if (temp >= _shootMode || temp < 0 || _limit.get_value()) //V5行程开关按下去是1
        {
            Generic<_nums>::resetEnc();
            return 0;
        }
        else
            return temp;
    }
    int getState()
    {
        double temp = getSensors();
        if (temp >= _shootReadyVal && temp < _shootShootVal)
        {
            _state = 1;
            return 1;
        }
        else if (temp >= _shootShootVal)
        {
            _state = -1;
            return -1;
        }
        else
        {
            _state = 0;
            return 0;
        }
    }
    /**
 * 打开关闭自动准备模式
 * @param mode true 打开自动模式 false 关闭自动模式
 */
    void setMode(bool mode)
    {
        if (!mode)
        {
            _mode = false;
            Generic<_nums>::_holdingFlag = 0;
        }
        else
            _mode = true;
    }
    virtual void holding() override
    {
        getState();
        if (_mode)
            if (((!_state && pros::millis() - _time >= _waittingTime) || (_state != -1 && _shootBtnFlag)) && pros::millis() - _time <= _waittingTime + _maxTime) //如果编码器值小于阀值 且 循环时间距离上次循环的时间小于1000毫秒 且FLAG==1
            {
                Generic<_nums>::set(127); //往后拉
                Generic<_nums>::_holdingFlag = 1;
            }
            else if (_state == -1) //发射中
            {
                Generic<_nums>::_holdingFlag = 0;
                _shootBtnFlag = false;
                _time = pros::millis();
                Generic<_nums>::set(0); //发射过程中马达不转
            }
            else
                Generic<_nums>::set(Generic<_nums>::_holdVal * Generic<_nums>::_holdingFlag);
        else
            Generic<_nums>::set(Generic<_nums>::_holdVal * Generic<_nums>::_holdingFlag);
    }
    virtual void joyControl(const bool &up, const bool &down, const bool &shootBtn)
    {
        if (up) //发射
        {
            Generic<_nums>::set(127);
            //set(127);
            _time = pros::millis();
            Generic<_nums>::_holdingFlag = 1;
            _shootBtnFlag = false;
            _mode = false;
        }
        else if (down) //回弹
        {
            Generic<_nums>::set(-127);
            _time = pros::millis();
            Generic<_nums>::_holdingFlag = 0;
            _shootBtnFlag = false;
            _mode = false;
        }
        else if (shootBtn)
        {
            _time = pros::millis();
            Generic<_nums>::_holdingFlag = 0;
            _shootBtnFlag = true;
            _mode = true;
        }
        else
            holding();
    }
    /**
 * 单键控制的全自动发射模式
 * @param shootBtn 发射按钮
 */
    virtual void joyControl(const bool &shootBtn)
    {

        if (shootBtn)
        {
            _time = pros::millis();
            Generic<_nums>::_holdingFlag = 0;
            _shootBtnFlag = true;
            _mode = true;
        }
        else
            holding();
    }
    //多线程循环函数
    void loop()
    {
        uint32_t now = pros::millis();
        while (true)
        {
            holding();
            pros::c::task_delay_until(&now, 10);
        }
    }
};

#endif /* end of include guard: SHOOT_HPP_ */
