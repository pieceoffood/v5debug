#ifndef INTAKE_HPP_
#define INTAKE_HPP_
#include "generic.hpp"
template <size_t _nums>
class CapIntake : public Generic<_nums>
{
  private:
    const int _capUpVal; //升到顶值
  public:
    CapIntake(const std::array<pros::Motor, _nums> &motorList, const int capUpVal, const int hold) : Generic<_nums>(motorList, hold), _capUpVal(capUpVal)
    {
    }
    /**
     * 夹子遥控模块
     * @param up   张开
     * @param down 夹紧
     */
    virtual void joyControl(const bool up, const bool down) override
    {
        double temp = Generic<_nums>::getEnc();
        bool tempIsSafe = Generic<_nums>::isSafeMode();
        if (up)
        {
            if (temp < _capUpVal && !tempIsSafe)
                Generic<_nums>::set(127);
            else
                Generic<_nums>::set(10);
            Generic<_nums>::_holdingFlag = 1;
        }
        else if (down)
        {
            if (temp > 5 && !tempIsSafe)
                Generic<_nums>::set(-127);
            else
                Generic<_nums>::set(-10);
            Generic<_nums>::_holdingFlag = -1;
        }
        else
        {
            Generic<_nums>::holding();
        }
    }
    /**
     * 设置夹子开或者关
     * @param mode true:张开 false:夹紧
     */
    virtual void setMode(bool mode)
    {
        if (mode)
            Generic<_nums>::_holdingFlag = 1;
        else
            Generic<_nums>::_holdingFlag = -1;
    }
};
#if defined(ROBOT_ALMIGHTY) //全能机
extern CapIntake<1> capIntake;

#elif defined(ROBOT_CAP) //盘子机

#else //矮子机

#endif
#endif /* end of include guard: INTAKE_HPP_ */
