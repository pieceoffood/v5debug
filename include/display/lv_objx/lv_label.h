/**
 * @Author: yan
 * @Date:   2018-10-08T14:08:09+08:00
 * @Email:  358079046@qq.com
 * @Last modified by:   yan
 * @Last modified time: 2018-10-08T14:53:41+08:00
 */




#ifndef LV_LABEL_H
#define LV_LABEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_conf.h"
#if USE_LV_LABEL != 0

#include "display/lv_core/lv_obj.h"
#include "display/lv_misc/lv_font.h"
#include "display/lv_misc/lv_fonts/lv_symbol_def.h"
#include "display/lv_misc/lv_txt.h"

/*********************
 *      DEFINES
 *********************/
#define LV_LABEL_DOT_NUM 3
#define LV_LABEL_POS_LAST 0xFFFF

/**********************
 *      TYPEDEFS
 **********************/

/*长模式行为。用于'lv_label_ext_t' */
typedef enum {
  LV_LABEL_LONG_EXPAND, /*将对象大小扩展为文本大小*/
  LV_LABEL_LONG_BREAK,  /*保持对象宽度，打破太长的线条和扩展对象高度*/
  LV_LABEL_LONG_SCROLL, /*展开对象大小并滚动文本 parent（移动标签对象）*/
  LV_LABEL_LONG_DOT,    /*K如果文本是， 保持大小并在末尾写点   太长了*/
  LV_LABEL_LONG_ROLL,   /*保持大小并无限滚动文本*/
} lv_label_long_mode_t;

/*标签对齐政策*/
typedef enum {
  LV_LABEL_ALIGN_LEFT,
  LV_LABEL_ALIGN_CENTER,
} lv_label_align_t;

/*标签数据*/
typedef struct {
  /*从'base_obj'继承，所以没有继承的ext。* /  / *分机 祖先*/
  /*此类型的新数据 */
  char *text;                     /*标签文字*/
  lv_label_long_mode_t long_mode; /*确定如何处理长文*/
#if LV_TXT_UTF8 == 0
  char dot_tmp[LV_LABEL_DOT_NUM + 1]; /*存储被替换的角色 by dots（由图书馆处理*/
#else
  char dot_tmp[LV_LABEL_DOT_NUM * 4 + 1]; /*存储的字符 用点代替（由...处理） 图书馆*/
#endif
  uint16_t dot_end; /*点模式下的文本结束位置（由库处理）*/
  uint16_t anim_speed;    /*滚动和滚动动画的速度，以px / sec为单位*/
  lv_point_t offset;      /*文字绘制位置偏移*/
  uint8_t static_txt : 1; /*标记表示文本是静态*/
  uint8_t align : 2;      /*从'lv_label_align_t'中选择对齐类型*/
  uint8_t recolor : 1;    /*启用内联字母重新着色*/
  uint8_t expand : 1;     /*忽略实际宽度（由库使用LV_LABEL_LONG_ROLL*/
  uint8_t no_break : 1;   /*忽略换行符*/
  uint8_t body_draw : 1;  /*绘制背景体*/
} lv_label_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

 /**
  *创建标签对象
  * @param par指向对象的指针，它将是新标签的父级
  * @param复制指向按钮对象的指针，如果不是NULL，则新对象将从中复制
  * @return指向创建按钮的指针
  */
lv_obj_t *lv_label_create(lv_obj_t *par, lv_obj_t *copy);

/*=====================
 * Setter功能
 *====================*/

 /**
 *  为标签设置新文本。将分配内存以存储文本标签。
 * @param标签指向标签对象的指针
 * @param text'\ 0'终止字符串。使用NULL刷新NULL现在的文字。
  */
void lv_label_set_text(lv_obj_t *label, const char *text);

/**
 *从字符数组中为标签设置新文本。阵列不一定是'\ 0'终止。
 *将分配内存以通过标签存储阵列。
 * @param标签指向标签对象的指针
 * @param数组字符数组或NULL来刷新标签
 * @param以'字节'为单位调整'array'的大小
 */
void lv_label_set_array_text(lv_obj_t *label, const char *array, uint16_t size);

/**
*设置静态文本。它不会被标签保存，因此'text'变量标签存在时必须“活着”。
 * @param标签指向标签对象的指针
 * @param文本指向文本。使用当前文本刷新NULL。
 */
void lv_label_set_static_text(lv_obj_t *label, const char *text);

/**
 * 使用较长的文本设置标签的行为，然后设置对象大小
 * @param标签指向标签对象的指针
 * @param long_mode来自'lv_label_long_mode'枚举的新模式。
 */
void lv_label_set_long_mode(lv_obj_t *label, lv_label_long_mode_t long_mode);

/**
 *设置标签的对齐方式（左侧或中间）
 * @param标签指向标签对象的指针
 * @param align'LV_LABEL_ALIGN_LEFT'或'LV_LABEL_ALIGN_LEFT'
 */
void lv_label_set_align(lv_obj_t *label, lv_label_align_t align);

/**
 * 通过内联命令启用重新着色
 * @param标签指向标签对象的指针
 * @param recolor_en true：启用重新加载，false：禁用
 */
void lv_label_set_recolor(lv_obj_t *label, bool recolor_en);
/**
 *设置标签以忽略（或接受）'\ n'上的换行符
 * @param标签指向标签对象的指针
 * @param no_break_en true：忽略换行符，false：在'\ n'上换行
 */

void lv_label_set_no_break(lv_obj_t *label, bool no_break_en);

/**
 *设置标签以绘制（或不绘制）其样式主体中指定的背景
 * @param标签指向标签对象的指针
* @param body_en true：绘制正文; 假：不画身体
 */
void lv_label_set_body_draw(lv_obj_t *label, bool body_en);

/**
 *在LV_LABEL_LONG_ROLL和SCROLL模式下设置标签的动画速度
 * @param标签指向标签对象的指针
 * @param anim_speed以px / sec为单位的动画速度
 */
void lv_label_set_anim_speed(lv_obj_t *label, uint16_t anim_speed);

/**
 *设置标签的样式
 * @param标签指向标签对象的指针
 * @param样式指针指向一个样式
 */
static inline void lv_label_set_style(lv_obj_t *label, lv_style_t *style)
{
  lv_obj_set_style(label, style);
}
/*=====================
 * Getter functions
 *====================*/

 /**
  *获取标签文本
  * @param标签指向标签对象的指针
  * @return标签的文字
  */
char *lv_label_get_text(lv_obj_t *label);

/**
 *获得标签的长模式
 * @param标签指向标签对象的指针
 * @return长模式
 */
lv_label_long_mode_t lv_label_get_long_mode(lv_obj_t *label);

/**
 *获取align属性
 * @param标签指向标签对象的指针
 * @return LV_LABEL_ALIGN_LEFT或LV_LABEL_ALIGN_CENTER
 */
lv_label_align_t lv_label_get_align(lv_obj_t *label);

/**
 *获取重新着色属性
 * @param标签指向标签对象的指针
 * @return true：启用重新着色，false：禁用
 */
bool lv_label_get_recolor(lv_obj_t *label);

/**
 *获取no break属性
 * @param标签指向标签对象的指针
* @return true：no_break_enabled（忽略'\ n'换行符）; false：make line
 *打破'\ n'
 */
bool lv_label_get_no_break(lv_obj_t *label);
/**
 *获取正文绘制属性
 * @param标签指向标签对象的指针
* @return true：画出身体; 假：不画身体
 */
bool lv_label_get_body_draw(lv_obj_t *label);

/**
*以LV_LABEL_LONG_ROLL和SCROLL模式获取标签的动画速度
* @param标签指向标签对象的指针
* @return以px / sec为单位的动画速度
 */
uint16_t lv_label_get_anim_speed(lv_obj_t *label);

/**
*获取字母的相对x和y坐标
* @param标签指向标签对象的指针
* @param索引索引[0 ...文本长度]。表达了性格
*索引，而不是字节索引（UTF-8不同）
* @param pos将结果存储在此处（例如，index = 0给出0; 0坐标）
 */
void lv_label_get_letter_pos(lv_obj_t *label, uint16_t index, lv_point_t *pos);

/**
*获取标签相对点的字母索引
* @param标签指向标签对象
* @param pos指针指向标签上的坐标
* @return'pos_p'点上字母的索引（例如0; 0是0。 信）
*以字符索引表示，而不是字节索引（UTF-8不同）
 */
uint16_t lv_label_get_letter_on(lv_obj_t *label, lv_point_t *pos);

/**
*获取标签对象的样式
* @param标签指向标签对象的指针
* @return指向标签样式的指针
 */
static inline lv_style_t *lv_label_get_style(lv_obj_t *label) {
  return lv_obj_get_style(label);
}

/*=====================
 * Other functions
 *====================*/

/**
*在标签上插入文字。标签文本不能是静态的。
 * @param标签指向标签对象的指针
 * @param pos要插入的字符索引。用字符索引表示而不是 字节索引（UTF-8不同） 0：在第一个char之前。
 * LV_LABEL_POS_LAST：在最后一个char之后。
 * @param txt指向要插入的文本
 */
void lv_label_ins_text(lv_obj_t *label, uint32_t pos, const char *txt);

/**
 * 删除标签中的字符。标签文本不能是静态的。
 * @param标签指向标签对象的指针
 * @param pos要插入的字符索引。用字符索引表示而不是 字节索引（UTF-8不同）
 * 0：在第一个char之前。
 * @param cnt要剪切的字符数
 */
void lv_label_cut_text(lv_obj_t *label, uint32_t pos, uint32_t cnt);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_LABEL*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_LABEL_H*/
