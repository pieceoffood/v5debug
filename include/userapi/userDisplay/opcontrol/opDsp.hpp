/**
 * @Author: yan
 * @Date:   2018-10-11T10:26:32+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-13T17:37:43+08:00
 */
#ifndef OPDSP_HPP_
#define OPDSP_HPP_
#include "userapi/userDisplay/userDisplay.hpp"
class OpDsp
{
  private:
    UserDisplay *_data;
    int _maxLoopTime = 0;
    int _minLoopTime = 20;
    char _buf_long[256];

  public:
    OpDsp(UserDisplay *data) : _data(data)
    {
        lv_scr_load(_data->opcontrolPage);
        if (!pros::competition::is_connected()) //没插场控
            startP(_data->opcontrolPage);
        else //插了场控
        {
            lv_obj_t *lab = lv_label_create(_data->opcontrolPage, nullptr);
            lv_label_set_text(lab, "遥控程序执行中");
        }
    }
    ~OpDsp()
    {
        std::cout << "opDsp destructor" << std::endl;
    }
    void loopTime(const int loopTime)
    {
        if (loopTime > _maxLoopTime)
            _maxLoopTime = loopTime;
        if (loopTime < _minLoopTime)
            _minLoopTime = loopTime;
        sprintf(_buf_long, "loop:%d max:%d min:%d\n", loopTime, _maxLoopTime, _minLoopTime);
        lv_label_set_text(_data->loopTimeLab, _buf_long);
    }
    void startP(lv_obj_t *para)
    {
        static const char *btnm_map[] = {"在线检测", "机器人检测", "\n",
                                         "自动赛", "手动赛", "\n",
                                         "前后PID", "旋转PID", "\n",
                                         "ODOM测试", "自定义测试", ""};

        lv_obj_t *btnm = lv_btnm_create(para, NULL); //创建按钮集群
        lv_btnm_set_map(btnm, btnm_map);
        lv_obj_set_size(btnm, LV_HOR_RES, LV_VER_RES - 30);
        lv_obj_set_y(btnm, 30);
    }
};

#endif /* end of include guard: OPDSP_HPP_ */
