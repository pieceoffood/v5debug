/**
 * @Author: yan
 * @Date:   2018-10-16T10:11:21+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-16T10:32:26+08:00
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
        userDisplay.creartSensorsInfo(userDisplay.opcontrolPage, LV_HOR_RES);
    printf("Key pressed: %s\n", txt);

    return LV_RES_INV;
}
void UserDisplay::createStartPage()
{
    static const char *btnm_map[] = {"传感器信息", "机器人检测", "\n",
                                     "自动赛", "手动赛", "\n",
                                     "前后PID", "旋转PID", "\n",
                                     "ODOM测试", "自定义测试", ""};
    if (startBTNM == nullptr)
        startBTNM = lv_btnm_create(opcontrolPage, nullptr); //创建按钮集群
    lv_btnm_set_map(startBTNM, btnm_map);
    lv_obj_set_size(startBTNM, LV_HOR_RES, LV_VER_RES - 30);
    lv_obj_set_y(startBTNM, 30);
    lv_btnm_set_action(startBTNM, btnm_action);
}
