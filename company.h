//
// Created by Shahak on 06/06/2017.
//

#ifndef ESCAPETECHNION_COMPANY_H
#define ESCAPETECHNION_COMPANY_H

#include "mtm_ex3.h"
#include "set.h"
#include "room.h"

/**
 * Company will be implemented in this file as a set
 */
typedef struct Company_t *Company;

/**
 * a type used to return error codes related to Company
 */
typedef enum {
    COMPANY_SUCCESS,
    COMPANY_NULL_PARAMETER,
    COMPANY_INVALID_PARAMETER,
    COMPANY_OUT_OF_MEMORY,
    COMPANY_ROOM_ALREADY_EXISTS,
    COMPANY_ROOM_DOES_NOT_EXIST
} CompanyErrorCode;

/**
 * creates a new company according to the relevant input parameters and returns
 * the relevant result code.
 * @param email - the email address of the company which will be used
 *        to identify the company.
 * @param Faculty - the name of the faculty that the company is listed under
 * @param companyError - enum to get the result of the func:
 *                     COMPANY_SUCCESS - company created successfully
 *                     COMPANY_NULL_PARAMETER - if email is NULL
 *                     COMPANY_INVALID_PARAMETER - one of the params is Invalid
 *                     COMPANY_OUT_OF_MEMORY - Allocation problem occurred
 * @return Company - a pointer to the successfully created company if everything
 *         went well NULL otherwise
 */
Company companyCreate(TechnionFaculty Faculty, char *email,
                      CompanyErrorCode *companyError);

/**
 * destroys a company and all of it's components. releases all relevant
 * allocated memory.
 * @param element - a pointer to the relevant company to be destroyed
 */
void companyDestroy(SetElement element);

/**
 * creates a new room according to the relevant input parameters and returns
 * the relevant result code. calculates the working hours of the room and if
 * found valid, calls roomCreate to add the room to the set.
 * @param company - the company to which the room needs to be added
 * @param id - the id of the room
 * @param price - entry price per person (must be a multiple of 4)
 * @param num_ppl - recommended number of people for this specific room
 * @param working_hrs - start time and close time of the room
 * @param difficulty - the difficulty level of the room
 * @return COMPANY_SUCCESS - the function finished with no errors
 *         COMPANY_NULL_PARAMETER - company is NULL
 *         COMPANY_INVALID_PARAMETER - if company is NULL
 *         COMPANY_MEMORY_PROBLEM - the room allocation was not successful
 *         COMPANY_ROOM_ALREADY_EXISTS - room with same id under that company
 *         already exists
 */
CompanyErrorCode companyAddRoom(Company company, int id, int price,
                                int num_ppl, int open_time, int close_time,
                                int difficulty);

/**
 * removes a room from the company set
 * @param company - the company from which the room needs to be removed
 * @param room - the room which needs to be removed from the company
 * @return COMPANY_SUCCESS - the room was removed successfully
 *         COMPANY_ROOM_DOES_NOT_EXIST - the room does not exist in the company
 *         COMPANY_NULL_PARAMETER - company ot room are NULL
 *         reservation
 */
CompanyErrorCode companyRemoveRoom(Company company, Room room);

/**
 * a comparison of two companies by email
 * @param element1 - the first company
 * @param element2 - the second company
 * @return 0 if same, positive num if the first is greater, negative otherwise
 *         if one of the elements is NULL returns -1
 */
int companyCompareElements(SetElement element1, SetElement element2);

/**
 * receives a source company element and copies it's data into a newly created
 * company element
 * @param src_company - the source company that needs to be copied
 * @return pointer to the new allocated company or NULL if the allocation failed
 */
SetElement companyCopyElement(SetElement src_company);

/**
 * receives a company and returns its email
 * @param company - the requested company
 * @param companyError - enum to get the result of the func:
 *                     COMPANY_SUCCESS - email returned successfully
 *                     COMPANY_NULL_PARAMETER - if company is NULL
 *                     COMPANY_OUT_OF_MEMORY - Allocation problem occurred
 * @return a pointer to the char* if the allocation worked and NULL if failed
 */
char *companyGetEmail(Company company, CompanyErrorCode *companyError);

/**
 * receives a company and returns the faculty it's under
 * @param company - the requested company
 * @param companyError - enum to get the result of the func:
 *                     COMPANY_SUCCESS - company created successfully
 *                     COMPANY_INVALID_PARAMETER - one of the params are Invalid
 *                     COMPANY_OUT_OF_MEMORY - Allocation problem occurred
 * @return the faculty the company's listed in or UNKNOWN if an error was found
 */
TechnionFaculty companyGetFaculty(Company company);

/**
 * receives a company and checks if it's email is equal to an email received
 * through the parameters
 * @param company - the company to be checked
 * @param email - the email to compare
 * @return true - if the company's email equals 'email'
 *         false - if the emails are different
 */
bool isCompanyEmailEqual(Company company, char *email);

/**
 * searches for a room in the company by its ID and returns it if exists
 * @param company - ptr to the company
 * @param id - the room ID that we are looking for
 * @return the room if we found it and NULL is it is not in the company or
 *         the company is NULL
 */
Room companyGetRoomByID(Company company, int id);

/**
 * receives a company, faculty and an escaper with his reservation details and
 * find out by a pre-determined formula which of the company's rooms would be
 * the best match for him. rooms with same result will be sorted for the room
 * with the minimal room id
 * @param company - the company to iterate through
 * @param escaperFaculty - the faculty of the escaper
 * @param P_e - the number of people for the reservation
 * @param skill - the skill level of the escaper who ordered
 * @param result - a pointer to return the result of the calculation
 * @param faculty_distance - a pointer to return the difference between the
 *         enum value of the escaper faculty and company faculty
 * @param room_id - a pointer to return the room with the minimal id found
 * @return a pointer to the most recommended room found
 */
Room companyMostRecommendedRoom(Company company, TechnionFaculty escaperFaculty,
                                int P_e, int skill, int *result,
                                int *faculty_distance,
                                int *room_id);

#endif //ESCAPETECHNION_COMPANY_H
