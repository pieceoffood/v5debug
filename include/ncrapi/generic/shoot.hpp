#ifndef SHOOT_HPP_
#define SHOOT_HPP_
#include "generic.hpp"
template <size_t _nums>
class LinearShoot : protected Generic<_nums>
{
  private:
  public:
    LinearShoot(const std::array<pros::Motor, _nums> &motorList, const int hold = 10) : Generic<_nums>(motorList, hold) {}
};
#endif /* end of include guard: SHOOT_HPP_ */
