//
// Created by Shahak on 11/06/2017.
//

#ifndef HW3_FACULTY_H
#define HW3_FACULTY_H

#include "mtm_ex3.h"
#include "set.h"
#include "company.h"

/**
 * Faculty will be implemented in this file as a set
 */
typedef struct Faculty_t *Faculty;

/**
 * a type to used to return error codes related to faculties
 */
typedef enum {
    FACULTY_SUCCESS,
    FACULTY_COMPANY_ALREADY_EXISTS,
    FACULTY_COMPANY_DOES_NOT_EXIST,
    FACULTY_INVALID_PARAMETER,
    FACULTY_OUT_OF_MEMORY,
} FacultyErrorCode;


/**
 * receives a faculty name and initializes a faculty with the specified name
 * @param FacultyName - the name of the faculty
 * @return a pointer to the created faculty if succeeded or NULL if the
 *         the allocation failed
 */
Faculty facultyCreate(TechnionFaculty nameFaculty);

/**
 * receives a faculty and destroys it, including all of the internal companies
 * @param faculty - the faculty to be destroyed
 */
void facultyDestroy(SetElement faculty);

/**
 * receives a faculty and a company email adds the company to the faculty
 * @param faculty - the faculty to list the room in
 * @param email - the email of the company to be added
 * @return FACULTY_SUCCESS - if the function succeeded
 *         FACULTY_INVALID_PARAMETER - if a null parameter was received
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
 *         FACULTY_INVALID_PARAMETER - if a NULL was received as an input
 *         FACULTY_COMPANY_DOES_NOT_EXIST - if the company to be removed wasn't
 *         found in the faculty
 */
FacultyErrorCode facultyRemoveCompany(Faculty faculty, Company company);

/**
 * receives two faculty elements and returns a comparison result
 * @param faculty_1 - the first faculty element
 * @param faculty_2 - the second faculty element
 * @return 0 - if the faculties are identical (by name)
 *         1 - if the faculties are different (by name)
 *         -1 / INVALID_PARAMETER - if a NULL was received as an input
 */
int facultyCompareElements(SetElement faculty_1, SetElement faculty_2);

/**
 * receives a faculty element and copies it, including all of the elements and
 * the companies set into a new allocated faculty
 * @param src_faculty - the faculty to copy
 * @return a pointer to the new allocated faculty if succeeded or NULL if an
 *         allocation failed
 */
SetElement facultyCopyElement(SetElement src_faculty);

/**
 * receives a faculty and returns the value of the minimum room id within the
 * faculty
 * @param faculty - the faculty to iterate through
 * @return the value of the minimum room ID or -1 / INVALID_PARAMETER if no room
 *         was found in the faculty
 */
int facultyGetMinRoomID(Faculty faculty);

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
 * @param email - the email address to look for in the companies
 * @return true - if the email address was found
 *         false - if the email address wasn't found
 */
Company facultyGetCompanyByEmail(Faculty faculty, char *email);








#endif //HW3_FACULTY_H
