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
    lv_obj_t *label; //标题栏

  public:
    UserDisplay()
    {
        label = lv_label_create(lv_scr_act(), NULL);
        lv_obj_set_x(label, 10);
        lv_label_set_text(label, "display Initialization...");
    }
    void setLabel(const char *text)
    {
        lv_label_set_text(label, text);
    }
};
