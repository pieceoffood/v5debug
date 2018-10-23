
#ifndef NCRAPI_HPP_
#define NCRAPI_HPP_

#include "ncrapi/systemData.hpp"
#include "ncrapi/userDisplay/userDisplay.hpp"
#include "ncrapi\chassis\chassis.hpp"
#include "ncrapi\generic\generic.hpp"

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

#endif /* end of include guard: ncrapi_HPP_ */
