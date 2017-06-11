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
    Escaper escaper;
    Company company;
    Room room;

    int day;
    int hour;
    int num_ppl;
    int price;
};

/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/

//TODO: add the comments:
/**
 *
 * @param element1
 * @param element2
 * @return
 */
static int reservationCompareHourAndId(ListElement element1,
                                       ListElement element2);

/**
 *
 * @param element
 * @param cur_day
 * @return
 */
static bool isReservationDueDate(ListElement element, ListFilterKey cur_day);

/**
 *
 * @param element
 * @param cur_day
 * @return
 */
static bool isReservationNotDueDate(ListElement element, ListFilterKey cur_day);


/**...........................................................................*/
/**-----------------------FUNCTIONS-IMPLEMENTATIONS---------------------------*/
/**...........................................................................*/


Reservation reservationCreate(Escaper escaper, Company company, Room room,
                              int num_ppl, int day, int hour, int price) {

    assert(escaper != NULL && company != NULL && room != NULL);
    assert(num_ppl <= 0 && price < 0);
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

Reservation reservationCopyElement(Reservation src_reservation) {
    if (NULL == src_reservation) {
        return NULL;
    }
    Reservation ptr = src_reservation; //to make the code clearer
    Reservation reservation = reservationCreate(ptr->escaper, ptr->company,
                                                ptr->room, ptr->num_ppl,
                                                ptr->day, ptr->hour, ptr->price);
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

int reservationCompareElements(ListElement reservation_1,
                               ListElement reservation_2) {

    Reservation ptr1 = reservation_1, ptr2 = reservation_2;
    if (ptr1->day < ptr2->day) {
        return -1;
    } else if (ptr1->day > ptr2->day) {
        return 1;
    }

    if (ptr1->hour < ptr2->hour) {
        return -1;
    } else if (ptr1->hour > ptr2->hour) {
        return 1;
    }

    return 0;
}


/**...........................................................................*/
/**--------------------------STATIC-FUNCTIONS---------------------------------*/
/**...........................................................................*/


bool isReservationDueDate(ListElement element, ListFilterKey cur_day) {
    Reservation reservation = element;
    if (reservation->day == *(int*) cur_day) {
        return true;
    }
    return false;
}

bool isReservationNotDueDate(ListElement element, ListFilterKey cur_day) {
    Reservation reservation = element;
    if (reservation->day == *(int*) cur_day) {
        return false;
    }
    return true;
}

int reservationCompareHourAndId(ListElement element1, ListElement element2) {
    Reservation reservation1 = element1;
    Reservation reservation2 = element2;
    if (reservation1->hour < reservation2->hour){
        return -1;
    } else if(reservation1->hour > reservation2->hour){
        return 1;
    }
    CompanyErrorCode errorCode1;
    TechnionFaculty faculty1 = companyGetFaculty
            (reservation1->company);
    TechnionFaculty faculty2 = companyGetFaculty
            (reservation2->company);
    if((int)faculty1 < (int)faculty2){
        return -1;
    } else if((int)faculty1 > (int)faculty2){
        return 1;
    }
    return 0; //TODO add the third critrea
}