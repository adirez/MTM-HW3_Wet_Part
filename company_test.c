//
// Created by adire on 09-Jun-17.
//
#include <string.h>
#include <stdlib.h>

#include "test_utilities.h"
#include "company.h"

bool testCompanyCreate() {
    ASSERT_TEST(companyCreate(UNKNOWN, "@", NULL) == NULL);
    CompanyErrorCode companyError;
    ASSERT_TEST(companyCreate(UNKNOWN, "@", &companyError) == NULL);
    ASSERT_TEST(companyError == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate((TechnionFaculty)-1, "@", &companyError) == NULL);
    ASSERT_TEST(companyError == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate(PHYSICS, NULL, &companyError) == NULL);
    ASSERT_TEST(companyError == COMPANY_NULL_PARAMETER);
    ASSERT_TEST(companyCreate(PHYSICS, "", &companyError) == NULL);
    ASSERT_TEST(companyError == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate(PHYSICS, "@@", &companyError) == NULL);
    ASSERT_TEST(companyError == COMPANY_INVALID_PARAMETER);
    ASSERT_TEST(companyCreate(PHYSICS, "@@@", &companyError) == NULL);
    ASSERT_TEST(companyError == COMPANY_INVALID_PARAMETER);

    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    ASSERT_TEST(company != NULL);
    ASSERT_TEST(companyError == COMPANY_SUCCESS);

    companyDestroy(company);
    return true;
}

bool testCompanyDestroy() {
    companyDestroy(NULL);

    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    ASSERT_TEST(companyError == COMPANY_SUCCESS);
    companyDestroy(company);

    return true;
}

bool testCompanyAddRoom() {
    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    companyError = companyAddRoom(NULL, 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(companyError == COMPANY_NULL_PARAMETER);
    companyError = companyAddRoom(company, -1, 12, 20, 1, 2, 1);
    ASSERT_TEST(companyError == COMPANY_INVALID_PARAMETER);
    companyError = companyAddRoom(company, 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(companyError == COMPANY_SUCCESS);

    Room room = companyGetRoomByID(company, 123);
    ASSERT_TEST(roomGetID(room) == 123);

    companyError = companyAddRoom(company, 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(companyError == COMPANY_ROOM_ALREADY_EXISTS);

    companyRemoveRoom(company, room);
    companyDestroy(company);
    return true;
}

bool testCompanyRemoveRoom() {
    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    companyAddRoom(company, 123, 12, 20, 1, 2, 1);

    Room room = companyGetRoomByID(company, 123);

    ASSERT_TEST(companyRemoveRoom(company, room) == COMPANY_SUCCESS);

    ASSERT_TEST(companyGetRoomByID(company, 123) == NULL);

    ASSERT_TEST(companyRemoveRoom(NULL, room) == COMPANY_NULL_PARAMETER);
    ASSERT_TEST(companyRemoveRoom(company, NULL) == COMPANY_NULL_PARAMETER);
    ASSERT_TEST(companyRemoveRoom(company, room) == COMPANY_ROOM_DOES_NOT_EXIST);

    companyDestroy(company);
    return true;
}

bool testCompanyCompareElements() {
    CompanyErrorCode companyError;
    Company company1 = companyCreate(PHYSICS, "abc@", &companyError);
    Company company2 = companyCreate(PHYSICS, "abc@", &companyError);
    Company company3 = companyCreate(PHYSICS, "b@", &companyError);
    Company company4 = companyCreate(PHYSICS, "c@", &companyError);

    ASSERT_TEST(companyCompareElements(company1, company2) == 0);
    ASSERT_TEST(companyCompareElements(company1, company3) < 0);
    ASSERT_TEST(companyCompareElements(company4, company3) > 0);

    companyDestroy(company1);
    companyDestroy(company2);
    companyDestroy(company3);
    companyDestroy(company4);

    return true;
}

bool testCompanyCopyElement() {
    ASSERT_TEST(companyCopyElement(NULL) == NULL);

    CompanyErrorCode companyError;
    Company company1 = companyCreate(PHYSICS, "te@st", &companyError);
    Company company2 = companyCopyElement(company1);

    ASSERT_TEST(companyCompareElements(company1, company2) == 0);

    companyDestroy(company1);
    companyDestroy(company2);
    return true;
}

bool testCompanyGetEmail() {
    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    ASSERT_TEST(companyGetEmail(company, NULL) == NULL);
    ASSERT_TEST(companyGetEmail(NULL, &companyError) == NULL);
    ASSERT_TEST(companyError == COMPANY_NULL_PARAMETER);

    char* email = companyGetEmail(company, &companyError);
    ASSERT_TEST(companyError == COMPANY_SUCCESS);
    ASSERT_TEST(strcmp(email, "te@st") == 0);

    free(email);
    companyDestroy(company);
    return true;
}

bool testCompanyGetFaculty() {
    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    ASSERT_TEST(companyGetFaculty(NULL) == UNKNOWN);

    TechnionFaculty faculty = companyGetFaculty(company);
    ASSERT_TEST(faculty == PHYSICS);

    companyDestroy(company);

    return true;
}

bool testIsCompanyEmailEqual() {
    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);

    ASSERT_TEST(isCompanyEmailEqual(NULL, "adi@gmail") == false);
    ASSERT_TEST(isCompanyEmailEqual(company, NULL) == false);
    ASSERT_TEST(isCompanyEmailEqual(company, "adi@gmail") == false);
    ASSERT_TEST(isCompanyEmailEqual(company, "te@st") == true);

    companyDestroy(company);
    return true;
}

bool testCompanyGetRoomByID() {
    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    companyAddRoom(company, 20, 4, 5, 10, 20, 1);
    companyAddRoom(company, 15, 8, 2, 10, 15, 3);
    companyAddRoom(company, 10, 12, 1, 2, 4, 7);

    Room room1 = companyGetRoomByID(company, 11);
    ASSERT_TEST(room1 == NULL);

    Room room2 = companyGetRoomByID(company, 20);
    ASSERT_TEST(room2 != NULL);
    Room room3 = companyGetRoomByID(company, 15);
    ASSERT_TEST(room3 != NULL);
    Room room4 = companyGetRoomByID(company, 10);
    ASSERT_TEST(room4 != NULL);

    companyRemoveRoom(company, room2);
    companyRemoveRoom(company, room3);
    companyRemoveRoom(company, room4);
    companyDestroy(company);
    return true;
}

bool testCompanyGetMinRoomID() {
    CompanyErrorCode companyError;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);
    companyAddRoom(company, 20, 4, 5, 10, 20, 1);
    companyAddRoom(company, 15, 8, 2, 10, 15, 3);
    companyAddRoom(company, 10, 12, 1, 2, 4, 7);

    ASSERT_TEST(companyGetMinRoomID(company) == 10);

    Room room1 = companyGetRoomByID(company, 20);
    Room room2 = companyGetRoomByID(company, 15);
    Room room3 = companyGetRoomByID(company, 10);

    companyRemoveRoom(company, room1);
    companyRemoveRoom(company, room2);
    companyRemoveRoom(company, room3);
    companyDestroy(company);
    return true;
}

bool testCompanyMostRecommendedRoom() {
    CompanyErrorCode companyError;
    int result, faculty_distance, id;
    Company company = companyCreate(PHYSICS, "te@st", &companyError);

    Room room_null = companyMostRecommendedRoom(company, PHYSICS, 2, 3, &result,
                                                &faculty_distance, &id);
    ASSERT_TEST(room_null == NULL);

    companyAddRoom(company, 20, 4, 5, 10, 20, 1);
    companyAddRoom(company, 15, 8, 2, 10, 15, 3);
    companyAddRoom(company, 10, 12, 1, 2, 4, 7);

    Room room1 = companyGetRoomByID(company, 20);
    Room room2 = companyGetRoomByID(company, 15);
    Room room3 = companyGetRoomByID(company, 10);

    Room room4 = companyMostRecommendedRoom(company, PHYSICS, 2, 3, &result,
                               &faculty_distance, &id);
    ASSERT_TEST(roomCompareElements(room2, room4) == 0);
    ASSERT_TEST(result == 0);
    ASSERT_TEST(faculty_distance == 0);
    ASSERT_TEST(id == 15);

    Room room5 = companyMostRecommendedRoom(company, BIOLOGY, 5, 1, &result,
                                            &faculty_distance, &id);
    ASSERT_TEST(roomCompareElements(room1, room5) == 0);
    ASSERT_TEST(result == 0);
    ASSERT_TEST(faculty_distance == 2);
    ASSERT_TEST(id == 20);

    Room room6 = companyMostRecommendedRoom(company, PHYSICS, 1, 7, &result,
                                            &faculty_distance, &id);
    ASSERT_TEST(roomCompareElements(room3, room6) == 0);
    ASSERT_TEST(result == 0);
    ASSERT_TEST(faculty_distance == 0);
    ASSERT_TEST(id == 10);

    Room room7 = companyMostRecommendedRoom(company, PHYSICS, 3, 6, &result,
                                            &faculty_distance, &id);
    ASSERT_TEST(roomCompareElements(room3, room7) == 0);
    ASSERT_TEST(result == 5);
    ASSERT_TEST(faculty_distance == 0);
    ASSERT_TEST(id == 10);

    companyRemoveRoom(company, room1);
    companyRemoveRoom(company, room2);
    companyRemoveRoom(company, room3);
    companyDestroy(company);
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
    RUN_TEST(testIsCompanyEmailEqual);
    RUN_TEST(testCompanyGetRoomByID);
    RUN_TEST(testCompanyGetMinRoomID);
    RUN_TEST(testCompanyMostRecommendedRoom);

    return 0;
}