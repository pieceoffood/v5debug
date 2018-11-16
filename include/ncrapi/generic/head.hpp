#ifndef HEAD_HPP_
#define HEAD_HPP_
#include "generic.hpp"
template <size_t _nums>
class Head : public Generic<_nums>
{
  private:
    int _headLimitValue = 0;

  public:
    Head(const std::array<pros::Motor, _nums> &motorList, const int hold = 0) : Generic<_nums>(motorList, hold)
    {
        Generic<_nums>::resetEnc();
        Generic<_nums>::setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    }
    virtual void joyControl(const bool up, const bool down) override
    {
        bool tempIsSafe = Generic<_nums>::isSafeMode();
        if (up)
        {
            if (!tempIsSafe)
                Generic<_nums>::set(127);
            else
                Generic<_nums>::set(5);
            Generic<_nums>::_holdingFlag = 1;
        }
        else if (down)
        {
            if (!tempIsSafe)
                Generic<_nums>::set(-127);
            else
                Generic<_nums>::set(-5);
            Generic<_nums>::_holdingFlag = -1;
        }
        else
        {
            Generic<_nums>::holding();
        }
    }
};
#endif /* end of include guard: HEAD_HPP_ */
