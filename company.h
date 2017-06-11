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
    COMPANY_ROOM_ALREADY_EXISTS,
    COMPANY_ROOM_DOES_NOT_EXIST,
    COMPANY_INVALID_PARAMETER,
    COMPANY_RESERVATION_EXISTS,
    COMPANY_OUT_OF_MEMORY
} CompanyErrorCode;

/**
 * creates a new company according to the relevant input parameters and returns
 * the relevant result code.
 * @param email - the email address of the company which will be used
 *        to identify the company.
 * @param Faculty - the name of the faculty that the company is listed under
 * @param CompanyError - the result of the creation
 * @return Company - a pointer to the successfully created company if everything
 *         went ok
 *         NULL - if the allocation was not successful
 */
Company companyCreate(TechnionFaculty Faculty, char *email);

/**
 * destroys a company and all of it's components. releases all relevant
 * allocated memory.
 * @param company - a pointer to the relevant company to be destroyed
 * @return COMPANY_SUCCESS - the room was removed successfuly
 *         COMPANY_INVALID_PARAMETER - one of the parameters was invalid
 *         COMPANY_ROOM_DOES_NOT_EXIST - the asked room wasn't found
 *         COMPANY_RESERVATION_EXISTS - one of the rooms has an existing
 *         reservation
 */
void companyDestroy(Company company);

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
 *         COMPANY_INVALID_PARAMETER - the function received an invalid
 *         parameter as an input
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
 *         COMPANY_INVALID_PARAMETER - one of the parameters was invalid
 *         reservation
 */
CompanyErrorCode companyRemoveRoom(Company company, Room room);

/**
 * a comparison of two companies by email
 * @param company1 - the first company
 * @param company2 - the second company
 * @return -1 - INVALID_PARAMETER
 * @return 1 - emails are different
 * @return 0 - emails are equal
 */
int companyCompareElements(SetElement company1, SetElement company2);

/**
 * frees all relevant allocated memory of a specific company element
 * @param company - the company  to be freed
 */
void companyFreeElement(SetElement company);

/**
 * receives a source company element and copies it's data into a newly created
 * company element
 * @param src_company - the source company that needs to be copied
 * @return pointer to the new allocated company or NULL if the allocation failed
 */
SetElement companyCopyElement(SetElement src_company);

/**
 * receives a company and returns it's email
 * @param company - the requested company
 * @param CompanyError - a type to get the result of the function
 * @return a pointer to the char* if the allocation worked and NULL if failed
 */
char *companyGetEmail(Company company);

/**
 * receives a company and returns the faculty it's listen in
 * @param company - the requested company
 * @param CompanyError - an error type to return the result / error
 * @return the faculty the company's listed in or UNKNOWN if an error was found
 */
TechnionFaculty companyGetFaculty(Company company);

/**
 * receives a company and a room id and iterates over the company's rooms to
 * check if a room with the received id exists
 * @param company - the company to be checked
 * @param room_id - the id we're looking for
 * @param CompanyError - a type to return the result of the function
 * @return a pointer to the room if exists, else NULL
 */
Room companyFindRoom(Company company, int room_id);

/**
 * receives a company and checks if it's email is equal to an email received
 * through the parameters
 * @param company - the company to be checked
 * @param email - the email to compare
 * @param CompanyError - a type to hold the result of the function
 * @return true - if the company's email equals 'email'
 *         false - if the emails are different
 */
bool isCompanyEmailEqual(Company company, char *email);

/**
 * receives a company and a room id and checks if a room with this id exists
 * within the company
 * @param company - the company to iterate through
 * @param room_id - the id to look for
 * @return true - if the id was found
 *         false - if the id wasn't found
 */
bool isRoomIdInCompany(Company company, int room_id);

/**
 * receives a company, faculty and an escaper with his reservation details and
 * find out by a pre-determined formula which of the company's rooms would be
 * the best match for him. rooms with same result will be sorted for the room
 * with the minimal room id
 * @param company - the company to iterate through
 * @param escaperFaculty - the faculty of the escaper
 * @param P_r - the number of people for the reservation
 * @param skill - the skill level of the escaper who ordered
 * @param result - a pointer to return the result of the calculation
 * @param faculty_distance - a pointer to return the difference between the
 *         enum value of the escaper faculty and company faculty
 * @param room_id - a pointer to return the room with the minimal id found
 * @return a pointer to the most recommended room found
 */
Room mostRecommendedRoom(Company company, TechnionFaculty escaperFaculty,
                         int P_r, int skill,
                         int *result, int *faculty_distance, int *room_id);

/**
 * receives a company and returns the minimum id of the company rooms
 * @param company - the company to iterate through
 * @return an integer, representing the minimum value
 */
int companyGetMinRoomID(Company company);

#endif //ESCAPETECHNION_COMPANY_H
