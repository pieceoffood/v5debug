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
        Generic<_nums>::resetEnc();
    }
    // virtual void holding() override
    // {
    //     if (Generic<_nums>::_holdingFlag == -1)
    //         Generic<_nums>::set(Generic<_nums>::_holdVal * Generic<_nums>::_holdingFlag);
    //     else
    //         Generic<_nums>::set(0);
    // }
    /**
     * 夹子遥控模块
     * @param up   张开
     * @param down 夹紧
     */
    virtual void joyControl(const bool up, const bool down) override
    {
        double temp = Generic<_nums>::getEnc();
        if (up)
        {
            if (temp < _capUpVal)
                Generic<_nums>::set(127);
            else
                Generic<_nums>::set(10);
            Generic<_nums>::_holdingFlag = 1;
        }
        else if (down)
        {
            if (temp > 5)
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
};
#endif /* end of include guard: INTAKE_HPP_ */
