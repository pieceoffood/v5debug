/**
 * @Author: yan
 * @Date:   2018-10-11T10:42:20+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-14T11:56:40+08:00
 */
#ifndef INITDSP_HPP_
#define INITDSP_HPP_
#include "userapi/userDisplay/userDisplay.hpp"
class InitDsp
{
  private:
    UserDisplay *_data;

  public:
    InitDsp(UserDisplay *data) : _data(data)
    {
        lv_scr_load(_data->initPage);
        lv_obj_t *lab1 = lv_label_create(_data->initPage, nullptr);
        lv_obj_t *lab2 = lv_label_create(_data->initPage, nullptr);
        lv_label_set_text(lab1, "机器人初始化中...\n");
        okapi::ADIGyro gyro(1);
        if(gyro.get()==PROS_ERR)
        lv_label_set_text(lab2, "警告!!!陀螺仪初始化失败\n");
        else
        lv_label_set_text(lab2, "陀螺仪初始化完毕\n");
    }
    ~InitDsp() { std::cout << "InitDsp destructor" << std::endl; }
};
#endif /* end of include guard: INITDSP_HPP_ */
