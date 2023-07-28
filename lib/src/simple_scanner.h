#ifndef SIMPLE_SCANNER_H
#define SIMPLE_SCANNER_H

#include <stdbool.h>

#define MAX_KEY_SIZE 50
#define MAX_NAME_SIZE 50
#define MAX_SPECIAL_SIZE 15
#define MAX_NUM_SPACIALS 6
#define MAX_PLACE_SIZE 50
#define MAX_STATUS_SIZE 25

/**
 * @brief Define some mock types for nock messages
 * 
 */
typedef enum ss_types {
    SS_MSG_UNKNOWN,
    SS_LONG_MESSAGE,
    SS_SPECIAL_MESSAGE,
    SS_NOT_SPECIAL_MESSAGE,
} ss_types_t;

/**
 * @brief Long data 
 * @example "LONG TYPE: name=lodon,51.5072,0.1276"
 * 
 */
typedef struct ss_long_data {
    char name[MAX_NAME_SIZE];
    double latitude;
    double longitude;
} ss_long_data_t;

/**
 * @brief special data
 * @example "SPECIAL TYPE: \"external system one\",2.675421345,-1.675,north,al:25,coosign:none,alert"
 * 
 */
typedef struct ss_special_data {
    char name[MAX_NAME_SIZE];
    double latitude;
    double longitude;
    char special[MAX_NUM_SPACIALS][MAX_SPECIAL_SIZE];
    int num_special;
} ss_special_data_t;

/**
 * @brief not special data
 * @example "NOT SPECIAL TYPE: \"external system two\",\"Ormskirk research\",\"acive\""
 */
typedef struct ss_not_special_data {
    char name[MAX_NAME_SIZE];
    char place[MAX_PLACE_SIZE];
    char status[MAX_PLACE_SIZE];
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