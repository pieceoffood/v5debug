/**
 * @Author: yan
 * @Date:   2018-10-08T10:28:31+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T13:24:32+08:00
 */

#ifndef DISPLAYTEST_HPP_
#define DISPLAYTEST_HPP_
#include "display/lv_conf.h"
#include "display/lvgl.h"
static lv_res_t btn_rel_action(lv_obj_t *btn);
static lv_res_t ddlist_action(lv_obj_t *ddlist);

/**
*在按钮释放时调用
*@ PARAM BTN指向释放按钮的指针
*@返回LVHRESIOK，因为在这个函数中没有删除对象
*/
static lv_res_t btn_rel_action(lv_obj_t *btn)
{
    /*增加按钮宽度*/
    lv_coord_t width = lv_obj_get_width(btn);
    lv_obj_set_width(btn, width + 20);

    return LV_RES_OK;
}
/**
*在下拉列表中选择新选项时调用
*@ PARAM-DDLIST指针指向下拉列表
*@返回LVHRESIOK，因为在这个函数中没有删除对象
*/
static lv_res_t ddlist_action(lv_obj_t *ddlist)
{
    uint16_t opt = lv_ddlist_get_selected(ddlist); /*获取选定选项的ID*/

    lv_obj_t *slider = static_cast<lv_obj_t *>(lv_obj_get_free_ptr(ddlist)); /*获取保存的滑块*/
    lv_slider_set_value(slider, (opt * 100) / 4);                            /*根据选择修改滑块值*/

    return LV_RES_OK;
}

class DisplayTest
{
  private:
  public:
    DisplayTest() {}
    void onlineTest()
    {
    }
    /**
 * 创建一个简单的“你好世界”！标签
 */
    void lv_tutorial_hello_world(void)
    {
        /*在当前活动的屏幕上创建标签*/
        lv_obj_t *label1 = lv_label_create(lv_scr_act(), NULL);
        lv_obj_t *label2 = lv_label_create(lv_scr_act(), NULL);
        lv_obj_t *label3 = lv_label_create(lv_scr_act(), NULL);
        /*修改标签的文本*/
        lv_label_set_text(label1, "Hello world!");
        lv_label_set_text(label2, "Hello V5!");
        lv_label_set_text(label3, "I am Team 8982!");
        /**将标签对齐到中心
    * NULL意味着在父级上对齐（现在是屏幕）
    *结尾处的0, 0表示对齐后的x，y偏移**/
        lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
        lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 20);
        lv_obj_align(label3, NULL, LV_ALIGN_CENTER, 0, 40);
    }

    /**
 * 创建一些对象
 */
    void lv_tutorial_objects(void)
    {

        /*********
      *创建屏幕
      ***********/
        /*创建新的屏幕并加载它
      *可以从任何类型的对象类型创建屏幕
      *现在使用一个页面，它是一个滚动内容的对象*/
        lv_obj_t *scr = lv_page_create(NULL, NULL);
        lv_scr_load(scr);

        /****************
     *添加标题
     ****************/
        lv_obj_t *label = lv_label_create(scr, NULL);       /*第一个参数 (scr) 是父类 */
        lv_label_set_text(label, "please set red or blue"); /*设置标题文本*/
        lv_obj_set_x(label, 50);                            /*设置X轴的位置*/

        /***********************
     * 创建两个按钮对象
     ***********************/
        /*创建按钮*/
        lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);           /*在当前加载的屏幕上创建按钮*/
        lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_rel_action); /*在按钮释放时调用SET函数*/
        lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);   /*标签下方对齐*/

        /*在按钮上创建标签（“标签”变量可以重复使用）*/
        label = lv_label_create(btn1, NULL);
        lv_label_set_text(label, "red");

        /*复制前一个按钮*/
        lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), btn1);      /*第二个参数是要复制的对象。*/
        lv_obj_align(btn2, btn1, LV_ALIGN_OUT_RIGHT_MID, 50, 0); /*对齐PREV.按钮。*/

        /*在按钮上创建标签*/
        label = lv_label_create(btn2, NULL);
        lv_label_set_text(label, "blue");

        /****************
     *添加滑块
     ****************/
        lv_obj_t *slider = lv_slider_create(scr, NULL);                          /*创建一个滑块*/
        lv_obj_set_size(slider, lv_obj_get_width(lv_scr_act()) / 3, LV_DPI / 3); /*设置滑块尺寸*/
        lv_obj_align(slider, btn1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);             /*在第一个按钮下面对齐*/
        lv_slider_set_value(slider, 30);                                         /*设置当前值*/

        /***********************
     * 添加下拉列表
     ************************/
        lv_obj_t *ddlist = lv_ddlist_create(lv_scr_act(), NULL);         /*创建下拉列表*/
        lv_obj_align(ddlist, slider, LV_ALIGN_OUT_RIGHT_TOP, 50, 0);     /*在滑块旁边对齐*/
        lv_obj_set_free_ptr(ddlist, slider);                             /*在ddlist中保存滑块指针(used in 'ddlist_action()')*/
        lv_obj_set_top(ddlist, true);                                    /*点击时启用顶部*/
        lv_ddlist_set_options(ddlist, "None\nLittle\nHalf\nA lot\nAll"); /*设置选项*/
        lv_ddlist_set_action(ddlist, ddlist_action);                     /*选择新选项的SET函数被选中*/

        /****************
     * 创建图表
     ****************/
        lv_obj_t *chart = lv_chart_create(lv_scr_act(), NULL);                        /*创建图表*/
        lv_obj_set_size(chart, lv_obj_get_width(scr) / 2, lv_obj_get_width(scr) / 4); /*设置大小*/
        lv_obj_align(chart, slider, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 50);                 /*在滑块下方对齐*/
        lv_chart_set_series_width(chart, 3);                                          /*设置线宽*/

        /*添加红色数据序列并设置若干点*/
        lv_chart_series_t *dl1 = lv_chart_add_series(chart, LV_COLOR_RED);
        lv_chart_set_next(chart, dl1, 10);
        lv_chart_set_next(chart, dl1, 25);
        lv_chart_set_next(chart, dl1, 45);
        lv_chart_set_next(chart, dl1, 80);

        /*添加蓝色数据序列并设置若干点*/
        lv_chart_series_t *dl2 = lv_chart_add_series(chart, LV_COLOR_MAKE(0x40, 0x70, 0xC0));
        lv_chart_set_next(chart, dl2, 10);
        lv_chart_set_next(chart, dl2, 25);
        lv_chart_set_next(chart, dl2, 45);
        lv_chart_set_next(chart, dl2, 80);
        lv_chart_set_next(chart, dl2, 75);
        lv_chart_set_next(chart, dl2, 505);
    }
    /**
     * 创建对象和样式
     */
    void lv_tutorial_styles(void)
    {

        /****************************************
     * 基本对象+默认样式的标签
     ****************************************/
        /*创建简单对象*/
        lv_obj_t *obj1;
        obj1 = lv_obj_create(lv_scr_act(), NULL);
        lv_obj_set_pos(obj1, 10, 10);

        /*向对象添加标签*/
        lv_obj_t *label;
        label = lv_label_create(obj1, NULL);
        lv_label_set_text(label, "skillAuto");
        lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

        /****************************************
     * 具有“漂亮颜色”样式的基本对象
     ****************************************/
        /*创建简单对象*/
        lv_obj_t *obj2;
        obj2 = lv_obj_create(lv_scr_act(), NULL);
        lv_obj_align(obj2, obj1, LV_ALIGN_OUT_RIGHT_MID, 20, 0); /*与前一个对象对齐*/
                                                                 /* 创建一个新的样式 */
        static lv_style_t style_new2;                            /*样式不能是局部变量*/
        lv_style_copy(&style_new2, &lv_style_pretty);            /*复制内置样式作为起点*/
        style_new2.body.radius = LV_RADIUS_CIRCLE;               /*窗口全圆角*/
        style_new2.body.main_color = LV_COLOR_WHITE;             /*白色主色*/
        style_new2.body.grad_color = LV_COLOR_RED;               /*红色渐变色*/
        style_new2.body.shadow.color = LV_COLOR_SILVER;          /*浅灰色阴影色*/
        style_new2.body.shadow.width = 8;                        /*8像素阴影*/
        style_new2.body.border.width = 2;                        /*2 像素边框宽度*/
        style_new2.text.color = LV_COLOR_BLACK;                  /*黑色文本 */
        style_new2.text.letter_space = 5;                        /*10 像素字母空间*/
        lv_obj_set_style(obj2, &style_new2);                     //  lv_obj_set_style(obj2, &lv_style_pretty);                /*设置内置风格*/
        /* 增加一个标签对象 默认情况下，标签继承父的样式。*/
        label = lv_label_create(obj2, NULL);
        lv_label_set_text(label, "red_side");
        lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

        /*****************************
     * 具有新风格的基本对象
     *****************************/
        /* 创建一个新的样式 */
        static lv_style_t style_new;                   /*样式不能是局部变量*/
        lv_style_copy(&style_new, &lv_style_pretty);   /*复制内置样式作为起点*/
        style_new.body.radius = LV_RADIUS_CIRCLE;      /*窗口全圆角*/
        style_new.body.main_color = LV_COLOR_WHITE;    /*白色主色*/
        style_new.body.grad_color = LV_COLOR_BLUE;     /*蓝色渐变色*/
        style_new.body.shadow.color = LV_COLOR_SILVER; /*浅灰色阴影色*/
        style_new.body.shadow.width = 8;               /*8像素阴影*/
        style_new.body.border.width = 2;               /*2 像素边框宽度*/
        style_new.text.color = LV_COLOR_BLACK;         /*红色文本 */
        style_new.text.letter_space = 5;               /*10 像素字母空间*/

        /*创建基本对象并应用新样式*/
        lv_obj_t *obj3;
        obj3 = lv_obj_create(lv_scr_act(), NULL);
        lv_obj_align(obj3, obj2, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
        lv_obj_set_style(obj3, &style_new);

        /* 向对象添加标签。 默认继承父的样式 */
        label = lv_label_create(obj3, NULL);
        lv_label_set_text(label, "blue_side");
        lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

        /************************
     * 创建样式栏
     ***********************/
        /* 创建条形背景样式*/
        static lv_style_t style_bar_bg;
        lv_style_copy(&style_bar_bg, &lv_style_pretty);
        style_bar_bg.body.radius = 3;
        style_bar_bg.body.empty = 1;                    /*空（未填写）*/
        style_bar_bg.body.border.color = LV_COLOR_GRAY; /*灰色边框颜色*/
        style_bar_bg.body.border.width = 6;             /*2 PX边框宽度*/
        style_bar_bg.body.border.opa = LV_OPA_COVER;

        /* 创建条形指示器样式 */
        static lv_style_t style_bar_indic;
        lv_style_copy(&style_bar_indic, &lv_style_pretty);
        style_bar_indic.body.radius = 3;
        style_bar_indic.body.main_color = LV_COLOR_GRAY; /*白色主色*/
        style_bar_indic.body.grad_color = LV_COLOR_GRAY; /*蓝色渐变色*/
        style_bar_indic.body.border.width = 0;           /*2 PX边框宽度**/
        style_bar_indic.body.padding.hor = 8;
        style_bar_indic.body.padding.ver = 8;

        /*创建一个条并应用样式*/
        lv_obj_t *bar = lv_bar_create(lv_scr_act(), NULL);
        lv_bar_set_style(bar, LV_BAR_STYLE_BG, &style_bar_bg);
        lv_bar_set_style(bar, LV_BAR_STYLE_INDIC, &style_bar_indic);
        lv_bar_set_value(bar, 70);
        lv_obj_set_size(bar, 200, 30);
        lv_obj_align(bar, obj1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
    }
    /**
 * 初始化主题并创建相同的对象，如 "lv_tutorial_objects'
 */
    void lv_tutorial_themes(void)
    {
        /*初始化外星人主题
     * 210：绿色色调值
     * NULL: 使用默认字体 (LV_FONT_DEFAULT)*/
        lv_theme_t *th = lv_theme_alien_init(210, NULL);

        /*设置Surand系统主题*/
        lv_theme_set_current(th);

        /*创建 'lv_tutorial_objects'*/
        lv_tutorial_objects();
    }
    lv_style_t btn3_style;
    /**
 * 将某些对象装箱并使其动画化
 */
    void lv_tutorial_animations(void)
    {
        lv_obj_t *label;

        /*创建一个按钮演示内置动画*/
        lv_obj_t *btn1;
        btn1 = lv_btn_create(lv_scr_act(), NULL);
        lv_obj_set_pos(btn1, 10, 10); /*设置一个位置。这将是动画的目的地*/
        lv_obj_set_size(btn1, 80, 50);

        label = lv_label_create(btn1, NULL);
        lv_label_set_text(label, "skillAuto");

        /* 使用内置函数在按钮中浮动*用2000毫秒延迟动画并在300毫秒中浮动。＊回调*/
        lv_obj_animate(btn1, static_cast<lv_anim_builtin_t>(LV_ANIM_FLOAT_TOP | LV_ANIM_IN), 300, 2000, NULL); //插入从上往下的动画

        /*创建一个按钮来演示用户定义的动画*/
        lv_obj_t *btn2;
        btn2 = lv_btn_create(lv_scr_act(), NULL);
        lv_obj_set_pos(btn2, 10, 80); /*设置一个位置。这将是动画的目的地*/
        lv_obj_set_size(btn2, 80, 50);

        label = lv_label_create(btn2, NULL);
        lv_label_set_text(label, "red_side");

        /*创建动画以连续向左移动按钮*/
        lv_anim_t a;
        a.var = btn2;
        a.start = lv_obj_get_x(btn2);
        a.end = a.start + (100);
        a.fp = (lv_anim_fp_t)lv_obj_set_x;
        a.path = lv_anim_path_linear;
        a.end_cb = NULL;
        a.act_time = -1000;   /*设置延迟的负数*/
        a.time = 400;         /*动画400毫秒*/
        a.playback = 1;       /*当动画准备好的时候也要向后移动*/
        a.playback_pause = 0; /*回放前等待*/
        a.repeat = 1;         /*重复动画*/
        a.repeat_pause = 500; /*重复前等待*/
        lv_anim_create(&a);

        /*创建一个按钮演示样式动画*/
        lv_obj_t *btn3;
        btn3 = lv_btn_create(lv_scr_act(), NULL);
        lv_obj_set_pos(btn3, 10, 150); /*设置一个位置。这将是动画的目的地*/
        lv_obj_set_size(btn3, 80, 50);

        label = lv_label_create(btn3, NULL);
        lv_label_set_text(label, "blue_side");

        /*为按钮创建一个独特的样式*/
        lv_style_copy(&btn3_style, lv_btn_get_style(btn3, LV_BTN_STYLE_REL));
        lv_btn_set_style(btn3, static_cast<lv_btn_style_t>(LV_BTN_STATE_REL), &btn3_style);
        /*使新风格焕然一新*/
        lv_style_anim_t sa;
        sa.style_anim = &btn3_style;        /*这个样式将被动画化*/
        sa.style_start = &lv_style_btn_rel; /*风格之初 (也可以是'style_anim')*/
        sa.style_end = &lv_style_pretty;    /*风格和(也可以是 'style_anim' as)*/
        sa.act_time = -500;                 /*这些参数与普通动画相同。*/
        sa.time = 1000;
        sa.playback = 1;
        sa.playback_pause = 500;
        sa.repeat = 1;
        sa.repeat_pause = 500;
        sa.end_cb = NULL;
        lv_style_anim_create(&sa);
    }

    /**
 * 创建一些对象动画
 */
    void lv_tutorial_responsive(void)
    {
        lv_obj_t *label;

        /*LV_DPI*/
        lv_obj_t *btn1;
        btn1 = lv_btn_create(lv_scr_act(), NULL);
        lv_obj_set_pos(btn1, LV_DPI / 10, LV_DPI / 10); /*使用LV_DPI 来设置位置*/
        lv_obj_set_size(btn1, LV_DPI, LV_DPI / 2);      /*使用 LVDOI 来设置尺寸*/

        label = lv_label_create(btn1, NULL);
        lv_label_set_text(label, "LV_DPI");

        /*排列*/
        lv_obj_t *btn2;
        btn2 = lv_btn_create(lv_scr_act(), btn1);
        lv_obj_align(btn2, btn1, LV_ALIGN_OUT_RIGHT_MID, LV_DPI / 4, 0);

        label = lv_label_create(btn2, NULL);
        lv_label_set_text(label, "Align");

        /*自动拟合*/
        lv_obj_t *btn3;
        btn3 = lv_btn_create(lv_scr_act(), btn1);
        lv_btn_set_fit(btn3, true, true);

        label = lv_label_create(btn3, NULL);
        lv_label_set_text(label, "Fit");

        lv_obj_align(btn3, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 4); /*由于标签已经调整大小，对齐*/

        /*布局*/
        lv_obj_t *btn4;
        btn4 = lv_btn_create(lv_scr_act(), btn1);
        lv_btn_set_fit(btn4, true, true);         /*也使用自动拟合*/
        lv_btn_set_layout(btn4, LV_LAYOUT_COL_R); /*右对齐列布局*/

        label = lv_label_create(btn4, NULL);
        lv_label_set_text(label, "First");

        label = lv_label_create(btn4, NULL);
        lv_label_set_text(label, "Second");

        label = lv_label_create(btn4, NULL);
        lv_label_set_text(label, "Third");

        lv_obj_align(btn4, btn2, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 4); /*由于标签已经调整大小，对齐*/
    }
};
#endif /* end of include guard: DISPLAYTEST_HPP_ */
