/**
 * @file lv_text.h
 *
 */

#ifndef LV_TXT_H
#define LV_TXT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_area.h"
#include "lv_font.h"
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#define LV_TXT_COLOR_CMD "#"

    /**********************
 *      TYPEDEFS
 **********************/
    typedef enum
    {
        LV_TXT_FLAG_NONE = 0x00,
        LV_TXT_FLAG_RECOLOR = 0x01,  /*启用recolor命令解析*/
        LV_TXT_FLAG_EXPAND = 0x02,   /*忽略宽度（由库使用）*/
        LV_TXT_FLAG_NO_BREAK = 0x04, /*忽略换行符（由库使用）*/
        LV_TXT_FLAG_CENTER = 0x08,   /*将文本对齐到中间*/
    } lv_txt_flag_t;

    typedef enum
    {
        LV_TXT_CMD_STATE_WAIT, /*等待命令*/
        LV_TXT_CMD_STATE_PAR,  /*处理参数*/
        LV_TXT_CMD_STATE_IN,   /*处理命令*/
    } lv_txt_cmd_state_t;

    /**********************
 * GLOBAL PROTOTYPES
 **********************/

    /**
    *获取文本大小
    * @param size_res指向'point_t'变量的指针，用于存储结果
    * @param文本指向文本
    * @param font pinter指向文本的字体
    * @param letter_space文字空格
    * @param line_space文本的行间距
    * @param标记来自'txt_flag_t'枚举的文本的设置
    * @param max_width max with the text（打破符合此大小的行）设置CORD_MAX以避免换行
 */
    void lv_txt_get_size(lv_point_t *size_res, const char *text, const lv_font_t *font,
                         lv_coord_t letter_space, lv_coord_t line_space, lv_coord_t max_width, lv_txt_flag_t flag);

    /**
    *获取下一行文字。检查线路长度和断开字符。
     * @param txt'\ 0'终止字符串
     * @param font_p指向字体的指针
     * @param letter_space字母空间
     * @param max_width max with the text（打破符合此大小的行）设置CORD_MAX以避免换行
     * @param标记来自'txt_flag_t'枚举的文本的设置
     * @return新行的第一个字符的索引
 */
    uint16_t lv_txt_get_next_line(const char *txt, const lv_font_t *font_p,
                                  lv_coord_t letter_space, lv_coord_t max_l, lv_txt_flag_t flag);

    /**
    *给出具有给定字体的文本的长度
    * @param txt'\ 0'终止字符串
    * @param char_num'txt'中的字符数
    * @param font_p指向字体的指针
    * @param letter_space字母空间
    * @param标记来自'txt_flag_t'枚举的文本的设置
    * @return char_num长文本的长度
 */
    lv_coord_t lv_txt_get_width(const char *txt, uint16_t char_num,
                                const lv_font_t *font_p, lv_coord_t letter_space, lv_txt_flag_t flag);

    /**
    *检查字符串中的下一个字符，并确定te字符是否是命令的一部分
    * @param状态指向txt_cmd_state_t变量的指针，该变量存储命令处理的当前状态
    * @param c当前字符
    * @return true：该字符是命令的一部分，不应该写入，false：应该写下这个角色
 */
    bool lv_txt_is_cmd(lv_txt_cmd_state_t *state, uint32_t c);

    /**
    *将字符串插入另一个字符串
    * @param txt_buf原始文本（必须足够大才能显示结果文本）
    * @param pos位置插入（0：原始文本之前，1：第一个char之后等）
    * @param ins_txt要插入的文本
 */
    void lv_txt_ins(char *txt_buf, uint32_t pos, const char *ins_txt);

    /**
    *删除字符串的一部分
    * @param txt字符串进行修改
    * @param pos位置开始删除（0：第一个char之前，1：第一个char之后等）
    * @param len要删除的字符数
 */
    void lv_txt_cut(char *txt, uint32_t pos, uint32_t len);

    /**
    *给出UTF-8编码字符的大小
    * @param c UTF-8字符开始的字符
   * @return UTF-8字符长度（1,2,3或4）。O代码无效
 */
    uint8_t lv_txt_utf8_size(uint8_t c);

    /**
    *将Unicode字母转换为UTF-8。
    * @param letter_uni是一封Unicode字母
    * @return Little Endian中的UTF-8编码字符与C字符兼容（例如'Á'，'Ű'）

 */
    uint32_t lv_txt_unicode_to_utf8(uint32_t letter_uni);

    /**
    *从字符串中解码UTF-8字符。
    * @param txt指向'\ 0'终止字符串
    * @param我在'txt'开始索引从哪里开始。通话结束后，它将指向'txt'中的下一个UTF-8字符。NULL使用txt [0]作为索引
    * @return解码的Unicode字符或无效的UTF-8代码为0
 */
    uint32_t lv_txt_utf8_next(const char *txt, uint32_t *i);

    /**
    *从字符串中获取以前的UTF-8字符。
    * @param txt指向'\ 0'终止字符串
   * @param i_start索引'txt'从哪里开始。通话结束后，它将指向'txt'中的下一个UTF-8字符。
    * @return解码的Unicode字符或无效的UTF-8代码为0
 */
    uint32_t lv_txt_utf8_prev(const char *txt, uint32_t *i_start);

    /**
    *将字母索引（以UTF-8文本格式）转换为字节索引。
    *例如在“AÁRT”中，'R'的索引是2但是从字节3开始，因为'Á'是2个字节长
    * @param txt'\ 0'终止UTF-8字符串
    * @param utf8_id字母索引
    *'utf8_id'th字母的@return字节索引
 */
    uint32_t txt_utf8_get_byte_id(const char *txt, uint32_t utf8_id);

    /**
    *将字节索引（以UTF-8文本格式）转换为字符索引。
    *例如在“AÁRT”中，'R'的索引是2但是从字节3开始，因为'Á'是2个字节长
    * @param txt'\ 0'终止UTF-8字符串
    * @param byte_id字节索引
    * @return'byte_id'th位置字母的字符索引
 */
    uint32_t lv_txt_utf8_get_char_id(const char *txt, uint32_t byte_id);

    /**
    *获取字符串中的字符数（和非字节数）。如果启用，则使用UTF-8对其进行解码。
     *例如：“ÁBC”是3个字符（但是4个字节）
     * @param txt'\ 0'终止字符串
     * @return字符数
 */
    uint32_t lv_txt_get_length(const char *txt);

    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*USE_TXT*/
