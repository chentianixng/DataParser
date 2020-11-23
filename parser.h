#ifndef _PARSER_H_
#define _PARSER_H_

#include "queue.h"

typedef enum
{
    RESULT_FALSE,
    RESULT_TRUE
} ParserResult;

typedef struct DataParser
{
    Queue *parser_queue;
    Node *resule_pointer;
    uint8 *data_header;
    int header_size;
    uint8 *data_footer;
    int footer_size;
    int result_size;
    ParserResult parserResult;
} DataParser;

/* 初始化一个解析器 */
DataParser *parser_init(uint8_t *_data_header, int _header_size, uint8_t *_data_footer, int _foot_size, int _data_frame_size);
/* 将数据添加到解析器中进行解析 */
ParserResult parser_put_data(DataParser *_parser, uint8_t _data);
/* 解析成功后从解析器中取出解析结果 */
int parser_get_data(DataParser *_parser, int _index);
/* 重置解析器 */
void parser_reset(DataParser *_parser);
/* 释放解析器 */
void parser_release(DataParser *_parser);

#endif
