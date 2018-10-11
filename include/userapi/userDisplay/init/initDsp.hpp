/**
 * @Author: yan
 * @Date:   2018-10-11T10:42:20+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-11T10:52:45+08:00
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
        lv_obj_t *lab = lv_label_create(_data->initPage, nullptr);
        lv_label_set_text(lab, "robot Initialization...");
    }
    ~InitDsp() { std::cout << "InitDsp destructor" << std::endl; }
};
#endif /* end of include guard: INITDSP_HPP_ */
