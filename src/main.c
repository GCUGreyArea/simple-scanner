#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>
#include <errno.h>

#include <libSimpleScanner.h>


inline static void print_long_data(ss_data_t* data) {
    if(data->type != SS_LONG_MESSAGE) {
        fprintf(stderr, "ERRROR: Wrong message type");
        abort();
    }

    printf("LONG MESSAGE\n");
    printf("\tlatitude: %f\n",data->data.long_data.latitude);
    printf("\tlongetude: %f\n",data->data.long_data.longitude);
}


inline static void print_special_data(ss_data_t*data) {
    if(data->type != SS_SPECIAL_MESSAGE) {
        fprintf(stderr, "ERRROR: Wrong message type");
        abort();
    }

    printf("SPECIAL MESSAGE\n");
    printf("\tname: %s\n",data->data.special_data.name);
    printf("\tlatitude: %f\n",data->data.special_data.latitude);
    printf("\tlongetude: %f\n",data->data.special_data.longitude);

    for(int i=0;i<data->data.special_data.num_special;i++) {
        printf("\tspecial data [%d]: %s\n",i, data->data.special_data.special[i]);
    }

}


inline static void print_not_special_data(ss_data_t*data) {

}


int main(int argc, const char **argv)
{
    if(argc == 1) {
        printf("please supply a message to parse\n");
        return 1;
    }

    char * msg = (char*) argv[1];

    ss_data_t data = {0};

    if(ss_parse_message(&data,msg)) {
        switch(data.type) {
            case SS_LONG_MESSAGE:
                print_long_data(&data);
                break;
            case SS_SPECIAL_MESSAGE:
                print_special_data(&data);
                break;
            case SS_NOT_SPECIAL_MESSAGE:
                print_not_special_data(&data);
                break;
            case SS_MSG_UNKNOWN:
                printf("Unknonw message type\n");
            default:
                break;

        }

    }
    return 0;
}