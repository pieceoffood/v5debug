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
#include "ncrapi/generic/intake.hpp"
#include "ncrapi/generic/lift.hpp"
#include "ncrapi/generic/shoot.hpp"
#include "ncrapi/system/systemData.hpp"
#include "ncrapi/userDisplay/userDisplay.hpp"

//版本号
#define NCR_VERSION_MAJOR 5 //主要版本号
#define NCR_VERSION_MINOR 0 //辅助版本号
#define NCR_VERSION_PATCH 0 //补丁版本号
#define NCR_VERSION_STRING "5.0.0"

//视觉定义 这里有问题 官方说下个版本修复
// extern pros::vision_signature_s_t BALL;
// extern pros::vision_signature_s_t RED_CAP;
// extern pros::vision_signature_s_t BLUE_CAP;
// extern pros::vision_signature_s_t RED_FALG;
// extern pros::vision_signature_s_t BLUE_FALG;
// extern pros::vision_signature_s_t RED_PLAT;
// extern pros::vision_signature_s_t BLUE_PLAT;
// extern pros::vision_signature_s_t CENTRAL_PLAT;
// extern pros::vision_signature_s_t HIGH_COLUMN;
// extern pros::vision_signature_s_t LOW_COLUMN;
//通用部件
extern pros::Controller joy1;
extern pros::Controller joy2;
extern Chassis chassis;
extern pros::Vision visionF;

#if defined(ROBOT_ALMIGHTY) //全能机

extern Shoot<1> shoot;
extern Lift<1> lift;
extern Generic<1> intake;
extern CapIntake<1> capIntake;
extern pros::Task _shootTask;
//静态外部变量
static void taskShoot(void *para)
{
    shoot.loop();
}
#elif defined(ROBOT_CAP) //盘子机

#else //矮子机
extern Generic<1> head;
extern Generic<1> intake;
extern pros::Vision vision;
extern Shoot<2> shoot;
extern pros::Task _shootTask;
//静态外部变量
static void taskShoot(void *para)
{
    shoot.loop();
}
#endif
#endif /* end of include guard: ncrapi_HPP_ */
