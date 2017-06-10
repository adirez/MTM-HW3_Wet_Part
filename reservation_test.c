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
    ASSERT_TEST(reservationErrorCode == ROOM_INVALID_PARAMETER);
    ASSERT_TEST(reservationCreate(escaper, NULL, room, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == ROOM_INVALID_PARAMETER);
    ASSERT_TEST(reservationCreate(escaper, company, NULL, 5, 2, 14, 4,
                                  &reservationErrorCode) == NULL);
    ASSERT_TEST(reservationErrorCode == ROOM_INVALID_PARAMETER);

    escaperDestroy(escaper);
    roomDestroy(room);
    companyDestroy(company);

    return true;
}

bool testReservationDestroy() {

    return true;
}

bool testReservationFreeElement() {

    return true;
}

bool testReservationCopyElement() {

    return true;
}

bool testReservationGetEscaper() {

    return true;
}

bool testReservationGetCompany() {

    return true;
}

bool testReservationGetRoom() {

    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testReservationCreate);
    RUN_TEST(testReservationDestroy);
    RUN_TEST(testReservationFreeElement);
    RUN_TEST(testReservationCopyElement);
    RUN_TEST(testReservationGetEscaper);
    RUN_TEST(testReservationGetCompany);
    RUN_TEST(testReservationGetRoom);

    return 0;
}