/**
 * @Author: yan
 * @Date:   2018-10-11T10:43:23+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-13T17:12:36+08:00
 */
#ifndef DISABLEDSP_HPP_
#define DISABLEDSP_HPP_
#include "userapi/userDisplay/userDisplay.hpp"
class DisabledDsp
{
  private:
    UserDisplay *_data;

  public:
    DisabledDsp(UserDisplay *data) : _data(data)
    {
        lv_scr_load(_data->disabledPage);
        lv_obj_t *lab = lv_label_create(_data->disabledPage, nullptr);
        lv_label_set_text(lab, "场控关闭状态...");
    }
    ~DisabledDsp() { std::cout << "DisabledDsp destructor" << std::endl; }
};
#endif /* end of include guard: DISABLEDSP_HPP_ */
