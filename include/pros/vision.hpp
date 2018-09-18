/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-18T22:03:46+08:00
 */

#ifndef _PROS_VISION_HPP_
#define _PROS_VISION_HPP_

#include "pros/vision.h"

#include <cstdint>

namespace pros
{
class Vision
{
  public:
    /**
 * 视觉传感器的构造函数
 * @param port       V1端口号从1-21开始
 * @param zero_point 	其中一个pros::vision_zero_e_t设置FOV的（0,0）坐标
 */
    Vision(std::uint8_t port, vision_zero_e_t zero_point = E_VISION_ZERO_TOPLEFT);

    /**
 * 清除视觉传感器LED颜色，将其重置为默认行为，显示最突出的对象签名颜色。
 * 达到错误状态时，此函数使用以下errno值：
 * EINVAL - 给定值不在V5端口范围内（1-21）。
 * EACCES - 另一个资源目前正在尝试访问该端口。
 * @return  如果没有错误则返回 0，否则返回 PROS_ERR
 */
    std::int32_t clear_led(void) const;

    /**
 * 根据size_id获取第n个最大的对象。
 * @param  size_id 从列表中读取的对象大致按对象大小排序（0是最大项，1是第二大项等）
 * @return        与给定大小id对应的vision_object_s_t对象，如果发生错误则返回 PROS_ERR。
 */
    vision_object_s_t get_by_size(const std::uint32_t size_id) const;

    /**
 * 根据size_id获取给定签名的第n个最大对象
 * @param  size_id 从列表中读取的对象大致按对象大小排序（0是最大项，1是第二大项等）
 * @param  sig_id  将返回对象的签名号
 * @return        与给定签名和size_id对应的vision_object_s_t对象，如果发生错误则返回 PROS_ERR。
 */
    vision_object_s_t get_by_sig(const std::uint32_t size_id, const std::uint32_t sig_id) const;

    /**
 * 获取视觉传感器的曝光参数。
 * @return  当发生错误时，[0,100]，PROS_ERR的当前曝光百分比参数
 */
    std::int32_t get_exposure(void) const;

    /**
 * 返回视觉传感器当前检测到的对象数。
 * @return  指定视觉传感器上检测到的对象数。如果端口无效或发生错误，则返回PROS_ERR。
 */
    std::int32_t get_object_count(void) const;

    /**
 * 获取视觉传感器的白平衡参数
 * @return  返回传感器的当前RGB白平衡设置
 */
    std::int32_t get_white_balance(void) const;

    /**
 * 将object_count对象描述符读入object_arr。
 * @param  size_id     	从按列表大致排序的列表中读取的第一个对象（0是最大项，1是第二大项等）
 * @param  object_count 要读取多少个对象
 * @param  object_arr   指向将数据复制到的指针
 * @return              复制的对象签名数。如果视觉传感器检测到的对象较少，则此数字将小于object_count。
 *                      如果端口无效，发生错误或找到的对象少于size_id，则返回PROS_ERR。
 *                      object_arr中未找到的所有对象都被赋予VISION_OBJECT_ERR_SIG作为其签名。
 */
    std::int32_t read_by_size(const std::uint32_t size_id, const std::uint32_t object_count,
                              vision_object_s_t *const object_arr) const;

    /**
 * 将object_count对象描述符读入object_arr。
 * @param  size_id      从按列表大致排序的列表中读取的第一个对象（0是最大项，1是第二大项等）
 * @param  sig_id       将返回对象的签名号
 * @param  object_count 要读取多少个对象
 * @param  object_arr   指向将数据复制到的指针
 * @return              复制的对象签名数。如果视觉传感器检测到的对象较少，则此数字将小于object_count。
 * 						如果端口无效，发生错误或找到的对象少于size_id，则返回PROS_ERR。
 * 						object_arr中未找到的所有对象都被赋予VISION_OBJECT_ERR_SIG作为其签名。
 */
    std::int32_t read_by_sig(const std::uint32_t size_id, const std::uint32_t sig_id, const std::uint32_t object_count,
                             vision_object_s_t *const object_arr) const;

    /**
 * 启用/禁用视觉传感器上的自动白平衡。
 * @param  enable 传递0表示禁用，1表示启用
 * @return       如果没有错误则返回0，否则返回PROS_ERR
 */
    std::int32_t set_auto_white_balance(const std::uint8_t enable) const;

    /**
 * 设置视觉传感器的曝光参数。
 * @param  percent [0,100]的新曝光百分比
 * @return         如果没有错误则返回 0，否则返回 PROS_ERR
 */
    std::int32_t set_exposure(const std::uint8_t percent) const;

    /**
 * 设置视觉传感器LED颜色，覆盖自动行为。
 * @param  rgb 用于设置LED的RGB代码
 * @return     如果没有错误则返回 0，否则返回 PROS_ERR
 */
    std::int32_t set_led(const std::int32_t rgb) const;

    /**
 * 在视觉传感器上手动设置白平衡参数。此功能将禁用自动白平衡。
 * @param  rgb 白平衡参数
 * @return     如果没有错误则返回0，否则返回PROS_ERR
 */
    std::int32_t set_white_balance(const std::int32_t rgb) const;

    /**
 * 设置视场的（0，0）坐标。这将影响为每个请求返回的坐标.
 * 来自传感器的VIENION ObjutsSyt，因此建议此功能仅用于在其使用开始时配置传感器。
 * @param  zero_point 坐标
 * @return            如果设置成功则返回1。否则0。
 */
    std::int32_t set_zero_point(vision_zero_e_t zero_point) const;

  private:
    std::uint8_t _port;
};
} // namespace pros
#endif // _PROS_VISION_HPP_
