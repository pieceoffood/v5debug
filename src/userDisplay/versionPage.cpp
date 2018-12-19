#include "main.hpp"

namespace ncrapi
{
void UserDisplay::creartVersion(lv_obj_t *parent)
{

    createUserObj(OBJ_BTNM_SON, false, "versionPage", parent);

    lv_obj_t *verLab = lv_label_create(displayObj[OBJ_BTNM_SON], nullptr); //创建LAB条
    userDisplay->ostr.clear();                                             //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
    userDisplay->ostr.str("");                                             //2：调用str("")将缓冲区清零，清除脏数据
    userDisplay->ostr << "pros_version:" << PROS_VERSION_STRING << '\n'
                      << "oklib_version:3.3.7" << '\n'
                      << "lvgl_version:" << LVGL_VERSION_INFO << '\n'
                      << "ncr_version:" << NCR_VERSION_STRING << '\n'
                      << "robot_style:" << sysData->robotStyle << '\n'
                      << "user:" << sysData->userName << '\n'
                      << "team_number:" << sysData->teamNum << std::endl;
    std::string temp = userDisplay->ostr.str();
    lv_label_set_text(verLab, temp.c_str());
    lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, closeAction);
}
} // namespace ncrapi