/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-16T22:09:58+08:00
 */
#ifndef _PROS_ADI_H_
#define _PROS_ADI_H_

#include <stdint.h>
#ifndef PROS_ERR
#define PROS_ERR (INT32_MAX)
#endif

#ifdef __cplusplus
extern "C"
{
    namespace pros
    {
#endif

    /**
 * 表示ADI端口的端口类型。
 */
    typedef enum adi_port_config_e
    {
        E_ADI_ANALOG_IN = 0,
        E_ADI_ANALOG_OUT,
        E_ADI_DIGITAL_IN,
        E_ADI_DIGITAL_OUT,

        E_ADI_SMART_BUTTON,
        E_ADI_SMART_POT,

        E_ADI_LEGACY_BUTTON,
        E_ADI_LEGACY_POT,
        E_ADI_LEGACY_LINE_SENSOR,
        E_ADI_LEGACY_LIGHT_SENSOR,
        E_ADI_LEGACY_GYRO,
        E_ADI_LEGACY_ACCELEROMETER,

        E_ADI_LEGACY_SERVO,
        E_ADI_LEGACY_PWM,

        E_ADI_LEGACY_ENCODER,
        E_ADI_LEGACY_ULTRASONIC,

        E_ADI_TYPE_UNDEFINED = 255,
        E_ADI_ERR = PROS_ERR
    } adi_port_config_e_t;

#ifdef PROS_USE_SIMPLE_NAMES
#define ADI_ANALOG_IN E_ADI_ANALOG_IN
#define ADI_ANALOG_OUT E_ADI_ANALOG_OUT
#define ADI_DIGITAL_IN E_ADI_DIGITAL_IN
#define ADI_DIGITAL_OUT E_ADI_DIGITAL_OUT
#define ADI_SMART_BUTTON E_ADI_SMART_BUTTON
#define ADI_SMART_POT E_ADI_SMART_POT
#define ADI_LEGACY_BUTTON E_ADI_LEGACY_BUTTON
#define ADI_LEGACY_POT E_ADI_LEGACY_POT
#define ADI_LEGACY_LINE_SENSOR E_ADI_LEGACY_LINE_SENSOR
#define ADI_LEGACY_LIGHT_SENSOR E_ADI_LEGACY_LIGHT_SENSOR
#define ADI_LEGACY_GYRO E_ADI_LEGACY_GYRO
#define ADI_LEGACY_ACCELEROMETER E_ADI_LEGACY_ACCELEROMETER
#define ADI_LEGACY_SERVO E_ADI_LEGACY_SERVO
#define ADI_LEGACY_PWM E_ADI_LEGACY_PWM
#define ADI_LEGACY_ENCODER E_ADI_LEGACY_ENCODER
#define ADI_LEGACY_ULTRASONIC E_ADI_LEGACY_ULTRASONIC
#define ADI_TYPE_UNDEFINED E_ADI_TYPE_UNDEFINED
#define ADI_ERR E_ADI_ERR
#endif

#define NUM_ADI_PORTS 8

#ifdef __cplusplus
    namespace c
    {
#endif

    /******************************************************************************/
    /**                         ADI使用通用函数                				    **/
    /**                                                                          **/
    /**       这些函数允许与任何ADI端口类型进行交互。 						      **/
    /******************************************************************************/

    /**
	*获取给定ADI端口的配置。
	*
	*当错误状态为：
	*到达：
	*给定值不在ADI端口的范围内。
	＊EACACES——另一个资源目前正在尝试访问ADI。
	*
	*PARAM端口
	* ADI端口号（从1-8，‘a’-‘h’，‘a’-h’）返回。
	＊配置
	*
	*返回给定端口的ADI配置
 */
    adi_port_config_e_t adi_port_get_config(uint8_t port);

    /**
	*获取给定ADI端口的值。
	*
	*当错误状态为：
	*到达：
	* EINVAL-给定值不在ADI端口的范围内。
	＊EACACES——另一个资源目前正在尝试访问ADI。
	*
	*PARAM端口
	* ADI端口号（从1-8，‘a’-‘h’，‘a’-h’）为其值
	*将被退还
	*
	*返回为给定端口存储的值
 */
    int32_t adi_port_get_value(uint8_t port);

    /**
	*配置一个ADI端口作为一个给定的传感器类型。
	*
	*当错误状态为：
	*到达：
	*给定值不在ADI端口的范围内。
	＊EACACES——另一个资源目前正在尝试访问ADI。
	*
	*PARAM端口
	* ADI端口号（从1-8，‘a’-h’，‘a’-h’）配置
	*PARAM类型
	*端口的配置类型
	*
	*如果手术成功或假若手术，则返回1。
	*失败，设置错误。
 */
    int32_t adi_port_set_config(uint8_t port, adi_port_config_e_t type);

    /**
	*为给定的ADI端口设置值。
	*
	*这只适用于配置为输出的端口，并且行为将改变。
	*取决于端口的配置。
	*
	*当错误状态为：
	*到达：
	*给定值不在ADI端口的范围内。
	＊EACACES——另一个资源目前正在尝试访问ADI。
	*
	*PARAM端口
	* ADI端口号（从1-8，‘a’-‘h’，‘a’-h’）为其值
	*将被设置
	*PARAM值
	*设置ADI端口的值
	*
	*如果手术成功或假若手术，则返回1。
	*失败，设置错误。
 */
    int32_t adi_port_set_value(uint8_t port, int32_t value);

/******************************************************************************/
/**                      PROS 2兼容功能                                       **/
/**                                                                          **/
/**     这些功能为PROS 2 API提供了类似的功能。                                 **/
/******************************************************************************/

/**
 * Used for adi_digital_write() to specify a logic HIGH state to output.
 *
 * In reality, using any non-zero expression or "true" will work to set a pin to
 * HIGH.
 */
#define HIGH 1
/**
 * Used for adi_digital_write() to specify a logic LOW state to output.
 *
 * In reality, using a zero expression or "false" will work to set a pin to LOW.
 */
#define LOW 0

/**
 * adi_pin_mode() state for a digital input.
 */
#define INPUT 0x00
/**
 * adi_pin_mode() state for a digital output.
 */
#define OUTPUT 0x01
/**
 * adi_pin_mode() state for an analog input.
 */
#define INPUT_ANALOG 0x02

/**
 * adi_pin_mode() state for an analog output.
 */
#define OUTPUT_ANALOG 0x03

    /**
	校准指定通道上的模拟传感器。
	该方法假设此时真实传感器值没有主动改变，并计算大约500个样本的平均值，相隔1 ms，持续0.5秒的校准时间。
	返回并存储如此计算的平均值，以便稍后调用 adi_analog_read_calibrated和adi_analog_read_calibrated_HR函数。这些函数将在调用时返回此值与当前传感器值之间的差值。
	当传感器值可能不稳定（陀螺仪旋转，加速度计移动）时，请勿使用此功能。
	*
    *ADI当前以10ms的间隔返回数据，与校准功能的1ms采样率相对应。为了与PROS 2类似，保留该采样率，并且增加采样率将不会在功能性能方面产生明显差异。
	*errno当达到错误状态时，此函数使用以下值：
    *EINVAL - 端口号超出范围或端口未配置为模拟输入。
	* ADI端口校准（从1-8，‘a’-‘h’，‘a’-’h’）
	*
	*返回由这个函数计算的平均传感器值
 */
    int32_t adi_analog_calibrate(uint8_t port);
    /**
	读取模拟输入通道并返回12位值。
	如果模拟引脚已切换到其他模式，则返回的值不确定。返回值的含义取决于所连接的传感器。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为模拟输入。
	EACCES - 另一个资源目前正在尝试访问ADI。
	*
	*PARAM端口
	* ADI端口（从1-8，‘a’-h’，‘a’-h’），值将为
	*返回
	*
	*返回模拟传感器值，其中0的值反映输入电压。
	*近0伏和4095的值反映了近5伏的输入电压。
	*/
    int32_t adi_analog_read(uint8_t port);

    /**
	读取模拟输入通道的校准值。
	所述adi_analog_calibrate功能必须首先在该通道上运行。此功能不适合用于积分的传感器值，因为舍入误差会累积，从而导致随时间漂移。请改用adi_analog_read_calibrated_HR。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为模拟输入。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *     要读取的ADI端口号（从1-8，'a' - 'h'，'A' - 'H'）
 * \return 传感器值与其校准默认值（-4095到4095）之间的差值。
 */
    int32_t adi_analog_read_calibrated(uint8_t port);

    /**
	以更高的精度读取模拟输入通道1-8的校准值。
	该adi_analog_calibrate功能必须先运行。这适用于陀螺仪和加速度计等集成传感器值，以减少由于四舍五入引起的漂移，不应用于线路跟踪器或电位计等传感器。
	返回的值实际上具有16位“精度”，即使ADC仅读取12位，因此当在时间上积分时，由两个值之间的平均值引起的误差在洗涤中出现。将值视为真实值乘以16。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为模拟输入。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *        The ADI port (from 1-8, 'a'-'h', 'A'-'H') for which the value will be
 *        returned
 *
 * 返回：传感器值与校准默认值-16384到16384的差值。
 */
    int32_t adi_analog_read_calibrated_HR(uint8_t port);

    /**
	获取配置为数字输入的引脚的数字值（1或0）。
	如果引脚被配置为某种其他模式，则返回反映引脚当前状态的数字值，该数字值可能与当前设置值不同或不同。对于配置为模拟输入的引脚，返回值未定义。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为数字输入。
	EACCES - 另一个资源目前正在尝试访问ADI。
 * \param port
 *        The ADI port to read (from 1-8, 'a'-'h', 'A'-'H')
 *
 * \return True if the pin is HIGH, or false if it is LOW
 */
    int32_t adi_digital_read(uint8_t port);

    /**
	返回数字按钮按下的上升边框。
	此功能不是线程安全的。轮询单个按钮的多个任务在相同的情况下可能会返回不同的结果，因此只有一个任务应该为任何给定的按钮调用此函数。
	例如，任务A为按钮1和2调用此功能。任务B可以为按钮3调用此功能，但不应该为按钮1或2调用此函数。此功能的典型用例是调用opcontrol内部以检测新按钮按下，而不是任何其他任务。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为数字输入。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *        The ADI port to read (from 1-8, 'a'-'h', 'A'-'H')
 *
返回：如果按下控制器上的按钮并且上次调用此函数时没有按下，则返回 1，否则返回 0。
 */
    int32_t adi_digital_get_new_press(uint8_t port);

    /**
	设置配置为数字输出的引脚的数字值（1或0）。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为数字输出。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *        The ADI port to read (from 1-8, 'a'-'h', 'A'-'H')
 * \param value
 *        An expression evaluating to "true" or "false" to set the output to
 *        HIGH or LOW respectively, or the constants HIGH or LOW themselves
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
返回：如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    int32_t adi_digital_write(uint8_t port, const bool value);

    /**
	通过各种设置将引脚配置为输入或输出。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *        The ADI port to read (from 1-8, 'a'-'h', 'A'-'H')
 * \param mode
 *        One of INPUT, INPUT_ANALOG, INPUT_FLOATING, OUTPUT, or OUTPUT_OD
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 *返回：如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    int32_t adi_pin_mode(uint8_t port, uint8_t mode);

    /**
	设置给定端口上的电机速度。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为电机。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *        The ADI port to set (from 1-8, 'a'-'h', 'A'-'H')
 * \param speed
 *        The new signed speed; -127 is full reverse and 127 is full forward,
 *        with 0 being off
 *
返回：如果操作成功则返回 1，否则返回 PROS_ERR
 */
    int32_t adi_motor_set(uint8_t port, int8_t speed);

    /**
	返回给定端口上电机的最后设定速度。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为电机。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *        The ADI port to get (from 1-8, 'a'-'h', 'A'-'H')
 *
 * 返回：给定端口上电机的最后设置速度。
 */
    int32_t adi_motor_get(uint8_t port);

    /**
	停止给定端口上的电机。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 端口号超出范围或端口未配置为电机。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port
 *        The ADI port to set (from 1-8, 'a'-'h', 'A'-'H')
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 *返回：如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    int32_t adi_motor_stop(uint8_t port);

    /**
	*初始化编码器的引用类型。
	*这仅包含编码器的端口号，不同于它作为一个对象在编码器2中存储编码器数据。
 */
    typedef int32_t adi_encoder_t;

    /**
	获取编码器记录的刻度数。
	编码器旋转一周的值为360
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 编码器端口号超出范围或端口未配置为编码器。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param enc
 *        The adi_encoder_t object from adi_encoder_init() to read
 *
返回：自上次启动或重置以来的有符号和累计计数。
 */
    int32_t adi_encoder_get(adi_encoder_t enc);

    /**
	在两个ADI端口上初始化并启用正交编码器。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 给定端口与下面参数列表中的条件不匹配。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 	参数
 	port_top	来自编码器传感器的“顶部”电线，可拆卸盖板朝上。这应该在端口1,3,5或7（'A'，'C'，'E'，'G'）。
 	port_bottom	来自编码器传感器的“底部”导线
 	相反	如果“为”，传感器将以相反的方向计数
 *
返回：要存储的adi_encoder_t对象，用于以后调用编码器函数。
 */
    adi_encoder_t adi_encoder_init(uint8_t port_top, uint8_t port_bottom, const bool reverse);

    /**
	将编码器重置为零。
	在启用编码器时使用此方法是安全的。在停止或启动编码器之前无需调用此方法。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 编码器端口号超出范围或端口未配置为编码器。
	EACCES - 另一个资源目前正在尝试访问ADI
 *
 * \param enc
 *        The adi_encoder_t object from adi_encoder_init() to reset
 *
返回：如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    int32_t adi_encoder_reset(adi_encoder_t enc);

    /**
	停止并禁用编码器。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 编码器端口号超出范围或端口未配置为编码器。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param enc
 *        The adi_encoder_t object from adi_encoder_init() to stop
 *
 返回：如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    int32_t adi_encoder_shutdown(adi_encoder_t enc);

    /**
 * Reference type for an initialized ultrasonic.
 *
 * This merely contains the port number for the ultrasonic, unlike its use as an
 * object to store encoder data in PROS 2.
 */
    typedef int32_t adi_ultrasonic_t;

    /**
	以厘米为单位获取当前超声波传感器值。
	如果未找到任何对象，则返回零。如果超声波传感器从未启动，则返回值为PROS_ERR。圆形和蓬松的对象可能导致返回不准确的值。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 超声波端口号超出范围或超声波端口未正确配置。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param ult
 *        The adi_ultrasonic_t object from adi_ultrasonic_init() to read
 * 返回：到最近对象的距离，以厘米为单位。
 */
    int32_t adi_ultrasonic_get(adi_ultrasonic_t ult);

    /**
	在指定的ADI端口上初始化超声波传感器。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 给定端口与下面给出的参数标准不匹配。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param port_echo
 *        The port connected to the yellow INPUT cable. This should be in port
 *        1, 3, 5, or 7 ('A', 'C', 'E', 'G').
 * \param port_ping
 *        The port connected to the orange OUTPUT cable. This should be in the
 *        next highest port following port_echo.
 *
*返回：要存储的adi_ultrasonic_t对象，用于以后调用超声波函数。
 */
    adi_ultrasonic_t adi_ultrasonic_init(uint8_t port_echo, uint8_t port_ping);

    /**
	停止并禁用超声波传感器。
	errno当达到错误状态时，此函数使用以下值：
	EINVAL - 超声波端口号超出范围或超声波端口未正确配置。
	EACCES - 另一个资源目前正在尝试访问ADI。
 *
 * \param ult
 *        The adi_ultrasonic_t object from adi_ultrasonic_init() to stop
 *
返回：如果操作成功则返回 1，否则返回 PROS_ERR。
 */
    int32_t adi_ultrasonic_shutdown(adi_ultrasonic_t ult);

#ifdef __cplusplus
    } // namespace c
    } // namespace pros
}
#endif

#endif // _PROS_ADI_H_
