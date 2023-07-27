#include <string.h>
#include <stdlib.h>

#include "simple_scanner.h"

/**
 * @brief Clasify the mesage into a type amnd move the poiter past the header 
 *
 * @param str 
 * @return ss_types_t 
 */
inline static ss_types_t ss_clasify_and_advance_message(char **str)
{
    char header[18] = {'\0'};

    int cnt = 0;
    char *msg = *str;
    while (msg[cnt] != ':' && msg[cnt] != '\0' && cnt != 17)
    {
        header[cnt] = msg[cnt];
        cnt++;
    }

    header[++cnt] = '\0';

    if (strcmp(header, "LONG TYPE") == 0)
    {
        *str += strlen("LONG TYPE") + 1;
        return SS_LONG_MESSAGE;
    }
    else if (strcmp(header, "SPECIAL TYPE") == 0)
    {
        *str += strlen("SPECIAL TYPE") + 1;
        return SS_SPECIAL_MESSAGE;
    }
    else if (strcmp(header, "NOT SPECIAL TYPE") == 0)
    {
        *str += strlen("NOT SPECIAL TYPE") + 1;
        return SS_NOT_SPECIAL_MESSAGE;
    }

    return SS_MSG_UNKNOWN;
}

/**
 * @brief Move omnto the start of data
 *
 * @param str
 * @return char*
 */
inline static char *ss_getstart_of_data(char *str)
{
    while (*str == ':' || *str == ' ')
    {
        str++;
    }

    return str;
}

/**
 * @brief parse from the start of the message to the next comma
 *
 * @param dest
 * @param msg
 * @return char*
 */
inline static char *ss_parse_next(char *dest, char *msg, char delim)
{
    int cnt = 0;
    while (msg[cnt] != ',' && msg[cnt] != '\0')
    {
        dest[cnt] = msg[cnt];
        cnt++;
    }

    char *ret = &msg[cnt];
    if(msg[cnt] == ',') {
        ret = &msg[cnt+1];
    }

    dest[cnt+1] = '\0';


    return ret;
}

/**
 * @brief Parse a ling message
 * @example "LONG TYPE: 1.87435322456,10.896"
 *
 * @param data
 * @param msg
 * @return true
 * @return false
 */
bool ss_parse_long_mesage(ss_data_t *data, char *msg)
{
    // spaces and colons
    msg = ss_getstart_of_data(msg);

    char latitude[25] = {'\0'};

    msg = ss_parse_next(latitude, msg, ',');
    if (msg == NULL)
    {
        return false;
    }

    data->type = SS_LONG_MESSAGE;
    char *end = NULL;

    data->data.long_data.latitude = strtod(latitude, &end);
    data->data.long_data.longitude = strtod(msg, &end);

    return true;
}

/**
 * @brief Parse message type SPECIAL TYPE
 *
 * @example "SPECIAL TYPE: \"external system one\",2.675421345,-1.675,north,al:25,coosign:none,alert"
 * @param data
 * @param msg
 * @return true
 * @return false
 */
bool ss_parse_special_message(ss_data_t *data, char *msg)
{
    msg = ss_getstart_of_data(msg);

    // The first part of the message is deliniated by the character \", so it's
    // easy to parse
    msg = ss_parse_next(data->data.special_data.name,msg,',');

    char latitude[25] = {'\0'};
    char longetude[25] = {'\0'};

    msg = ss_parse_next(latitude,msg,',');
    if(msg == NULL || msg[0] == '\0') {
        return false;
    }

    msg = ss_parse_next(longetude,msg,',');
    if(msg == NULL || msg[0] == '\0') {
        return false;
    }

    char *end;
    data->data.special_data.latitude = strtod(latitude, &end);
    data->data.special_data.longitude = strtod(longetude, &end);

    // now get special symbols (or whatever they are)
    int special_count = 0;
    while (*msg != '\0')
    {
        char *str = data->data.special_data.special[special_count++];
        msg = ss_parse_next(str, msg, ',');
    }

    data->data.special_data.num_special = special_count;
    data->type = SS_SPECIAL_MESSAGE;
    return true;
}

bool ss_parse_not_special_message(ss_data_t *data, char *msg)
{
    msg = ss_parse_next(data->data.not_special_data.name,msg,',');
    if(msg == NULL || msg[0] == '\0') {
        return false;
    }

    msg = ss_parse_next(data->data.not_special_data.place,msg,',');
    if(msg == NULL || msg[0] == '\0') {
        return false;
    }
    msg = ss_parse_next(data->data.not_special_data.status,msg,','); 

    data->type = SS_NOT_SPECIAL_MESSAGE;

    return true;
}

bool ss_parse_message(ss_data_t *data, char *msg)
{
    ss_types_t type = ss_clasify_and_advance_message(&msg);

    switch (type)
    {
    case SS_LONG_MESSAGE:
        return ss_parse_long_mesage(data, msg);
    case SS_SPECIAL_MESSAGE:
        return ss_parse_special_message(data, msg);
    case SS_NOT_SPECIAL_MESSAGE:
        return ss_parse_not_special_message(data, msg);
    case SS_MSG_UNKNOWN:
    default:
        break;
    }

    return false;
}
