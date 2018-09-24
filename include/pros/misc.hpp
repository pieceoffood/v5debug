/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-24T22:00:43+08:00
 */

#ifndef _PROS_MISC_HPP_
#define _PROS_MISC_HPP_

#include "pros/misc.h"

#include <cstdint>
#include <string>

namespace pros
{
class Controller
{
  public:
    /**
 * 遥控器构造函数
 * @param id 遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 */
    Controller(controller_id_e_t id);

    /**
 * 遥控器是否连接到场控
 * @return  如果V5 Brain连接到竞争控制，则返回 true，否则返回 false。
 */
    std::int32_t is_connected(void);

    /**
 * 获取遥控器的模拟值(摇杆)
 * @param  channel 得到的模拟通道。必须是ANALOG_LEFT_X，ANALOG_LEFT_Y， ANALOG_RIGHT_X，ANALOG_RIGHT_Y之一
 * @return         模拟通道的当前读数：[ - 127,127]。如果遥控器未连接，则返回0
 */
    std::int32_t get_analog(controller_analog_e_t channel);
    /**
 * 获取给定遥控器的电池容量。
 * @return  遥控器的电池容量。
 */
    std::int32_t get_battery_capacity(void);
    /**
 * 获取给定遥控器的电池电量。
 * @return  遥控器的电池电量。
 */
    std::int32_t get_battery_level(void);

    /**
 * 获取遥控器上数字通道（按钮）的值。
 * @param  button 	要读的按钮。必须是DIGITAL_ {RIGHT，DOWN，LEFT，UP，A，B，Y，X，R1，R2，L1，L2}之一
 * @return        如果按下遥控器上的按钮，则返回 1。如果遥控器未连接，则返回0
 */
    std::int32_t get_digital(controller_digital_e_t button);

    /**
 * 返回遥控器按钮按下的上升边框。
 * 此功能不是线程安全的。轮询单个按钮的多个任务在相同的情况下可能会返回不同的结果，
 * 因此只有一个任务应该为任何给定的按钮调用此函数。
 * 例如，任务A为按钮1和2调用此功能。任务B可以为按钮3调用此功能，但不应该为按钮1或2调用此函数。
 * 此功能的典型用例是调用opcontrol内部以检测新按钮按下，而不是任何其他任务。
 * @param  button 要读的按钮。必须是DIGITAL_ {RIGHT，DOWN，LEFT，UP，A，B，Y，X，R1，R2，L1，L2}之一
 * @return       如果按下遥控器上的按钮并且上次调用此函数时没有按下，则返回 1，否则返回 0。
 */
    std::int32_t get_digital_new_press(controller_digital_e_t button);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
    template <typename T>
    T convert_args(T arg)
    {
        return arg;
    }
    const char *convert_args(const std::string &arg)
    {
        return arg.c_str();
    }
#pragma GCC diagnostic pop

    /**
 * 将文本设置到遥控器LCD屏幕。类似printf
 * @param  line 显示文本的行号[0-2]。
 * @param  col  显示文本的列号[0-14]。
 * @param  fmt  要打印到遥控器的格式字符串
 * @param  args 格式字符串的参数列表
 * @return      如果操作成功则返回 1，PROS_ERR否则返回。
 */
    template <typename... Params>
    std::int32_t print(std::uint8_t line, std::uint8_t col, const char *fmt, Params... args)
    {
        return pros::c::controller_print(_id, line, fmt, convert_args(args)...);
    }
    /**
 * 将文本设置到遥控器LCD屏幕。类似print
 * 遥控器文本设置是一个缓慢的过程，因此在有线连接上或在Vexnet上50ms的更新速度不会超过10ms，也不会应用于遥控器。
 * @param  line 显示文本的行号[0-2]
 * @param  col  显示文本的列号[0-14]。
 * @param  str  要打印到遥控器的预格式化字符串。
 * @return      如果操作成功则返回 1，PROS_ERR否则返回。
 */
    std::int32_t set_text(std::uint8_t line, std::uint8_t col, const char *str);

    /**
 * 清除遥控器屏幕的单独一行。
 * @param  line 要清除的行号[0-2]
 * @return   如果操作成功则返回 1，PROS_ERR否则返回。
 */
    std::int32_t clear_line(std::uint8_t line);

    /**
 * 清楚遥控器屏幕所有行
 * @return  如果操作成功则返回 1，PROS_ERR否则返回。
 */
    std::int32_t clear(void);

  private:
    controller_id_e_t _id;
};

namespace battery
{
/**
 * 获取电池容量
 * @return  返回电池的容量值
 */
double get_capacity(void);

/**
 * 获取电池当前的电流
 * @return  电池当前电流
 */
int32_t get_current(void);

/**
 * 获取电池当前温度
 * @return  返回电池的温度
 */
double get_temperature(void);

/**
 * 获取当前电池电压
 * @return  电池当前电压
 */
int32_t get_voltage(void);
} // namespace battery

namespace competition
{
/**
 * 获取当前场控的状态
 * @return  竞争控制状态作为位掩码，具有COMPETITION_ {ENABLED，AUTONOMOUS，CONNECTED}。
 */
std::uint8_t get_status(void);
/**
 *	是否正在进行自动赛?
 * @return  如果V5 Brain处于自动赛模式，则返回 True，否则返回 false。
 */
std::uint8_t is_autonomous(void);
/**
 * 是否连接场控
 * @return  如果V5 Brain连接到场控，则返回 true，否则返回 false。
 */
std::uint8_t is_connected(void);
/**
 * 场控是否关闭
 * @return  如果禁用V5 Brain，则返回 true，否则返回 false。
 */
std::uint8_t is_disabled(void);
} // namespace competition
} // namespace pros

#endif // _PROS_MISC_HPP_
