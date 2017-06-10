//
// Created by Shahak on 06/06/2017.
//

#include "reservation.h"
#include "utils.h"
#include "escaper.h"
#include "company.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INVALID_PARAMETER -1

struct Reservation_t {
    Escaper reservation_escaper;
    Company reservation_company;
    Room reservation_room;

    int reservation_day;
    int reservation_hour;
    int num_ppl;
    int total_cost;
};


/**
 * receives all the arguments to create a reservation and checks if they're all
 * valid
 * @param escaper_email - the email of the escaper
 * @param company_email - the email of the company the room is listed in
 * @param FacultyOfEscaper - the faculty the escaper is listed in
 * @param FacultyOfRoom - the faculty the room is listed in
 * @param room_id - the id of the asked room
 * @param num_ppl - number of escapers for the reservation
 * @param escaper_skill - the expertise level of the escaper
 * @param reservation_day - number of days for the reservation to take place
 * @param reservation_hour - the hour the room is reserved for
 * @param total_cost - the total amount to pay
 * @return true - all fields are valid
 *         false - not all fields are valid
 */
Reservation reservationCreate(Escaper escaper, Company company, Room room,
                              int num_ppl, int reservation_day,
                              int reservation_hour, int total_cost,
                              ReservationErrorCode *ReservationError) {

    assert(escaper != NULL && company != NULL && room != NULL);
    if (escaper == NULL || company == NULL || room == NULL || num_ppl <= 0 ||
            total_cost < 0) {
        *ReservationError = RESERVATION_INVALID_PARAMETER;
        return NULL;
    }

    Reservation reservation = malloc(sizeof(*reservation));
    if (NULL == reservation) {
        *ReservationError = RESERVATION_OUT_OF_MEMORY;
        return NULL;
    }

    reservation->reservation_escaper = escaper;
    reservation->reservation_company = company;
    reservation->reservation_room = room;

    reservation->num_ppl = num_ppl;
    reservation->reservation_day = reservation_day;
    reservation->reservation_hour = reservation_hour;
    reservation->total_cost = total_cost;
    *ReservationError = RESERVATION_SUCCESS;
    return reservation;
}


ReservationErrorCode reservationDestroy(Reservation reservation) {
    if (NULL == reservation) {
        return RESERVATION_INVALID_PARAMETER;
    }
    free(reservation);
    return RESERVATION_SUCCESS;
}

void reservationFreeElement(ListElement reservation) {
    if (NULL == reservation) {
        return;
    }
    reservationDestroy(reservation);
}

ListElement reservationCopyElement(ListElement src_reservation) {
    if (NULL == src_reservation) {
        return NULL;
    }
    Reservation ptr = src_reservation; //to make the code clearer
    ReservationErrorCode CopyResult;
    Reservation reservation = reservationCreate(ptr->reservation_escaper,
                                                ptr->reservation_company,
                                                ptr->reservation_room,
                                                ptr->num_ppl,
                                                ptr->reservation_day,
                                                ptr->reservation_hour,
                                                ptr->total_cost, &CopyResult);
    if (CopyResult == RESERVATION_OUT_OF_MEMORY ||
        CopyResult == RESERVATION_INVALID_PARAMETER) {
        return NULL;
    }
    return reservation;
}

Escaper reservationGetEscaper(Reservation reservation,
                           ReservationErrorCode *error) {
    if (NULL == reservation) {
        *error = RESERVATION_INVALID_PARAMETER;
        return NULL;
    }
    *error = RESERVATION_SUCCESS;
    return reservation->reservation_escaper;
}

Company reservationGetCompany(Reservation reservation,
                           ReservationErrorCode *error) {
    if (NULL == reservation) {
        *error = RESERVATION_INVALID_PARAMETER;
        return NULL;
    }
    *error = RESERVATION_SUCCESS;
    return reservation->reservation_company;
}

Room reservationGetRoom(Reservation reservation, ReservationErrorCode *error) {
    if (NULL == reservation) {
        *error = RESERVATION_INVALID_PARAMETER;
        return NULL;
    }
    *error = RESERVATION_SUCCESS;
    return reservation->reservation_room;
}