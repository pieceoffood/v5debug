/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-18T23:01:24+08:00
 */

//杂项函数库

#ifndef _PROS_MISC_H_
#define _PROS_MISC_H_

#include <stdint.h>

#define NUM_V5_PORTS (22)

/******************************************************************************/
/**                             V5 Competition                               **/
/******************************************************************************/
#define COMPETITION_DISABLED (1 << 0)
#define COMPETITION_AUTONOMOUS (1 << 1)
#define COMPETITION_CONNECTED (1 << 2)

#ifdef __cplusplus
extern "C"
{
    namespace pros
    {
    namespace c
    {
#endif
    /**
 * 监测场控状态。
 * @return 以比特为掩码的竞争控制状态 竞争{{启用、自治、连接}。
 */
    uint8_t competition_get_status(void);
#ifdef __cplusplus
    }
    }
}
#endif
#define competition_is_disabled() ((competition_get_status() & COMPETITION_DISABLED) != 0)
#define competition_is_connected() ((competition_get_status() & COMPETITION_CONNECTED) != 0)
#define competition_is_autonomous() ((competition_get_status() & COMPETITION_AUTONOMOUS) != 0)

/******************************************************************************/
/**                              V5 Controller                               **/
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
    namespace pros
    {
#endif

    typedef enum
    {
        E_CONTROLLER_MASTER = 0, //主要遥控器值为0
        E_CONTROLLER_PARTNER     //副遥控器值为1
    } controller_id_e_t;

    typedef enum
    {
        E_CONTROLLER_ANALOG_LEFT_X = 0, //以前的CH4 0
        E_CONTROLLER_ANALOG_LEFT_Y,     //以前CH3  1
        E_CONTROLLER_ANALOG_RIGHT_X,    //以前的CH1 2
        E_CONTROLLER_ANALOG_RIGHT_Y     //以前的CH2 3
    } controller_analog_e_t;
    //遥控器的按钮
    typedef enum
    {
        E_CONTROLLER_DIGITAL_L1 = 6,
        E_CONTROLLER_DIGITAL_L2,
        E_CONTROLLER_DIGITAL_R1,
        E_CONTROLLER_DIGITAL_R2,
        E_CONTROLLER_DIGITAL_UP,
        E_CONTROLLER_DIGITAL_DOWN,
        E_CONTROLLER_DIGITAL_LEFT,
        E_CONTROLLER_DIGITAL_RIGHT,
        E_CONTROLLER_DIGITAL_X,
        E_CONTROLLER_DIGITAL_B,
        E_CONTROLLER_DIGITAL_Y,
        E_CONTROLLER_DIGITAL_A
    } controller_digital_e_t;

#ifdef PROS_USE_SIMPLE_NAMES
#ifdef __cplusplus
#define CONTROLLER_MASTER pros::E_CONTROLLER_MASTER
#define CONTROLLER_PARTNER pros::E_CONTROLLER_PARTNER
#define ANALOG_LEFT_X pros::E_CONTROLLER_ANALOG_LEFT_X
#define ANALOG_LEFT_Y pros::E_CONTROLLER_ANALOG_LEFT_Y
#define ANALOG_RIGHT_X pros::E_CONTROLLER_ANALOG_RIGHT_X
#define ANALOG_RIGHT_Y pros::E_CONTROLLER_ANALOG_RIGHT_Y
#define DIGITAL_L1 pros::E_CONTROLLER_DIGITAL_L1
#define DIGITAL_L2 pros::E_CONTROLLER_DIGITAL_L2
#define DIGITAL_R1 pros::E_CONTROLLER_DIGITAL_R1
#define DIGITAL_R2 pros::E_CONTROLLER_DIGITAL_R2
#define DIGITAL_UP pros::E_CONTROLLER_DIGITAL_UP
#define DIGITAL_DOWN pros::E_CONTROLLER_DIGITAL_DOWN
#define DIGITAL_LEFT pros::E_CONTROLLER_DIGITAL_LEFT
#define DIGITAL_RIGHT pros::E_CONTROLLER_DIGITAL_RIGHT
#define DIGITAL_X pros::E_CONTROLLER_DIGITAL_X
#define DIGITAL_B pros::E_CONTROLLER_DIGITAL_B
#define DIGITAL_Y pros::E_CONTROLLER_DIGITAL_Y
#define DIGITAL_A pros::E_CONTROLLER_DIGITAL_A
#else
#define CONTROLLER_MASTER E_CONTROLLER_MASTER
#define CONTROLLER_PARTNER E_CONTROLLER_PARTNER
#define ANALOG_LEFT_X E_CONTROLLER_ANALOG_LEFT_X
#define ANALOG_LEFT_Y E_CONTROLLER_ANALOG_LEFT_Y
#define ANALOG_RIGHT_X E_CONTROLLER_ANALOG_RIGHT_X
#define ANALOG_RIGHT_Y E_CONTROLLER_ANALOG_RIGHT_Y
#define DIGITAL_L1 E_CONTROLLER_DIGITAL_L1
#define DIGITAL_L2 E_CONTROLLER_DIGITAL_L2
#define DIGITAL_R1 E_CONTROLLER_DIGITAL_R1
#define DIGITAL_R2 E_CONTROLLER_DIGITAL_R2
#define DIGITAL_UP E_CONTROLLER_DIGITAL_UP
#define DIGITAL_DOWN E_CONTROLLER_DIGITAL_DOWN
#define DIGITAL_LEFT E_CONTROLLER_DIGITAL_LEFT
#define DIGITAL_RIGHT E_CONTROLLER_DIGITAL_RIGHT
#define DIGITAL_X E_CONTROLLER_DIGITAL_X
#define DIGITAL_B E_CONTROLLER_DIGITAL_B
#define DIGITAL_Y E_CONTROLLER_DIGITAL_Y
#define DIGITAL_A E_CONTROLLER_DIGITAL_A
#endif
#endif

#ifdef __cplusplus
    namespace c
    {
#endif

    /**
 * 检查遥控器是否连接。
 * @param  id 遥控器的ID（主遥CONTROLLER_MASTER 或 副遥CONTROLLER_PARTNER）。
 * @return    如果遥控器连接，返回1，否则为0
 */
    int32_t controller_is_connected(controller_id_e_t id);

    /**
 * 获得遥控器上模拟通道（操纵杆）的值。
 * @param  id      遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @param  channel 得到的模拟通道。必须是ANALOG_LEFT_X，ANALOG_LEFT_Y， ANALOG_RIGHT_X，ANALOG_RIGHT_Y之一
 * @return         模拟通道的当前读数：[ - 127,127]。如果遥控器未连接，则返回0
 */
    int32_t controller_get_analog(controller_id_e_t id, controller_analog_e_t channel);

    /**
 * 获取给定遥控器的电池容量。
 * @param  id 遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @return   遥控器的电池容量。
 */
    int32_t controller_get_battery_capacity(controller_id_e_t id);

    /**
 *获取给定遥控器的电池电量。
 * @param  id 遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @return   遥控器的电池电量。
 */
    int32_t controller_get_battery_level(controller_id_e_t id);
    /**
 * 获取遥控器上数字通道（按钮）的值。
 * @param  id     遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @param  button 要读的按钮。必须是DIGITAL_ {RIGHT，DOWN，LEFT，UP，A，B，Y，X，R1，R2，L1，L2}之一
 * @return        如果按下遥控器上的按钮，则返回 1。如果遥控器未连接，则返回0
 */
    int32_t controller_get_digital(controller_id_e_t id, controller_digital_e_t button);

    /**
 * 返回遥控器按钮按下的上升边框。
 * 此功能不是线程安全的。轮询单个按钮的多个任务在相同的情况下可能会返回不同的结果，
 * 因此只有一个任务应该为任何给定的按钮调用此函数。
 * 例如，任务A为按钮1和2调用此功能。任务B可以为按钮3调用此功能，但不应该为按钮1或2调用此函数。
 * 此功能的典型用例是调用opcontrol内部以检测新按钮按下，而不是任何其他任务。
 * @param  id     遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @param  button 要读的按钮。必须是DIGITAL_ {RIGHT，DOWN，LEFT，UP，A，B，Y，X，R1，R2，L1，L2}之一
 * @return        如果按下遥控器上的按钮并且上次调用此函数时没有按下，则返回 1，否则返回 0。
 */
    int32_t controller_get_digital_new_press(controller_id_e_t id, controller_digital_e_t button);
    /**
 * 将文本设置到遥控器LCD屏幕。用法类似printf
 * @param  id      遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @param  line    显示文本的行号[0-2]。
 * @param  col     显示文本的列号[0-14]。
 * @param  fmt     要打印到遥控器的格式字符串
 * @param  VARARGS 格式字符串的参数列表
 * @return         如果操作成功则返回 1，PROS_ERR否则返回。
 */
    int32_t controller_print(controller_id_e_t id, uint8_t line, uint8_t col, const char *fmt, ...);

    /**
 * 将文本设置到遥控器LCD屏幕。
 * 遥控器文本设置是一个缓慢的过程，因此在有线连接上或在Vexnet上50ms的更新速度不会超过10ms，也不会应用于遥控器。
 * @param  id   遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @param  line 显示文本的行号[0-2]。
 * @param  col  显示文本的列号[0-14]。
 * @param  str  要打印到遥控器的预格式化字符串。
 * @return      如果操作成功则返回 1，PROS_ERR否则返回。
 */
    int32_t controller_set_text(controller_id_e_t id, uint8_t line, uint8_t col, const char *str);

    /**
 * 清除遥控器屏幕的单独一行。
 * @param  id    遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @param  line  要清除的行号[0-2]
 * @return      如果操作成功则返回 1，PROS_ERR否则返回。
 */
    int32_t controller_clear_line(controller_id_e_t id, uint8_t line);

    /**
 * 清除遥控器屏幕的所有行。
 * @param  id  遥控器的ID（例如主遥控器或伙伴遥控器）。必须是CONTROLLER_MASTER或CONTROLLER_PARTNER之一
 * @return    如果操作成功则返回 1，PROS_ERR否则返回。
 */
    int32_t controller_clear(controller_id_e_t id);
    /**
 * 获取VEXos报告的电池当前电压。
 * @return  电池的当前电压。
 */
    int32_t battery_get_voltage(void);

    /**
 * 获取VEXos报告的电池当前电流。
 * @return  电池的当前电流。
 */
    int32_t battery_get_current(void);

    /**
 * 获取VEXos报告的电池当前温度。
 * @return  电池的当前温度。
 */
    double battery_get_temperature(void);

    /**
 * 获取VEXos报告的电池当前容量。
 * @return  电池的当前容量。
 */
    double battery_get_capacity(void);

#ifdef __cplusplus
    }
    }
}
#endif

#endif // _PROS_MISC_H_
