/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-24T17:21:31+08:00
 */
#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES //如果定义了这句话 可以使用一些更短的函数或者宏的名字

/**
 * 如果定义，C++文字将可供使用。
 * 例如，你可以做“4ym＝50”，将马达4的目标速度设定为50。
 */
#define PROS_USE_LITERALS

#include "api.h"

// using namespace pros;
// using namespace okapi;
//这里可以添加更多的头文件

//#include "pros/api_legacy.h"

#ifdef __cplusplus
//这里可以添加CPP的头文件
#include "ncrapi\ncrapi.hpp"
// #include "okapi\api.hpp"

#endif

#endif // _PROS_MAIN_H_
