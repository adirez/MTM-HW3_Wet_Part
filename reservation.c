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

ReservationErrorCode reservationGetDay(Reservation reservation, int *day) {
    if (NULL == reservation || NULL == day) {
        *day = INVALID_PARAMETER;
        return RESERVATION_INVALID_PARAMETER;
    }
    *day = reservation->reservation_day;
    return RESERVATION_SUCCESS;
}

ReservationErrorCode reservationGetHour(Reservation reservation, int *hour) {
    if (NULL == reservation || NULL == hour) {
        *hour = INVALID_PARAMETER;
        return RESERVATION_INVALID_PARAMETER;
    }
    *hour = reservation->reservation_hour;
    return RESERVATION_SUCCESS;
}

static bool isReservationDueDate(ListElement element, ListFilterKey cur_day) {
    Reservation reservation = element;
    if (reservation->reservation_day == (int) cur_day) {
        return true;
    }
    return false;
}