/**
 * @Author: yan
 * @Date:   2018-10-24T08:20:36+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-26T09:28:28+08:00
 */

#ifndef NCRAPI_HPP_
#define NCRAPI_HPP_

#include "ncrapi/chassis/chassis.hpp"
#include "ncrapi/generic/generic.hpp"
#include "ncrapi/generic/shoot.hpp"
#include "ncrapi/systemData.hpp"
#include "ncrapi/userDisplay/userDisplay.hpp"

//版本号
#define NCR_VERSION_MAJOR 5 //主要版本号
#define NCR_VERSION_MINOR 0 //辅助版本号
#define NCR_VERSION_PATCH 0 //补丁版本号
#define NCR_VERSION_STRING "5.0.0"

#define test ; //输入用户名
#if defined(pig)
#inlcude "pig.hpp"
#else
#include "userConfig/example.hpp"
#endif
extern pros::Controller joy1;
extern pros::Controller joy2;
extern Chassis chassis;
extern LinearShoot<2> shoot;
extern Generic<2> intake;
#endif /* end of include guard: ncrapi_HPP_ */
