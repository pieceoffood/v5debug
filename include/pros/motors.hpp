/**
 * @Author: 陈昱安
 * @Date:   2018-09-24T21:24:20+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-24T22:40:17+08:00
 */

#ifndef _PROS_MOTORS_HPP_
#define _PROS_MOTORS_HPP_

#include "pros/motors.h"
#include <cstdint>

namespace pros
{
class Motor
{
  public:
    /**
   * 马达构造函数带齿轮设置,带编码器
   * @param  port          V1端口号从1-21
   * @param  gearset  E_MOTOR_GEARSET_36 = 0, // 36:1, 100 RPM, Red gear set
                      E_MOTOR_GEARSET_18 = 1, // 18:1, 200 RPM, Green gear set
                      E_MOTOR_GEARSET_06 = 2, // 6:1, 600 RPM, Blue gear set
   * @param  reverse       1反转电机，0是默认的
   * @param  encoder_units   E_MOTOR_ENCODER_DEGREES = 0,   // Position is recorded as angle in degrees as a floating point number
                             E_MOTOR_ENCODER_ROTATIONS = 1, // Position is recorded as angle in rotations as a floating point number
                             E_MOTOR_ENCODER_COUNTS = 2,    // Position is recorded as raw encoder ticks as a whole number
   */
    explicit Motor(const std::uint8_t port, const motor_gearset_e_t gearset, const bool reverse,
                   const motor_encoder_units_e_t encoder_units);
    /**
			    * 马达构造函数 带齿轮设置
			    * @param  port    V1端口号从1-21
			    * @param  gearset  E_MOTOR_GEARSET_36 = 0, // 36:1, 100 RPM, Red gear set
			                       E_MOTOR_GEARSET_18 = 1, // 18:1, 200 RPM, Green gear set
			                       E_MOTOR_GEARSET_06 = 2, // 6:1, 600 RPM, Blue gear set
			    * @param  reverse 1反转电机，0是默认的
			    */
    explicit Motor(const std::uint8_t port, const motor_gearset_e_t gearset, const bool reverse);

    explicit Motor(const std::uint8_t port, const motor_gearset_e_t gearset);
    /**
   * 普通马达构造函数
   * @param  port   V1端口号从1-21
   * @param  reverse 1反转电机，0是默认的
   */
    explicit Motor(const std::uint8_t port, const bool reverse);

    explicit Motor(const std::uint8_t port);

    /****************************************************************************/
    /**                        马达运动函数                                     **/
    /**                                                                         **/
    /**                   这些功能允许程序员使电机移动						       **/
    /****************************************************************************/
    /**
    * 运算符重载 将电机PWM设置为-127到127。
    * 这样可以轻松映射到控制器模拟摇杆的输入，以便进行简单的操作控制。
    * 电机的实际行为类似于使用 motorSet。
    * 例如Motor a(1) a=127;就是motorSet(1,127)
    */
    virtual std::int32_t operator=(std::int32_t voltage) const;

    /**
      * 设置电动机PWM 跟上面一样的意思,换种写法
      * @param  voltage -127到127
      * @return         设置成功则返回1 错误返回0
      */
    virtual std::int32_t move(std::int32_t voltage) const;

    /**
 * 设置要移动到的电机的目标绝对位置。
 * 该运动相对于初始化时电动机的位置或最近用tare_position重置的位置。
 * 注意:此功能只是设置电机的目标，它不会阻止程序执行，直到运动结束。示例代码显示了如何阻止移动完成。
 * @param  position 移动到电机编码器单元的绝对位置
 * @param  velocity 机芯的最大允许速度
 * @return          1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t move_absolute(const double position, const std::int32_t velocity) const;

    /**
 *设置要移动到的电机的相对目标位置。
 *此运动相对于get_position中给出的电机的当前位置 。
 *注意此功能只是设置电机的目标，它不会阻止程序执行，直到运动结束。示例代码显示了如何阻止移动完成。
 * @param  position 移动到电机编码器单元的相对位置
 * @param  velocity 机芯的最大允许速度
 * @return   1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t move_relative(const double position, const std::int32_t velocity) const;

    /**
 * 设置电机的速度。
 * 该速度对应于不同的实际速度，这取决于用于电动机的齿轮组。
 * 这导致一个范围的+ -100为 E_MOTOR_GEARSET_36，+ -200为E_MOTOR_GEARSET_18，和+ -600为 蓝色。
 * 与设置电机电压相反，速度通过PID保持以确保一致的速度。
 * @param  velocity 新的电机速度为+ -100，+ -200或+ -600，具体取决于电机的齿轮组
 * @return           1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t move_velocity(const std::int32_t velocity) const;

    /**
 * 将电机电压设置为-12000 mV至12000 mV。
 * @param  voltage 电机的新电压为-12000 mV至12000 mV
 * @return        1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t move_voltage(const std::int32_t voltage) const;

    /**
 * 更改配置文件移动的输出速度（move_absolute或 move_relative）。如果电机没有跟随异形运动，这将不起作用。
 * @param  velocity 新的电机速度为+ -100，+ -200或+ -600，具体取决于电机的齿轮组
 * @return         1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t modify_profiled_velocity(const std::int32_t velocity) const;

    /**
 *获取用户为电机设置的目标位置。
 * @return  编码器单元中的目标位置或PROS_ERR_F操作失败时的设置errno。
 */
    virtual double get_target_position(void) const;

    /**
 * 获取用户指令电机的速度。
 * @return  指令电机速度从+ -100，+ -200，+ -600，或者PROS_ERR如果操作失败，则设置errno。
 */
    virtual std::int32_t get_target_velocity(void) const;

    /****************************************************************************/
    /**                               马达遥测函数                                      **/
    /**                                                                        **/
    /**           这些功能允许程序员从电机收集遥测。 **/
    /****************************************************************************/

    /**
 * 获取电机的内置编码器实际速度。根据编码器类型设置的
 * @return  在电机的实际速度 motor_encoder_units_e_t每秒或者PROS_ERR_F如果操作失败，设置errno。
 */
    virtual double get_actual_velocity(void) const;

    /**
 * 获取电机以mA为单位的电流。
 * @return  电机的电流（mA）或PROS_ERR操作失败，设置errno。
 */
    virtual std::int32_t get_current_draw(void) const;

    /**
 * 获取电机的运动方向。
 * @return  返回： 1表示向正方向移动，-1表示向负方向移动，PROS_ERR如果操作失败，则返回设置errno。
 */
    virtual std::int32_t get_direction(void) const;

    /**
 * 以百分比形式获取电机的效率。100％的效率意味着电动机在没有电力的情况下进行电动移动，效率为0％意味着电动机正在吸取动力而不是移动。
 * @return  电机的效率百分比或PROS_ERR_F操作失败，设置errno。
 */
    virtual double get_efficiency(void) const;

    /**
 * 检测电机是否超过其电流限制。(监测是否热保)
 * @return  如果超出电机电流限制则返回 1;如果未超过电流限制则返回 0，或者PROS_ERR如果操作失败，则返回设置 errno。
 */
    virtual std::int32_t is_over_current(void) const;

    /**
	 * 电机是否停止转动。
	 * @return  1如果电机未转动且0电机正在移动，或者PROS_ERR操作失败，则进行设置errno。
	 */
    virtual std::int32_t is_stopped(void) const;

    /**
 * 获取电机的零位置标志。拿来监测自动赛开始前的准备状态不错 动了就报警
 * @return  1如果电机处于零绝对位置并且0电机已从绝对零点移动，或者PROS_ERR操作失败设置errno。
 */
    virtual std::int32_t get_zero_position_flag(void) const;

    /**
       * 不知道干嘛用的
   * 获取电机经历的故障。将此位域与位中的位掩码进行比较pros::motor_fault_e_t。
   * @return 当前未知的位域。
   */
    virtual std::uint32_t get_faults(void) const;

    /**
     * 不知道干嘛用的
 * 获取电机运行设置的标志。将此位域与位中的位掩码进行比较pros::motor_flag_e_t。
 * @return 当前未知的位域。
 */
    virtual std::uint32_t get_flags(void) const;

    /**
 * 获取给定时间戳下电机的原始编码器计数。(就是返回一个时间点的编码器值 可以是NOW 也是可以是LAST)
 * @param  timestamp 指向将返回编码器计数的时间（以毫秒为单位）的指针
 * @return           给定时间戳的原始编码器计数或PROS_ERR操作失败时的设置errno。
 */
    virtual std::int32_t get_raw_position(std::uint32_t *const timestamp) const;

    /**
 * 监测马达是否超过最高温度限制 跟监测电流配套使用(防热保)
 * @return  如果超过温度限制则返回 1;如果温度低于限制则返回 0，或者PROS_ERR如果操作失败，则返回设置errno。
 */
    virtual std::int32_t is_over_temp(void) const;

    /**
 * 获取电机在编码器单元中的绝对位置。
 * @return 电机在编码器单元中的绝对位置或PROS_ERR_F 操作失败时的设置errno。
 */
    virtual double get_position(void) const;

    /**
 * 获取电机以瓦特为单位的功率。
 * @return  电机的功耗以瓦为单位或PROS_ERR_F操作失败，设置errno。
 */
    virtual double get_power(void) const;

    /**
	 * 获取电机的温度，单位为摄氏度。这种褪色的分辨率是5摄氏度。当温度读数大于或等于55°C时，电机将开始降低功率。
	 * @return  电机温度（摄氏度）或PROS_ERR_F操作失败，设置errno。
	 */
    virtual double get_temperature(void) const;

    /**
	 * 获取电机产生的扭矩，单位为Nm。
	 * @return  电机在NM中的扭矩或PROS_ERR_F操作失败时的设置errno。
	 */
    virtual double get_torque(void) const;

    /**
 * 获取以mV为单位输送到电机的电压。
 * @return  电机的电压，单位为mV或PROS_ERR_F操作失败，设置errno。
 */
    virtual std::int32_t get_voltage(void) const;

    /****************************************************************************/
    /**                           马达功能配置函数        			                 **/
    /**                                                                        **/
    /**  These functions allow programmers to configure the behavior of motors **/
    /****************************************************************************/
    /**
 * 以编码器单位设置电机的零位。这将是电机“绝对”位置的未来参考点。
 * @param  position 编码器单元中的新参考位置
 * @return        1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t set_zero_position(const double position) const;

    /**
	 * 将电机的“绝对”零位置设置为当前位置。似乎每次开机都得设置下
	 * @return  1如果操作成功或PROS_ERR操作失败，则进行设置errno。
	 */
    virtual std::int32_t tare_position(void) const;

    /**
 * 设置马达停止的时候的模式 比如不干涉啊 快到刹车啊 悬停啊
 * @param  mode  E_MOTOR_BRAKE_COAST = 0, 不干涉 E_MOTOR_BRAKE_BRAKE = 1, 刹车 E_MOTOR_BRAKE_HOLD = 2,悬停
 * @return       1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t set_brake_mode(const motor_brake_mode_e_t mode) const;

    /**
 * 以mA为单位设置电机的电流限制。默认限制为2500 mA。
 * @param  limit mA的新电流限制
 * @return     1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t set_current_limit(const std::int32_t limit) const;

    /**
 * 设置编码器模式
 * @param  units  E_MOTOR_ENCODER_DEGREES = 0,   // Position is recorded as angle in degrees as a floating point number
                  E_MOTOR_ENCODER_ROTATIONS = 1, // Position is recorded as angle in rotations as a floating point number
                  E_MOTOR_ENCODER_COUNTS = 2,    // Position is recorded as raw encoder ticks as a whole number
 * @return       1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t set_encoder_units(const motor_encoder_units_e_t units) const;

    /**
 * 设置电机齿轮比
 * @param  gearset 新的电机齿轮组
 * @return        1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t set_gearing(const motor_gearset_e_t gearset) const;

    /**
     * 普通增量式PID
 * 获取浮点值并返回格式正确的pid结构。该pros::motor_pid_s_t结构是在4.4格式，即0×20是2.0，0×21是2.0625，
 * 等此函数将浮点值转换为最接近的4.4值。
 * @param  kf 前馈常数
 * @param  kp 比例
 * @param  ki 积分
 * @param  kd 微分
 * @return  pros::motor_pid_s_t 4.4中正确格式化的结构。
 */
    static motor_pid_s_t convert_pid(double kf, double kp, double ki, double kd);

    /**
     * 抗积分饱和PID
 * 获取浮点值并返回格式正确的pid结构。该pros::motor_pid_full_s_t结构是在4.4格式，即0×20是2.0，0×21是2.0625，等此函数将浮点值转换为最接近的4.4值。
 * @param  kf         前馈常数
 * @param  kp        比例
 * @param  ki        积分
 * @param  kd        微分
 * @param  filter    用于过滤轮廓加速度的常量
 * @param  limit     积分限制
 * @param  threshold 误差值 确定位置移动是否达到其目标的阈值。这对速度PID控制器没有影响。
 * @param  loopspeed 运行PID计算的速率（以ms为单位
 * @return           pros::motor_pid_s_t 4.4中正确格式化的结构。
 */
    static motor_pid_full_s_t convert_pid_full(double kf, double kp, double ki, double kd, double filter, double limit,
                                               double threshold, double loopspeed);

    /**
										        * 实时修改各种PID参数...
										    * 设置其中一个pros::motor_pid_s_t用于电机。这只是为了修改主PID常数。
										    * 只有结构的非零值才会改变现有的电机常数。
										    * 警告:此功能处于测试阶段，建议在修改PID值时要小心。特别大的常数会损坏电机。
										    * @param  pid 新的电机PID常数
										    * @return     1如果操作成功或PROS_ERR操作失败，则进行设置errno。
										    */
    virtual std::int32_t set_pos_pid(const motor_pid_s_t pid) const;

    virtual std::int32_t set_pos_pid_full(const motor_pid_full_s_t pid) const;

    virtual std::int32_t set_vel_pid(const motor_pid_s_t pid) const;

    virtual std::int32_t set_vel_pid_full(const motor_pid_full_s_t pid) const;

    /**
 * 设置电机正反转
 * @param  reverse 1反转电机，0是默认的
 * @return        1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t set_reversed(const bool reverse) const;

    /**
 * 设置电机的电压限制，单位为mV。
 * @param  limit 以伏特为单位的新电压限制 最大10000mv (10V)
 * @return       1如果操作成功或PROS_ERR操作失败，则进行设置errno。
 */
    virtual std::int32_t set_voltage_limit(const std::int32_t limit) const;

    /**
 * 获取电机的制动模式。
 * @return  motor_brake_mode_e_t中的一个，根据为电机设置的内容，或者E_MOTOR_BRAKE_INVALID操作失败，设置errno。
 */
    virtual motor_brake_mode_e_t get_brake_mode(void) const;

    /**
  * 以mA为单位获取电机的电流限制。默认限制为2500 mA。
  * @return 电机的电流限制（mA）或PROS_ERR操作失败，设置errno。
  */
    virtual std::int32_t get_current_limit(void) const;

    /**
 * 获取为电机设置的编码器单位。
 * @return  motor_encoder_units_e_t中的一个，根据为电机设置的内容或E_MOTOR_ENCODER_INVALID操作失败。
 */
    virtual motor_encoder_units_e_t get_encoder_units(void) const;

    /**
 * 获取马达的齿轮设置
 * @return  motor_gearset_e_t中的一个，根据为电机设置的内容，或者E_GEARSET_INVALID操作失败。
 */
    virtual motor_gearset_e_t get_gearing(void) const;

    /**
    * 获取为电机设置的PID。如果尚未使用pros :: Motor :: set_pos_pid（）或pros :: Motor :: set_pos_pid_full（）函数，
    * 则此函数将为所有参数返回零
    * @return  A pros::motor_pid_full_s_t包含给定电机的最后设置*的PID常数位置
    */
    virtual motor_pid_full_s_t get_pos_pid(void) const;

    virtual motor_pid_full_s_t get_vel_pid(void) const;

    /**
 * 获取当前马达是否反转
 * @return  如果电机已反转则返回 1;如果电机未反转则返回 0，或者PROS_ERR如果操作失败，则返回设置errno。
 */
    virtual std::int32_t is_reversed(void) const;

    /**
 * 获取电动机当前最高电压设置
 * @return  返回电动机电压
 */
    virtual std::int32_t get_voltage_limit(void) const;

  private:
    const std::uint8_t _port;
};

namespace literals
{
//运算符重载 跟以前一样 比如1_mtr
const pros::Motor operator"" _mtr(const unsigned long long int m);
const pros::Motor operator"" _rmtr(const unsigned long long int m);
} // namespace literals
} // namespace pros
#endif // _PROS_MOTORS_HPP_
