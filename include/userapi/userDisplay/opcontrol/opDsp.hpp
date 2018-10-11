/**
 * @Author: yan
 * @Date:   2018-10-11T10:26:32+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-11T10:38:50+08:00
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
        if (!pros::competition::is_connected())
        {
            startP(_data->opcontrolPage);
        }
        else
        {
            lv_obj_t *lab = lv_label_create(_data->opcontrolPage, nullptr);
            lv_label_set_text(lab, "robot opcontroling...");
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
        static const char *btnm_map[] = {"onlineTest", "robotTest", "\n",
                                         "autonomous", "opcontorl", "\n",
                                         "frPid", "rotatePid", "\n",
                                         "odomTest", "customTest", ""};

        lv_obj_t *btnm = lv_btnm_create(para, NULL); //创建按钮集群
        lv_btnm_set_map(btnm, btnm_map);
        lv_obj_set_size(btnm, LV_HOR_RES, LV_VER_RES);
    }
};

#endif /* end of include guard: OPDSP_HPP_ */
