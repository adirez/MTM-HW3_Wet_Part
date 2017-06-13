//
// Created by Shahak on 06/06/2017.
//

#include <stdlib.h>
#include <assert.h>

#include "reservation.h"
#include "utils.h"

#define INVALID_PARAMETER -1

struct Reservation_t {
    Escaper escaper;
    Company company;
    Room room;

    int day;
    int hour;
    int num_ppl;
    int price;
};

/**...........................................................................*/
/**-----------------------FUNCTIONS-IMPLEMENTATIONS---------------------------*/
/**...........................................................................*/

Reservation reservationCreate(Escaper escaper, Company company, Room room,
                              int num_ppl, int day, int hour, int price,
                              ReservationErrorCode *reservationError) {
    if(NULL == reservationError){
        return NULL;
    }
    if (NULL == escaper || NULL == company || NULL == room){
        *reservationError = RESERVATION_NULL_PARAMETER;
        return NULL;
    }
    if (num_ppl <= 0){
        *reservationError = RESERVATION_INVALID_PARAMETER;
        return NULL;
    }

    Reservation reservation = malloc(sizeof(*reservation));
    if (NULL == reservation) {
        *reservationError = RESERVATION_OUT_OF_MEMORY;
        return NULL;
    }
    reservation->escaper = escaper;
    reservation->company = company;
    reservation->room = room;

    reservation->num_ppl = num_ppl;
    reservation->day = day;
    reservation->hour = hour;
    reservation->price = price;

    *reservationError = RESERVATION_SUCCESS;
    return reservation;
}


void reservationDestroy(ListElement element) {
    if(NULL == element){
        return;
    }
    free(element);
}

ListElement reservationCopyElement(ListElement src_reservation) {
    if (NULL == src_reservation) {
        return NULL;
    }
    ReservationErrorCode reservationError;
    Reservation ptr = src_reservation;
    Reservation reservation = reservationCreate(ptr->escaper, ptr->company,
                                                ptr->room, ptr->num_ppl,
                                                ptr->day, ptr->hour,
                                                ptr->price, &reservationError);
    if (reservationError != RESERVATION_SUCCESS) {
        return NULL;
    }
    return reservation;
}

Escaper reservationGetEscaper(Reservation reservation) {
    if (NULL == reservation) {
        return NULL;
    }
    return reservation->escaper;
}

Company reservationGetCompany(Reservation reservation) {
    if (NULL == reservation) {
        return NULL;
    }
    return reservation->company;
}

Room reservationGetRoom(Reservation reservation) {
    if (NULL == reservation) {
        return NULL;
    }
    return reservation->room;
}

int reservationGetNumPpl(Reservation reservation) {
    if (NULL == reservation) {
        return INVALID_PARAMETER;
    }
    return reservation->num_ppl;
}

int reservationGetDay(Reservation reservation) {
    if (NULL == reservation) {
        return INVALID_PARAMETER;
    }
    return reservation->day;
}

int reservationGetHour(Reservation reservation) {
    if (NULL == reservation) {
        return INVALID_PARAMETER;
    }
    return reservation->hour;
}

int reservationGetPrice(Reservation reservation) {
    if (NULL == reservation) {
        return INVALID_PARAMETER;
    }
    return reservation->price;
}

bool isReservationDueDate(ListElement element, ListFilterKey cur_day) {
    Reservation reservation = element;
    if (reservation->day == *(int*) cur_day) {
        return true;
    }
    return false;
}

bool isReservationRelevant(ListElement element, ListFilterKey cur_day) {
    Reservation reservation = element;
    if (reservation->day == *(int*) cur_day) {
        return false;
    }
    return true;
}

int reservationCompareElements(ListElement element1, ListElement element2) {
    if (NULL == element1 || NULL == element2){
        return INVALID_PARAMETER;
    }
    Reservation reservation1 = element1, reservation2 = element2;
    if (reservation1->day < reservation2->day){
        return -1;
    } else if(reservation1->day > reservation2->day){
        return 1;
    }
    assert(reservation1->day == reservation2->day);
    if (reservation1->hour < reservation2->hour){
        return -1;
    } else if(reservation1->hour > reservation2->hour){
        return 1;
    }
    return 0;
}

int reservationCompareForPrint(ListElement element1, ListElement element2) {
    if (NULL == element1 || NULL == element2){
        return INVALID_PARAMETER;
    }
    int hour_cmp = reservationCompareElements(element1, element2);
    if(hour_cmp != 0){
        return hour_cmp;
    }
    Reservation reservation1 = element1, reservation2 = element2;

    TechnionFaculty faculty1 = companyGetFaculty(reservation1->company);
    TechnionFaculty faculty2 = companyGetFaculty(reservation2->company);
    int faculty_cmp = (int)faculty1 - (int)faculty2;
    if(faculty_cmp != 0){
        return faculty_cmp;
    }

    Room room1 = reservation1->room;
    Room room2 = reservation2->room;

    return roomGetID(room1) - roomGetID(room2);
}

