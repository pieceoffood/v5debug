/**
 * @Author: 陈昱安
 * @Date:   2018-10-11T21:09:49+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-24T22:43:22+08:00
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
    *为给定的端口和规范创建一个Motor对象。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param端口
    * V5端口号从1-21开始
    * \ param gearset
    *电机的齿轮组
    * \ param reverse
    * True反转电机，false是默认值
    * \ param encoder_units
    *电机的编码器单元
	 */
    explicit Motor(const std::uint8_t port, const motor_gearset_e_t gearset, const bool reverse,
                   const motor_encoder_units_e_t encoder_units);

    explicit Motor(const std::uint8_t port, const motor_gearset_e_t gearset, const bool reverse);

    explicit Motor(const std::uint8_t port, const motor_gearset_e_t gearset);

    explicit Motor(const std::uint8_t port, const bool reverse);

    explicit Motor(const std::uint8_t port);

    /****************************************************************************/
    /**                         Motor movement functions                       **/
    /**                                                                        **/
    /**          These functions allow programmers to make motors move         **/
    /****************************************************************************/
    /**
    *将电机电压设置为-128至127。
    *
    *这可以很容易地映射到控制器模拟的输入
    *坚持使用简单的opcontrol。电机的实际行为是
    *类似于使用pros :: Motor :: move（）或PROS 2 API中的motorSet。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param电压
    *新电机电压从-127到127
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t operator=(std::int32_t voltage) const;

    /**
    *将电机电压设置为-127至127。
    *
    *这可以很容易地映射到控制器模拟的输入
    *坚持使用简单的opcontrol。电机的实际行为是
    *类似于使用PROS 2 API中的motor_move（）或motorSet（）。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param电压
    *新电机电压从-127到127
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t move(std::int32_t voltage) const;

    /**
    *设置要移动到的电机的目标绝对位置。
    *
    *此运动相对于初始化时的电机位置或
    *最近重置时的位置
    * pros :: Motor :: set_zero_position（）。
    *
    * \注意此功能只是设置电机的目标，它不会阻止
    *程序执行直到运动结束。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param位置
    *移动到电机编码器单元的绝对位置
    * \ param速度
    *以RPM为单位的最大运动速度
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t move_absolute(const double position, const std::int32_t velocity) const;

    /**
    *设置要移动到的电机的相对目标位置。
    *
    *此运动与电机的当前位置有关，如下所示
    * pros :: Motor :: motor_get_position（）。提供10.0作为位置参数
    *将导致电机顺时针移动10个单位，无论如何
    *目前的位置是。
    *
    * \注意此功能只是设置电机的目标，它不会阻止
    *程序执行直到运动结束。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param位置
    *移动到电机编码器单元的相对位置
    * \ param速度
    *以RPM为单位的最大运动速度
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t move_relative(const double position, const std::int32_t velocity) const;

    /**
    *设定电机的速度。
    *
    *此速度对应于不同的实际速度，具体取决于
    *用于电机的齿轮组。这导致范围为+ -100
    * E_MOTOR_GEARSET_36，E_MOTOR_GEARSET_18 + -200，+  -  600
    * E_MOTOR_GEARSET_6。使用PID保持速度以确保一致
    *速度，而不是设置电机的电压。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param速度
    *新的电机速度从 -  +  -  100，+ -200或+ -600取决于
    *马达的齿轮组
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t move_velocity(const std::int32_t velocity) const;

    /**
    *将电机的输出电压设置为-12000至12000（以毫伏为单位）。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param端口
    * V5端口号从1-21开始
    * \ param电压
    *新电压值从-12000到12000
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t move_voltage(const std::int32_t voltage) const;

    /**
    *改变异形运动的输出速度（motor_move_absolute（）
    *或motor_move_relative（））。如果没有电机，这将不起作用
    *跟随异形运动。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param速度
    *新的电机速度从+ -100，+ -200或+ -600取决于
    *马达的齿轮组
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t modify_profiled_velocity(const std::int32_t velocity) const;

    /**
    *获取用户为电机设置的目标位置。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return其编码器单元中的目标位置或PROS_ERR_F（如果是）
    *操作失败，设置错误。
	 */
    virtual double get_target_position(void) const;

    /**
    *获取用户指令电机的速度。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return指令电机速度为+ -100，+ -200或+ -600，或
    * PROS_ERR如果操作失败，则设置errno。
	 */
    virtual std::int32_t get_target_velocity(void) const;

    /****************************************************************************/
    /**                        Motor telemetry functions                       **/
    /**                                                                        **/
    /**    These functions allow programmers to collect telemetry from motors  **/
    /****************************************************************************/

    /**
    *获取电机的实际速度。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return电机的实际速度，单位为RPM或PROS_ERR_F（如果操作）
    *失败，设置错误。
	 */
    virtual double get_actual_velocity(void) const;

    /**
    *获取电机以mA为单位的电流。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return如果操作失败，电机的电流为mA或PROS_ERR，
    *设置errno。
	 */
    virtual std::int32_t get_current_draw(void) const;

    /**
    *获取电机的运动方向。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \返回1表示正向移动，-1表示移动
    *负方向，如果操作失败则为PROS_ERR，设置为errno。
	 */
    virtual std::int32_t get_direction(void) const;

    /**
    *以百分比的形式获得电机的效率。
    *
    * 100％的效率意味着电机在电动时移动
    *无电功率，效率为0％表示电机
    *是吸引力而不是移动。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return电机的效率百分比或PROS_ERR_F（如果操作）
    *失败，设置错误。
	 */
    virtual double get_efficiency(void) const;

    /**
    *检查电机是否超过其电流限制。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \如果超过电动机的电流限制则返回1，如果超过则返回0
    *不超过电流限制，如果操作失败，则设置PROS_ERR
    *错误。
	 */
    virtual std::int32_t is_over_current(void) const;

    /**
    *检查电机是否停止。
    *
    * \注意虽然此功能可以转发电机，电机的数据
    *目前不提供任何价值。此函数返回PROS_ERR
    *错误设置为ENOSYS。
    *
    * \如果电机未移动则返回1，如果电机正在移动则返回0，或PROS_ERR
    *如果操作失败，请设置errno
	 */
    virtual std::int32_t is_stopped(void) const;

    /**
    *检查电机是否处于零位。
    *
    * \注意虽然此功能可以转发电机，电机的数据
    *目前不提供任何价值。此函数返回PROS_ERR
    *错误设置为ENOSYS。
    *
    * \如果电机处于零绝对位置则返回1，如果电机处于0则返回0
    *从绝对零点移动，如果操作失败，则设置为PROS_ERR
    *错误
	 */
    virtual std::int32_t get_zero_position_flag(void) const;

    /**
    *获取电机经历的故障。
    *
    *将此位域与pros :: motor_fault_e_t中的位掩码进行比较。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param端口
    * V5端口号从1-21开始
    *
    * \ return包含电机故障的位域。
	 */
    virtual std::uint32_t get_faults(void) const;

    /**
    *获取电机运行设置的标志。
    *
    *将此位域与pros :: motor_flag_e_t中的位掩码进行比较。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param端口
    * V5端口号从1-21开始
    *
    * \ return包含电机标志的位域。
	 */
    virtual std::uint32_t get_flags(void) const;

    /**
    *获取给定时间戳下电机的原始编码器计数。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param [in]时间戳
    *指向编码器计数的时间（以毫秒为单位）的指针
    *将被退回。如果为NULL，则为编码器的时间戳
    *将不提供读数
    *
    * \ return在给定时间戳或PROS_ERR处的原始编码器计数
    * 手术失败。
	 */
    virtual std::int32_t get_raw_position(std::uint32_t *const timestamp) const;

    /**
    *获取电机的温度限制标志。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \如果超过温度限制则返回1，如果温度超过则返回0
    *低于限制，如果操作失败则为PROS_ERR，设置为errno。
	 */
    virtual std::int32_t is_over_temp(void) const;

    /**
    *获取电机在编码器单元中的绝对位置。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \返回电机在编码器单元或PROS_ERR_F中的绝对位置
    *如果操作失败，请设置errno。
	 */
    virtual double get_position(void) const;

    /**
    *获取电机以瓦特为单位的功率。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return如果操作，电机的功率以瓦特或PROS_ERR_F为单位
    *失败，设置错误。
	 */
    virtual double get_power(void) const;

    /**
    *以摄氏度为单位获取电机的温度。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return如果电机的温度以摄氏度或PROS_ERR_F为单位
    *操作失败，设置错误。
	 */
    virtual double get_temperature(void) const;

    /**
    *获取牛顿米（Nm）中电机产生的扭矩。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return如果操作失败，电机的扭矩为Nm或PROS_ERR_F，
    *设置errno。
	 */
    virtual double get_torque(void) const;

    /**
    *以毫伏为单位获取输送到电机的电压。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return如果操作失败，则以mV或PROS_ERR_F为单位返回电机电压，
    *设置errno。
	 */
    virtual std::int32_t get_voltage(void) const;

    /****************************************************************************/
    /**                      Motor configuration functions                     **/
    /**                                                                        **/
    /**  These functions allow programmers to configure the behavior of motors **/
    /****************************************************************************/

    /**
    *以编码器单位设置电机的位置。
    *
    *这将是电机“绝对”的未来参考点
    *位置。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param位置
    *编码器单元中的新参考位置
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_zero_position(const double position) const;

    /**
    *将电机的“绝对”零位置设置为当前位置。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t tare_position(void) const;

    /**
    *将motor_brake_mode_e_t中的一个设置为电机。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param模式
    * motor_brake_mode_e_t设置电机
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_brake_mode(const motor_brake_mode_e_t mode) const;

    /**
    *以mA为单位设置电机的电流限制。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param限制
    *以mA为单位的新电流限制
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_current_limit(const std::int32_t limit) const;

    /**
    *为电机编码器设置motor_encoder_units_e_t之一。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param单位
    *新的电机编码器单元
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_encoder_units(const motor_encoder_units_e_t units) const;

    /**
    *为电机设置motor_gearset_e_t之一。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param gearset
    *新的电机齿轮组
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_gearing(const motor_gearset_e_t gearset) const;

    /**
    *获取浮点值并返回格式正确的pid结构。
    * motor_pid_s_t结构是4.4格式，即0x20是2.0,0x21是
    * 2.0625等
    *此函数将浮点值转换为最接近的4.4
    *价值。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param kf
    *前馈常数
    * \ param kp
    *比例常数
    * \ param ki
    *积分常数
    * \ param kd
    *导数常数
    *
    * \ return在4.4中正确格式化的motor_pid_s_t结构。
	 */
    static motor_pid_s_t convert_pid(double kf, double kp, double ki, double kd);

    /**
    *获取浮点值并返回格式正确的pid结构。
    * motor_pid_s_t结构是4.4格式，即0x20是2.0,0x21是
    * 2.0625等
    *此函数将浮点值转换为最接近的4.4
    *价值。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param kf
    *前馈常数
    * \ param kp
    *比例常数
    * \ param ki
    *积分常数
    * \ param kd
    *导数常数
    * \ param过滤器
    *用于过滤轮廓加速度的常量
    * \ param限制
    *积分限制
    * \ param阈值
    *确定位置移动是否达到其的阈值
    *目标。这对速度PID计算没有影响。
    * \ param loopspeed
    * PID计算以ms为单位运行的速率
    *
    * \ return在4.4中正确格式化的motor_pid_s_t结构。
	 */
    static motor_pid_full_s_t convert_pid_full(double kf, double kp, double ki, double kd, double filter, double limit,
                                               double threshold, double loopspeed);

    /**
    *为电机设置motor_pid_s_t之一。这只是为了修改
    *主要PID常数。
    *
    *只有结构的非零值才会改变现有的电机
    *常数。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param pid
    *新的电机PID常数
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_pos_pid(const motor_pid_s_t pid) const;

    /**
    *为电机设置motor_pid_full_s_t之一。
    *
    *只有结构的非零值才会改变现有的电机
    *常数。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param pid
    *新的电机PID常数
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_pos_pid_full(const motor_pid_full_s_t pid) const;

    /**
    *为电机设置motor_pid_s_t之一。这只是为了修改
    *主要PID常数。
    *
    *只有结构的非零值才会改变现有的电机
    *常数。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param pid
    *新的电机PID常数
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_vel_pid(const motor_pid_s_t pid) const;

    /**
    *为电机设置motor_pid_full_s_t之一。
    *
    *只有结构的非零值才会改变现有的电机
    *常数。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param pid
    *新的电机PID常数
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_vel_pid_full(const motor_pid_full_s_t pid) const;

    /**
    *设置电机的反向标志。
    *
    *这将反转其移动和为其位置返回的值。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param reverse
    * True反转电机，false是默认值
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_reversed(const bool reverse) const;

    /**
    *以伏特为单位设置电机的电压限制。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ param限制
    *以伏特为单位的新电压限制
    *
    * \如果操作成功则返回1或如果操作则返回PROS_ERR
    *失败，设置错误。
	 */
    virtual std::int32_t set_voltage_limit(const std::int32_t limit) const;

    /**
    *获取为电机设置的制动模式。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return motor_brake_mode_e_t中的一个，根据设置的内容
    * motor，如果操作失败，则为E_MOTOR_BRAKE_INVALID，设置为errno。
	 */
    virtual motor_brake_mode_e_t get_brake_mode(void) const;

    /**
    *以mA为单位获取电机的电流限制。
    *
    *默认值为2500 mA。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return如果操作失败，则以mA或PROS_ERR为单位的电机电流限制，
    *设置errno。
	 */
    virtual std::int32_t get_current_limit(void) const;

    /**
    *获取为电机设置的编码器单位。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return motor_encoder_units_e_t中的一个根据设置的内容
    *如果操作失败，则为motor或E_MOTOR_ENCODER_INVALID。
	 */
    virtual motor_encoder_units_e_t get_encoder_units(void) const;

    /**
    *获取为电机设置的齿轮组。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \返回motor_gearset_e_t中的一个，根据为电机设置的内容，
    如果操作失败，则为*或E_GEARSET_INVALID。
	 */
    virtual motor_gearset_e_t get_gearing(void) const;

    /**
    *获取为电机设置的位置PID。此功能将返回
    如果motor_set_pos_pid（）或者，则所有参数都为零
    * motor_set_pos_pid_full（）函数尚未使用。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    *此外，在错误状态下，设置返回结构的所有值
    *到它们的负最大值。
    *
    * \ return包含最后设置的位置PID常数的motor_pid_full_s_t
    *给定电机
	 */
    virtual motor_pid_full_s_t get_pos_pid(void) const;

    /**
    *获取为电机设置的速度PID。此功能将返回
    *如果是motor_set_vel_pid（）或者，则所有参数都为零
    * motor_set_vel_pid_full（）函数尚未使用。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EINVAL  - 给定值不在V5端口范围内（1-21）。
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    *此外，在错误状态下，设置返回结构的所有值
    *到它们的负最大值。
    *
    * \ return包含最后设置的速度PID常数的motor_pid_full_s_t
    *给定电机
	 */
    virtual motor_pid_full_s_t get_vel_pid(void) const;

    /**
    *获取用户设置的电机运行方向。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \如果电机反转则返回1，如果电机没有则返回0
    *反转，如果操作失败则为PROS_ERR，设置为errno。
	 */
    virtual std::int32_t is_reversed(void) const;

    /**
    *获取用户设置的电压限制。
    *
    *默认值为0V，表示没有软件限制
    *强加于电压。
    *
    *当错误状态为时，此函数使用以下errno值
    * 到达：
    * EACCES  - 另一个资源目前正在尝试访问该端口。
    *
    * \ return如果操作失败，电机的电压限制为V或PROS_ERR，
    *设置errno。
	 */
    virtual std::int32_t get_voltage_limit(void) const;

  private:
    const std::uint8_t _port;
};

namespace literals
{
const pros::Motor operator"" _mtr(const unsigned long long int m);
const pros::Motor operator"" _rmtr(const unsigned long long int m);
} // namespace literals
} // namespace pros
#endif // _PROS_MOTORS_HPP_
