//
// Created by adire on 09-Jun-17.
//
#include "test_utilities.h"
#include "escape_technion.h"
#include <string.h>
#include <stdlib.h>

//TODO: add test create with different inout channels

bool testEscapeTechnionDestroy() {
    ASSERT_TEST(escapeTechnionDestroy(NULL) == MTM_NULL_PARAMETER);

    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();
    ASSERT_TEST(escapeTechnionDestroy(escapeTechnion) == MTM_SUCCESS);

    return true;
}

bool testEscapeTechnionAddCompany() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    ASSERT_TEST(escapeTechnionAddCompany(NULL, PHYSICS, "adi@gmail") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adigmail") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adi@gma@") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, UNKNOWN, "adi@gm") ==
                MTM_INVALID_PARAMETER);


    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "@") ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, PHYSICS, "@") ==
                MTM_EMAIL_ALREADY_EXISTS);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "adi@") ==
                MTM_EMAIL_ALREADY_EXISTS);

    escapeTechnionRemoveCompany(escapeTechnion, "@");
    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionRemoveCompany() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adi@gmail");

    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "@") ==
                MTM_COMPANY_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "@@") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveCompany(NULL, "adi@gmail") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "adi@gmail") ==
                MTM_SUCCESS);

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "sha@hak");
    escapeTechnionAddRoom(escapeTechnion, "sha@hak", 123, 12, 5, "10-20", 10);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    escapeTechnionReservationReceived(escapeTechnion, "adi@", 123, PHYSICS,
                                      "2-10", 5);
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "sha@hak") ==
                MTM_RESERVATION_EXISTS);

    escapeTechnionRemoveEscaper(escapeTechnion, "adi@");
    ASSERT_TEST(escapeTechnionRemoveCompany(escapeTechnion, "sha@hak") ==
                MTM_SUCCESS);
    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionAddRoom() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adi@gmail");
    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "sha@hak");

    ASSERT_TEST(escapeTechnionAddRoom(NULL, "adi@gmail", 123, 12,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail@", 123, 12,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "", 123, 12,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 0, 12,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", -1, 12,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 11,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 0,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, -1,
                                      5, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      0, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                     -1, "10-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10+20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "1-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                     5, "10-203", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "20-19", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "1020", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-20", 11) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-20", 0) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-20", -1) == MTM_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmai", 123, 12,
                           5, "10-20", 10) == MTM_COMPANY_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-20", 10) == MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-20", 10) == MTM_ID_ALREADY_EXIST);
    //test same id different companies same faculty
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "sha@hak", 123, 4,
                                      2, "11-13", 7) == MTM_ID_ALREADY_EXIST);


    escapeTechnionRemoveRoom(escapeTechnion, 123, PHYSICS);
    escapeTechnionRemoveCompany(escapeTechnion, "adi@gmail");
    escapeTechnionDestroy(escapeTechnion);
    return true;
}


bool testEscapeTechnionRemoveRoom() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "adi@gmail");

    escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12, 5, "10-20", 10);

    ASSERT_TEST(escapeTechnionRemoveRoom(NULL, 123, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 0, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, -1, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 123, UNKNOWN) ==
                MTM_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 1234, PHYSICS) ==
                MTM_ID_DOES_NOT_EXIST);

    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 123, PHYSICS) ==
                MTM_SUCCESS);

    escapeTechnionRemoveCompany(escapeTechnion, "adi@gmail");

    escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "sha@hak");
    escapeTechnionAddRoom(escapeTechnion, "sha@hak", 12345, 12, 5, "10-20", 10);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    escapeTechnionReservationReceived(escapeTechnion, "adi@", 12345, BIOLOGY,
                                      "2-10", 5);
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 12345, BIOLOGY) ==
                MTM_RESERVATION_EXISTS);

    escapeTechnionRemoveEscaper(escapeTechnion, "adi@");
    ASSERT_TEST(escapeTechnionRemoveRoom(escapeTechnion, 12345, BIOLOGY) ==
                MTM_SUCCESS);

    escapeTechnionRemoveCompany(escapeTechnion, "adi@");
    escapeTechnionDestroy(escapeTechnion);
    return true;
}


bool testEscapeTechnionAddEscaper() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    ASSERT_TEST(escapeTechnionAddEscaper(NULL, "adi@", 5, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "", 5, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@@", 5, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 11, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", -1, PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, UNKNOWN) ==
                MTM_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS) ==
                MTM_SUCCESS);

    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "adi@", 10, BIOLOGY) ==
                MTM_EMAIL_ALREADY_EXISTS);

    escapeTechnionRemoveEscaper(escapeTechnion, "adi@");

    escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "@");

    ASSERT_TEST(escapeTechnionAddEscaper(escapeTechnion, "@", 10, BIOLOGY) ==
                MTM_EMAIL_ALREADY_EXISTS);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionRemoveEscaper() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    ASSERT_TEST(escapeTechnionRemoveEscaper(NULL, "adi@") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "@ad@i@") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "@adi@") ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "") ==
                MTM_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "@") ==
                MTM_CLIENT_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "adi@") ==
                MTM_CLIENT_EMAIL_DOES_NOT_EXIST);


    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);

    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "adi@") ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionRemoveEscaper(escapeTechnion, "adi@") ==
                MTM_CLIENT_EMAIL_DOES_NOT_EXIST);

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionReservationReceived() {
    MtmErrorCode EscapeTechnionError;

    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "company@");
    escapeTechnionAddRoom(escapeTechnion, "company@", 123, 12, 5, "10-20", 10);
    escapeTechnionAddEscaper(escapeTechnion, "adi@gmail", 5, PHYSICS);
    escapeTechnionAddEscaper(escapeTechnion, "@", 5, PHYSICS);
    escapeTechnionAddEscaper(escapeTechnion, "adi@", 5, PHYSICS);
    escapeTechnionAddEscaper(escapeTechnion, "@gmail", 5, PHYSICS);

    //test Illegal params
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, NULL, 123,
                                                  PHYSICS, "3-4", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "a@di@gmail", 123,
                                              PHYSICS, "3-4", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "", 123, PHYSICS,
                                              "3-4", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 0,
                                              PHYSICS, "3-4", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", -1,
                                              PHYSICS, "3-4", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              UNKNOWN, "3-4", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "-3-4", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-24", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-30", 5) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-4", 0) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-4", -1) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(
            escapeTechnionReservationReceived(NULL, "adi@gmail", 123, PHYSICS,
                                              "3-4", 5) == MTM_INVALID_PARAMETER);


    //test wrong email
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "not@exist", 123,
                                              PHYSICS, "3-4", 5) == MTM_CLIENT_EMAIL_DOES_NOT_EXIST);

    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "not@exist", 12,
                                              PHYSICS, "3-4", 5) == MTM_CLIENT_EMAIL_DOES_NOT_EXIST);

    //test wrong room id
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 12,
                                              PHYSICS, "3-4", 5) == MTM_ID_DOES_NOT_EXIST);


    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-10", 5) == MTM_SUCCESS);
    //test client is already in room at that time
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-10", 5) == MTM_CLIENT_IN_ROOM);
    //test reservation out of room's opening hours
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-21", 5) == MTM_ROOM_NOT_AVAILABLE);
    //test same hour and different day reservation
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "2-10", 5) == MTM_SUCCESS);

    //test one hour after reservation that was already booked
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "adi@gmail", 123,
                                              PHYSICS, "3-11", 5) == MTM_SUCCESS);
    //test different escaper when room is not available
    ASSERT_TEST(
            escapeTechnionReservationReceived(escapeTechnion, "@", 123, PHYSICS,
                                              "3-11", 5) == MTM_ROOM_NOT_AVAILABLE);

    escapeTechnionRemoveCompany(escapeTechnion, "company");
    escapeTechnionRemoveRoom(escapeTechnion, 123, PHYSICS);
    escapeTechnionRemoveEscaper(escapeTechnion, "adi@gmail");
    escapeTechnionRemoveEscaper(escapeTechnion, "@");
    escapeTechnionRemoveEscaper(escapeTechnion, "adi@");
    escapeTechnionRemoveEscaper(escapeTechnion, "@gmail");
    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionRecommendedRoom() {
    MtmErrorCode EscapeTechnionError;

    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    escapeTechnionAddEscaper(escapeTechnion, "escaper@", 5, CHEMISTRY);


    ASSERT_TEST(escapeTechnionRecommendedRoom("@@", 5, escapeTechnion) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom(NULL, 5, escapeTechnion) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom("", 5, escapeTechnion) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 0, escapeTechnion) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", -1, escapeTechnion)
                == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 5, NULL) ==
                MTM_INVALID_PARAMETER);

    ASSERT_TEST(escapeTechnionRecommendedRoom("not@exist", 5, escapeTechnion) ==
                MTM_CLIENT_EMAIL_DOES_NOT_EXIST);

    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 5, escapeTechnion) ==
                MTM_NO_ROOMS_AVAILABLE);

    escapeTechnionAddCompany(escapeTechnion, PHYSICS, "company@1");
    escapeTechnionAddCompany(escapeTechnion, MATHEMATICS, "company@2");
    escapeTechnionAddCompany(escapeTechnion, BIOLOGY, "company@3");

    escapeTechnionAddRoom(escapeTechnion, "company@1", 1, 4, 5, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@1", 2, 4, 5, "08-10", 7);


    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 5, escapeTechnion) ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@", 1,
                                                  PHYSICS, "0-08", 5) == MTM_CLIENT_IN_ROOM);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@", 1,
                                                  PHYSICS, "0-09", 5) == MTM_SUCCESS);

    escapeTechnionAddRoom(escapeTechnion, "company@1", 3, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@1", 4, 4, 4, "08-10", 4);

    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 5, escapeTechnion) ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@", 4,
                                                  PHYSICS, "1-08", 5) == MTM_CLIENT_IN_ROOM);

    escapeTechnionAddRoom(escapeTechnion, "company@2", 5, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@3", 6, 4, 7, "08-10", 6);

    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 5, escapeTechnion) ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@", 6,
                                                  BIOLOGY, "1-09", 5) == MTM_CLIENT_IN_ROOM);

    escapeTechnionAddRoom(escapeTechnion, "company@1", 7, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@3", 8, 4, 7, "08-10", 6);

    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 5, escapeTechnion) ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@", 8,
                                                  BIOLOGY, "2-08", 5) == MTM_CLIENT_IN_ROOM);

    escapeTechnionAddRoom(escapeTechnion, "company@2", 9, 4, 7, "08-10", 6);
    escapeTechnionAddRoom(escapeTechnion, "company@2", 10, 4, 7, "08-10", 6);

    ASSERT_TEST(escapeTechnionRecommendedRoom("escaper@", 5, escapeTechnion) ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionReservationReceived(escapeTechnion, "escaper@", 9,
                                                  MATHEMATICS, "2-09", 5) == MTM_CLIENT_IN_ROOM);

    escapeTechnionRemoveEscaper(escapeTechnion, "escaper@");
    escapeTechnionRemoveCompany(escapeTechnion, "company@1");
    escapeTechnionRemoveCompany(escapeTechnion, "company@2");
    escapeTechnionRemoveCompany(escapeTechnion, "company@3");
    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionRecommendedRoom() {
    MtmErrorCode EscapeTechnionError;

    EscapeTechnion escapeTechnion = escapeTechnionCreate
            ();

    return true;
}

int main(int argv, char **arc) {

    RUN_TEST(testEscapeTechnionDestroy);
    RUN_TEST(testEscapeTechnionAddCompany);
    RUN_TEST(testEscapeTechnionRemoveCompany);
    RUN_TEST(testEscapeTechnionAddRoom);
    RUN_TEST(testEscapeTechnionRemoveRoom);
    RUN_TEST(testEscapeTechnionAddEscaper);
    RUN_TEST(testEscapeTechnionRemoveEscaper);
    RUN_TEST(testEscapeTechnionReservationReceived);
    RUN_TEST(testEscapeTechnionRecommendedRoom);
    RUN_TEST(testEscapeTechnionRecommendedRoom);

    return 0;
}