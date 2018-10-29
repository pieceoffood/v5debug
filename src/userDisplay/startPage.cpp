/**
 * @Author: 陈昱安
 * @Date:   2018-10-22T22:01:37+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-10-28T22:09:06+08:00
 */

#include "main.h"
/**
 * 按钮阵列的动作
 * @param  btnm 按钮阵列
 * @param  txt  按钮的名字
 * @return      系统值
 */
static lv_res_t btnm_action(lv_obj_t *btnm, const char *txt)
{
    (void)btnm; /*Unused*/
    //TODO 做一个字符串判断
    if (!strcmp(txt, "传感器信息"))
        userDisplay.creartSensorsInfo(userDisplay.displayObj[OBJ_OPCONTROL], LV_HOR_RES);
    printf("Key pressed: %s\n", txt);

    return LV_RES_INV;
}
void UserDisplay::createStartObj()
{
    static const char *btnm_map[] = {"传感器信息", "机器人检测", "\n",
                                     "自动赛", "手动赛", "\n",
                                     "前后PID", "旋转PID", "\n",
                                     "ODOM测试", "自定义测试", ""};
    if (displayObj[BTNM_START] == nullptr)
        displayObj[BTNM_START] = lv_btnm_create(userDisplay.displayObj[OBJ_OPCONTROL], nullptr); //创建按钮集群
    lv_btnm_set_map(displayObj[BTNM_START], btnm_map);
    lv_obj_set_size(displayObj[BTNM_START], LV_HOR_RES, LV_VER_RES - 30);
    lv_obj_set_y(displayObj[BTNM_START], 30);
    lv_btnm_set_action(displayObj[BTNM_START], btnm_action);
}
