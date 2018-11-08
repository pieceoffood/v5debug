/**
 * \file pros/vision.h
 *
 * Contains prototypes for the VEX Vision Sensor-related functions.
 *
 * Visit https://pros.cs.purdue.edu/v5/tutorials/topical/vision.html to learn
 * more.
 *
 * This file should not be modified by users, since it gets replaced whenever
 * a kernel upgrade occurs.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_VISION_H_
#define _PROS_VISION_H_

#define VISION_OBJECT_ERR_SIG 255
// Parameters given by VEX
#define VISION_FOV_WIDTH 316
#define VISION_FOV_HEIGHT 212

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
    namespace pros
    {
#endif
    /**
*此枚举定义了不同类型的对象
*可由视觉传感器检测到
 */
    typedef enum vision_object_type
    {
        E_VISION_OBJECT_NORMAL = 0,
        E_VISION_OBJECT_COLOR_CODE = 1,
        E_VISION_OBJECT_LINE = 2
    } vision_object_type_e_t;

    /**
	*此结构包含视觉传感器使用的参数
    *检测物体。
 */
    typedef struct __attribute__((__packed__)) vision_signature
    {
        uint8_t id;
        uint8_t _pad[3];
        float range;
        int32_t u_min;
        int32_t u_max;
        int32_t u_mean;
        int32_t v_min;
        int32_t v_max;
        int32_t v_mean;
        uint32_t rgb;
        uint32_t type;
    } vision_signature_s_t;

    /**
	*此结构包含检测到的对象的描述符
    *视觉传感器
 */
    typedef struct __attribute__((__packed__)) vision_object
    {
        //对象签名
        uint16_t signature;
        //对象类型，例如正常，颜色代码或行检测
        vision_object_type_e_t type;
        //对象的左边界坐标
        int16_t left_coord;
        //对象的顶部边界坐标
        int16_t top_coord;
        //对象的宽度
        int16_t width;
        //对象的高度
        int16_t height;
        //颜色代码对象的角度，以0.1度为单位（例如10  - > 1度，155- > 15.5度
        uint16_t angle;

        //对象中间的坐标（根据上面的值计算）
        int16_t x_middle_coord;
        int16_t y_middle_coord;
    } vision_object_s_t;

    typedef enum vision_zero
    {
        E_VISION_ZERO_TOPLEFT = 0, //（0,0）坐标是FOV的左上角
        E_VISION_ZERO_CENTER = 1   //（0,0）坐标是FOV的中心
    } vision_zero_e_t;

#ifdef PROS_USE_SIMPLE_NAMES
#ifdef __cplusplus
#define VISION_OBJECT_NORMAL pros::E_VISION_OBJECT_NORMAL
#define VISION_OBJECT_COLOR_CODE pros::E_VISION_OBJECT_COLOR_CODE
#define VISION_OBJECT_LINE pros::E_VISION_OBJECT_LINE
#define VISION_ZERO_TOPLEFT pros::E_VISION_ZERO_TOPLEFT
#define VISION_ZERO_CENTER pros::E_VISION_ZERO_CENTER
#else
#define VISION_OBJECT_NORMAL E_VISION_OBJECT_NORMAL
#define VISION_OBJECT_COLOR_CODE E_VISION_OBJECT_COLOR_CODE
#define VISION_OBJECT_LINE E_VISION_OBJECT_LINE
#define VISION_ZERO_TOPLEFT E_VISION_ZERO_TOPLEFT
#define VISION_ZERO_CENTER E_VISION_ZERO_CENTER
#endif
#endif

#ifdef __cplusplus
    namespace c
    {
#endif

    /**
 * Clears the vision sensor LED color, reseting it back to its default behavior,
 * displaying the most prominent object signature color.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 * failed, setting errno.
 */
    int32_t vision_clear_led(uint8_t port);

    /**
 * Gets the nth largest object according to size_id.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 * \param size_id
 *        The object to read from a list roughly ordered by object size
 *        (0 is the largest item, 1 is the second largest, etc.)
 *
 * \return The vision_object_s_t object corresponding to the given size id, or
 * PROS_ERR if an error occurred.
 */
    vision_object_s_t vision_get_by_size(uint8_t port, const uint32_t size_id);

    /**
 * Gets the nth largest object of the given signature according to size_id.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 * EAGAIN - Reading the Vision Sensor failed for an unknown reason.
 *
 * \param port
 *        The V5 port number from 1-21
 * \param size_id
 *        The object to read from a list roughly ordered by object size
 *        (0 is the largest item, 1 is the second largest, etc.)
 * \param signature
 *        The signature ID [1-7] for which an object will be returned.
 *
 * \return The vision_object_s_t object corresponding to the given signature and
 * size_id, or PROS_ERR if an error occurred.
 */
    vision_object_s_t vision_get_by_sig(uint8_t port, const uint32_t size_id, const uint32_t sig_id);

    /**
 * Gets the exposure parameter of the Vision Sensor.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 *
 * \return The current exposure percentage parameter from [0,100], PROS_ERR if
 * an error occurred
 */
    int32_t vision_get_exposure(uint8_t port);

    /**
 * Gets the number of objects currently detected by the Vision Sensor.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 *
 * \return The number of objects detected on the specified vision sensor.
 * Returns PROS_ERR if the port was invalid or an error occurred.
 */
    int32_t vision_get_object_count(uint8_t port);

    /**
 * Get the white balance parameter of the Vision Sensor.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 * 		    The V5 port number from 1-21
 *
 * \return The current RGB white balance setting of the sensor
 */
    int32_t vision_get_white_balance(uint8_t port);

    /**
 * Reads up to object_count object descriptors into object_arr.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21), or
 *          fewer than object_count number of objects were found.
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 * \param size_id
 *        The object to read from a list roughly ordered by object size
 *        (0 is the largest item, 1 is the second largest, etc.)
 * \param object_count
 *        The number of objects to read
 * \param[out] object_arr
 *             A pointer to copy the objects into
 *
 * \return The number of object signatures copied. This number will be less than
 * object_count if there are fewer objects detected by the vision sensor.
 * Returns PROS_ERR if the port was invalid, an error occurred, or fewer objects
 * than size_id were found. All objects in object_arr that were not found are
 * given VISION_OBJECT_ERR_SIG as their signature.
 */
    int32_t vision_read_by_size(uint8_t port, const uint32_t size_id, const uint32_t object_count,
                                vision_object_s_t *const object_arr);

    /**
 * Reads up to object_count object descriptors into object_arr.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21), or
 *          fewer than object_count number of objects were found.
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 * \param object_count
 *        The number of objects to read
 * \param size_id
 *        The object to read from a list roughly ordered by object size
 *        (0 is the largest item, 1 is the second largest, etc.)
 * \param signature
 *        The signature ID [1-7] for which an object will be returned.
 * \param[out] object_arr
 *             A pointer to copy the objects into
 *
 * \return The number of object signatures copied. This number will be less than
 * object_count if there are fewer objects detected by the vision sensor.
 * Returns PROS_ERR if the port was invalid, an error occurred, or fewer objects
 * than size_id were found. All objects in object_arr that were not found are
 * given VISION_OBJECT_ERR_SIG as their signature.
 */
    int32_t vision_read_by_sig(uint8_t port, const uint32_t size_id, const uint32_t sig_id, const uint32_t object_count,
                               vision_object_s_t *const object_arr);

    /**
 * Enables/disables auto white-balancing on the Vision Sensor.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 * 		    The V5 port number from 1-21
 * \param enabled
 * 		    Pass 0 to disable, 1 to enable
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 * failed, setting errno.
 */
    int32_t vision_set_auto_white_balance(uint8_t port, const uint8_t enable);

    /**
 * Sets the exposure parameter of the Vision Sensor.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 * \param percent
 *        The new exposure percentage from [0,100]
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 * failed, setting errno.
 */
    int32_t vision_set_exposure(uint8_t port, const uint8_t percent);

    /**
 * Sets the vision sensor LED color, overriding the automatic behavior.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 *        The V5 port number from 1-21
 * \param rgb
 *        An RGB code to set the LED to
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 * failed, setting errno.
 */
    int32_t vision_set_led(uint8_t port, const int32_t rgb);

    /**
 * Sets the white balance parameter of the Vision Sensor.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 * 		    The V5 port number from 1-21
 * \param rgb
 *        The new RGB white balance setting of the sensor
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 * failed, setting errno.
 */
    int32_t vision_set_white_balance(uint8_t port, const int32_t rgb);

    /**
 * Sets the (0,0) coordinate for the Field of View.
 *
 * This will affect the coordinates returned for each request for a
 * vision_object_s_t from the sensor, so it is recommended that this function
 * only be used to configure the sensor at the beginning of its use.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * EINVAL - The given value is not within the range of V5 ports (1-21).
 * EACCES - Another resource is currently trying to access the port.
 *
 * \param port
 * 		    The V5 port number from 1-21
 * \param zero_point
 *        One of vision_zero_e_t to set the (0,0) coordinate for the FOV
 *
 * \return 1 if the operation was successful or PROS_ERR if the operation
 * failed, setting errno.
 */
    int32_t vision_set_zero_point(uint8_t port, vision_zero_e_t zero_point);

#ifdef __cplusplus
    } // namespace c
    } // namespace pros
}
#endif

#endif // _PROS_VISION_H_
