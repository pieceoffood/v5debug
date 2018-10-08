/**
 * @Author: yan
 * @Date:   2018-10-08T14:23:01+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T15:54:22+08:00
 */
#include "display/lv_conf.h"
#include "display/lvgl.h"
class UserDisplay
{
  private:
    lv_obj_t *_label; //标题栏
    lv_obj_t *loopTimeLab; //循环标题栏
    char _buf_long[256];
    int _maxLoopTime=0;
    int _minLoopTime=20;
  public:

    UserDisplay()
    {
        _label = lv_label_create(lv_scr_act(), NULL);
        lv_obj_set_x(_label, 10);
        lv_label_set_text(_label, "display Initialization...");
        loopTimeLab=lv_label_create(lv_scr_act(),NULL);
        lv_obj_align(loopTimeLab, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    }
    void initialize()
    {
      lv_label_set_text(_label, "robot Initialization...");
      lv_obj_set_hidden(loopTimeLab,1);

    }

    void disabled()
    {
        lv_label_set_text(_label, "competition disabled...");
        lv_obj_set_hidden(loopTimeLab,1);
    }

    void competition_initialize()
    {
      lv_label_set_text(_label, "competition Initialization...");
      lv_obj_set_hidden(loopTimeLab,1);
    }
    void autonomous()
    {
      lv_label_set_text(_label, "robot autonomousing...");
      lv_obj_set_hidden(loopTimeLab,1);
    }

    void opcontrol()
    {
      lv_label_set_text(_label, "robot opcontroling...");
      lv_obj_set_hidden(loopTimeLab,0);
    }
    void loopTime(const int loopTime)
    {
      if(loopTime>_maxLoopTime)
        _maxLoopTime=loopTime;
      if(loopTime<_minLoopTime)
        _minLoopTime=loopTime;
      sprintf(_buf_long, "loop:%d max:%d min:%d\n", loopTime,_maxLoopTime,_minLoopTime);
      lv_label_set_text(loopTimeLab, _buf_long);
    }
    void startPage()
    {

    }
};
