#ifndef ROBOTSET_HPP_
#define ROBOTSET_HPP_

#define xuanxuan //输入用户名
#if defined(pig)
#inlcude "userConfig/pig.hpp"
#elif defined(chicken)
#include "ncrapi/userConfig/chicken.hpp" //全能机配置
#elif defined(sheep)
#include "ncrapi/userConfig/sheep.hpp" //全能机配置
#elif defined(xuanxuan)
#include "ncrapi/userConfig/xuanxuan.hpp" //矮子机配置
#elif defined(bird)
#include "ncrapi/userConfig/bird.hpp"

#else

#endif

#endif /* end of include guard: ROBOTSET_HPP_ */
