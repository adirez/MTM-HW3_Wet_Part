//
// Created by Shahak on 06/06/2017.
//

#ifndef HW3_ESCAPER_H
#define HW3_ESCAPER_H

#include "mtm_ex3.h"
#include "set.h"

/**
 * Escaper will be implemented in this file as a set
 */
typedef struct Escaper_t *Escaper;

/**
 * a type used to return error codes related to Escaper
 */
typedef enum {
    ESCAPER_SUCCESS,
    ESCAPER_NULL_PARAMETER,
    ESCAPER_INVALID_PARAMETER,
    ESCAPER_OUT_OF_MEMORY
} EscaperErrorCode;

/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/


/**
 * creates a new escaper client according to the relevant input parameters
 * @param email - the email of the escaper to be created
 * @param Faculty - the Faculty the escaper is listed in
 * @param skill_level - the expertise of the escaper
 * @param escaperError - enum to get the result of the func:
 *                    ESCAPER_SUCCESS - escaper created successfully
 *                    ESCAPER_NULL_PARAMETER - email is NULL
 *                    ESCAPER_INVALID_PARAMETER - one of the params are Invalid
 *                    ESCAPER_OUT_OF_MEMORY - Allocation problem occurred
 * @return Escaper - ptr to the new escaper if everything went well
 *         NULL - if the allocation was not successful or if email is NULL
 */
Escaper escaperCreate(char *email, TechnionFaculty escaperFaculty,
                      int skill_level, EscaperErrorCode *escaperError);

/**
 * destroys an escaper and and releases all relevant allocated memory.
 * @param element - a pointer to the relevant escaper to be destroyed
 */
void escaperDestroy(SetElement element);

/**
 * a comparison of two escapers by their email
 * @param element1 - the first escaper
 * @param element2 - the second escaper
 * @return 0 if same, positive num if the first is greater, negative otherwise
 */
int escaperCompareElements(SetElement element1, SetElement element2);

/**
 * receives a source escaper element and copies it's data into a newly created
 * escaper element
 * @param src_escaper - the source escaper that needs to be copied
 * @return pointer to the new allocated escaper or NULL if the allocation failed
 */
SetElement escaperCopyElement(SetElement src_escaper);

/**
 * receives an escaper and returns the email listed in his profile
 * @param escaper - the ptr to the escaper
 * @param escaperError - enum to get the result of the func:
 *                    ESCAPER_SUCCESS - email returned successfully
 *                    ESCAPER_NULL_PARAMETER - escaper is NULL
 *                    ESCAPER_OUT_OF_MEMORY - Allocation problem occurred
 * @return a pointer to the char* if the allocation worked and NULL if failed
 */
char *escaperGetEmail(Escaper escaper, EscaperErrorCode *escaperError);

/**
 * receives an escaper and returns the faculty he's listed in
 * @param escaper - the ptr to the escaper
 * @return the faculty of the escaper or UNKNOWN if an error was found
 */
TechnionFaculty escaperGetNameFaculty(Escaper escaper);

/**
 * receives an escaper and returns his skill level
 * @param escaper - the ptr to the escaper
 * @return the skill level of the escaper or -1 if received NULL param
 */
int escaperGetSkillLevel(Escaper escaper);

/**
 * receives an escaper and checks if his email is equal to an email received
 * through the parameters
 * @param escaper - the escaper to be checked
 * @param email - the email to compare
 * @return true - if the escaper's email equals 'email'
 *         false - if the emails are different
 */
bool isEscaperEmailEqual(Escaper escaper, char *email);

#endif //HW3_ESCAPER_H
