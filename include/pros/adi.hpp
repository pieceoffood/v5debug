/**
 * @Author: 陈昱安
 * @Date:   2018-09-24T21:24:39+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-24T21:42:12+08:00
 */
#ifndef _PROS_ADI_HPP_
#define _PROS_ADI_HPP_

#include "pros/adi.h"

#include <cstdint>

namespace pros
{
class ADIPort
{
  public:
    /**
   * 构造函数:配置一个ADI端口作为一个给定的传感器类型。
   * @param port 端口号（从1-8，‘a’-h’，‘a’-h’）配置
   * @param type 端口的配置类型
   */
    ADIPort(std::uint8_t port, adi_port_config_e_t type = E_ADI_TYPE_UNDEFINED);

    virtual ~ADIPort(void);

    /**
 * 返回给定ADI端口的配置。
 * @return  返回给定ADI端口的配置。
 */
    std::int32_t get_config(void) const;

    /**
 * 返回给定ADI端口的值。
 * @return  返回给定ADI端口的值。
 */
    std::int32_t get_value(void) const;

    /**
 * 将ADI端口配置为充当给定的传感器类型。
 * @param  type 端口的配置类型
 * @return  如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    std::int32_t set_config(adi_port_config_e_t type) const;

    /**
 * 设置给定ADI端口的值,这仅适用于配置为输出的端口，并且行为将根据端口的配置而更改。
 * @param  value 需要设置的值
 * @return       如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    std::int32_t set_value(std::int32_t value) const;

  protected:
    ADIPort(void);
    std::uint8_t _port;
};

class ADIAnalogIn : private ADIPort
{
  public:
    /**
   * 构造函数 配置一个ADI端口作为一个模拟输入。
   * @param port ADI端口号（从1-8，‘a’-h’，‘a’-h’）配置
   */
    ADIAnalogIn(std::uint8_t port);

    /**
  * 校准指定通道上的模拟传感器。
  * 该方法假设此时真实传感器值没有主动改变，并计算大约500个样本的平均值，相隔1 ms，持续0.5秒的校准时间。返回并存储如此计算的平均值，
  * 以便稍后调用 adi_analog_read_calibrated和adi_analog_read_calibrated_HR函数。这些函数将在调用时返回此值与当前传感器值之间的差值。
  * 当传感器值可能不稳定（陀螺仪旋转，加速度计移动）时，请勿使用此功能。
  * 注意ADI当前以10ms的间隔返回数据，与校准功能的1ms采样率相反。为了与PROS 2类似，保留该采样率，并且增加采样率将不会在功能性能方面产生明显差异。
  * @return  此函数计算的平均传感器值。
  */
    std::int32_t calibrate(void) const;

    /**
 * 读取模拟输入通道的校准值。
 * 所述adi_analog_calibrate功能必须首先在该通道上运行。
 * 此功能不适合用于积分的传感器值，因为舍入误差会累积，从而导致随时间漂移。请改用adi_analog_read_calibrated_HR。
 * @return  传感器值与其校准默认值（-4095到4095）之间的差值。
 */
    std::int32_t get_value_calibrated(void) const;

    /**
 * 以更高的精度读取模拟输入通道1-8的校准值。
 * 该adi_analog_calibrate功能必须先运行。
 * 这适用于陀螺仪和加速度计等集成传感器值，以减少由于四舍五入引起的漂移，不应用于线路跟踪器或电位计等传感器。
 * 返回的值实际上具有16位“精度”，即使ADC仅读取12位，因此当在时间上积分时，由两个值之间的平均值引起的误差在洗涤中出现。将值视为真实值乘以16。
 * @return  传感器值与校准默认值-16384到16384之间的差值。
 */
    std::int32_t get_value_calibrated_HR(void) const;

    //get_value继承自ADIPort
    using ADIPort::get_value;
};

using ADIPotentiometer = ADIAnalogIn;
using ADILineSensor = ADIAnalogIn;
using ADILightSensor = ADIAnalogIn;
using ADIAccelerometer = ADIAnalogIn;

class ADIAnalogOut : private ADIPort
{
  public:
    /**
   * 配置一个ADI端口作为模拟输出。
   * @param port ADI端口号（从1-8，‘a’-h’，‘a’-h’）配置
   */
    ADIAnalogOut(std::uint8_t port);
    //继承set_value
    using ADIPort::set_value;
};

class ADIDigitalOut : private ADIPort
{
  public:
    /**
   * 配置一个ADI端口作为数字输出
   * @param port       ADI端口号（从1-8，‘a’-h’，‘a’-h’）配置
   * @param init_state 默认状态LOW 或者HIGH
   */
    ADIDigitalOut(std::uint8_t port, bool init_state = LOW);

    //继承了set_value
    using ADIPort::set_value;
};

class ADIDigitalIn : private ADIPort
{
  public:
    /**
   * 配置一个ADI端口作为数字输入
   * @param port   ADI端口号（从1-8，‘a’-h’，‘a’-h’）配置
   */
    ADIDigitalIn(std::uint8_t port);

    /**
	 *返回数字按钮按下的上升边框。
	 *此功能不是线程安全的。轮询单个按钮的多个任务在相同的情况下可能会返回不同的结果，因此只有一个任务应该为任何给定的按钮调用此函数。
	 *例如，任务A为按钮1和2调用此功能。任务B可以为按钮3调用此功能，但不应该为按钮1或2调用此函数。此功能的典型用例是调用opcontrol内部以检测新按钮按下，而不是任何其他任务。
	 * @return  如果按下控制器上的按钮并且上次调用此函数时没有按下，则返回 1，否则返回 0。
	 */
    std::int32_t get_new_press(void) const;

    //继承了set_value
    using ADIPort::get_value;
};

using ADIButton = ADIDigitalIn;

class ADIMotor : private ADIPort
{
  public:
    /**
   * 配置一个ADI端口作为马达
   * @param port 马达端口号
   */
    ADIMotor(std::uint8_t port);

    /**
 * 停止当前电机
 * @return  如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    std::int32_t stop(void) const;

    //继承设置值(+-127)
    using ADIPort::set_value;

    //获取当前设置值
    using ADIPort::get_value;
};

class ADIEncoder : private ADIPort
{
  public:
    /**
   * 配置一个ADI端口作为双向编码器
   * @param port_top    来自编码器传感器的“顶部”电线，可拆卸盖板朝上。这应该在端口1,3,5或7（'A'，'C'，'E'，'G'）。
   * @param port_bottom 来自编码器传感器的“底部”导线
   * @param reversed    传感器将以相反的方向计数。默认值为“false”。
   */
    ADIEncoder(std::uint8_t port_top, std::uint8_t port_bottom, bool reversed = false);

    /**
	* 重置编码器
    * @return  返回：如果操作成功则返回 1，否则返回 PROS_ERR。
	*/
    std::int32_t reset(void) const;

    /**
 *获取编码器记录的刻度数。
 *转一圈的值为360
 * @return  返回编码器的当前积分值
 */
    std::int32_t get_value(void) const;
};

class ADIUltrasonic : private ADIPort
{
  public:
    /**
   * 配置一个ADI端口给超声波传感器
   * @param port_echo 连接到黄色INPUT电缆的端口。这应该在端口1,3,5或7（'A'，'C'，'E'，'G'）。
   * @param port_ping 连接到橙色OUTPUT电缆的端口。这应该是在port_echo之后的下一个最高端口。
   */
    ADIUltrasonic(std::uint8_t port_echo, std::uint8_t port_ping);

    //以厘米为单位获取当前超声波传感器值。
    using ADIPort::get_value;
};

class ADIGyro : private ADIPort
{
  public:
    /**
 * 在给定端口上初始化陀螺仪。如果先前未将给定端口配置为陀螺仪，则此功能将启动1秒校准周期。
 * 如果需要校准，强烈建议在机器人静止时从初始化调用此功能。
 * @param port       ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）初始化为陀螺仪
 * @param multiplier 	标量值将由陀螺仪航向值多重化
 */
    ADIGyro(std::uint8_t port, double multiplier = 1);

    ~ADIGyro(void) override;

    /**
 * 获取当前陀螺仪角度，以十分之一度为单位。除非将乘数应用于陀螺仪，否则返回值将是表示旋转度数10的整数。
 * 圆圈有360度，因此陀螺仪将返回3600一整圈。
 * @return  陀螺仪角度，以十分之一度为单位。
 */
    double get_value(void) const;

    /**
 * 将陀螺仪值重置为零。
 * @return  返回：如果操作成功或PROS_ERR操作失败，则返回 1 ，设置errno。
 */
    std::int32_t reset(void) const;
};
} // namespace pros

#endif // _PROS_ADI_HPP_
