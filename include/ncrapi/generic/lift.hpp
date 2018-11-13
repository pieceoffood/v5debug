#ifndef LIFT_HPP_
#define LIFT_HPP_
#include "generic.hpp"
#include "shoot.hpp"
extern Shoot<1> shoot;
template <size_t _nums>
class Lift : public Generic<_nums>
{
  private:
    int _liftUpVal; //升到顶值

  public:
    Lift(const std::array<pros::Motor, _nums> &motorList, const int liftUpVal, const int hold = 10) : Generic<_nums>(motorList, hold), _liftUpVal(liftUpVal)
    {
        Generic<_nums>::setBrakeMode(pros::E_MOTOR_BRAKE_HOLD); //设置为悬停模式
        Generic<_nums>::resetEnc();
    }
    void joyControl(const bool up, const bool down) override
    {
        double temp = Generic<_nums>::getEnc();
        bool isSafe = Generic<_nums>::isSafeMode();
        if (up)
        {
            shoot.setMode(false);
            Generic<_nums>::_holdingFlag = 1;
            if (temp < _liftUpVal)
                Generic<_nums>::set(127);
            else
                Generic<_nums>::set(10);
        }
        else if (down)
        {
            shoot.setMode(false);
            Generic<_nums>::_holdingFlag = -1;
            if (temp > 20)
                Generic<_nums>::set(-127);
            else
                Generic<_nums>::set(-10);
        }
        else
        {
            if (Generic<_nums>::getEnc() <= 20)
                shoot.setMode(true);
            Generic<_nums>::holding();
        }
    }
};
#endif /* end of include guard: LIFT_HPP_ */
