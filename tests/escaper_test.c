//
// Created by adire on 09-Jun-17.
//
#include "test_utilities.h"
#include "escaper.h"
#include <string.h>


bool testEscaperCreate() {
    EscaperErrorCode errorCode;
    ASSERT_TEST(escaperCreate(NULL, PHYSICS, 5, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);
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
    ASSERT_TEST(escaperDestroy(NULL) == ESCAPER_INVALID_PARAMETER);

    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    ASSERT_TEST(errorCode == ESCAPER_SUCCESS);
    ASSERT_TEST(escaperDestroy(escaper) == ESCAPER_SUCCESS);

    return true;
}

bool testEscaperCompareElements() {
    EscaperErrorCode errorCode;
    Escaper escaper1 = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    Escaper escaper2 = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    Escaper escaper3 = escaperCreate("adi@gmai", PHYSICS, 5, &errorCode);

    ASSERT_TEST(escaperCompareElements(NULL, escaper2) == -1);
    ASSERT_TEST(escaperCompareElements(escaper1, NULL) == -1);

    ASSERT_TEST(escaperCompareElements(escaper1, escaper2) == 0);
    ASSERT_TEST(escaperCompareElements(escaper1, escaper3) == 1);

    escaperDestroy(escaper1);
    escaperDestroy(escaper2);
    escaperDestroy(escaper3);
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
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);

    char* email = escaperGetEmail(escaper, &errorCode);
    ASSERT_TEST(errorCode == ESCAPER_SUCCESS);
    ASSERT_TEST(strcmp(email, "adi@gmail") == 0);

    escaperDestroy(escaper);
    return true;
}

bool testEscaperGetFaculty() {
    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    ASSERT_TEST(escaperGetFaculty(NULL, &errorCode) == UNKNOWN);
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);

    TechnionFaculty faculty = escaperGetFaculty(escaper, &errorCode);
    ASSERT_TEST(errorCode == ESCAPER_SUCCESS);
    ASSERT_TEST(faculty == PHYSICS);

    escaperDestroy(escaper);
    return true;
}
bool testEscaperGetSkillLevel() {
    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);
    ASSERT_TEST(escaperGetSkillLevel(NULL, &errorCode) == -1);
    ASSERT_TEST(errorCode == ESCAPER_INVALID_PARAMETER);

    int skill_level = escaperGetSkillLevel(escaper, &errorCode);
    ASSERT_TEST(errorCode == ESCAPER_SUCCESS);
    ASSERT_TEST(skill_level == 5);

    escaperDestroy(escaper);
    return true;
}

bool testIsEscaperWithEmail() {
    EscaperErrorCode errorCode;
    Escaper escaper = escaperCreate("adi@gmail", PHYSICS, 5, &errorCode);

    ASSERT_TEST(isEscaperWithEmail(NULL, "adi@gmail") == false);
    ASSERT_TEST(isEscaperWithEmail(escaper, NULL) == false);
    ASSERT_TEST(isEscaperWithEmail(escaper, "adi@gmail") == true);

    escaperDestroy(escaper);
    return true;
}

int main(int argv, char **arc) {

    RUN_TEST(testEscaperCreate);
    RUN_TEST(testEscaperDestroy);
    RUN_TEST(testEscaperCompareElements);
    RUN_TEST(testEscaperCopyElement);
    RUN_TEST(testEscaperGetEmail);
    RUN_TEST(testEscaperGetFaculty);
    RUN_TEST(testEscaperGetSkillLevel);
    RUN_TEST(testIsEscaperWithEmail);

    return 0;
}