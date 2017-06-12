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

#define MAX_SIZE MAX_LEN+1
#define SPACE ' '
#define TAB '\t'
#define NEW_LINE '\n'
#define EMPTY '\0'
#define COMMENT '#'
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

/**
 *
 * @param token
 * @param buffer
 * @param delim
 * @return
 */
static MtmErrorCode getCompanyCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *buffer, char *delim);

/**
 *
 * @param token
 * @param buffer
 * @param delim
 * @return
 */
static MtmErrorCode getRoomCommands(EscapeTechnion escapeTechnion, char *token,
                                    char *buffer, char *delim);

/**
 *
 * @param token
 * @param buffer
 * @param delim
 * @return
 */
static MtmErrorCode getEscaperCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *buffer, char *delim);

/**
 *
 * @param token
 * @param buffer
 * @param delim
 * @return
 */
static MtmErrorCode getReportCommands(EscapeTechnion escapeTechnion,
                                      char *token, char *buffer, char *delim);

static MtmErrorCode getCompanyAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim);

static MtmErrorCode getCompanyRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *buffer, char *delim);

static MtmErrorCode getRoomAdd(EscapeTechnion escapeTechnion, char *token,
                               char *buffer, char *delim);

static MtmErrorCode getRoomRemove(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim);

static MtmErrorCode getEscaperAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim);

static MtmErrorCode getEscaperRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *buffer, char *delim);

static MtmErrorCode getEscaperOrder(EscapeTechnion escapeTechnion, char *token,
                                    char *buffer, char *delim);

static MtmErrorCode getEscaperRecommend(EscapeTechnion escapeTechnion,
                                        char *token, char *buffer, char *delim);

static MtmErrorCode getReportDay(EscapeTechnion escapeTechnion, char *token,
                                 char *buffer, char *delim);

static MtmErrorCode getReportBest(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim);


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

    errorCode = getCommands(escapeTechnion, input_file, output_file);

    fclose(input_file);
    fclose(output_file);
    escapeTechnionDestroy(escapeTechnion);

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
    char buffer[MAX_SIZE] = "";
    char delim[4];
    delim[0] = TAB, delim[1] = SPACE, delim[2] = NEW_LINE, delim[3] = EMPTY;

    char *token = NULL;
    MtmErrorCode parserError = MTM_SUCCESS;
    while (fgets(buffer, MAX_SIZE, input_file) != NULL) {
        token = strtok(buffer, delim);
        if (NULL == token) {
            continue;
        }
        if (strcmp(token, "company") == 0) {
            printf("company\n"); //TODO
            parserError = getCompanyCommands(escapeTechnion, token, buffer,
                                             delim);
            mtmPrintErrorMessage(stderr, parserError);
            if (parserError == MTM_OUT_OF_MEMORY) {
                return MTM_OUT_OF_MEMORY;
            }
        } else if (strcmp(token, "room") == 0) {
            printf("room\n"); //TODO
            parserError = getRoomCommands(escapeTechnion, token, buffer, delim);
            mtmPrintErrorMessage(stderr, parserError);
            if (parserError == MTM_OUT_OF_MEMORY) {
                return MTM_OUT_OF_MEMORY;
            }
        } else if (strcmp(token, "escaper") == 0) {
            printf("escaper\n"); //TODO
            parserError = getEscaperCommands(escapeTechnion, token, buffer,
                                             delim);
            mtmPrintErrorMessage(stderr, parserError);
            if (parserError == MTM_OUT_OF_MEMORY) {
                return MTM_OUT_OF_MEMORY;
            }
        } else if (strcmp(token, "report") == 0) {
            printf("report\n"); //TODO
            parserError = getReportCommands(escapeTechnion, token, buffer,
                                            delim);
            mtmPrintErrorMessage(stderr, parserError);
            if (parserError == MTM_OUT_OF_MEMORY) {
                return MTM_OUT_OF_MEMORY;
            }
        } else if (strcmp(token, COMMENT) == 0) {
            continue;
        }
    }
    return MTM_SUCCESS;
}

static MtmErrorCode getCompanyCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *buffer, char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        parserError = getCompanyAdd(NULL, token, buffer, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        parserError = getCompanyRemove(token, buffer, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getRoomCommands(EscapeTechnion escapeTechnion, char *token,
                                    char *buffer, char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        parserError = getRoomAdd(token, buffer, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        parserError = getRoomRemove(token, buffer, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getEscaperCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *buffer, char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        parserError = getEscaperAdd(token, buffer, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        parserError = getEscaperRemove(token, buffer, delim);
        return parserError;
    }

    if (strcmp(token, "order") == 0) {
        parserError = getEscaperOrder(token, buffer, delim);
        return parserError;
    }

    if (strcmp(token, "recommend") == 0) {
        parserError = getEscaperRecommend(token, buffer, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getReportCommands(EscapeTechnion escapeTechnion,
                                      char *token, char *buffer, char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "day") == 0) {
        parserError = getReportDay(token, buffer, delim);
        return parserError;
    }

    if (strcmp(token, "best") == 0) {
        parserError = getReportBest(token, buffer, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getCompanyAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim) {
    char *company_email = strtok(NULL, delim);
    char *company_faculty = strtok(NULL, delim);
    int faculty_num = atoi(company_faculty);
    TechnionFaculty companyaculty = (TechnionFaculty)faculty_num;
    return escapeTechnionAddCompany(escapeTechnion, companyFaculty,
                                    company_email);
}

static MtmErrorCode getCompanyRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *buffer, char *delim);

static MtmErrorCode getRoomAdd(EscapeTechnion escapeTechnion, char *token,
                               char *buffer, char *delim);

static MtmErrorCode getRoomRemove(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim);

static MtmErrorCode getEscaperAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim);

static MtmErrorCode getEscaperRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *buffer, char *delim);

static MtmErrorCode getEscaperOrder(EscapeTechnion escapeTechnion, char *token,
                                    char *buffer, char *delim);

static MtmErrorCode getEscaperRecommend(EscapeTechnion escapeTechnion,
                                        char *token, char *buffer, char *delim);

static MtmErrorCode getReportDay(EscapeTechnion escapeTechnion, char *token,
                                 char *buffer, char *delim);

static MtmErrorCode getReportBest(EscapeTechnion escapeTechnion, char *token,
                                  char *buffer, char *delim);