//
// Created by Shahak on 12/06/2017.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "escape_technion.h"

#define MAX_SIZE MAX_LEN+1
#define SPACE ' '
#define TAB '\t'
#define NEW_LINE '\n'
#define EMPTY '\0'
#define COMMENT "#"
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
                                       char *token, char *delim);

/**
 *
 * @param token
 * @param buffer
 * @param delim
 * @return
 */
static MtmErrorCode getRoomCommands(EscapeTechnion escapeTechnion, char *token,
                                   char *delim);

/**
 *
 * @param token
 * @param buffer
 * @param delim
 * @return
 */
static MtmErrorCode getEscaperCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *delim);

/**
 *
 * @param token
 * @param buffer
 * @param delim
 * @return
 */
static MtmErrorCode getReportCommands(EscapeTechnion escapeTechnion,
                                      FILE *output_file, char *token,
                                      char *delim);

static MtmErrorCode getCompanyAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *delim);

static MtmErrorCode getCompanyRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *delim);

static MtmErrorCode getRoomAdd(EscapeTechnion escapeTechnion, char *token,
                               char *delim);

static MtmErrorCode getRoomRemove(EscapeTechnion escapeTechnion, char *token,
                                  char *delim);

static MtmErrorCode getEscaperAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *delim);

static MtmErrorCode getEscaperRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *delim);

static MtmErrorCode getEscaperOrder(EscapeTechnion escapeTechnion, char *token,
                                    char *delim);

static MtmErrorCode getEscaperRecommend(EscapeTechnion escapeTechnion,
                                        char *token, char *delim);


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
    MtmErrorCode parserError;
    while (fgets(buffer, MAX_SIZE, input_file) != NULL) {
        token = strtok(buffer, delim);
        if (NULL == token) {
            continue;
        }
        if (strcmp(token, "company") == 0) {
            printf("you chose company\n"); //TODO
            parserError = getCompanyCommands(escapeTechnion, token, delim);
            mtmPrintErrorMessage(stderr, parserError);
            if (parserError == MTM_OUT_OF_MEMORY) {
                return MTM_OUT_OF_MEMORY;
            }
        } else if (strcmp(token, "room") == 0) {
            printf("you chose room\n"); //TODO
            parserError = getRoomCommands(escapeTechnion, token, delim);
            mtmPrintErrorMessage(stderr, parserError);
            if (parserError == MTM_OUT_OF_MEMORY) {
                return MTM_OUT_OF_MEMORY;
            }
        } else if (strcmp(token, "escaper") == 0) {
            printf("you chose escaper\n"); //TODO
            parserError = getEscaperCommands(escapeTechnion, token, delim);
            mtmPrintErrorMessage(stderr, parserError);
            if (parserError == MTM_OUT_OF_MEMORY) {
                return MTM_OUT_OF_MEMORY;
            }
        } else if (strcmp(token, "report") == 0) {
            printf("you chose report\n"); //TODO
            parserError = getReportCommands(escapeTechnion, output_file, token,
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
                                       char *token, char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        printf(" you chose add\n"); //TODO
        parserError = getCompanyAdd(NULL, token, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        printf(" you chose remove\n"); //TODO
        parserError = getCompanyRemove(escapeTechnion, token, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getRoomCommands(EscapeTechnion escapeTechnion, char *token,
                                    char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        printf(" you chose add\n"); //TODO
        parserError = getRoomAdd(escapeTechnion, token, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        printf(" you chose remove\n"); //TODO
        parserError = getRoomRemove(escapeTechnion, token, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getEscaperCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        printf(" you chose add\n"); //TODO
        parserError = getEscaperAdd(escapeTechnion, token, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        printf(" you chose remove\n"); //TODO
        parserError = getEscaperRemove(escapeTechnion, token, delim);
        return parserError;
    }

    if (strcmp(token, "order") == 0) {
        printf(" you chose order\n"); //TODO
        parserError = getEscaperOrder(escapeTechnion, token, delim);
        return parserError;
    }

    if (strcmp(token, "recommend") == 0) {
        printf(" you chose recommend\n"); //TODO
        parserError = getEscaperRecommend(escapeTechnion, token, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getReportCommands(EscapeTechnion escapeTechnion,
                                      FILE *output_file, char *token,
                                      char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "day") == 0) {
        printf(" you chose day\n"); //TODO
        parserError = escapeTechnionReportDay(escapeTechnion, output_file);
        return parserError;
    }

    if (strcmp(token, "best") == 0) {
        printf(" you chose best\n"); //TODO
        parserError = escapeTechnionReportBest(escapeTechnion, output_file);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getCompanyAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *delim) {
    char *company_email = strtok(NULL, delim);

    char *company_faculty_str = strtok(NULL, delim);
    int faculty_num = atoi(company_faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)faculty_num;

    return escapeTechnionAddCompany(escapeTechnion, nameFaculty, company_email);
}

static MtmErrorCode getCompanyRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *delim) {
    char *company_email = strtok(NULL, delim);

    return escapeTechnionRemoveCompany(escapeTechnion, company_email);
}

static MtmErrorCode getRoomAdd(EscapeTechnion escapeTechnion, char *token,
                               char *delim) {
    char *company_email = strtok(NULL, delim);

    char *room_id_str = strtok(NULL, delim);
    int room_id = atoi(room_id_str);

    char *price_str = strtok(NULL, delim);
    int price = atoi(price_str);

    char *num_ppl_str = strtok(NULL, delim);
    int num_ppl = atoi(num_ppl_str);

    char *working_hrs = strtok(NULL, delim);

    char *difficulty_str = strtok(NULL, delim);
    int difficulty = atoi(difficulty_str);

    return escapeTechnionAddRoom(escapeTechnion, company_email, room_id, price,
                                 num_ppl, working_hrs, difficulty);
}

static MtmErrorCode getRoomRemove(EscapeTechnion escapeTechnion, char *token,
                                  char *delim) {
    char *faculty_str = strtok(NULL, delim);
    int faculty_num = atoi(faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)faculty_num;

    char *room_id_str = strtok(NULL, delim);
    int room_id = atoi(room_id_str);

    return escapeTechnionRemoveRoom(escapeTechnion, room_id, nameFaculty);
}

static MtmErrorCode getEscaperAdd(EscapeTechnion escapeTechnion, char *token,
                                  char *delim) {
    char *escaper_email = strtok(NULL, delim);

    char *escaper_faculty_str = strtok(NULL, delim);
    int escaper_faculty_num = atoi(escaper_faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)escaper_faculty_num;

    char *skill_level_str = strtok(NULL, delim);
    int skill_level = atoi(skill_level_str);

    return escapeTechnionAddEscaper(escapeTechnion, escaper_email, skill_level,
                                    nameFaculty);
}

static MtmErrorCode getEscaperRemove(EscapeTechnion escapeTechnion, char *token,
                                     char *delim) {
    char *escaper_email = strtok(NULL, delim);

    return escapeTechnionRemoveEscaper(escapeTechnion, escaper_email);
}

static MtmErrorCode getEscaperOrder(EscapeTechnion escapeTechnion, char *token,
                                    char *delim) {
    char *escaper_email = strtok(NULL, delim);

    char *room_faculty_str = strtok(NULL, delim);
    int room_faculty_num = atoi(room_faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)room_faculty_num;

    char *room_id_str = strtok(NULL, delim);
    int room_id = atoi(room_id_str);

    char *reservation_time = strtok(NULL, delim);

    char *num_ppl_str = strtok(NULL, delim);
    int num_ppl = atoi(num_ppl_str);

    return escapeTechnionReservationReceived(escapeTechnion, escaper_email,
                                             room_id, nameFaculty,
                                             reservation_time, num_ppl);
}

static MtmErrorCode getEscaperRecommend(EscapeTechnion escapeTechnion,
                                        char *token, char *delim){
    char *escaper_email = strtok(NULL, delim);

    char *num_ppl_str = strtok(NULL, delim);
    int num_ppl = atoi(num_ppl_str);

    return escapeTechnionRecommendedRoom(escaper_email, num_ppl,
                                         escapeTechnion);
}
