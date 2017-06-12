//
// Created by Shahak on 12/06/2017.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "escape_technion.h"

#define SPACE ' '
#define TAB '   '
#define COMMENT '#'
#define PROG_NAME ""
#define I_FLAG "-i"
#define O_FLAG "-o"

/**
 * determines the input method and the output method by the command line input
 * @param input - a string to hold the input file name (optional)
 * @param output - a string to hold the output file name (optional)
 * @param argc - the number of arguments received from the user
 * @param argv - a strings array containing the arguments from the user's input
 * @return MTM_SUCCESS - if the command was valid
 *         MTM_INVALID_COMMAND_LINE_PARAMETERS - if the command was invalid
 *         MTM_OUT_OF_MEMORY - if an allocation failed
 */
static MtmErrorCode getInputOutputMethod(char **input_type, char **output_type,
                                         int argc, const char *argv[]);

/**
 * accesses the input / output channels. set to std I/O by default, and in case
 * of need opens the relevant I/O files
 * @param input_file - a type to hold the input channel
 * @param output_file - a type to hold the output channel
 * @param input_type - a type to hold the input file name if exists
 * @param output_type - a type to hold the output file name if exists
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_CANNOT_OPEN_FILE - if there was a problem reading a file
 */
static MtmErrorCode accessInputOuputMethod(FILE **input_file,FILE **output_file,
                                           char *input_type, char *output_type);

/**
 *
 * @param escapeTechnion
 * @param input_file
 * @param output_file
 * @return
 */
static MtmErrorCode getCommands(EscapeTechnion escapeTechnion, FILE *input_file,
                                FILE *output_file);

int main(int argc, const char *argv[]) {

    char *input_type = NULL;
    char *output_type = NULL;
    FILE *input_file = stdin;
    FILE *output_file = stdout;
    MtmErrorCode errorCode = getInputOutputMethod(&input_type, &output_type,
                                                  argc, argv);
    if (errorCode != MTM_SUCCESS) {
        mtmPrintErrorMessage(stderr, errorCode);
        return 0;
    }

    errorCode = accessInputOuputMethod(&input_file, &output_file,
                                       input_type, output_type);
    if (errorCode != MTM_SUCCESS) {
        mtmPrintErrorMessage(stderr, errorCode);
        return 0;
    }


    EscapeTechnion escapeTechnion = escapeTechnionCreate();
    if (NULL == escapeTechnion) {
        errorCode = MTM_OUT_OF_MEMORY;
        mtmPrintErrorMessage(stderr, errorCode);
        fclose(input_file);
        fclose(output_file);
        return 0;
    }



    return 0;
}


/**...........................................................................*/
/**--------------------------STATIC-FUNCTIONS---------------------------------*/
/**...........................................................................*/


static MtmErrorCode getInputOutputMethod(char **input_type, char **output_type,
                                         int argc, const char *argv[]) {
    if (argc == 2 || argc == 4 || argc > 5) {
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    }
    bool is_i_flag = false, is_o_flag = false;
    int idx = 1;
    while (argv[idx]) {
        if (strcmp(argv[idx], I_FLAG) == 0) {
            if (is_i_flag) {
                if (is_o_flag) {
                    free(*output_type);
                }
                return MTM_INVALID_COMMAND_LINE_PARAMETERS;
            }
            is_i_flag = true;
            idx++;
            *input_type = malloc(strlen(argv[idx]) * sizeof(char) + 1);
            if (NULL == *input_type) {
                if (is_o_flag) {
                    free(*output_type);
                }
                return MTM_OUT_OF_MEMORY;
            }
            strcpy(*input_type, argv[idx]);
            idx++;
            continue;
        } else if (strcmp(argv[idx], O_FLAG) == 0) {
            if (is_o_flag) {
                if (is_i_flag) {
                    free(*input_type);
                }
                return MTM_INVALID_COMMAND_LINE_PARAMETERS;
            }
            is_o_flag = true;
            idx++;
            *output_type = malloc(strlen(argv[idx]) * sizeof(char) + 1);
            if (NULL == *output_type) {
                if (is_i_flag) {
                    free(*input_type);
                }
                return MTM_OUT_OF_MEMORY;
            }
            strcpy(*output_type, argv[idx]);
            idx++;
            continue;
        }
    }
    return MTM_SUCCESS;
}

static MtmErrorCode accessInputOuputMethod(FILE **input_file,FILE **output_file,
                                           char *input_type, char *output_type){

    if (NULL != input_type) {
        *input_file = fopen(input_type, "r");
        free(input_type);

        if (NULL == *input_file) {
            free(output_type);
            return MTM_CANNOT_OPEN_FILE;
        }
    }

    if (NULL != output_type) {
        *output_file = fopen(output_type, "w");
        free(output_type);

        if (NULL == *output_file) {
            fclose(*input_file);
            return MTM_CANNOT_OPEN_FILE;
        }
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getCommands(EscapeTechnion escapeTechnion, FILE *input_file,
                                FILE *output_file) {
    char buffer[MAX_LEN + 1] = "";

}


