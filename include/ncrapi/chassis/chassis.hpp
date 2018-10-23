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
    /**
     * 遥控模块 单摇杆双摇杆都用这个
     * @param leftY     前后的通道
     * @param rightX    左右的通道
     * @param threshold 遥控器矫正阀值
     */
    void arcade(int leftY, int rightX, const int threshold = 0)
    {
        if (abs(leftY) < threshold)
            leftY = 0;
        if (abs(rightX) < threshold)
            rightX = 0;

        int left = leftY + rightX;
        int right = leftY - rightX;
        if (left > 127 || left < -127)
            left = static_cast<int>(copysign(127.0, static_cast<float>(left)));
        if (right > 127 || right < -127)
            right = static_cast<int>(copysign(127.0, static_cast<float>(right)));
        set(left, right);
    }
};
#endif /* end of include guard: CHASSIS_HPP_ */
