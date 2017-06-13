//
// Created by Shahak on 12/06/2017.
//


/**...........................................................................*/
/**---------------------------DEFINES-&-INCLUDES------------------------------*/
/**...........................................................................*/


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


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/


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
 * a while loop determined by EOF to receive commands from the user. translates
 * the commands into the available functions and redirects accordingly
 * @param escapeTechnion - the system to perform the actions on
 * @param input_file - standard input / input file
 * @param output_file - standard output / output file
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_OUT_OF_MEMORY - if an allocation failed
 */
static MtmErrorCode getCommands(EscapeTechnion escapeTechnion, FILE *input_file,
                                FILE *output_file);

/**
 * identifies the relevant command on companies
 * @param escapeTechnion - the system to perform the actions on
 * @param token - a string to hold the relevant word of the given command
 * @param buffer - the original string holding the given command
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getCompanyCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *delim);

/**
 * identifies the relevant command on rooms
 * @param escapeTechnion - the system to perform the actions on
 * @param token - a string to hold the relevant word of the given command
 * @param buffer - the original string holding the given command
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getRoomCommands(EscapeTechnion escapeTechnion, char *token,
                                   char *delim);

/**
 * identifies the relevant command on escapers
 * @param escapeTechnion - the system to perform the actions on
 * @param token - a string to hold the relevant word of the given command
 * @param buffer - the original string holding the given command
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getEscaperCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *delim);

/**
 * identifies the relevant report command
 * @param escapeTechnion - the system to perform the actions on
 * @param output_file - standard output / output file
 * @param token - a string to hold the relevant word of the given command
 * @param buffer - the original string holding the given command
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getReportCommands(EscapeTechnion escapeTechnion,
                                      FILE *output_file, char *token,
                                      char *delim);

/**
 * receives arguments for companyAdd and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getCompanyAdd(EscapeTechnion escapeTechnion, char *delim);

/**
 * receives arguments for companyRemove and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getCompanyRemove(EscapeTechnion escapeTechnion,
                                     char *delim);

/**
 * receives arguments for roomAdd and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getRoomAdd(EscapeTechnion escapeTechnion, char *delim);

/**
 * receives arguments for roomRemove and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getRoomRemove(EscapeTechnion escapeTechnion, char *delim);

/**
 * receives arguments for escaperAdd and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getEscaperAdd(EscapeTechnion escapeTechnion, char *delim);

/**
 * receives arguments for escaperRemove and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getEscaperRemove(EscapeTechnion escapeTechnion,
                                     char *delim);

/**
 * receives arguments for escaperOrder and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getEscaperOrder(EscapeTechnion escapeTechnion, char *delim);

/**
 * receives arguments for escaperRecommend and calls the functions
 * @param escapeTechnion - the system to perform the actions on
 * @param delim - the delimit of the commands (tab,white space etc)
 * @return MtmErrorCode translated from the relevant EscapeTechnionErrorCode
 */
static MtmErrorCode getEscaperRecommend(EscapeTechnion escapeTechnion,

                                        char *delim);
/**
 * receives an EscapeTechnion error code and converts it to the suitable
 * Mtm error code
 * @param error - the original EscapeTechnion error code
 * @return - the output MtmErrorCode
 */
static MtmErrorCode convertEscapeTechnionError(EscapeTechnionErrorCode error);


/**...........................................................................*/
/**----------------------------MAIN-FUNCTION----------------------------------*/
/**...........................................................................*/



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
            parserError = getCompanyCommands(escapeTechnion, token, delim);
            if (parserError != MTM_SUCCESS) {
                mtmPrintErrorMessage(stderr, parserError);
                if (parserError == MTM_OUT_OF_MEMORY){
                    return MTM_OUT_OF_MEMORY;
                }
            }
        } else if (strcmp(token, "room") == 0) {
            parserError = getRoomCommands(escapeTechnion, token, delim);
            if (parserError != MTM_SUCCESS) {
                mtmPrintErrorMessage(stderr, parserError);
                if (parserError == MTM_OUT_OF_MEMORY){
                    return MTM_OUT_OF_MEMORY;
                }
            }
        } else if (strcmp(token, "escaper") == 0) {
            parserError = getEscaperCommands(escapeTechnion, token, delim);
            if (parserError != MTM_SUCCESS) {
                mtmPrintErrorMessage(stderr, parserError);
                if (parserError == MTM_OUT_OF_MEMORY){
                    return MTM_OUT_OF_MEMORY;
                }
            }
        } else if (strcmp(token, "report") == 0) {
            parserError = getReportCommands(escapeTechnion, output_file, token,
                                            delim);
            if (parserError != MTM_SUCCESS) {
                mtmPrintErrorMessage(stderr, parserError);
                if (parserError == MTM_OUT_OF_MEMORY){
                    return MTM_OUT_OF_MEMORY;
                }
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
        parserError = getCompanyAdd(escapeTechnion, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        parserError = getCompanyRemove(escapeTechnion, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getRoomCommands(EscapeTechnion escapeTechnion, char *token,
                                    char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        parserError = getRoomAdd(escapeTechnion, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        parserError = getRoomRemove(escapeTechnion, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getEscaperCommands(EscapeTechnion escapeTechnion,
                                       char *token, char *delim) {
    token = strtok(NULL, delim);
    MtmErrorCode parserError;
    if (strcmp(token, "add") == 0) {
        parserError = getEscaperAdd(escapeTechnion, delim);
        return parserError;
    }

    if (strcmp(token, "remove") == 0) {
        parserError = getEscaperRemove(escapeTechnion, delim);
        return parserError;
    }

    if (strcmp(token, "order") == 0) {
        parserError = getEscaperOrder(escapeTechnion, delim);
        return parserError;
    }

    if (strcmp(token, "recommend") == 0) {
        parserError = getEscaperRecommend(escapeTechnion, delim);
        return parserError;
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getReportCommands(EscapeTechnion escapeTechnion,
                                      FILE *output_file, char *token,
                                      char *delim) {
    token = strtok(NULL, delim);
    EscapeTechnionErrorCode errorCode;
    if (strcmp(token, "day") == 0) {
        errorCode = escapeTechnionReportDay(escapeTechnion, output_file);
        return convertEscapeTechnionError(errorCode);
    }

    if (strcmp(token, "best") == 0) {
        errorCode = escapeTechnionReportBest(escapeTechnion, output_file);
        return convertEscapeTechnionError(errorCode);
    }

    return MTM_SUCCESS;
}

static MtmErrorCode getCompanyAdd(EscapeTechnion escapeTechnion, char *delim) {
     char *company_email = strtok(NULL, delim);

    char *company_faculty_str = strtok(NULL, delim);
    int faculty_num = atoi(company_faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)faculty_num;
    EscapeTechnionErrorCode errorCode = escapeTechnionAddCompany(escapeTechnion,
                                                                 nameFaculty,
                                                                 company_email);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode getCompanyRemove(EscapeTechnion escapeTechnion,
                                     char *delim) {
    char *company_email = strtok(NULL, delim);

    EscapeTechnionErrorCode errorCode;
    errorCode = escapeTechnionRemoveCompany(escapeTechnion, company_email);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode getRoomAdd(EscapeTechnion escapeTechnion, char *delim) {
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

    EscapeTechnionErrorCode errorCode = escapeTechnionAddRoom(escapeTechnion,
                                                              company_email,
                                                              room_id, price,
                                                              num_ppl,
                                                              working_hrs,
                                                              difficulty);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode getRoomRemove(EscapeTechnion escapeTechnion, char *delim) {

    char *faculty_str = strtok(NULL, delim);
    int faculty_num = atoi(faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)faculty_num;

    char *room_id_str = strtok(NULL, delim);
    int room_id = atoi(room_id_str);

    EscapeTechnionErrorCode errorCode = escapeTechnionRemoveRoom(escapeTechnion,
                                                                 room_id,
                                                                 nameFaculty);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode getEscaperAdd(EscapeTechnion escapeTechnion, char *delim) {

    char *escaper_email = strtok(NULL, delim);

    char *escaper_faculty_str = strtok(NULL, delim);
    int escaper_faculty_num = atoi(escaper_faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)escaper_faculty_num;

    char *skill_level_str = strtok(NULL, delim);
    int skill_level = atoi(skill_level_str);

    EscapeTechnionErrorCode errorCode = escapeTechnionAddEscaper(escapeTechnion,
                                                                 escaper_email,
                                                                 skill_level,
                                                                 nameFaculty);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode getEscaperRemove(EscapeTechnion escapeTechnion,
                                     char *delim) {
    char *escaper_email = strtok(NULL, delim);

    EscapeTechnionErrorCode errorCode;
    errorCode = escapeTechnionRemoveEscaper(escapeTechnion, escaper_email);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode getEscaperOrder(EscapeTechnion escapeTechnion, char *delim) {

    char *escaper_email = strtok(NULL, delim);

    char *room_faculty_str = strtok(NULL, delim);
    int room_faculty_num = atoi(room_faculty_str);
    TechnionFaculty nameFaculty = (TechnionFaculty)room_faculty_num;

    char *room_id_str = strtok(NULL, delim);
    int room_id = atoi(room_id_str);

    char *reservation_time = strtok(NULL, delim);

    char *num_ppl_str = strtok(NULL, delim);
    int num_ppl = atoi(num_ppl_str);

    EscapeTechnionErrorCode errorCode;
    errorCode = escapeTechnionReservationReceived(escapeTechnion, escaper_email,
                                                  room_id, nameFaculty,
                                                  reservation_time, num_ppl);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode getEscaperRecommend(EscapeTechnion escapeTechnion,
                                        char *delim){
    char *escaper_email = strtok(NULL, delim);

    char *num_ppl_str = strtok(NULL, delim);
    int num_ppl = atoi(num_ppl_str);

    EscapeTechnionErrorCode errorCode;
    errorCode = escapeTechnionRecommendedRoom(escapeTechnion, num_ppl,
                                              escaper_email);
    return convertEscapeTechnionError(errorCode);
}

static MtmErrorCode convertEscapeTechnionError(EscapeTechnionErrorCode error) {
    if (error == ESCAPE_TECHNION_OUT_OF_MEMORY) {
        return MTM_OUT_OF_MEMORY;
    } else if (error == ESCAPE_TECHNION_NULL_PARAMETER) {
        return MTM_NULL_PARAMETER;
    } else if (error == ESCAPE_TECHNION_INVALID_PARAMETER) {
        return MTM_INVALID_PARAMETER;
    } else if (error == ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS) {
        return MTM_EMAIL_ALREADY_EXISTS;
    } else if (error == ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST) {
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    } else if (error == ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST) {
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    } else if (error == ESCAPE_TECHNION_ID_ALREADY_EXIST) {
        return MTM_ID_ALREADY_EXIST;
    } else if (error == ESCAPE_TECHNION_ID_DOES_NOT_EXIST) {
        return MTM_ID_DOES_NOT_EXIST;
    } else if (error == ESCAPE_TECHNION_CLIENT_IN_ROOM) {
        return MTM_CLIENT_IN_ROOM;
    } else if (error == ESCAPE_TECHNION_ROOM_NOT_AVAILABLE) {
        return MTM_ROOM_NOT_AVAILABLE;
    } else if (error == ESCAPE_TECHNION_RESERVATION_EXISTS) {
        return MTM_RESERVATION_EXISTS;
    } else if (error == ESCAPE_TECHNION_NO_ROOMS_AVAILABLE) {
        return MTM_NO_ROOMS_AVAILABLE;
    }

    return MTM_SUCCESS;
}