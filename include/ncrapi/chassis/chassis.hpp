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
constexpr int realSpeed[128] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
    73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
    97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
    121, 122, 123, 124, 125, 126, 127};
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
     * @param verticalVal     前后的通道
     * @param horizontalVal    左右的通道
     * @param threshold 遥控器矫正阀值
     */
    void arcade(int verticalVal, int horizontalVal, const int rotateMaxSpeed = 127, const int threshold = 0, const int speedMode[128] = realSpeed)
    {

        if (abs(verticalVal) < threshold)
            verticalVal = 0;
        if (abs(horizontalVal) < threshold)
            horizontalVal = 0;
        else if (abs(horizontalVal) >= rotateMaxSpeed)
            horizontalVal = static_cast<int>(copysign(rotateMaxSpeed, static_cast<float>(horizontalVal)));
        int left = verticalVal + horizontalVal;
        int right = verticalVal - horizontalVal;
        int leftSign = static_cast<int>(copysign(1.0, static_cast<float>(left)));
        int rightSign = static_cast<int>(copysign(1.0, static_cast<float>(right)));
        if (left > 127 || left < -127)
            left = 127 * leftSign;
        if (right > 127 || right < -127)
            right = 127 * rightSign;
        set(speedMode[left] * leftSign, speedMode[right] * rightSign);
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
     * 获取左边马达平均温度
     * @return 返回左边马达平均温度
     */
    double getTemperatureLeft()
    {
        double sum = 0;
        for (size_t i = 0; i < 2; i++)
            sum += _motorList[i].get_temperature();
        return sum / 2;
    }
    /**
     * 获取右边马达平均温度
     * @return 返回右边马达平均温度
     */
    double getTemperatureRight()
    {
        double sum = 0;
        for (size_t i = 2; i < 4; i++)
            sum += _motorList[i].get_temperature();
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
