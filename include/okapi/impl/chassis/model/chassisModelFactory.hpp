/**
 * @Author: yan
 * @Date:   2018-10-08T14:15:45+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-15T15:16:45+08:00
 */

#ifndef _OKAPI_CHASSISMODELFACTORY_HPP_
#define _OKAPI_CHASSISMODELFACTORY_HPP_

#include "okapi/api/chassis/model/skidSteerModel.hpp"
#include "okapi/api/chassis/model/threeEncoderSkidSteerModel.hpp"
#include "okapi/api/chassis/model/xDriveModel.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"

namespace okapi
{
class ChassisModelFactory
{
  public:
    /**
   * Model for a skid steer drive (wheels parallel with robot's direction of motion). When all
   * motors are powered +127, the robot should move forward in a straight line.
   *
   * This constructor infers the two sensors from the left and right motors (using the integrated
   * encoders).
   *
   * @param ileftSideMotor left side motor
   * @param irightSideMotor right side motor
   */
    static SkidSteerModel create(Motor ileftSideMotor,
                                 Motor irightSideMotor,
                                 double imaxVelocity,
                                 double imaxVoltage = 12000);

    /**
   * Model for a skid steer drive (wheels parallel with robot's direction of motion). When all
   * motors are powered +127, the robot should move forward in a straight line.
   *
   * This constructor infers the two sensors from the left and right motors (using the integrated
   * encoders).
   *
   * @param ileftSideMotor left side motor
   * @param irightSideMotor right side motor
   */
    static SkidSteerModel create(MotorGroup ileftSideMotor,
                                 MotorGroup irightSideMotor,
                                 double imaxVelocity,
                                 double imaxVoltage = 12000);

    /**
   * Model for a skid steer drive (wheels parallel with robot's direction of motion). When all
   * motors are powered +127, the robot should move forward in a straight line.
   *
   * This constructor infers the two sensors from the left and right motors (using the integrated
   * encoders).
   *
   * @param ileftSideMotor left side motor
   * @param irightSideMotor right side motor
   */
    static SkidSteerModel create(MotorGroup ileftSideMotor,
                                 MotorGroup irightSideMotor,
                                 ADIEncoder ileftEnc,
                                 ADIEncoder irightEnc,
                                 double imaxVelocity,
                                 double imaxVoltage = 12000);

    /**
    * x驱动器的型号（滑轮转向驱动器的45度轮）。当所有电机都通电时
    * +127，机器人应该以直线向前移动。
    *这个构造函数从左上角和右上角的电机推断出两个传感器（使用
    *集成编码器）。
    * @param itopLeftMotor左上方电机
    * @param itopRightMotor右上方电机
    * @param ibottomRightMotor右下方电机
    * @param ibottomLeftMotor左下电机
   */
    static XDriveModel create(Motor itopLeftMotor,
                              Motor itopRightMotor,
                              Motor ibottomRightMotor,
                              Motor ibottomLeftMotor,
                              double imaxVelocity,
                              double imaxVoltage = 12000);

    /**
    * x驱动器的型号（滑轮转向驱动器的45度轮）。当所有电机都通电时
    * +127，机器人应该以直线向前移动。
    *
    *这个构造函数从左上角和右上角的电机推断出两个传感器（使用
    *集成编码器）。
    *
    * @param itopLeftMotor左上方电机
    * @param itopRightMotor右上方电机
    * @param ibottomRightMotor右下方电机
    * @param ibottomLeftMotor左下电机
   */
    static XDriveModel create(Motor itopLeftMotor,
                              Motor itopRightMotor,
                              Motor ibottomRightMotor,
                              Motor ibottomLeftMotor,
                              ADIEncoder ileftEnc,
                              ADIEncoder irightEnc,
                              double imaxVelocity,
                              double imaxVoltage = 12000);

    /**
   * Model for a skid steer drive (wheels parallel with robot's direction of motion). When all
   * motors are powered +127, the robot should move forward in a straight line.
   *
   * @param ileftSideMotor left side motor
   * @param irightSideMotor right side motor
   * @param ileftEnc left side encoder
   * @param imiddleEnc middle encoder (mounted perpendicular to the left and right side encoders)
   * @param irightEnc right side encoder
   */
    static ThreeEncoderSkidSteerModel create(Motor ileftSideMotor,
                                             Motor irightSideMotor,
                                             ADIEncoder ileftEnc,
                                             ADIEncoder imiddleEnc,
                                             ADIEncoder irightEnc,
                                             double imaxVelocity,
                                             double imaxVoltage = 12000);

    /**
   * Model for a skid steer drive (wheels parallel with robot's direction of motion). When all
   * motors are powered +127, the robot should move forward in a straight line.
   *
   * @param ileftSideMotor left side motor
   * @param irightSideMotor right side motor
   * @param ileftEnc left side encoder
   * @param imiddleEnc middle encoder (mounted perpendicular to the left and right side encoders)
   * @param irightEnc right side encoder
   */
    static ThreeEncoderSkidSteerModel create(MotorGroup ileftSideMotor,
                                             MotorGroup irightSideMotor,
                                             ADIEncoder ileftEnc,
                                             ADIEncoder imiddleEnc,
                                             ADIEncoder irightEnc,
                                             double imaxVelocity,
                                             double imaxVoltage = 12000);
};
} // namespace okapi

#endif
