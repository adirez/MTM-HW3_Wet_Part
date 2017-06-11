//
// Created by Shahak on 06/06/2017.
//

#ifndef HW3_RESERVATION_H
#define HW3_RESERVATION_H

#include "mtm_ex3.h"
#include "list.h"
#include "escaper.h"
#include "company.h"
#include "room.h"

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


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/


/**
 * creates a new reservation according to the relevant input parameters and
 * returns the relevant result code.
 * @param escaper - ptr to the escaper who made the reservation
 * @param company - ptr to the company in which the room that the reservation
 *        was made for
 * @param room - ptr to the room that the reservation was made for
 * @param num_ppl - number of escapers for the reservation
 * @param day - the day of the reservation since beginning of time
 * @param hour - the hour the room is reserved for
 * @param price - the total amount to pay
 * @return Reservation - a pointer to the successful reservation if everything
 *         went ok
           NULL - if the allocation was not successful
 */
Reservation reservationCreate(Escaper escaper, Company company, Room room,
                              int num_ppl, int day,
                              int hour, int price);

/**
 * destroys a reservation and and releases all relevant allocated memory.
 * @param reservation - a pointer to the relevant reservation to be destroyed
 * @return RESERVATION_SUCCESS - the reservation was removed successfully
 *         RESERVATION_INVALID_PARAMETER - one of the parameters was invalid
 */
void reservationDestroy(ListElement reservation);

//TODO: check if we need this:

/**
 * compares between two reservations received as an input
 * @param reservation_1 - the first reservation
 * @param reservation_2 - the second reservation
 * @return 0 - if the reservations are identical (by all fields)
 */


/**
 * receives a source reservation element and copies it's data into a newly
 * created reservation element
 * @param src_reservation - the source reservation that needs to be copied
 * @return pointer to the new allocated reservation or NULL if the allocation
 * failed
 */
Reservation reservationCopyElement(Reservation src_reservation);

/**
 * receives a reservation type and returns a ptr to the escaper whom reserved it
 * @param reservation - ptr to the reservation
 * @param error - a type to get the result of the function
 * @return ptr to the escaper
 */
Escaper reservationGetEscaper(Reservation reservation);
/**
 * receives a reservation type and returns a ptr to the company that controls
 * the room for which the reservation is for
 * @param reservation - ptr to the reservation
 * @param error - a type to get the result of the function
 * @return ptr to the company
 */
Company reservationGetCompany(Reservation reservation);
/**
 * receives a reservation type and returns a ptr to the room that the
 * reservation is for
 * @param reservation - ptr to the reservation
 * @param error - a type to get the result of the function
 * @return ptr to the room
 */
Room reservationGetRoom(Reservation reservation);

/**
 * receives a reservation and a pointer to an integer and returns through it the
 * day listed in the reservation
 * @param reservation - the reservation to check
 * @param day - the integer pointer to update with the day value
 * @return RESERVATION_SUCCESS - if the function worked
 *         RESERVATION_INVALID_PARAMETERS - if one of the parameteres was
 *         invalid
 */
int reservationGetDay(Reservation reservation);

/**
 * receives a reservation and a pointer to an integer and returns through it the
 * hour listed in the reservation
 * @param reservation - the reservation to check
 * @param hour - the integer pointer to update with the hour value
 * @return RESERVATION_SUCCESS - if the function worked
 *         RESERVATION_INVALID_PARAMETERS - if one of the parameteres was
 *         invalid
 */
int reservationGetHour(Reservation reservation);
//TODO: add comments
int reservationGetNumPpl(Reservation reservation);

int reservationGetPrice(Reservation reservation);

int reservationCompareHourAndId(ListElement element1, ListElement element2);



/**
 *
 * @param reservation_1
 * @param reservation_2
 * @return
 */
int reservationCompareElements(ListElement reservation_1,
                               ListElement reservation_2);

/**
 *
 * @param element
 * @param cur_day
 * @return
 */
bool isReservationDueDate(ListElement element, ListFilterKey cur_day);

bool isReservationNotDueDate(ListElement element, ListFilterKey cur_day);


#endif //HW3_RESERVATION_H
