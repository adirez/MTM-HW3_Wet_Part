//
// Created by adire on 09-Jun-17.
//
#include "test_utilities.h"
#include "escaper.h"
#include <string.h>
#include <stdlib.h>


bool testEscaperCreate() {
    ASSERT_TEST(escaperCreate(NULL, PHYSICS, 5, NULL) == NULL);
    EscaperErrorCode errorCode;
    ASSERT_TEST(escaperCreate(NULL, PHYSICS, 5, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ESCAPER_NULL_PARAMETER);
    ASSERT_TEST(escaperCreate("adi", PHYSICS, 5, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);
    ASSERT_TEST(escaperCreate("adi@gmail", UNKNOWN, 5, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);
    ASSERT_TEST(escaperCreate("adi@gmail", PHYSICS, 11, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);
    ASSERT_TEST(escaperCreate("adi@gmail", PHYSICS, 0, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);

    return true;
}

bool testEscaperDestroy() {
    escaperDestroy(NULL);

    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    ASSERT_TEST(errorCode == ESCAPER_SUCCESS);
    escaperDestroy(escaper);

    return true;
}

bool testEscaperCompareElements() {
    EscaperErrorCode errorCode;
    Escaper escaper1 = escaperCreate("abc@", PHYSICS, 5, &errorCode);
    Escaper escaper2 = escaperCreate("abc@", PHYSICS, 5, &errorCode);
    Escaper escaper3 = escaperCreate("b@", PHYSICS, 5, &errorCode);
    Escaper escaper4 = escaperCreate("c@", PHYSICS, 5, &errorCode);

    ASSERT_TEST(escaperCompareElements(escaper1, escaper2) == 0);
    ASSERT_TEST(escaperCompareElements(escaper1, escaper3) < 0);
    ASSERT_TEST(escaperCompareElements(escaper4, escaper3) > 0);

    escaperDestroy(escaper1);
    escaperDestroy(escaper2);
    escaperDestroy(escaper3);
    escaperDestroy(escaper4);
    return true;
}

bool testEscaperCopyElement() {
    ASSERT_TEST(escaperCopyElement(NULL) == NULL);

    EscaperErrorCode errorCode;
    Escaper escaper1 = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    Escaper escaper2 = escaperCopyElement(escaper1);

    ASSERT_TEST(escaperCompareElements(escaper1, escaper2) == 0);

    escaperDestroy(escaper1);
    escaperDestroy(escaper2);
    return true;
}

bool testEscaperGetEmail() {
    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    ASSERT_TEST(escaperGetEmail(NULL, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ESCAPER_NULL_PARAMETER);

    char* email = escaperGetEmail(escaper, &errorCode);
    ASSERT_TEST(errorCode == ESCAPER_SUCCESS);
    ASSERT_TEST(strcmp(email, "adi@gmail") == 0);

    free(email);
    escaperDestroy(escaper);
    return true;
}

bool testEscaperGetNameFaculty() {
    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    ASSERT_TEST(escaperGetNameFaculty(NULL) == UNKNOWN);

    ASSERT_TEST(escaperGetNameFaculty(escaper) == PHYSICS);

    escaperDestroy(escaper);
    return true;
}
bool testEscaperGetSkillLevel() {
    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    ASSERT_TEST(escaperGetSkillLevel(NULL) == -1);

    ASSERT_TEST(escaperGetSkillLevel(escaper) == 5);

    escaperDestroy(escaper);
    return true;
}

bool testIsEscaperWithEmail() {
    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);

    ASSERT_TEST(isEscaperEmailEqual(NULL, "adi@gmail") == false);
    ASSERT_TEST(isEscaperEmailEqual(escaper, NULL) == false);
    ASSERT_TEST(isEscaperEmailEqual(escaper, "adi@gmail") == true);

    escaperDestroy(escaper);
    return true;
}

int main(int argv, char **arc) {

    RUN_TEST(testEscaperCreate);
    RUN_TEST(testEscaperDestroy);
    RUN_TEST(testEscaperCompareElements);
    RUN_TEST(testEscaperCopyElement);
    RUN_TEST(testEscaperGetEmail);
    RUN_TEST(testEscaperGetNameFaculty);
    RUN_TEST(testEscaperGetSkillLevel);
    RUN_TEST(testIsEscaperWithEmail);

    return 0;
}