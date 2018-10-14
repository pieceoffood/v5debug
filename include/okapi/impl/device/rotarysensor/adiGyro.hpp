/**
 * @Author: yan
 * @Date:   2018-10-08T14:15:45+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-14T10:46:28+08:00
 */

#ifndef _OKAPI_GYRO_HPP_
#define _OKAPI_GYRO_HPP_

#include "api.h"
#include "okapi/api/control/controllerInput.hpp"
#include "okapi/api/device/rotarysensor/continuousRotarySensor.hpp"

namespace okapi
{
class ADIGyro : public ContinuousRotarySensor
{
  public:
    /**
    *给定ADI端口上的陀螺仪。如果端口先前未配置为陀螺仪，然后构造函数将阻塞1秒进行校准。陀螺仪的测量值为十分之一度，因此每转有3600个测量点。
    * @param iport ADI端口号
    * @param乘以一个值乘以陀螺仪标题值
   */
    ADIGyro(std::uint8_t iport, double imultiplier = 1);

    virtual ~ADIGyro();

    /**
    *获取当前传感器值。
    * @return当前传感器值，或者``PROS_ERR``失败。
   */
    double get() const override;

    /**
    *将传感器重置为零。
    * @return 1成功，PROS_ERR失败
   */
    std::int32_t reset() override;

    /**
    *获取传感器值以用于控制回路。可以自动调用此方法
    *控制器的另一个线程。
    * @return当前传感器值，或者``PROS_ERR``失败。
   */
    double controllerGet() override;

  protected:
    pros::ADIGyro gyro;
};
} // namespace okapi

#endif
