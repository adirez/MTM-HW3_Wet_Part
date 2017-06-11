//
// Created by Shahak on 07/06/2017.
//

#ifndef HW3_ESCAPETECHNION_H
#define HW3_ESCAPETECHNION_H

#include "company.h"
#include "room.h"
#include "escaper.h"
#include "reservation.h"

/**
 * EscapeTechnion will be implemented in this flie.
 */
typedef struct EscapeTechnion_t *EscapeTechnion;
//TODO: add inout channel to comment


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/


/**
 * creates a member of EscapeTechnion type, including all internal fields of
 * companies, rooms, faculties and reservations with all relevant allocations.
 * @param EscapeTechnionError - a type to hold the result of the function
 * @return a pointer to the allocated system or NULL if an error was found
 */
EscapeTechnion escapeTechnionCreate();

/**
 * receives an escapeTechnion type and destroys it, including releasing all
 * allocated memory from internal fields
 * @param escapeTechnion - the type to be destroyed
 * @return MTM_SUCCESS - if the function worked ok
 *         MTM_NULL_PARAMETER - if the argument was NULL
 */
void escapeTechnionDestroy(EscapeTechnion escapeTechnion);

/**
 * receives an escapeTechnion type system and details of a company and creates
 * a new company with suitable details within the system
 * @param escapeTechnion - the system to create the company in
 * @param email - the email of the company to be created
 * @param Faculty - the faculty of the company to be created
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_INVALID_PARAMETER - if one of the parameters was incompatible
 *         MTM_MEMORY_PROBLEM - if the allocations failed
 *         MTM_EMAIL_ALREADY_EXISTS - if the email is already in use
 */
MtmErrorCode escapeTechnionAddCompany(EscapeTechnion escapeTechnion,
                                      char *email, TechnionFaculty Faculty);

/**
 * receives an escapeTechnion system and a company email and iterates through
 * the system to find a company with a matching email and remove it
 * @param escapeTechnion - the system to iterate through
 * @param company_email - the email to look for
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_INVALID_PARAMETER - if one of the parameters was incompatible
 *         MTM_RESERVATION_EXISTS - if the company has an active reservation
 *         MTM_COMPANY_EMAIL_DOES_NOT_EXIST - if the company's email wasn't
 *         found in the system
 */
MtmErrorCode escapeTechnionRemoveCompany(EscapeTechnion escapeTechnion,
                                         char *company_email);

/**
 * receives an escapeTechnion type system and details of a room and a company
 * and creates a new room inside the company with suitable details within the
 * system
 * @param escapeTechnion - the system to create the company in
 * @param company_email - the email of the company to list the room under
 * @param room_id - the id of the room to be added
 * @param price - the price of the room to be added
 * @param num_ppl - the recommended number of people for the room
 * @param working_hours - a string representing the working hours of the room
 * @param difficulty - the difficulty level of the room
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_INVALID_PARAMETER - if one of the parameters was incompatible
 *         MTM_COMPANY_EMAIL_DOES_NOT_EXIST - if the company's email wasn't
 *         found in the system
 *         MTM_ID_ALREADY_EXIST - if the room id is already in use in the
 *         company
 *         MTM_OUT_OF_MEMORY - if one of the allocations failed
 */
MtmErrorCode escapeTechnionAddRoom(EscapeTechnion escapeTechnion,
                                   char *company_email, int room_id, int price,
                                   int num_ppl, char *working_hours,
                                   int difficulty);

/**
 * receives an escapeTechnion system, a room and a faculty and iterates through
 * the system to find a room under the listed faculty to remove the room from
 * the right company (according to a matching faculty)
 * @param escapeTechnion - the system to iterate through
 * @param room_id - the id to look for
 * @param Faculty - the faculty the room should be listed under
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_INVALID_PARAMETER - if one of the parameters was incompatible
 *         MTM_RESERVATION_EXISTS - if the company has an active reservation
 *         MTM_ID_DOES_NOT_EXIST - if the room id wasn't found in the system
 *         with the specified faculty
 */
MtmErrorCode escapeTechnionRemoveRoom(EscapeTechnion escapeTechnion,
                                      int room_id, TechnionFaculty Faculty);

/**
 * receives an escapeTechnion system and escaper's details and adds the escaper
 * to the list.
 * @param escapeTechnion - the system to iterate through
 * @param escaper_email - the email of the escaper to be added
 * @param skill_level - the skill level of the escaper
 * @param FacultyOfEscaper - the faculty of the escaper
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_INVALID_PARAMETER - if one of the parameters was incompatible
 *         MTM_EMAIL_ALREADY_EXISTS- if the escaper's email is  already in use
 *         in the system
 *         MTM_OUT_OF_MEMORY - if one of the allocations failed
 */
MtmErrorCode escapeTechnionAddEscaper(EscapeTechnion escapeTechnion,
                                      char *escaper_email, int skill_level,
                                      TechnionFaculty FacultyOfEscaper);

/**
 * receives an escapeTechnion system and an email of an escaper and iterates
 * through the system to find an escaper witht the specific email and remove
 * from the system
 * @param email - the email of the escaper
 * @param escapeTechnion - the system to iterate through
 * @return MTM_SUCCESS - if the function succeeded
 *         MTM_CLIENT_EMAIL_DOES_NOT_EXIST - if the email wasn't found in the
 *         system
 *         MTM_INVALID_PARAMETER - if one of the parameteres was incorrect
 */
MtmErrorCode escapeTechnionRemoveEscaper(char *email,
                                         EscapeTechnion escapeTechnion);

/**
 * receives the details of a reservation, checks if the room and escaper are
 * available at the specified time and if the escaper is entitled to receive a
 * discount and creates the reservation
 * @param escaper_email - the email of the escaper
 * @param room_id - the id of the room to be reserved
 * @param FacultyOfRoom - the faculty of the room to be reserved
 * @param time - a string containing the day and hour of the reservation
 * @param num_ppl - the number of people in the reservation
 * @param escapeTechnion - the system to iterate through
 * @return MTM_SUCCESS - if the reservation was created successfully
 *         MTM_CLIENT_EMAIL_DOES_NOT_EXIST - if the escaper wasn't found in the
 *         system
 *         MTM_ID_DOES_NOT_EXIST - if the room wasn't found in the system
 *         MTM_CLIENT_IN_ROOM - if the client already has a reservation at the
 *         specified time
 *         MTM_INVALID_PARAMETER - if one of the parameters is invalid
 *         MTM_ROOM_NOT_AVAILABLE - if the room is taken or not working in the
 *         hours of the reservation
 */
MtmErrorCode escapeTechnionReservationReceived(char *escaper_email, int room_id,
                                               TechnionFaculty FacultyOfRoom,
                                               char *time, int num_ppl,
                                               EscapeTechnion escapeTechnion);
/**
 *
 * @param escaper_email
 * @param num_ppl
 * @param escapeTechnion
 * @return
 */
MtmErrorCode escapeTechnionRecommendedRoom(char *escaper_email, int num_ppl,
                                           EscapeTechnion escapeTechnion);


/**
 *
 * @param company
 * @param escaperFaculty
 * @param P_e
 * @param skill
 * @param result
 * @param faculty_distance
 * @param room_id
 * @return
 */
Room mostRecommendedRoom(Company company, TechnionFaculty escaperFaculty,
                         int P_e, int skill,
                         int *result, int *faculty_distance, int *room_id);


void escapeTechnionReportDay(EscapeTechnion escapeTechnion);

#endif //HW3_ESCAPETECHNION_H
