#ifndef LIFT_HPP_
#define LIFT_HPP_
#include "generic.hpp"
template <size_t _nums>
class Lift : public Generic<_nums>
{
  private:
    const int _liftUpVal; //升到顶值

  public:
    Lift(const std::array<pros::Motor, _nums> &motorList, const int liftUpVal) : Generic<_nums>(motorList), _liftUpVal(liftUpVal)
    {
        Generic<_nums>::setBrakeMode(pros::E_MOTOR_BRAKE_HOLD); //设置为悬停模式
        Generic<_nums>::resetEnc();
    }
    virtual void joyControl(const bool &up, const bool &down) override
    {
        if (up && Generic<_nums>::getEnc() <= _liftUpVal)
        {
            Generic<_nums>::set(127);
        }
        else if (down && Generic<_nums>::getEnc() >= 0)
        {
            Generic<_nums>::set(-127);
        }
        else
        {
            Generic<_nums>::set(0);
        }
    }
};
#endif /* end of include guard: LIFT_HPP_ */
