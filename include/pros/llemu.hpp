/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-17T21:00:04+08:00
 */

#ifndef _PROS_LLEMU_HPP_
#define _PROS_LLEMU_HPP_

#include <cstdint>
#include <string>

#include "pros/llemu.h"
/**
 * 老式液晶屏的库函数 没必要翻译
 */
namespace pros
{
namespace lcd
{

/**
 * 检查液晶屏是否被初始化
 * @return  是被初始化了返回TRUE 否则 返回FALSE
 */
bool is_initialized(void);

/**
 * 将显示初始化为基于UART的三键VEX LCD的仿真。
 * @return  true LCD是否已成功初始化，或者false是否已初始化。
 */
bool initialize(void);

/**
 * 关闭传统LCD仿真器
 * 调用此函数将清除整个显示，并且在另一次初始化调用之前，您将无法再调用任何LLEMU函数。
 * @return  true如果操作成功，或者false以其他方式设置 errno上面指定的值。
 */
bool shutdown(void);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
namespace
{
template <typename T>
T convert_args(T arg)
{
    return arg;
}
const char *convert_args(const std::string &arg)
{
    return arg.c_str();
}
} // namespace
#pragma GCC diagnostic pop

/**
 * Displays a formatted string on the emulated three-button LCD screen.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO  - The LCD has not been initialized. Call lcd_initialize() first.
 * EINVAL - The line number specified is not in the range [0-7]
 *
 * \param line
 *        The line on which to display the text [0-7]
 * \param fmt
 *        Format string
 * \param ...
 *        Optional list of arguments for the format string
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 */
template <typename... Params>
bool print(std::int16_t line, const char *fmt, Params... args)
{
    return pros::c::lcd_print(line, fmt, convert_args(args)...);
}

/**
 * Displays a string on the emulated three-button LCD screen.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO  - The LCD has not been initialized. Call lcd_initialize() first.
 * EINVAL - The line number specified is not in the range [0-7]
 *
 * \param line
 *        The line on which to display the text [0-7]
 * \param text
 *        The text to display
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 */
bool set_text(std::int16_t line, std::string text);

/**
 * 清除模拟三键液晶屏上的文字。
 * @return  true如果操作成功，或者false以其他方式设置 errno上面指定的值。
 */
bool clear(void);

/**
 * Clears the contents of a line of the emulated three-button LCD screen.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO  - The LCD has not been initialized. Call lcd_initialize() first.
 * EINVAL - The line number specified is not in the range [0-7]
 *
 * \param line
 *        The line to clear
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 */
bool clear_line(std::int16_t line);

using lcd_btn_cb_fn_t = void (*)(void);

/**
 * Registers a callback function for the leftmost button.
 *
 * When the leftmost button on the emulated three-button LCD is pressed, the
 * user-provided callback function will be invoked.
 *
 * \param cb
 * A callback function of type lcd_btn_cb_fn_t(void (*cb)(void))
 */
void register_btn0_cb(lcd_btn_cb_fn_t cb);

/**
 * Registers a callback function for the center button.
 *
 * When the center button on the emulated three-button LCD is pressed, the
 * user-provided callback function will be invoked.
 *
 * \param cb
 * A callback function of type lcd_btn_cb_fn_t(void (*cb)(void))
 */
void register_btn1_cb(lcd_btn_cb_fn_t cb);

/**
 * Registers a callback function for the rightmost button.
 *
 * When the rightmost button on the emulated three-button LCD is pressed, the
 * user-provided callback function will be invoked.
 *
 * \param cb
 * A callback function of type lcd_btn_cb_fn_t(void (*cb)(void))
 */
void register_btn2_cb(lcd_btn_cb_fn_t cb);

/**
 * Gets the button status from the emulated three-button LCD.
 *
 * The value returned is a 3-bit integer where 1 0 0 indicates the left button
 * is pressed, 0 1 0 indicates the center button is pressed, and 0 0 1
 * indicates the right button is pressed. 0 is returned if no buttons are
 * currently being pressed.
 *
 * Note that this function is provided for legacy API compatibility purposes,
 * with the caveat that the V5 touch screen does not actually support pressing
 * multiple points on the screen at the same time.
 *
 * \return The buttons pressed as a bit mask
 */
std::uint8_t read_buttons(void);
} // namespace lcd
} // namespace pros

#endif // _PROS_LLEMU_HPP_
