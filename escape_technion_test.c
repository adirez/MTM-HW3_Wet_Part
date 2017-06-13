//
// Created by adire on 09-Jun-17.
//
#include "test_utilities.h"
#include "escape_technion.h"


bool testEscapeTechnionCreateAndDestroy() {
    escapeTechnionDestroy(NULL);

    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    escapeTechnionDestroy(escapeTechnion);

    return true;
}

bool testEscapeTechnionAddCompany() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    ASSERT_TEST(escapeTechnionAddCompany(NULL, PHYSICS,"adi@gmail") ==
                ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS,"adigmail") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS,"adi@gma@") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, UNKNOWN, "adi@gm") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);


    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "@") ==
                ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "@") ==
                ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "adi@") ==
                ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionRemoveCompany() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adi@gmail");

    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "@") ==
                ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "@@") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveCompany(NULL, "adi@gmail") ==
                ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "adi@gmail") ==
                ESCAPE_TECHNION_SUCCESS);

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "sha@hak");
    escapeTechnionAddRoom(escapeTechnion, "sha@hak", 123, 12, 5, "10-20", 10);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    escapeTechnionReservationReceived(escapeTechnion, "adi@", 123, PHYSICS,
                                      "2-10", 5);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "sha@hak") ==
                ESCAPE_TECHNION_RESERVATION_EXISTS);

    escapeTechnionRemoveEscaper(escapeTechnion, "adi@");
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "sha@hak") ==
                ESCAPE_TECHNION_SUCCESS);
    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionAddRoom() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adi@gmail");
    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "sha@hak");

    ASSERT_TEST(escapeTechnionAddRoom(NULL, "adi@gmail", 123, 12,
                5, "10-20", 10) == ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail@", 123, 12,
                5, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "", 123, 12,
                5, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 0, 12,
                5, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", -1, 12,
                5, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 11,
                5, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 0,
                5, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, -1,
                5, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                0, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                -1, "10-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "10+20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "1-20", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "10-203", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "20-19", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "1020", 10) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "10-20", 11) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "10-20", 0) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "10-20", -1) == ESCAPE_TECHNION_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmai", 123, 12,
                5, "10-20", 10) ==
                        ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "10-20", 10) == ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                5, "10-20", 10) == ESCAPE_TECHNION_ID_ALREADY_EXIST);
    //test same id different companies same faculty
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "sha@hak", 123, 4,
                2, "11-13", 7) == ESCAPE_TECHNION_ID_ALREADY_EXIST);


    escapeTechnionDestroy(escapeTechnion);
    return true;
}


bool testEscapeTechnionRemoveRoom() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adi@gmail");

    escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12, 5, "10-20", 10);

    ASSERT_TEST(escapeTechnionRemoveRoom(NULL, 123, PHYSICS) ==
                ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 0, PHYSICS) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, -1, PHYSICS) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 123, UNKNOWN) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 1234, PHYSICS) ==
                ESCAPE_TECHNION_ID_DOES_NOT_EXIST);

    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 123, PHYSICS) ==
                ESCAPE_TECHNION_SUCCESS);

    escapeTechnionRemoveCompany(escapeTechnion, "adi@gmail");

    escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "sha@hak");
    escapeTechnionAddRoom(escapeTechnion, "sha@hak", 12345, 12, 5, "10-20", 10);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    escapeTechnionReservationReceived(escapeTechnion, "adi@", 12345, BIOLOGY,
                                      "2-10", 5);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 12345, BIOLOGY) ==
                ESCAPE_TECHNION_RESERVATION_EXISTS);

    escapeTechnionRemoveEscaper(escapeTechnion, "adi@");
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 12345, BIOLOGY) ==
                ESCAPE_TECHNION_SUCCESS);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}


bool testEscapeTechnionAddEscaper() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    ASSERT_TEST(escapeTechnionAddEscaper(NULL, "adi@", 5, PHYSICS) ==
                ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "", 5, PHYSICS) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@@", 5, PHYSICS) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 11, PHYSICS) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", -1, PHYSICS) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, UNKNOWN) ==
                ESCAPE_TECHNION_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS) ==
                ESCAPE_TECHNION_SUCCESS);

    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 10, BIOLOGY) ==
                ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);

    escapeTechnionRemoveEscaper(escapeTechnion, "adi@");

    escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "@");

    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "@", 10, BIOLOGY) ==
                ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionRemoveEscaper() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    ASSERT_TEST(escapeTechnionRemoveEscaper(NULL, "adi@") ==
                ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "@ad@i@") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "@adi@") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "@") ==
                ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "adi@") ==
                ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);


    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);

    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "adi@") ==
                ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "adi@") ==
                ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionReservationReceived() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "company@");
    escapeTechnionAddRoom(escapeTechnion, "company@", 123, 12, 5, "10-20", 10);
    escapeTechnionAddEscaper(escapeTechnion, "adi@gmail", 5, PHYSICS);
    escapeTechnionAddEscaper(escapeTechnion, "@", 5, PHYSICS);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    escapeTechnionAddEscaper(escapeTechnion, "@gmail", 5, PHYSICS);

    //test Illegal params
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, NULL, 123,
                PHYSICS, "3-4", 5) == ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion,
                "a@di@gmail", 123, PHYSICS, "3-4", 5) ==
                        ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "", 123,
                PHYSICS, "3-4", 5) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                0, PHYSICS, "3-4", 5) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                -1, PHYSICS, "3-4", 5) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, UNKNOWN, "3-4", 5) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "-3-4", 5) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-24", 5) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-30", 5) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-4", 0) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-4", -1) == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionReservationReceived(NULL, "adi@gmail", 123,
                PHYSICS, "3-4", 5) == ESCAPE_TECHNION_NULL_PARAMETER);


    //test wrong email
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "not@exist",
                123, PHYSICS, "3-4", 5) ==
                        ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);

    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "not@exist",
                12, PHYSICS, "3-4", 5) ==
                        ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);

    //test wrong room id
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                12, PHYSICS, "3-4", 5) == ESCAPE_TECHNION_ID_DOES_NOT_EXIST);


    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-10", 5) == ESCAPE_TECHNION_SUCCESS);
    //test client is already in room at that time
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-10", 5) == ESCAPE_TECHNION_CLIENT_IN_ROOM);
    //test reservation out of room's opening hours
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-21", 5) == ESCAPE_TECHNION_ROOM_NOT_AVAILABLE);
    //test same hour and different day reservation
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "2-10", 5) == ESCAPE_TECHNION_SUCCESS);

    //test one hour after reservation that was already booked
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "adi@gmail",
                123, PHYSICS, "3-11", 5) == ESCAPE_TECHNION_SUCCESS);
    //test different escaper when room is not available
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "@", 123,
                PHYSICS, "3-11", 5) == ESCAPE_TECHNION_ROOM_NOT_AVAILABLE);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionRecommendedRoom() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    escapeTechnionAddEscaper(escapeTechnion, "escaper@", 5, CHEMISTRY);

    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "@@") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, NULL) ==
                ESCAPE_TECHNION_NULL_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 0, "escaper@") ==
                ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, -1, "escaper@")
                == ESCAPE_TECHNION_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom(NULL, 5, "escaper@") ==
                ESCAPE_TECHNION_NULL_PARAMETER);

    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "not@exist") ==
                ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST);

    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "escaper@") ==
                ESCAPE_TECHNION_NO_ROOMS_AVAILABLE);

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "company@1");
    escapeTechnionAddCompany(escapeTechnion, MATHEMATICS, "company@2");
    escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "company@3");

    escapeTechnionAddRoom(escapeTechnion, "company@1", 1, 4, 5, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@1", 2, 4, 5, "08-10", 7);


    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "escaper@") ==
                ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@",
                1, PHYSICS, "0-08", 5) == ESCAPE_TECHNION_CLIENT_IN_ROOM);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@",
                1, PHYSICS, "0-09", 5) == ESCAPE_TECHNION_SUCCESS);

    escapeTechnionAddRoom(escapeTechnion, "company@1", 3, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@1", 4, 4, 4, "08-10", 4);

    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "escaper@") ==
                ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@",
                4, PHYSICS, "1-08", 5) == ESCAPE_TECHNION_CLIENT_IN_ROOM);

    escapeTechnionAddRoom(escapeTechnion, "company@2", 5, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@3", 6, 4, 7, "08-10", 6);

    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "escaper@") ==
                ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@",
                6, BIOLOGY, "1-09", 5) == ESCAPE_TECHNION_CLIENT_IN_ROOM);

    escapeTechnionAddRoom(escapeTechnion, "company@1", 7, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@3", 8, 4, 7, "08-10", 6);

    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "escaper@") ==
                ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@",
                8, BIOLOGY, "2-08", 5) == ESCAPE_TECHNION_CLIENT_IN_ROOM);

    escapeTechnionAddRoom(escapeTechnion, "company@2", 9, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@2", 10, 4, 7, "08-10", 6);

    ASSERT_TEST(escapeTechnionRecommendedRoom(escapeTechnion, 5, "escaper@") ==
                ESCAPE_TECHNION_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@",
                9, MATHEMATICS, "2-09", 5) == ESCAPE_TECHNION_CLIENT_IN_ROOM);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionReportDay() {
    EscapeTechnion escapeTechnion = escapeTechnionCreate();

    escapeTechnionAddEscaper(escapeTechnion, "adi@", 1, BIOLOGY);
    escapeTechnionAddEscaper(escapeTechnion, "shahak@", 5, MEDICINE);
    escapeTechnionAddEscaper(escapeTechnion, "cenzor@", 10, MATHEMATICS);

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "company@1");
    escapeTechnionAddCompany(escapeTechnion, MATHEMATICS, "company@2");
    escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "company@3");

    escapeTechnionAddRoom(escapeTechnion, "company@1", 11, 4, 1, "14-16", 10);

    escapeTechnionAddRoom(escapeTechnion, "company@2", 21, 8, 10, "02-08", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@2", 22, 12, 4, "11-23", 7);
    escapeTechnionAddRoom(escapeTechnion, "company@2", 23, 4, 5, "00-03", 2);
    escapeTechnionAddRoom(escapeTechnion, "company@2", 24, 20, 6, "08-10", 1);

    escapeTechnionAddRoom(escapeTechnion, "company@3", 31, 40, 3, "08-11", 9);
    escapeTechnionAddRoom(escapeTechnion, "company@3", 32, 16, 2, "10-11", 3);

    escapeTechnionReservationReceived(escapeTechnion, "adi@", 11,
                                      PHYSICS, "0-14", 2);

    escapeTechnionReservationReceived(escapeTechnion, "shahak@", 23,
                                      MATHEMATICS, "0-2", 5);

    escapeTechnionReservationReceived(escapeTechnion, "shahak@", 31,
                                      BIOLOGY, "2-10", 2);

    escapeTechnionReservationReceived(escapeTechnion, "adi@", 21,
                                      MATHEMATICS, "1-2", 6);

    escapeTechnionReportDay(escapeTechnion, stdout);

    escapeTechnionRecommendedRoom(escapeTechnion, 5, "cenzor@");

    escapeTechnionReservationReceived(escapeTechnion, "adi@", 23,
                                      MATHEMATICS, "0-2", 1);

    escapeTechnionReportDay(escapeTechnion, stdout);
    escapeTechnionReportDay(escapeTechnion, stdout);

    //TODO: add test for NULL output channel
    ASSERT_TEST(escapeTechnionReportDay(NULL, stdout) ==
                        ESCAPE_TECHNION_NULL_PARAMETER);


    escapeTechnionDestroy(escapeTechnion);
    return true;
}

int main(int argv, char **arc) {

    RUN_TEST(testEscapeTechnionCreateAndDestroy);
    RUN_TEST(testEscapeTechnionAddCompany);
    RUN_TEST(testEscapeTechnionRemoveCompany);
    RUN_TEST(testEscapeTechnionAddRoom);
    RUN_TEST(testEscapeTechnionRemoveRoom);
    RUN_TEST(testEscapeTechnionAddEscaper);
    RUN_TEST(testEscapeTechnionRemoveEscaper);
    RUN_TEST(testEscapeTechnionReservationReceived);
    RUN_TEST(testEscapeTechnionRecommendedRoom);
    RUN_TEST(testEscapeTechnionReportDay);

    return 0;
}