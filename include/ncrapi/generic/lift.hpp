#ifndef LIFT_HPP_
#define LIFT_HPP_
#include "generic.hpp"
#include "shoot.hpp"
#if defined(ROBOT_ALMIGHTY) //全能机
extern Shoot<1> shoot;

#elif defined(ROBOT_CAP) //盘子机

#else //矮子机
extern Shoot<2> shoot;
#endif

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
#if defined(ROBOT_ALMIGHTY) //全能机
            shoot.setMode(false);

#elif defined(ROBOT_CAP) //盘子机

#else //矮子机

#endif
            Generic<_nums>::_holdingFlag = 1;
            if (temp < _liftUpVal)
                Generic<_nums>::set(127);
            else
                Generic<_nums>::set(10);
        }
        else if (down)
        {
#if defined(ROBOT_ALMIGHTY) //全能机
            shoot.setMode(false);

#elif defined(ROBOT_CAP) //盘子机

#else //矮子机

#endif

            Generic<_nums>::_holdingFlag = -1;
            if (temp > 20)
                Generic<_nums>::set(-127);
            else
                Generic<_nums>::set(-10);
        }
        else
        {
#if defined(ROBOT_ALMIGHTY) //全能机
            if (Generic<_nums>::getEnc() <= 20)
                shoot.setMode(true);

#elif defined(ROBOT_CAP) //盘子机

#else //矮子机

#endif

            Generic<_nums>::holding();
        }
    }
};
#endif /* end of include guard: LIFT_HPP_ */
