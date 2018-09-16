# @Author: 陈昱安
# @Date:   2018-09-16T00:20:57+08:00
# @Email:  31612534@qq.com
# @Last modified by:   陈昱安
# @Last modified time: 2018-09-16T00:38:50+08:00



CSRCS += lv_draw_vbasic.c
CSRCS += lv_draw.c
CSRCS += lv_draw_rbasic.c

DEPPATH += --dep-path lvgl/lv_draw
VPATH += :lvgl/lv_draw

CFLAGS += "-I$(LVGL_DIR)/lvgl/lv_draw"
