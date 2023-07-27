#ifndef SIMPLE_SCANNER_H
#define SIMPLE_SCANNER_H

#include <stdbool.h>

/**
 * @brief Define some mock types for nock messages
 * 
 */
typedef enum ss_types {
    SS_LONG_MESSAGE,
    SS_SPECIAL_MESSAGE,
    SS_NOT_SPECIAL_MESSAGE,
    SS_MSG_UNKNOWN
} ss_types_t;

/**
 * @brief Long data 
 * @example "LONG TYPE: 1.87435322456,10.896"
 * 
 */
typedef struct ss_long_data {
    char name[50];
    double latitude;
    double longitude;
} ss_long_data_t;

/**
 * @brief special data
 * @example "SPECIAL TYPE: \"external system one\",2.675421345,-1.675,north,al:25,coosign:none,alert"
 * 
 */
typedef struct ss_special_data {
    char name[50];
    double latitude;
    double longitude;
    char special[6][15];
    int num_special;
} ss_special_data_t;

/**
 * @brief not special data
 * @example "NOT SPECIAL TYPE: \"external system two\",\"Ormskirk research\",\acive\"""
 */
typedef struct ss_not_special_data {
    char name[50];
    char place[50];
    char status[45];
} ss_not_special_data_t;


typedef struct ss_data {
    ss_types_t type;
    union {
        ss_long_data_t long_data;
        ss_special_data_t special_data;
        ss_not_special_data_t not_special_data;
    } data;
} ss_data_t;


bool ss_parse_message(ss_data_t * data,char * msg);

#endif//SIMPLE_SCANNER_H