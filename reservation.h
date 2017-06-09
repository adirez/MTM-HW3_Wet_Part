//
// Created by Shahak on 06/06/2017.
//

#ifndef HW3_RESERVATION_H
#define HW3_RESERVATION_H

#include "mtm_ex3.h"
#include "list.h"

/**
 * Reservation will be implemented in this file as a linked list
 */
typedef struct Reservation_t *Reservation;

/**
 * a type used to return error codes related to Reservation
 */
typedef enum {
    RESERVATION_SUCCESS,
    RESERVATION_INVALID_PARAMETER,
    RESERVATION_OUT_OF_MEMORY
} ReservationErrorCode;

/**
 * creates a new reservation according to the relevant input parameters and
 * returns the relevant result code.
 * @param escaper_email - the email of the escaper
 * @param company_email - the email of the company the room is listed in
 * @param FacultyOfEscaper - the faculty the escaper is listed in
 * @param FacultyOfRoom - the faculty the room is listed in
 * @param room_id - the id of the asked room
 * @param num_ppl - number of escapers for the reservation
 * @param escaper_skill - the expertise level of the escaper
 * @param days_to_reservation - number of days for the reservation to take place
 * @param reservation_hour - the hour the room is reserved for
 * @param total_cost - the total amount to pay
 * @return Reservation - a pointer to the successful reservation if everything
 *         went ok
           NULL - if the allocation was not successful
 */
Reservation reservationCreate(char *escaper_email, char *company_email,
                              TechnionFaculty FacultyOfEscaper,
                              TechnionFaculty FacultyOfRoom, int room_id,
                              int num_ppl, int escaper_skill,
                              int days_to_reservation, int reservation_hour,
                              int total_cost,
                              ReservationErrorCode *ReservationError);

/**
 * destroys a reservation and and releases all relevant allocated memory.
 * @param reservation - a pointer to the relevant reservation to be destroyed
 * @return RESERVATION_SUCCESS - the reservation was removed successfully
 *         RESERVATION_INVALID_PARAMETER - one of the parameters was invalid
 */
ReservationErrorCode reservationDestroy(Reservation reservation);


/**
 * compares between two reservations received as an input
 * @param reservation_1 - the first reservation
 * @param reservation_2 - the second reservation
 * @return 0 - if the reservations are identical (by all fields)
 */

/**
 * frees all relevant allocated memory of a specific escaper element
 * @param escaper - the escaper to be freed
 * @return RESERVATION_SUCCESS - the function went with no errors
 *         RESERVATION_INVALID_PARAMETER - one of the parameters was invalid
 */
void reservationFreeElement(ListElement reservation);

/**
 * receives a source reservation element and copies it's data into a newly
 * created reservation element
 * @param src_reservation - the source reservation that needs to be copied
 * @return pointer to the new allocated reservation or NULL if the allocation
 * failed
 */
ListElement reservationCopyElement(ListElement src_reservation);

/**
 * receives a reservation and an email address and checks if the email is listed
 * in the reservation as the company's email
 * @param reservation - the reservation to check
 * @param company_email - the email of the company to compare
 * @param ReservationError - a type to hold the result of the function
 * @return true - if the emails are equal
 *         false - if the emails are not equal
 */
bool isReservationCompanyEmailEqual(Reservation reservation,
                                    char *company_email,
                                    ReservationErrorCode *ReservationError);

/**
 * receives a reservation and an email address and checks if the email is listed
 * in the reservation as the escaper's email
 * @param reservation - the reservation to check
 * @param escaper_email - the email of the escaper to compare
 * @param ReservationError - a type to hold the result of the function
 * @return true - if the emails are equal
 *         false - if the emails are not equal
 */
bool isReservationEscaperEmailEqual(Reservation reservation,
                                    char *escaper_email,
                                    ReservationErrorCode *ReservationError);

/**
 * receives a reservation and a room id and checks if the id is listed
 * in the reservation
 * @param reservation - the reservation to check
 * @param room_id - the id of the room to compare
 * @param ReservationError - a type to hold the result of the function
 * @return true - if the IDs are equal
 *         false - if the IDs are not equal
 */
bool isReservationRoomIdEqual(Reservation reservation, int room_id,
                              ReservationErrorCode *ReservationError);

#endif //HW3_RESERVATION_H
