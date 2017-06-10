//
// Created by adire on 10-Jun-17.
//

#include "test_utilities.h"
#include "reservation.h"

bool testReservationCreate() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;
    RoomErrorCode roomErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate("@", PHYSICS, &companyErrorCode);
    Room room = roomCreate("@", 123, 12, 20, 1, 2, 1, &roomErrorCode);


    ASSERT_TEST(reservationCreate(NULL, company, room, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == RESERVATION_INVALID_PARAMETER);
    ASSERT_TEST(reservationCreate(escaper, NULL, room, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == RESERVATION_INVALID_PARAMETER);
    ASSERT_TEST(reservationCreate(escaper, company, NULL, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == RESERVATION_INVALID_PARAMETER);

    escaperDestroy(escaper);
    roomDestroy(room);
    companyDestroy(company);
    return true;
}

bool testReservationDestroy() {
    ASSERT_TEST(reservationDestroy(NULL) == RESERVATION_INVALID_PARAMETER);

    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;
    RoomErrorCode roomErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate("@", PHYSICS, &companyErrorCode);
    Room room = roomCreate("@", 123, 12, 20, 1, 2, 1, &roomErrorCode);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);
    ASSERT_TEST(reservationErrorCode == RESERVATION_SUCCESS);

    ASSERT_TEST(reservationDestroy(reservation) == RESERVATION_SUCCESS);

    escaperDestroy(escaper);
    roomDestroy(room);
    companyDestroy(company);
    return true;
}

bool testReservationCopyElement() {
    ASSERT_TEST(reservationCopyElement(NULL) == NULL);

    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;
    RoomErrorCode roomErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate("@", PHYSICS, &companyErrorCode);
    Room room = roomCreate("@", 123, 12, 20, 1, 2, 1, &roomErrorCode);

    Reservation reservation1 = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);

    Reservation reservation2 = reservationCopyElement(reservation1);
    ASSERT_TEST(reservationGetCompany(reservation1, &reservationErrorCode) ==
                reservationGetCompany(reservation2, &reservationErrorCode));
    ASSERT_TEST(reservationGetEscaper(reservation1, &reservationErrorCode) ==
                reservationGetEscaper(reservation2, &reservationErrorCode));
    ASSERT_TEST(reservationGetRoom(reservation1, &reservationErrorCode) ==
                reservationGetRoom(reservation2, &reservationErrorCode));

    reservationDestroy(reservation1);
    reservationDestroy(reservation2);

    escaperDestroy(escaper);
    roomDestroy(room);
    companyDestroy(company);
    return true;
}

bool testReservationGetEscaper() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;
    RoomErrorCode roomErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate("@", PHYSICS, &companyErrorCode);
    Room room = roomCreate("@", 123, 12, 20, 1, 2, 1, &roomErrorCode);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                 14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationGetEscaper(NULL, &reservationErrorCode) == NULL);

    ASSERT_TEST(reservationGetEscaper(reservation, &reservationErrorCode) ==
                        escaper);

    escaperDestroy(escaper);
    roomDestroy(room);
    companyDestroy(company);
    reservationDestroy(reservation);
    return true;
}

bool testReservationGetCompany() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;
    RoomErrorCode roomErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate("@", PHYSICS, &companyErrorCode);
    Room room = roomCreate("@", 123, 12, 20, 1, 2, 1, &roomErrorCode);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationGetCompany(NULL, &reservationErrorCode) == NULL);

    ASSERT_TEST(reservationGetCompany(reservation, &reservationErrorCode) ==
                company);

    escaperDestroy(escaper);
    roomDestroy(room);
    companyDestroy(company);
    reservationDestroy(reservation);
    return true;
}

bool testReservationGetRoom() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;
    RoomErrorCode roomErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate("@", PHYSICS, &companyErrorCode);
    Room room = roomCreate("@", 123, 12, 20, 1, 2, 1, &roomErrorCode);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationGetEscaper(NULL, &reservationErrorCode) == NULL);

    ASSERT_TEST(reservationGetRoom(reservation, &reservationErrorCode) ==
                room);

    escaperDestroy(escaper);
    roomDestroy(room);
    companyDestroy(company);
    reservationDestroy(reservation);
    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testReservationCreate);
    RUN_TEST(testReservationDestroy);
    RUN_TEST(testReservationCopyElement);
    RUN_TEST(testReservationGetEscaper);
    RUN_TEST(testReservationGetCompany);
    RUN_TEST(testReservationGetRoom);

    return 0;
}