//
// Created by adire on 09-Jun-17.
//
#include "test_utilities.h"
#include "escape_technion.h"
#include <string.h>
#include <stdlib.h>

bool testEscapeTechnionDestroy() {
    ASSERT_TEST(escapeTechnionDestroy(NULL) == MTM_NULL_PARAMETER);

    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate(&EscapeTechnionError);
    ASSERT_TEST(escapeTechnionDestroy(escapeTechnion) == MTM_SUCCESS);

    return true;
}

bool testEscapeTechnionAddCompany() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate(&EscapeTechnionError);

    ASSERT_TEST(escapeTechnionAddCompany(NULL, "adi@gmail", PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, "adigmail", PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, "adi@gma@", PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, "", PHYSICS) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, "adi@gm", UNKNOWN) ==
                MTM_INVALID_PARAMETER);


    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, "@", PHYSICS) ==
                MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionAddCompany(escapeTechnion, "@", PHYSICS) ==
                MTM_EMAIL_ALREADY_EXISTS);

    escapeTechnionRemoveCompany(escapeTechnion, "@");
    escapeTechnionDestroy(escapeTechnion);

    return true;
}

//TODO: add checks for a room with reservation
bool testEscapeTechnionRemoveCompany() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate(&EscapeTechnionError);

    escapeTechnionAddCompany(escapeTechnion, "adi@gmail", PHYSICS);

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

    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionAddRoom() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate(&EscapeTechnionError);

    escapeTechnionAddCompany(escapeTechnion, "adi@gmail", PHYSICS);

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
                                      -1, "10-20", 10) ==
                MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10+20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "1-20", 10) == MTM_INVALID_PARAMETER);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-203", 10) ==
                MTM_INVALID_PARAMETER);
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
                                      5, "10-20", 10) ==
                MTM_COMPANY_EMAIL_DOES_NOT_EXIST);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-20", 10) == MTM_SUCCESS);
    ASSERT_TEST(escapeTechnionAddRoom(escapeTechnion, "adi@gmail", 123, 12,
                                      5, "10-20", 10) == MTM_ID_ALREADY_EXIST);


    escapeTechnionRemoveRoom(escapeTechnion, 123, PHYSICS);
    escapeTechnionRemoveCompany(escapeTechnion, "adi@gmail");
    escapeTechnionDestroy(escapeTechnion);
    return true;
}

//TODO: add reservation tests
bool testEscapeTechnionRemoveRoom() {
    MtmErrorCode EscapeTechnionError;
    EscapeTechnion escapeTechnion = escapeTechnionCreate(&EscapeTechnionError);

    escapeTechnionAddCompany(escapeTechnion, "adi@gmail", PHYSICS);

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
    escapeTechnionDestroy(escapeTechnion);
    return true;
}

bool testEscapeTechnionAddEscaper() {

    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testEscapeTechnionDestroy);
    RUN_TEST(testEscapeTechnionAddCompany);
    RUN_TEST(testEscapeTechnionRemoveCompany);
    RUN_TEST(testEscapeTechnionAddRoom);
    RUN_TEST(testEscapeTechnionRemoveRoom);
    RUN_TEST(testEscapeTechnionAddEscaper);

    return 0;
}