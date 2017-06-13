//
// Created by Shahak on 07/06/2017.
//



/**...........................................................................*/
/**---------------------------DEFINES-&-INCLUDES------------------------------*/
/**...........................................................................*/



#ifndef HW3_ESCAPETECHNION_H
#define HW3_ESCAPETECHNION_H

#include "faculty.h"
#include "company.h"
#include "room.h"
#include "escaper.h"
#include "reservation.h"


/**...........................................................................*/
/**-----------------------------STRUCTURE-------------------------------------*/
/**...........................................................................*/



/**
 * EscapeTechnion will be implemented in this flie.
 */
typedef struct EscapeTechnion_t *EscapeTechnion;

/**
 * a type to used to return error codes related to escape technion systems
 */
typedef enum {
    ESCAPE_TECHNION_OUT_OF_MEMORY,
    ESCAPE_TECHNION_NULL_PARAMETER,
    ESCAPE_TECHNION_INVALID_PARAMETER,
    ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS,
    ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST,
    ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST,
    ESCAPE_TECHNION_ID_ALREADY_EXIST,
    ESCAPE_TECHNION_ID_DOES_NOT_EXIST,
    ESCAPE_TECHNION_CLIENT_IN_ROOM,
    ESCAPE_TECHNION_ROOM_NOT_AVAILABLE,
    ESCAPE_TECHNION_RESERVATION_EXISTS,
    ESCAPE_TECHNION_NO_ROOMS_AVAILABLE,
    ESCAPE_TECHNION_SUCCESS,
} EscapeTechnionErrorCode;


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
 * @return ESCAPE_TECHNION_SUCCESS - if the function worked ok
 *         ESCAPE_TECHNION_NULL_PARAMETER - if the argument was NULL
 */
void escapeTechnionDestroy(EscapeTechnion escapeTechnion);

/**
 * receives an escapeTechnion type system and details of a company and creates
 * a new company with suitable details within the system
 * @param escapeTechnion - the system to create the company in
 * @param email - the email of the company to be created
 * @param nameFaculty - the faculty of the company to be created
 * @return ESCAPE_TECHNION_SUCCESS - if the function succeeded
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the parameters was
 *         incompatible
 *         ESCAPE_TECHNION_MEMORY_PROBLEM - if the allocations failed
 *         ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS - if the email is already in use
 */
EscapeTechnionErrorCode escapeTechnionAddCompany(EscapeTechnion escapeTechnion,
                                                 TechnionFaculty nameFaculty,
                                                 char *email);

/**
 * receives an escapeTechnion system and a company email and iterates through
 * the system to find a company with a matching email and remove it
 * @param escapeTechnion - the system to iterate through
 * @param company_email - the email to look for
 * @return ESCAPE_TECHNION_SUCCESS - if the function succeeded
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the parameters was
 *         incompatible
 *         ESCAPE_TECHNION_RESERVATION_EXISTS - if the company has an active
 *         reservation
 *         ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST - if the company's email
 *         wasn't
 *         found in the system
 */
EscapeTechnionErrorCode escapeTechnionRemoveCompany(EscapeTechnion escapeTechnion,
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
 * @return ESCAPE_TECHNION_SUCCESS - if the function succeeded
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the parameters was
 *         incompatible
 *         ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST - if the company's email
 *         wasn't
 *         found in the system
 *         ESCAPE_TECHNION_ID_ALREADY_EXIST - if the room id is already in use
 *         in the
 *         company
 *         ESCAPE_TECHNION_OUT_OF_MEMORY - if one of the allocations failed
 */
EscapeTechnionErrorCode escapeTechnionAddRoom(EscapeTechnion escapeTechnion,
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
 * @return ESCAPE_TECHNION_SUCCESS - if the function succeeded
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the parameters was
 *         incompatible
 *         ESCAPE_TECHNION_RESERVATION_EXISTS - if the company has an active
 *         reservation
 *         ESCAPE_TECHNION_ID_DOES_NOT_EXIST - if the room id wasn't found in
 *         the system
 *         with the specified faculty
 */
EscapeTechnionErrorCode escapeTechnionRemoveRoom(EscapeTechnion escapeTechnion,
                                          int room_id, TechnionFaculty Faculty);

/**
 * receives an escapeTechnion system and escaper's details and adds the escaper
 * to the list.
 * @param escapeTechnion - the system to iterate through
 * @param email - the email of the escaper to be added
 * @param skill - the skill level of the escaper
 * @param nameFaculty - the faculty of the escaper
 * @return ESCAPE_TECHNION_SUCCESS - if the function succeeded
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the parameters was
 *         incompatible
 *         ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS- if the escaper's email is
 *         already in use
 *         in the system
 *         ESCAPE_TECHNION_OUT_OF_MEMORY - if one of the allocations failed
 */
EscapeTechnionErrorCode escapeTechnionAddEscaper(EscapeTechnion escapeTechnion,
                                                 char *email, int skill,
                                                 TechnionFaculty nameFaculty);

/**
 * receives an escapeTechnion system and an email of an escaper and iterates
 * through the system to find an escaper witht the specific email and remove
 * from the system
 * @param email - the email of the escaper
 * @param escapeTechnion - the system to iterate through
 * @return ESCAPE_TECHNION_SUCCESS - if the function succeeded
 *         ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST - if the email wasn't
 *         found in the
 *         system
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the parameteres was
 *         incorrect
 */
EscapeTechnionErrorCode escapeTechnionRemoveEscaper(EscapeTechnion escapeTechnion,
                                                    char *email);

/**
 * receives the details of a reservation, checks if the room and escaper are
 * available at the specified time and if the escaper is entitled to receive a
 * discount and creates the reservation
 * @param escaper_email - the email of the escaper
 * @param room_id - the id of the room to be reserved
 * @param nameFaculty - the faculty of the room to be reserved
 * @param time - a string containing the day and hour of the reservation
 * @param num_ppl - the number of people in the reservation
 * @param escapeTechnion - the system to iterate through
 * @return ESCAPE_TECHNION_SUCCESS - if the reservation was created successfully
 *         ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST - if the escaper wasn't
 *         found in the
 *         system
 *         ESCAPE_TECHNION_ID_DOES_NOT_EXIST - if the room wasn't found in the
 *         system
 *         ESCAPE_TECHNION_CLIENT_IN_ROOM - if the client already has a
 *         reservation at the
 *         specified time
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the parameters is
 *         invalid
 *         ESCAPE_TECHNION_ROOM_NOT_AVAILABLE - if the room is taken or not
 *         working in the
 *         hours of the reservation
 */
EscapeTechnionErrorCode escapeTechnionReservationReceived(EscapeTechnion
                                                          escapeTechnion,
                                               char *escaper_email, int room_id,
                                               TechnionFaculty nameFaculty,
                                               char *time, int num_ppl);
/**
 * receives an escapeTechnion system, number of people for a reservation and an
 * email address of the escaper who made the reservation and makes a reservation
 * for the most recommended room at the closest available time
 * @param escaper_email - the email of the escaper who made the reservation
 * @param num_ppl - the number of people for the reservation
 * @param escapeTechnion - the system to iterate through
 * @return ESCAPE_TECHNION_NULL_PARAMETER - if one of the params is NULL
 *         ESCAPE_TECHNION_INVALID_PARAMETER - if one of the params is invalid
 *         ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST - if the email of the
 *         escaper wasn't found in the system
 *         ESCAPE_TECHNION_NO_ROOMS_AVAILABLE - if there's no available room
 *         ESCAPE_TECHNION_SUCCESS - if a reservation was made successfully
 */
EscapeTechnionErrorCode escapeTechnionRecommendedRoom(EscapeTechnion
                                                      escapeTechnion,int num_ppl,
                                                      char *escaper_email);

/**
 * receives an escapeTechnion system and an output file and prints out the
 * daily report including all of the daily reservations. removes the irrelevant
 * reservations, updates earnings and advances the system days count
 * @param escapeTechnion - the system to iterate through
 * @param output_channel - standard output / output file
 * @return ESCAPE_TECHNION_NULL_PARAMETER - if one of the parameters is NULL
 *         ESCAPE_TECHNION_OUT_OF_MEMORY - if an allocation failed
 *         ESCAPE_TECHNION_SUCCESS - if the function succeeded
 */
EscapeTechnionErrorCode escapeTechnionReportDay(EscapeTechnion escapeTechnion,
                                                FILE *output_channel);

/**
 * receives an escapeTechnion system and an output file and prints out the best
 * faculties report including all of the current faculties and the top three
 * faculties by earnings (and the total earnings of the system)
 * @param escapeTechnion - the system to iterate through
 * @param output_channel - standard output / output file
 * @return ESCAPE_TECHNION_NULL_PARAMETER - if one of the params is NULL
 *         ESCAPE_TECHNION_SUCCESS - if the function succeeded
 */
EscapeTechnionErrorCode escapeTechnionReportBest(EscapeTechnion escapeTechnion,
                                      FILE *output_channel);

#endif //HW3_ESCAPETECHNION_H
