/**
 * @Author: yan
 * @Date:   2018-10-15T14:29:17+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T17:03:00+08:00
 */
#ifndef CHASSIS_HPP_
#define CHASSIS_HPP_
#include "api.h"
#include <array>
/**
 * 基础开环控制(无传感器马达类)
 * @param motorList 马达类别 注意加{}
 */
class Chassis
{
  private:
    // pros::Motor motorList[4];
    const std::array<pros::Motor, 4> _motorList;

  public:
    Chassis(const std::array<pros::Motor, 4> &motorList) : _motorList(motorList) {}
    ~Chassis() {}
    void set(const int left, const int right)
    {
        for (size_t i = 0; i < 2; i++)
            _motorList[i].move(left);
        for (size_t i = 2; i < 4; i++)
            _motorList[i].move(right);
    }
    /**
     * 普通前进后退 开环控制
     * @param pwm  前进+ 后退- 范围:+-127
     */
    void forward(const int pwm)
    {
        set(pwm, pwm);
    }
    /**
     * 普通旋转 开环控制
     * @param pwm 左转+ 右转- 范围:+-127
     */
    void rotate(const int pwm)
    {
        set(-pwm, pwm);
    }
    /**
     * 底盘马达停转
     */
    void stop()
    {
        set(0, 0);
    }
    void arcade(int leftY, int rightX)
    {
    }
};
#endif /* end of include guard: CHASSIS_HPP_ */
