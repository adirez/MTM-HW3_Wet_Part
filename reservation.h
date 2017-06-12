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
 * a type used to return error codes related to Room
 */
typedef enum {
    RESERVATION_SUCCESS,
    RESERVATION_NULL_PARAMETER,
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
 * @param reservationError - enum to get the result of the func:
 *                 RESERVATION_SUCCESS - reservation created successfully
 *                 RESERVATION_NULL_PARAMETER - one of the params is NULL
 *                 RESERVATION_INVALID_PARAMETER - one of the params is Invalid
 *                 RESERVATION_OUT_OF_MEMORY - Allocation problem occurred
 * @return Reservation - a pointer to the successful reservation if everything
 *         went well
           NULL - if the allocation was not successful
 */
Reservation reservationCreate(Escaper escaper, Company company, Room room,
                              int num_ppl, int day, int hour, int price,
                              ReservationErrorCode *reservationError);

/**
 * destroys a reservation and releases all relevant allocated memory.
 * @param reservation - a pointer to the relevant reservation to be destroyed
 */
void reservationDestroy(ListElement reservation);

/**
 * receives a source reservation element and copies it into a newly
 * created reservation element
 * @param src_reservation - the source reservation that needs to be copied
 * @return pointer to the new allocated reservation or NULL if the allocation
 * failed
 */
ListElement reservationCopyElement(ListElement src_reservation);

/**
 * receives a reservation type and returns a ptr to the escaper whom reserved it
 * @param reservation - ptr to the reservation
 * @return ptr to the escaper or NULL if the reservation is NULL
 */
Escaper reservationGetEscaper(Reservation reservation);
/**
 * receives a reservation type and returns a ptr to the company that controls
 * the room for which the reservation is for
 * @param reservation - ptr to the reservation
 * @return ptr to the company or NULL if the reservation is NULL
 */
Company reservationGetCompany(Reservation reservation);
/**
 * receives a reservation type and returns a ptr to the room that the
 * reservation is for
 * @param reservation - ptr to the reservation
 * @return ptr to the room or NULL if the reservation is NULL
 */
Room reservationGetRoom(Reservation reservation);

/**
 * returns the num of people of the reservation
 * @param reservation - ptr to the reservation
 * @return the num of people of the reservation or -1 if the reservation is NULL
 */
int reservationGetNumPpl(Reservation reservation);

/**
 * returns the day of the reservation
 * @param reservation - ptr to the reservation
 * @return the day of the reservation or -1 if the reservation is NULL
 */
int reservationGetDay(Reservation reservation);

/**
 * returns the hour of the reservation
 * @param reservation - ptr to the reservation
 * @return the hour of the reservation or -1 if the reservation is NULL
 */
int reservationGetHour(Reservation reservation);

/**
 * returns the price of the reservation
 * @param reservation - ptr to the reservation
 * @return the price of the reservation or -1 if the reservation is NULL
 */
int reservationGetPrice(Reservation reservation);

/**
 * filter function for the List use, checks if the reservation day is the
 * current day in the system, meaning that the reservation is already done.
 * in use for the report day print
 * @param element - the reservation to be checked
 * @param cur_day - the current day in the system
 * @return true if this is the reservation due day, false otherwise
 */
bool isReservationDueDate(ListElement element, ListFilterKey cur_day);

/**
 * compares between 2 reservations by their due date
 * @param reservation1
 * @param reservation2
 * @return 0 if same, positive num if the first is greater, negative otherwise
 */
int reservationCompareElements(ListElement element1, ListElement element2);

/**
 * filter function for the List use, checks if the reservation day is the
 * current day in the system, meaning that the reservation is already done.
 * in use for the report day to keep all the reservations that are stiill
 * relevant
 * @param reservation - the reservation to be checked
 * @param cur_day - the current day in the system
 * @return true if the reservation is still relevant, false otherwise
 */
bool isReservationRelevant(ListElement element, ListFilterKey cur_day);

/**
 * compare function to the List use, compares reservations by hour, faculty
 * priority and the smallest room ID in the faculty.
 * in use for the report day print
 * @param reservation1 - first reservation
 * @param reservation2 - second reservation
 * @return 0 if same, positive num if the first is greater, negative otherwise
 */
int reservationCompareForPrint(ListElement element1, ListElement element2);



#endif //HW3_RESERVATION_H
