//
// Created by Shahak on 11/06/2017.
//



/**...........................................................................*/
/**---------------------------DEFINES-&-INCLUDES------------------------------*/
/**...........................................................................*/



#ifndef HW3_FACULTY_H
#define HW3_FACULTY_H

#include "mtm_ex3.h"
#include "set.h"
#include "company.h"
#include "escaper.h"


/**...........................................................................*/
/**-----------------------------STRUCTURE-------------------------------------*/
/**...........................................................................*/



/**
 * Faculty will be implemented in this file as a set
 */
typedef struct Faculty_t *Faculty;

/**
 * a type to used to return error codes related to faculties
 */
typedef enum {
    FACULTY_SUCCESS,
    FACULTY_NULL_PARAMETER,
    FACULTY_INVALID_PARAMETER,
    FACULTY_OUT_OF_MEMORY,
    FACULTY_COMPANY_ALREADY_EXISTS,
    FACULTY_COMPANY_DOES_NOT_EXIST,
    FACULTY_ID_DOES_NOT_EXIST
} FacultyErrorCode;


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/


/**
 * receives a faculty name and initializes a faculty with the specified name
 * @param FacultyName - the name of the faculty
 * @param facultyError - enum to get the result of the func:
 *                      FACULTY_SUCCESS - faculty created successfully
 *                      FACULTY_INVALID_PARAMETER - if nameFaculty is invalid
 *                      FACULTY_OUT_OF_MEMORY - Allocation problem occurred
 * @return a pointer to the created faculty if succeeded or NULL if the
 *         the allocation failed or nameFaculty is invalid
 */
Faculty facultyCreate(TechnionFaculty nameFaculty,
                      FacultyErrorCode *facultyError);

/**
 * receives a faculty and destroys it, including all of the internal companies
 * @param element - the faculty to be destroyed
 */
void facultyDestroy(SetElement element);

/**
 * receives a faculty and a company email adds the company to the faculty
 * @param faculty - the faculty to list the room in
 * @param email - the email of the company to be added
 * @return FACULTY_SUCCESS - if the function succeeded
 *  *      FACULTY_NULL_PARAMETER - if a null parameter was received
 *         FACULTY_INVALID_PARAMETER - if invalid email was received
 *         FACULTY_OUT_OF_MEMORY - if an allocation failed
 *         FACULTY_COMPANY_ALREADY_EXISTS - if the company to be created is
 *         already listed
 */
FacultyErrorCode facultyAddCompany(Faculty faculty, char *email);

/**
 * receives a faculty and a company and removes the company from the faculty
 * @param faculty - the faculty to remove the company from
 * @param company - the company to remove from the faculty
 * @return FACULTY_SUCCESS - if the function succeeded
 *         FACULTY_NULL_PARAMETER - if a NULL parameter was received
 *         FACULTY_COMPANY_DOES_NOT_EXIST - if the company to be removed wasn't
 *         found in the faculty
 */
FacultyErrorCode facultyRemoveCompany(Faculty faculty, Company company);

/**
 * receives two faculty elements and returns a comparison result
 * @param element1 - the first faculty element
 * @param element2 - the second faculty element
 * @return 0 if same, positive num if the first is greater, negative otherwise
 *         if one of the elements is NULL returns -1
 */
int facultyCompareElements(SetElement element1, SetElement element2);

/**
 * receives a faculty element and copies it, including all of the elements and
 * the companies set into a new allocated faculty
 * @param src_faculty - the faculty to copy
 * @return a pointer to the new allocated faculty if succeeded or NULL if an
 *         allocation failed
 */
SetElement facultyCopyElement(SetElement src_faculty);

/**
 * receives a faculty and returns it's name
 * @param faculty - the faculty to get the name from
 * @return the faculty name or UNKNOWN if a NULL was received as an input
 */
TechnionFaculty facultyGetName(Faculty faculty);

/**
 * receives a faculty and returns it's earnings
 * @param faculty - the faculty to get the earnings from
 * @return the value of the faculty's earnings or -1 / INVALID_PARAMETER if a
 *         NULL was received as an input
 */
int facultyGetEarnings(Faculty faculty);

/**
 * receives a faculty and it's new earnings and updates the faculty's total
 * earnings
 * @param faculty - the faculty to update the earnings for
 * @param earnings - the new earnings to add to the faculty's total earnings
 */
void facultyIncEarnings(Faculty faculty, int earnings);

/**
 * receives a faculty and an email address and checks through all of the
 * companies in the faculty
 * @param faculty - the faculty to check the companies in
 * @param facultyError - enum to get the result of the func:
 *        FACULTY_SUCCESS - if the function succeeded
 *        FACULTY_NULL_PARAMETER - if a NULL parameter was received
 *        FACULTY_INVALID_PARAMETER - if the email sent in invalid
 *        FACULTY_COMPANY_DOES_NOT_EXIST - if the company to be removed wasn't
 *        found in the faculty
 * @return ptr to the wanted company or NULL if one of the params is NULL or
 * the company is not found in the faculty
 */
Company facultyGetCompanyByEmail(Faculty faculty, char *email,
                                 FacultyErrorCode *facultyError);

/**
 * receives a faculty and a room id and searches for the room id in the faculty
 * @param faculty - the faculty to to search for the room in
 * @param company - ptr to company to get the room's company back
 * @param id - the room id to look for
 * @param facultyError - enum to get the result of the func:
 *        FACULTY_SUCCESS - if the room was found
 *        FACULTY_NULL_PARAMETER - if a NULL parameter was received
 *        FACULTY_INVALID_PARAMETER - if the id id not positive
 *        FACULTY_ID_DOES_NOT_EXIST - if the room id wasn't found in the faculty
 * @return a pointer to the room if found and updates the company ptr to the
 * room's company or NULL if not found in both
 */
Room facultyGetRoomByID(Faculty faculty, Company *company, int id,
                        FacultyErrorCode *facultyError);

/**
 * receives a faculty and an email and check whether there is a company with
 * that email in the faculty
 * @param faculty - the faculty to search in
 * @param email - the email to check
 * @return true if a company was found with same email in the faculty false
 * otherwise
 */
bool isCompanyEmailFaculty(Faculty faculty, char *email);

/**
 * iterates through a faculty to find which room would be the most recommended
 * room for the escaper
 * @param faculty - the faculty to iterate through
 * @param escaper - the escaper to find the room for
 * @param escaperFaculty - the faculty of the escaper
 * @param P_e - the number of people for the reservation
 * @param skill - the skill level of the escaper
 * @param result - a pointer to receive the result through
 * @param faculty_distance - a pointer to receive the faculty distance through
 * @param room_id - a pointer to receive the room id through
 * @return a pointer to the most recommended room in faculty if found or NULL
 *         if not found
 */
Room facultyMostRecommendedRoom(Faculty faculty, Escaper escaper,
                                TechnionFaculty escaperFaculty, int P_e,
                                int skill, int *result, int *faculty_distance,
                                int *room_id, Company *cur_company);





#endif //HW3_FACULTY_H
