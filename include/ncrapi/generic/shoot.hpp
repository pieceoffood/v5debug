/**
 * @Author: 陈昱安
 * @Date:   2018-10-23T21:46:55+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-26T08:18:22+08:00
 */

#ifndef SHOOT_HPP_
#define SHOOT_HPP_
#include "generic.hpp"
template <size_t _nums>
class LinearShoot : protected Generic<_nums>
{
  private:
    std::shared_ptr<pros::ADIDigitalIn> _limit;

  public:
    LinearShoot(const std::array<pros::Motor *, _nums> &motorList, const int hold = 10, std::shared_ptr<pros::ADIDigitalIn> limit)
        : Generic<_nums>(motorList, hold), _limit(limit) {}
    bool getLimit()
    {
    }
};
#endif /* end of include guard: SHOOT_HPP_ */
