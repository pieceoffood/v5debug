/**
 * @Author: yan
 * @Date:   2018-10-11T13:09:06+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-11T13:20:19+08:00
 */
#ifndef AUTO_HPP_
#include "../systemData.hpp "

class AUTO
{
    //   private:
    //     CHASSIS *_chassis;
    //     LINEARSHOOT<2> *_shoot;
    //     int yFlag = 0;
    //     int thetaFlag = 0;
    //     const int _autoMode;             //0是普通自动赛 1是纯自动
    //     const int _shootHighFlagLimit;   //射高旗的距离
    //     const int _shootMiddleFlagLimit; //射中旗子的距离
    //     //初始化
    //     void init()
    //     {
    //         _chassis->resetSensors();
    //         _shoot->resetSensors();
    //         if (analogRead(RED_BLUE_POTEN) < SIDE_POTEN) //蓝方
    //         {
    //             yFlag = SITE_SIZE;
    //             thetaFlag = 360;
    //         }
    //         if (analogRead(OUT_IN_POTEN) < POS_POTEN) //前场
    //             _chassis->setState(F_X, abs(F_Y - yFlag), abs(F_THETA - thetaFlag));
    //         else if (analogRead(OUT_IN_POTEN) > POS_POTEN) //后场
    //             _chassis->setState(B_X, abs(B_Y - yFlag), abs(B_THETA - thetaFlag));
    //         else if (analogRead(OUT_IN_POTEN) >= 250 || analogRead(OUT_IN_POTEN) <= 260 || analogRead(RED_BLUE_POTEN) >= 250 || analogRead(RED_BLUE_POTEN) <= 260)
    //             print("Warnning!!!!!RED_BLUE OR OUT_IN_POTEN Error!!!");
    //     }
    //
    //   public:
    //     /**
    //        * 枚举旗子坐标,红方基准
    //        */
    //
    //     AUTO(CHASSIS *chassis, LINEARSHOOT<2> *shoot, const int shootHighFlagLimit, const int shootMiddleFlagLimit, const int autoMode = 0)
    //         : _chassis(chassis), _shoot(shoot), _shootHighFlagLimit(shootHighFlagLimit), _shootMiddleFlagLimit(shootMiddleFlagLimit), _autoMode(autoMode)
    //     {
    //         init();
    //         shootFlag(leftHighFlag, 180);
    //     }
    //     /**
    //  * 射中高旗
    //  * @param coordinate 中高旗的名字 枚举
    //  * @param theta      从什么角度去射
    //  */
    //     void shootFlag(const flagPosName &coordinate, const int theta)
    //     {
    //         int shootPosX = 0;
    //         int shootPosY = 0;
    //         if (flagCoordinate[_autoMode][coordinate].z >= 1000) //射高旗
    //         {
    //             shootPosX = flagCoordinate[_autoMode][coordinate].x + _shootHighFlagLimit * cos(180 - theta);
    //             shootPosY = flagCoordinate[_autoMode][coordinate].y - _shootHighFlagLimit * sin(180 - theta);
    //         }
    //         else //射中旗
    //         {
    //             shootPosX = flagCoordinate[_autoMode][coordinate].x + _shootMiddleFlagLimit * cos(180 - theta);
    //             shootPosY = flagCoordinate[_autoMode][coordinate].y - _shootMiddleFlagLimit * sin(180 - theta);
    //         }
    // #if (DEBUG_MODE)
    //         printf("shoot_pos_calc:x=%d,y=%d\n", shootPosX, shootPosY);
    // #endif
    //         _chassis->driveToPoint(shootPosX, shootPosY);
    //         _chassis->turnToAngle(theta);
    //         _shoot->shootingSet(1);
    //         wait(500);
    //     }
    //     /**
    //  * 撞旗,普通自动赛模式不会撞墙,纯自动模式会的
    //  * @param coordinate 低旗的名字
    //  */
    //     void bumperFlag(const flagPosName &coordinate)
    //     {
    //         int bumperFlagPosX = flagCoordinate[_autoMode][coordinate].x + 300;
    //         int bumperFlagPosY = flagCoordinate[_autoMode][coordinate].y - 142;
    //         _chassis->driveToPoint(bumperFlagPosX, bumperFlagPosY);
    //         _chassis->turnToAngle(180);
    //         _chassis->driveStraight(300);
    //         if (_autoMode)
    //         {
    //             _chassis->driveForward(40);
    //             wait(500);
    //             _chassis->driveForward(0);
    //             _chassis->setX(261);
    //             _chassis->setTheta(180);
    //             wait(500);
    //         }
    //     }
    //     /**
    //  * 翻盘子
    //  * @param x         哪一组盘子
    //  * @param intakePwm 吸吐的速度 +-127 正面翻是-127
    //  * @param waitTime  停着等待的时间
    //  * @param mode      模式:0:倒着开,1:正着开
    //  */
    //     void turnOverCap(int x, int intakePwm, unsigned long waitTime, bool mode = 0)
    //     {
    //         intake.set(intakePwm);
    //         _chassis->driveToPoint(capCoordinate[x].x, capCoordinate[x].y, mode);
    //         wait(waitTime);
    //         intake.stop(); //吸吐停止
    //     }
    //
    //     /**
    //      * 准备上平台
    //      * @param x 准备开台时X轴的坐标
    //      * @param y 准备开台时Y轴的坐标
    //      * @param backwards 是否倒着上平台 写false 倒着开上去写true 默认false
    //      */
    //
    //     void readyForPlatform(int x, int y, bool backwards = false)
    //     {
    //         _shoot->setMode(false);                 //关闭射球模式
    //         if (_chassis->getState().x < POS_POTEN) //在前场
    //         {
    //             _chassis->driveToPoint(x, abs(y - yFlag), backwards); //开到台子前
    //             _chassis->turnToAngle(0);                             //转向0度
    //         }
    //         else //在后场
    //         {
    //             _chassis->driveToPoint(x, abs(y - yFlag), backwards); //开到台子前
    //             _chassis->turnToAngle(180);                           //转向180度
    //         }
    //     }
    //     /**
    //      * 准备上平台
    //      * @param x 台子的X轴的坐标
    //      * @param y 台子的Y轴的坐标
    //      * @param
    //      * @param backwards 是否倒着上平台 写false 倒着开上去写true 默认false
    //      */
    //     void runToPlatform(int x, int y, int mode = 1, bool backwards = false)
    //     {
    //
    //         intake.set(127 * mode);                                         //吸吐吸
    //         _chassis->driveToPoint(x, abs(y - yFlag), backwards);           //开上台子
    //         if (_autoMode)                                                  //如果插了纯自动
    //             _chassis->driveToPoint(x, abs(y + 600 - yFlag), backwards); //开上高台
    //         intake.stop();                                                  //吸吐停
    //     }
};
#endif
