#ifndef ROBOTSET_HPP_
#define ROBOTSET_HPP_

#define xuanxuan //输入用户名
#if defined(pig)
#inlcude "userConfig/pig.hpp"

#elif defined(sheep)
#include "ncrapi/userConfig/AlmightyExample.hpp" //全能机配置

#elif defined(bird)
#include "ncrapi/userConfig/CapExample.hpp"

#else
#include "ncrapi/userConfig/DwarfExample.hpp" //默认矮子机配置
#endif

#endif /* end of include guard: ROBOTSET_HPP_ */
