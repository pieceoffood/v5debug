#ifndef SHOOT_HPP_
#define SHOOT_HPP_
#include "okapi\impl\device\motor\motor.hpp"
#include <array>
template <size_t nums>
class SHOOT
{
  private:
    std::array<okapi::Motor *, nums> _motorList;

  public:
    explicit SHOOT<1>(okapi::Motor *a) : _motorList(a) {}                     //一个马达
    explicit SHOOT<2>(okapi::Motor *a, okapi::Motor *b) : _motorList(a, b) {} //两个马达
    void set(const int x)
    {
        for (auto it : _motorList)
            it.moveVoltage(x);
    }
    void joyContorl()
    {
    }
};
#endif /* end of include guard:SHOOT_HPP_ */
