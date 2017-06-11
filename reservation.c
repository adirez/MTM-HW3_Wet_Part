//
// Created by Shahak on 06/06/2017.
//

#include <stdlib.h>
#include <assert.h>

#include "reservation.h"
#include "utils.h"

#define INVALID_PARAMETER -1

struct Reservation_t {
    TechnionFaculty Faculty;
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
                              int num_ppl, int day, int hour, int price) {
    assert(escaper != NULL && company != NULL && room != NULL);
    assert(isValidReservationParams(num_ppl, price));

    Reservation reservation = malloc(sizeof(*reservation));
    if (NULL == reservation) {
        return NULL;
    }

    reservation->escaper = escaper;
    reservation->company = company;
    reservation->room = room;

    reservation->num_ppl = num_ppl;
    reservation->day = day;
    reservation->hour = hour;
    reservation->price = price;
    return reservation;
}


void reservationDestroy(ListElement reservation) {
    if(NULL == reservation){
        return;
    }
    free(reservation);
}

ListElement reservationCopyElement(ListElement src_element) {
    if (NULL == src_element) {
        return NULL;
    }
    Reservation ptr = src_element;
    Reservation reservation = reservationCreate(ptr->escaper, ptr->company,
                                                ptr->room, ptr->num_ppl,
                                                ptr->day,ptr->hour, ptr->price);
    if (NULL == reservation) {
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

int reservationGetNumPpl(Reservation reservation) {
    if (NULL == reservation) {
        return INVALID_PARAMETER;
    }
    return reservation->num_ppl;
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

int reservationCompareForPrint(ListElement element1, ListElement element2) {
    Reservation reservation1 = element1, reservation2 = element2;
    if (reservation1->hour < reservation2->hour){
        return -1;
    } else if(reservation1->hour > reservation2->hour){
        return 1;
    }
    TechnionFaculty faculty1 = companyGetFaculty(reservation1->company);
    TechnionFaculty faculty2 = companyGetFaculty(reservation2->company);
    if((int)faculty1 < (int)faculty2){
        return -1;
    } else if((int)faculty1 > (int)faculty2){
        return 1;
    }

    return 0; //TODO add the third critrea
}

int reservationCompareElements(ListElement element1, ListElement element2) {
    Reservation reservation1 = element1, reservation2 = element2;
    if (reservation1->day < reservation2->day){
        return -1;
    } else if(reservation1->day > reservation2->day){
        return 1;
    }
    assert(reservation1->day == reservation2->day);
    if (reservation1->hour < reservation2->hour){
        return -1;
    } else if(reservation1->hour == reservation2->hour){
        return 1;
    }
    return 0;
}