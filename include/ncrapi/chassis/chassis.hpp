/**
 * @Author: yan
 * @Date:   2018-10-15T14:29:17+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-26T09:25:41+08:00
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
    const pros::ADIGyro _gyro;

  public:
    Chassis(const std::array<pros::Motor, 4> &motorList, const pros::ADIGyro &gyro) : _motorList(motorList), _gyro(gyro)
    {
        resetEnc();
    }
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
    void arcade(int leftY, int rightX, const int rotateMaxSpeed, const int threshold = 0)
    {

        if (abs(leftY) < threshold)
            leftY = 0;
        if (abs(rightX) < threshold)
            rightX = 0;
        else if (abs(rightX) >= rotateMaxSpeed)
            rightX = static_cast<int>(copysign(rotateMaxSpeed, static_cast<float>(rightX)));
        int left = leftY + rightX;
        int right = leftY - rightX;
        if (left > 127 || left < -127)
            left = static_cast<int>(copysign(127.0, static_cast<float>(left)));
        if (right > 127 || right < -127)
            right = static_cast<int>(copysign(127.0, static_cast<float>(right)));
        set(left, right);
    }
    /**
     * 重置底盘所有马达编码器
     */
    void resetEnc()
    {
        for (auto &it : _motorList)
            it.tare_position();
    }
    /**
     * 重置陀螺仪
     */
    void resetGyro()
    {
        _gyro.reset();
    }
    /**
     * 获取左侧底盘编码器值
     * @return 返回左侧底盘编码器值
     */
    double getEncLeft()
    {
        double sum = 0;
        for (size_t i = 0; i < 2; i++)
            sum += _motorList[i].get_position();
        return sum / 2;
    }
    /**
     * 获取右侧底盘编码器值
     * @return 返回右侧底盘编码器值
     */
    double getEncRight()
    {
        double sum = 0;
        for (size_t i = 2; i < 4; i++)
            sum += _motorList[i].get_position();
        return sum / 2;
    }
    /**
     * 获取底盘左右两个的编码器值
     * @return 返回四个底盘马达编码器的平均值
     */
    double getEncAll()
    {
        return (getEncLeft() + getEncRight()) / 2;
    }
    /**
     * 获取陀螺仪读数
     * @return 陀螺仪返回值
     */
    double getGyro()
    {
        return _gyro.get_value();
    }
};
#endif /* end of include guard: CHASSIS_HPP_ */
