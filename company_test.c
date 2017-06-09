//
// Created by adire on 09-Jun-17.
//

#include "test_utilities.h"
#include "company.h"
#include "reservation.h"
#include <string.h>

bool testCompanyCreate() {
    CompanyErrorCode errorCode;
    ASSERT_TEST(companyCreate(NULL, PHYSICS, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate(NULL, (TechnionFaculty) 20, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate("", PHYSICS, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate("adi", PHYSICS, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate("@adi@", PHYSICS, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);

    return true;
}

bool testCompanyDestroy() {

    ASSERT_TEST(companyDestroy(NULL) == COMPANY_INVALID_PARAMETER);

    CompanyErrorCode errorCode;
    Company company = companyCreate("adi@gmail", PHYSICS, &errorCode);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);
    ASSERT_TEST(companyDestroy(company) == COMPANY_SUCCESS);

    companyDestroy(company);
    return true;
}

bool testCompanyAddRoom() {
    CompanyErrorCode errorCode;
    Company company = companyCreate("adi@gmail", PHYSICS, &errorCode);
    errorCode = companyAddRoom(NULL, 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    errorCode = companyAddRoom(company, -1, 12, 20, 1, 2, 1);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    errorCode = companyAddRoom(company, 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);

    RoomErrorCode roomErrorCode;
    Room room = companyFindRoom(company, 123, &errorCode);
    ASSERT_TEST(roomGetID(room, &roomErrorCode) == 123);

    errorCode = companyAddRoom(company, 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(errorCode == COMPANY_ROOM_ALREADY_EXISTS);

    companyDestroy(company);
    return true;
}

bool testCompanyRemoveRoom() {
    CompanyErrorCode errorCode;
    Company company = companyCreate("adi@gmail", PHYSICS, &errorCode);
    companyAddRoom(company, 123, 12, 20, 1, 2, 1);

    Room room = companyFindRoom(company, 123, &errorCode);

    ASSERT_TEST(companyRemoveRoom(company, room) == COMPANY_SUCCESS);

    ASSERT_TEST(companyFindRoom(company, 123, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_ROOM_DOES_NOT_EXIST);

    ASSERT_TEST(companyRemoveRoom(NULL, room) == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyRemoveRoom(company, NULL) == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(
            companyRemoveRoom(company, room) == COMPANY_ROOM_DOES_NOT_EXIST);

    companyDestroy(company);
    return true;
}

bool testCompanyCompareElements() {
    CompanyErrorCode errorCode;
    Company company1 = companyCreate("adi@gmail", PHYSICS, &errorCode);
    Company company2 = companyCreate("adi@gmail", PHYSICS, &errorCode);
    Company company3 = companyCreate("adi@gmai", PHYSICS, &errorCode);

    ASSERT_TEST(companyCompareElements(NULL, company2) == -1);
    ASSERT_TEST(companyCompareElements(company1, NULL) == -1);

    ASSERT_TEST(companyCompareElements(company1, company2) == 0);
    ASSERT_TEST(companyCompareElements(company1, company3) == 1);

    companyDestroy(company1);
    companyDestroy(company2);
    companyDestroy(company3);
    return true;
}

bool testCompanyCopyElement() {
    ASSERT_TEST(companyCopyElement(NULL) == NULL);

    CompanyErrorCode errorCode;
    Company company1 = companyCreate("adi@gmail", PHYSICS, &errorCode);
    Company company2 = companyCopyElement(company1);

    ASSERT_TEST(roomCompareElements(company1, company2) == 0);

    companyDestroy(company1);
    companyDestroy(company2);
    return true;
}

bool testCompanyGetEmail() {
    CompanyErrorCode errorCode;
    Company company = companyCreate("adi@gmail", PHYSICS, &errorCode);
    ASSERT_TEST(companyGetEmail(NULL, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);

    char* email = companyGetEmail(company, &errorCode);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);
    ASSERT_TEST(strcmp(email, "adi@gmail") == 0);

    companyDestroy(company);
    return true;
}

bool testCompanyGetFaculty() {
    CompanyErrorCode errorCode;
    Company company = companyCreate("adi@gmail", PHYSICS, &errorCode);
    ASSERT_TEST(companyGetFaculty(NULL, &errorCode) == UNKNOWN);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);

    TechnionFaculty faculty = companyGetFaculty(company, &errorCode);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);
    ASSERT_TEST(faculty == PHYSICS);

    companyDestroy(company);

    return true;
}

bool testCompanyFindRoom() {
    CompanyErrorCode errorCode;
    Company company = companyCreate("adi@gmail", PHYSICS, &errorCode);
    companyAddRoom(company, 123, 12, 20, 1, 2, 1);
    companyAddRoom(company, 1234, 12, 20, 1, 2, 1);
    companyAddRoom(company, 1, 12, 20, 1, 2, 1);

    ASSERT_TEST(companyFindRoom(company, 10, &errorCode) == NULL);
    ASSERT_TEST(errorCode == COMPANY_ROOM_DOES_NOT_EXIST);

    Room room1 = companyFindRoom(company, 123, &errorCode);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);
    Room room2 = companyFindRoom(company, 1234, &errorCode);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);
    Room room3 = companyFindRoom(company, 1, &errorCode);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);

    companyRemoveRoom(company, room1);
    companyRemoveRoom(company, room2);
    companyRemoveRoom(company, room3);
    companyDestroy(company);
    return true;
}

bool testIsCompanyEmailEqual() {
    CompanyErrorCode errorCode;
    Company company1 = companyCreate("adi@gmail", PHYSICS, &errorCode);

    ASSERT_TEST(isCompanyEmailEqual(NULL, "adi@gmail", &errorCode) == false);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(isCompanyEmailEqual(company1, NULL, &errorCode) == false);
    ASSERT_TEST(errorCode == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(isCompanyEmailEqual(company1, "adi@gmail", &errorCode) == true);
    ASSERT_TEST(errorCode == COMPANY_SUCCESS);

    companyDestroy(company1);
    return true;
}


int main(int argv, char **arc) {
    RUN_TEST(testCompanyCreate);
    RUN_TEST(testCompanyDestroy);
    RUN_TEST(testCompanyAddRoom);
    RUN_TEST(testCompanyRemoveRoom);
    RUN_TEST(testCompanyCompareElements);
    RUN_TEST(testCompanyCopyElement);
    RUN_TEST(testCompanyGetEmail);
    RUN_TEST(testCompanyGetFaculty);
    RUN_TEST(testCompanyFindRoom);
    RUN_TEST(testIsCompanyEmailEqual);


    return 0;
}