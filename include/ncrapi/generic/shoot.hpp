/**
 * @Author: 陈昱安
 * @Date:   2018-10-23T21:46:55+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-24T21:07:37+08:00
 */

#ifndef SHOOT_HPP_
#define SHOOT_HPP_
#include "generic.hpp"
template <size_t _nums>
class LinearShoot : protected Generic<_nums>
{
  private:
  public:
    LinearShoot(const std::array<pros::Motor *, _nums> &motorList, const int hold = 10) : Generic<_nums>(motorList, hold) {}
};
#endif /* end of include guard: SHOOT_HPP_ */
