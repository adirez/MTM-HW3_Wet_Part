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


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/


/**
 * creates a new escaper client according to the relevant input parameters
 * @param email - the email of the escaper to be created
 * @param Faculty - the Faculty the escaper is listed in
 * @param skill_level - the expertise of the escaper
 * @return Escaper - ptr to the new escaper if everything went well
 *         NULL - if the allocation was not successful or if email is NULL
 */
Escaper escaperCreate(char *email, TechnionFaculty escaperFaculty,
                      int skill_level);

/**
 * destroys an escaper and and releases all relevant allocated memory.
 * @param escaper - a pointer to the relevant escaper to be destroyed
 */
void escaperDestroy(Escaper escaper);

/**
 * a comparison of two escapers by email
 * @param escaper1 - the first escaper
 * @param escaper2 - the second escaper
 * @return -1 - INVALID_PARAMETER - if one of the params are NULL
 * @return 1 - emails are different
 * @return 0 - emails are equal
 */
int escaperCompareElements(SetElement escaper_1, SetElement escaper_2);

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
 * @return a pointer to the char* if the allocation worked and NULL if failed
 */
char *escaperGetEmail(Escaper escaper);

/**
 * receives an escaper and returns the faculty he's listed in
 * @param escaper - the ptr to the escaper
 * @return the faculty of the escaper or UNKNOWN if an error was found
 */
TechnionFaculty escaperGetFaculty(Escaper escaper);

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
