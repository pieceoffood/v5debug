/**
 * @Author: yan
 * @Date:   2018-10-11T10:44:00+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-11T10:50:13+08:00
 */
#ifndef AUTODSP_HPP_
#define AUTODSP_HPP_
#include "userapi/userDisplay/userDisplay.hpp"
class AutoDsp
{
  private:
    UserDisplay *_data;

  public:
    AutoDsp(UserDisplay *data) : _data(data)
    {
        lv_scr_load(_data->autonomousPage);
        lv_obj_t *lab = lv_label_create(_data->autonomousPage, nullptr);
        lv_label_set_text(lab, "robot autonomousing...");
    }
    ~AutoDsp() { std::cout << "autoDsp destructor" << std::endl; }
};
#endif /* end of include guard: AUTODSP_HPP_ */
