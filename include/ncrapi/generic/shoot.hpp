/**
 * @Author: 陈昱安
 * @Date:   2018-10-23T21:46:55+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-27T22:41:40+08:00
 */

#ifndef SHOOT_HPP_
#define SHOOT_HPP_
#include "generic.hpp"
template <size_t _nums>
class LinearShoot : public Generic<_nums>
{
  private:
    const pros::ADIDigitalIn _limit;

  public:
    LinearShoot(const std::array<pros::Motor, _nums> &motorList, const pros::ADIDigitalIn &limit,
                const int hold = 10)
        : Generic<_nums>(motorList, hold), _limit(limit) {}
    /**
    * 重置弹射马达编码器
    */
    void resetEnc()
    {
        for (auto &it : Generic<_nums>::_motorList)
            it.tare_position();
    }
    /**
     * 获取弹射编码器值
     * @return 弹射编码器的值
     */
    double getEnc()
    {
        double temp = 0;
        for (auto &it : Generic<_nums>::_motorList)
            temp += it.get_position();
        return temp / _nums;
    }
    /**
     * 获取行程开关当前值
     * @return 返回行程开关值
     */
    std::int32_t getLimit()
    {
        return _limit.get_value();
    }
};
#endif /* end of include guard: SHOOT_HPP_ */
