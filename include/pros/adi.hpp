/**
 * @Author: 陈昱安
 * @Date:   2018-10-11T21:09:49+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-25T08:29:41+08:00
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
	*将ADI端口配置为充当给定的传感器类型。
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	* \ param端口
	*要配置的ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）
	* \ param类型
	*端口的配置类型
	 */
    ADIPort(std::uint8_t port, adi_port_config_e_t type = E_ADI_TYPE_UNDEFINED);

    virtual ~ADIPort(void);

    /**
	*获取给定ADI端口的配置。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return给定端口的ADI配置
	 */
    std::int32_t get_config(void) const;

    /**
	*获取给定ADI端口的值。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return为给定端口存储的值
	 */
    std::int32_t get_value(void) const;

    /**
	*将ADI端口配置为充当给定的传感器类型。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param类型
	*端口的配置类型
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    std::int32_t set_config(adi_port_config_e_t type) const;

    /**
	*设置给定ADI端口的值。
	*
	*这仅适用于配置为输出的端口，行为将
	*根据端口的配置而改变。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param值
	*将ADI端口设置为的值
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。.
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
	*配置ADI端口作为模拟输入。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param端口
	*要配置的ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）
	* \ param类型
	*端口的配置类型
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    ADIAnalogIn(std::uint8_t port);

    /**
	*校准指定端口上的模拟传感器并返回新的模拟传感器校准值。
	*
	*此方法假定真正的传感器值没有主动改变
	*这次计算大约500个样本的平均值，1 ms
	*分开，进行0.5秒的校准。由此计算出的平均值
	*被返回并存储以供以后调用
	* pros :: ADIAnalogIn :: get_value_calibrated（）和
	* pros :: ADIAnalogIn :: get_value_calibrated_HR（）函数。这些功能
	*将返回此值与当前传感器值之间的差值
	*被叫时
	*
	*当传感器值可能不稳定时，请勿使用此功能（陀螺仪旋转，加速度计运动）。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return此功能计算的平均传感器值
	 */
    std::int32_t calibrate(void) const;

    /**
	*获取模拟输入端口的12位校准值。
	*
	*必须首先运行pros :: ADIAnalogIn :: calibrate（）函数。这个
	*函数不适合用于集成的传感器值，如舍入误差会累积，导致随时间漂移。使用
	* pros :: ADIAnalogIn :: get_value_calibrated_HR（）代替。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return传感器值与其校准默认值的差值
	* -4095至409
	 */
    std::int32_t get_value_calibrated(void) const;

    /**
	*获取模拟输入端口的16位校准值。
	*
	*必须首先运行pros :: ADIAnalogIn :: calibrate（）函数。这是
	*用于集成传感器值，如陀螺仪和加速度计
	*减少由于四舍五入引起的漂移，不应用于传感器，如a
	*线跟踪器或电位器。
	*
	*返回的值实际上有16位“精度”，即使是ADC
	*仅读取12位，因此由平均值引起的误差为
	*随着时间的推移积分两个值之间是微不足道的。想想价值
	*作为真实值乘以16。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return传感器值与其校准默认值的差值
	* -16384至16384
	 */
    std::int32_t get_value_calibrated_HR(void) const;

    /**
	*获取指定端口的12位值。
	*
	*如果模拟引脚已切换为a，则返回的值不确定
	*不同的模式。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return模拟传感器值，其中值0反映输入
	*近0 V的电压和4095的值反映了输入电压
	*接近5 V
	 */
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
	*配置ADI端口作为模拟输出。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param端口
	*要配置的ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）
	* \ param类型
	*端口的配置类型
	 */
    ADIAnalogOut(std::uint8_t port);

    /**
	*设置给定ADI端口的值。
	*
	*这仅适用于配置为输出的端口，行为将
	*根据端口的配置而改变。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param值
	*将ADI端口设置为的值
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    using ADIPort::set_value;
};

class ADIDigitalOut : private ADIPort
{
  public:
    /**
	*将ADI端口配置为数字输出。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param端口
	*要配置的ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）
	* \ param类型
	*端口的配置类型
	 */
    ADIDigitalOut(std::uint8_t port, bool init_state = LOW);

    /**
	*设置给定ADI端口的值。
	*
	*这仅适用于配置为输出的端口，行为将
	*根据端口的配置而改变。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param值
	*将ADI端口设置为的值
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    using ADIPort::set_value;
};

class ADIDigitalIn : private ADIPort
{
  public:
    /**
	*将ADI端口配置为数字输入。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param端口
	*要配置的ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）
	* \ param类型
	*端口的配置类型
	 */
    ADIDigitalIn(std::uint8_t port);

    /**
	*获得数字按钮按下的上升边缘。
	*
	*此功能不是线程安全的。
	*轮询单个按钮的多个任务可能会返回不同的结果
	*相同的情况，所以只有一个任务应该为任何一个调用此函数
	*给出按钮。例如，任务A为按钮1和2调用此函数。任务B
	*可以为按钮3调用此功能，但不应对按钮1或2调用此功能
	*此函数的典型用例是调用opcontrol内部进行检测
	*按下新按钮，而不是任何其他任务。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \如果按下按钮并且最后一次没有按下，则返回1
	*此函数被调用，否则为0
	 */
    std::int32_t get_new_press(void) const;

    /**
	*获取给定ADI端口的值。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return为给定端口存储的值
	 */
    using ADIPort::get_value;
};

using ADIButton = ADIDigitalIn;

class ADIMotor : private ADIPort
{
  public:
    /**
	*配置ADI端口作为电机。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param端口
	*要配置的ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）
	* \ param类型
	*端口的配置类型
	 */
    ADIMotor(std::uint8_t port);

    /**
	*停止给定端口上的电机。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    std::int32_t stop(void) const;

    /**
	*设置给定端口上的电机速度。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param值
	*新签署的速度; -127是全反向，127是全向前，
	* 0关闭
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    using ADIPort::set_value;

    /**
	*获取给定端口上电机的最后设定速度。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return给定端口上电机的最后设定速度
	 */
    using ADIPort::get_value;
};

class ADIEncoder : private ADIPort
{
  public:
    /**
	*配置一组ADI端口作为编码器。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param port_top
	*来自编码器传感器的“顶部”电线，带有可拆卸的盖板侧
	* UP
	* \ param port_bottom
	*编码器传感器的“底部”导线
	* \ param reverse
	*如果“为”，传感器将按相反方向计数
	 */
    ADIEncoder(std::uint8_t port_top, std::uint8_t port_bottom, bool reversed = false);

    /**
	*将编码器值设置为零。
	*
	*启用编码器时使用此方法是安全的。它不是
	*必须在停止或启动编码器之前调用此方法。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    std::int32_t reset(void) const;

    /**
	*获取编码器记录的刻度数。
	*
	*一次革命有360个刻度。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return自上次开始或之后的已签名和累计计数
	* 重启
	 */
    std::int32_t get_value(void) const;
};

class ADIUltrasonic : private ADIPort
{
  public:
    /**
	*配置一组ADI端口作为超声波。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内。
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param port_ping
	*连接到橙色OUTPUT电缆的端口。这应该在
	* port_echo之后的下一个最高端口。
	* \ param port_echo
	*端口连接到黄色INPUT电缆。这应该在港口
	* 1,3,5或7（'A'，'C'，'E'，'G'）。
	 */
    ADIUltrasonic(std::uint8_t port_ping, std::uint8_t port_echo);

    /**
	*以厘米为单位获取当前超声波传感器值。
	*
	*如果未找到任何对象，则返回零。如果是超声波传感器
	*从未开始，返回值未定义。圆形和蓬松的物体可以
	*导致返回不准确的值。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return到最近的对象的距离，单位为m ^ -4（10000表示1
	*米），从传感器的安装点测量。
	 */
    using ADIPort::get_value;
};

class ADIGyro : private ADIPort
{
  public:
    /**
	*在给定端口上初始化陀螺仪。如果给定的端口没有
	*之前已配置为陀螺仪，此功能启动1300ms
	*校准期。
	*
	*强烈建议在initialize（）中创建ADIGyro对象
	*当机器人静止时，确保正确校准。如果是ADIGyro
	*对象在全局范围内声明，一个硬编码的1300ms延迟
	*初始化的开始将是确保陀螺仪的必要条件
	*自主/ opcontrol开始时返回的值是正确的。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EINVAL  - 给定值不在ADI端口范围内
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ param端口
	* ADI端口初始化为陀螺仪（从1-8，'a' - 'h'，'A' - 'H'）
	* \ param乘数
	*标量值将乘以陀螺仪标题值
	*由ADI提供
	 */
    ADIGyro(std::uint8_t port, double multiplier = 1);

    ~ADIGyro(void) override;

    /**
	*以十分之一度获得当前的陀螺仪角度。除非乘数是
	*应用于陀螺仪，返回值将是整数表示
	*旋转度数乘以10。
	*
	*圆圈有360度，因此陀螺仪将返回3600
	*整个轮换。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \ return以度为单位的陀螺仪角度。
	 */
    double get_value(void) const;

    /**
	*将陀螺仪值重置为零。
	*
	*当错误状态为时，此函数使用以下errno值
	* 到达：
	* EACCES  - 另一种资源目前正在尝试访问ADI。
	*
	* \如果操作成功则返回1或如果操作则返回PROS_ERR
	*失败，设置错误。
	 */
    std::int32_t reset(void) const;
};
} // namespace pros

#endif // _PROS_ADI_HPP_
