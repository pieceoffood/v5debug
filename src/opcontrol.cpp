/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:58+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-24T22:52:49+08:00
 */

#include "main.h"
using namespace pros::literals; //pros命令空间内包含的literals命名空间
using namespace pros;
/**
*手动模式
 */
void opcontrol()
{
    Controller master(pros::E_CONTROLLER_MASTER);
    auto left_mtr = 1_mtr;
    Motor right_mtr(2);
    while (true)
    {
        lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                   (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                   (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
        int left = master.get_analog(ANALOG_LEFT_Y);
        int right = master.get_analog(ANALOG_RIGHT_Y);

        left_mtr = left;
        right_mtr = right;
        pros::delay(20);
    }
}
