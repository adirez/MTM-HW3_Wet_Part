//
// Created by adire on 10-Jun-17.
//

#include "test_utilities.h"
#include "reservation.h"

bool testReservationCreate() {
    ASSERT_TEST(reservationCreate(NULL, NULL, NULL, 5, 2, 14, 4, NULL) == NULL);
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company, 123, 8, 5, 10, 20, 2);
    Room room = companyGetRoomByID(company, 123);

    ASSERT_TEST(reservationCreate(NULL, company, room, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == RESERVATION_NULL_PARAMETER);
    ASSERT_TEST(reservationCreate(escaper, NULL, room, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == RESERVATION_NULL_PARAMETER);
    ASSERT_TEST(reservationCreate(escaper, company, NULL, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == RESERVATION_NULL_PARAMETER);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);
    ASSERT_TEST(reservation != NULL);
    ASSERT_TEST(reservationErrorCode == RESERVATION_SUCCESS);

    escaperDestroy(escaper);
    reservationDestroy(reservation);
    companyDestroy(company);
    return true;
}

bool testReservationDestroy() {
    reservationDestroy(NULL);

    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company, 123, 8, 5, 10, 20, 2);
    Room room = companyGetRoomByID(company, 123);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);
    ASSERT_TEST(reservationErrorCode == RESERVATION_SUCCESS);

    escaperDestroy(escaper);
    reservationDestroy(reservation);
    companyDestroy(company);
    return true;
}

bool testReservationCopyElement() {
    ASSERT_TEST(reservationCopyElement(NULL) == NULL);

    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company, 123, 8, 5, 10, 20, 2);
    Room room = companyGetRoomByID(company, 123);

    Reservation reservation1 = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);

    Reservation reservation2 = reservationCopyElement(reservation1);
    ASSERT_TEST(reservationGetCompany(reservation1) ==
                        reservationGetCompany(reservation2));
    ASSERT_TEST(reservationGetEscaper(reservation1) ==
                        reservationGetEscaper(reservation2));
    ASSERT_TEST(reservationGetRoom(reservation1) ==
                        reservationGetRoom(reservation2));

    reservationDestroy(reservation1);
    reservationDestroy(reservation2);
    escaperDestroy(escaper);
    companyDestroy(company);
    return true;
}

bool testReservationGetters() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company, 123, 8, 5, 10, 20, 2);
    Room room = companyGetRoomByID(company, 123);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                 14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationGetEscaper(NULL) == NULL);
    ASSERT_TEST(reservationGetCompany(NULL) == NULL);
    ASSERT_TEST(reservationGetRoom(NULL) == NULL);
    ASSERT_TEST(reservationGetDay(NULL) == -1);
    ASSERT_TEST(reservationGetHour(NULL) == -1);
    ASSERT_TEST(reservationGetNumPpl(NULL) == -1);
    ASSERT_TEST(reservationGetPrice(NULL) == -1);

    ASSERT_TEST(reservationGetEscaper(reservation) == escaper);
    ASSERT_TEST(reservationGetCompany(reservation) == company);
    ASSERT_TEST(reservationGetRoom(reservation) == room);
    ASSERT_TEST(reservationGetNumPpl(reservation) == 5);
    ASSERT_TEST(reservationGetDay(reservation) == 2);
    ASSERT_TEST(reservationGetHour(reservation) == 14);
    ASSERT_TEST(reservationGetPrice(reservation) == 4);

    reservationDestroy(reservation);
    escaperDestroy(escaper);
    companyDestroy(company);
    return true;
}

bool testIsReservationDueDate() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company, 123, 8, 5, 10, 20, 2);
    Room room = companyGetRoomByID(company, 123);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);
    int cur_day = 2, not_cur_day = 1;
    ASSERT_TEST(isReservationDueDate(reservation, &cur_day) == true);
    ASSERT_TEST(isReservationDueDate(reservation, &not_cur_day) == false);

    reservationDestroy(reservation);
    escaperDestroy(escaper);
    companyDestroy(company);
    return true;
}

bool testIsReservationRelevant() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company, 123, 8, 5, 10, 20, 2);
    Room room = companyGetRoomByID(company, 123);

    Reservation reservation = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);
    int cur_day = 2, not_cur_day = 1;
    ASSERT_TEST(isReservationRelevant(reservation, &cur_day) == false);
    ASSERT_TEST(isReservationRelevant(reservation, &not_cur_day) == true);

    reservationDestroy(reservation);
    escaperDestroy(escaper);
    companyDestroy(company);
    return true;
}

bool testReservationCompareElements() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company, 123, 8, 5, 10, 20, 2);
    Room room = companyGetRoomByID(company, 123);

    Reservation reservation1 = reservationCreate(escaper, company, room, 5, 3,
                                                14, 4, &reservationErrorCode);
    Reservation reservation2 = reservationCreate(escaper, company, room, 5, 2,
                                                14, 4, &reservationErrorCode);
    Reservation reservation3 = reservationCreate(escaper, company, room, 5, 3,
                                                 16, 4, &reservationErrorCode);
    Reservation reservation4 = reservationCreate(escaper, company, room, 5, 3,
                                                 14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationCompareElements(reservation1, reservation2) == 1);
    ASSERT_TEST(reservationCompareElements(reservation1, reservation3) == -1);
    ASSERT_TEST(reservationCompareElements(reservation1, reservation4) == 0);

    reservationDestroy(reservation1);
    reservationDestroy(reservation2);
    reservationDestroy(reservation3);
    reservationDestroy(reservation4);
    escaperDestroy(escaper);
    companyDestroy(company);
    return true;
}

bool testReservationCompareForPrint() {
    ReservationErrorCode reservationErrorCode;
    EscaperErrorCode escaperErrorCode;
    CompanyErrorCode companyErrorCode;

    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &escaperErrorCode);
    Company company1 = companyCreate(PHYSICS, "@", &companyErrorCode);
    companyAddRoom(company1, 123, 8, 5, 10, 20, 2);
    Room room1 = companyGetRoomByID(company1, 123);


    Reservation reservation1 = reservationCreate(escaper, company1, room1, 5, 3,
                                                 14, 4, &reservationErrorCode);
    Reservation reservation2 = reservationCreate(escaper, company1, room1, 5, 2,
                                                 14, 4, &reservationErrorCode);
    Reservation reservation3 = reservationCreate(escaper, company1, room1, 5, 3,
                                                 16, 4, &reservationErrorCode);
    Reservation reservation4 = reservationCreate(escaper, company1, room1, 5, 3,
                                                 14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationCompareForPrint(reservation1, reservation2) > 0);
    ASSERT_TEST(reservationCompareForPrint(reservation1, reservation3) < 0);
    ASSERT_TEST(reservationCompareForPrint(reservation1, reservation4) == 0);

    Company company2 = companyCreate(BIOLOGY, "2@", &companyErrorCode);
    companyAddRoom(company2, 123, 8, 5, 10, 20, 2);
    Room room2 = companyGetRoomByID(company2, 123);

    Reservation reservation5 = reservationCreate(escaper, company2, room2, 5, 3,
                                                 14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationCompareForPrint(reservation1, reservation5) < 0);

    companyAddRoom(company1, 122, 8, 5, 10, 20, 2);
    Room room3 = companyGetRoomByID(company1, 122);

    Reservation reservation6 = reservationCreate(escaper, company1, room3, 5, 3,
                                                 14, 4, &reservationErrorCode);

    ASSERT_TEST(reservationCompareForPrint(reservation1, reservation6) > 0);

    reservationDestroy(reservation1);
    reservationDestroy(reservation2);
    reservationDestroy(reservation3);
    reservationDestroy(reservation4);
    reservationDestroy(reservation5);
    reservationDestroy(reservation6);
    escaperDestroy(escaper);
    companyDestroy(company1);
    companyDestroy(company2);
    return true;


    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testReservationCreate);
    RUN_TEST(testReservationDestroy);
    RUN_TEST(testReservationCopyElement);
    RUN_TEST(testReservationGetters);
    RUN_TEST(testIsReservationDueDate);
    RUN_TEST(testIsReservationRelevant);
    RUN_TEST(testReservationCompareElements);
    RUN_TEST(testReservationCompareForPrint);

    return 0;
}