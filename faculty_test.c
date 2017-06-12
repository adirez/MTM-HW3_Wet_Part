//
// Created by adire on 12-Jun-17.
//
#include "test_utilities.h"
#include "faculty.h"
#include <string.h>
#include <stdlib.h>


bool testFacultyCreate() {
    FacultyErrorCode facultyError;
    ASSERT_TEST(facultyCreate(PHYSICS, NULL) == NULL);
    ASSERT_TEST(facultyCreate(UNKNOWN, &facultyError) == NULL);
    ASSERT_TEST(facultyError == FACULTY_INVALID_PARAMETER);

    Faculty faculty = facultyCreate(PHYSICS, &facultyError);
    ASSERT_TEST(faculty != NULL);
    ASSERT_TEST(facultyError == FACULTY_SUCCESS);

    facultyDestroy(faculty);
    return true;
}

bool testFacultyDestroy() {
    facultyDestroy(NULL);

    FacultyErrorCode facultyError;
    Faculty faculty = facultyCreate(PHYSICS, &facultyError);
    facultyDestroy(faculty);
    return true;
}

bool testFacultyAddCompany() {
    FacultyErrorCode facultyError;
    Faculty faculty = facultyCreate(PHYSICS, &facultyError);
    ASSERT_TEST(facultyAddCompany(NULL, "adi@") == FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyAddCompany(faculty, NULL) == FACULTY_NULL_PARAMETER);

    ASSERT_TEST(facultyAddCompany(faculty, "") == FACULTY_INVALID_PARAMETER);
    ASSERT_TEST(facultyAddCompany(faculty, "@@") == FACULTY_INVALID_PARAMETER);
    ASSERT_TEST(facultyAddCompany(faculty, "abc") == FACULTY_INVALID_PARAMETER);

    ASSERT_TEST(facultyAddCompany(faculty, "abc@") == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddCompany(faculty, "abc@") ==
                        FACULTY_COMPANY_ALREADY_EXISTS);

    facultyDestroy(faculty);
    return true;
}

bool testFacultyRemoveCompany() {
    FacultyErrorCode facultyError;
    Faculty faculty1 = facultyCreate(PHYSICS, &facultyError);

    facultyAddCompany(faculty1, "abc@");
    facultyAddCompany(faculty1, "abc@2");

    Company company1 = facultyGetCompanyByEmail(faculty1, "abc@", &facultyError);
    Company company2 = facultyGetCompanyByEmail(faculty1, "abc@2", &facultyError);

    ASSERT_TEST(facultyRemoveCompany(faculty1, company1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyRemoveCompany(faculty1, company2) == FACULTY_SUCCESS);

    ASSERT_TEST(facultyRemoveCompany(NULL, company1) == FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyRemoveCompany(faculty1, NULL) == FACULTY_NULL_PARAMETER);

    Faculty faculty2 = facultyCreate(BIOLOGY, &facultyError);
    facultyAddCompany(faculty2, "z@");
    Company company3 = facultyGetCompanyByEmail(faculty2, "z@", &facultyError);

    ASSERT_TEST(facultyRemoveCompany(faculty1, company3) ==
                FACULTY_COMPANY_DOES_NOT_EXIST);

    facultyDestroy(faculty1);
    return true;
}

bool testFacultyCompareElements() {
    FacultyErrorCode facultyError;
    Faculty faculty1 = facultyCreate(PHYSICS, &facultyError);
    Faculty faculty2 = facultyCreate(BIOLOGY, &facultyError);
    Faculty faculty3 = facultyCreate(BIOLOGY, &facultyError);

    ASSERT_TEST(facultyCompareElements(faculty1, faculty2) < 0);
    ASSERT_TEST(facultyCompareElements(faculty2, faculty3) == 0);

    facultyDestroy(faculty1);
    facultyDestroy(faculty2);
    facultyDestroy(faculty3);
    return true;
}

bool testFacultyCopyElement() {
    ASSERT_TEST(facultyCopyElement(NULL) == NULL);

    FacultyErrorCode facultyError;
    Faculty faculty1 = facultyCreate(PHYSICS, &facultyError);

    facultyAddCompany(faculty1, "abc@");
    facultyAddCompany(faculty1, "abc@2");
    facultyAddCompany(faculty1, "abc@3");

    Faculty faculty2 = facultyCopyElement(faculty1);

    ASSERT_TEST(facultyCompareElements(faculty1, faculty2) == 0);

    Company company1 = facultyGetCompanyByEmail(faculty2, "abc@", &facultyError);
    ASSERT_TEST(company1 != NULL);
    Company company2 = facultyGetCompanyByEmail(faculty2, "abc@2", &facultyError);
    ASSERT_TEST(company2 != NULL);
    Company company3 = facultyGetCompanyByEmail(faculty2, "abc@3", &facultyError);
    ASSERT_TEST(company3 != NULL);

    facultyDestroy(faculty1);
    facultyDestroy(faculty2);
    return true;
}

bool testFacultyGetName() {
    ASSERT_TEST(facultyGetName(NULL) == UNKNOWN);

    FacultyErrorCode facultyError;
    Faculty faculty1 = facultyCreate(PHYSICS, &facultyError);
    Faculty faculty2 = facultyCreate(BIOLOGY, &facultyError);
    Faculty faculty3 = facultyCreate(MEDICINE, &facultyError);

    ASSERT_TEST(facultyGetName(faculty1) == PHYSICS);
    ASSERT_TEST(facultyGetName(faculty2) == BIOLOGY);
    ASSERT_TEST(facultyGetName(faculty3) == MEDICINE);

    facultyDestroy(faculty1);
    facultyDestroy(faculty2);
    facultyDestroy(faculty3);
    return true;
}

bool testFacultyEarnings() {
    ASSERT_TEST(facultyGetEarnings(NULL) == -1);

    FacultyErrorCode facultyError;
    Faculty faculty = facultyCreate(PHYSICS, &facultyError);

    ASSERT_TEST(facultyGetEarnings(faculty) == 0);

    facultyIncEarnings(faculty, 5);
    ASSERT_TEST(facultyGetEarnings(faculty) == 5);

    facultyDestroy(faculty);
    return true;
}

bool testFacultyGetCompanyByEmail() {
    FacultyErrorCode facultyError;
    ASSERT_TEST(facultyGetCompanyByEmail(NULL, "ad@", &facultyError) == NULL);
    ASSERT_TEST(facultyError == FACULTY_NULL_PARAMETER);

    Faculty faculty = facultyCreate(PHYSICS, &facultyError);

    ASSERT_TEST(facultyGetCompanyByEmail(faculty, NULL, &facultyError) == NULL);
    ASSERT_TEST(facultyError == FACULTY_NULL_PARAMETER);

    ASSERT_TEST(facultyGetCompanyByEmail(faculty, "", &facultyError) == NULL);
    ASSERT_TEST(facultyError == FACULTY_INVALID_PARAMETER);
    ASSERT_TEST(facultyGetCompanyByEmail(faculty, "@@", &facultyError) == NULL);
    ASSERT_TEST(facultyError == FACULTY_INVALID_PARAMETER);

    facultyAddCompany(faculty, "abc@");
    facultyAddCompany(faculty, "abc@2");
    facultyAddCompany(faculty, "abc@3");

    Company company1 = facultyGetCompanyByEmail(faculty, "abc@2", &facultyError);
    ASSERT_TEST(facultyError == FACULTY_SUCCESS);
    ASSERT_TEST(company1 != NULL);
    Company company2 = facultyGetCompanyByEmail(faculty, "abc@", &facultyError);
    ASSERT_TEST(facultyError == FACULTY_SUCCESS);
    ASSERT_TEST(company2 != NULL);
    Company company3 = facultyGetCompanyByEmail(faculty, "abc@3", &facultyError);
    ASSERT_TEST(facultyError == FACULTY_SUCCESS);
    ASSERT_TEST(company3 != NULL);

    ASSERT_TEST(facultyGetCompanyByEmail(faculty, "c@", &facultyError) == NULL);
    ASSERT_TEST(facultyError == FACULTY_COMPANY_DOES_NOT_EXIST);

    facultyDestroy(faculty);
    return true;
}

bool testFacultyGetRoomByID() {
    FacultyErrorCode facultyError;
    Faculty faculty = facultyCreate(PHYSICS, &facultyError);

    facultyAddCompany(faculty, "abc@");
    facultyAddCompany(faculty, "abc@2");
    facultyAddCompany(faculty, "abc@3");

    Company company1 = facultyGetCompanyByEmail(faculty, "abc@2", &facultyError);
    Company company2 = facultyGetCompanyByEmail(faculty, "abc@", &facultyError);
    Company company3 = facultyGetCompanyByEmail(faculty, "abc@3", &facultyError);

    companyAddRoom(company1, 11, 4, 5, 10, 20, 1);
    companyAddRoom(company1, 12, 8, 2, 10, 15, 3);
    companyAddRoom(company1, 13, 12, 1, 2, 4, 7);

    companyAddRoom(company2, 21, 4, 5, 10, 20, 1);
    companyAddRoom(company2, 22, 8, 2, 10, 15, 3);
    companyAddRoom(company2, 23, 12, 1, 2, 4, 9);

    companyAddRoom(company3, 31, 4, 5, 10, 20, 1);
    companyAddRoom(company3, 32, 8, 2, 10, 15, 3);
    companyAddRoom(company3, 33, 12, 1, 2, 4, 7);

    Company rooms_company;

    ASSERT_TEST(facultyGetRoomByID(NULL, &rooms_company, 3) == NULL);
    ASSERT_TEST(facultyGetRoomByID(faculty, NULL, 3) == NULL);

    ASSERT_TEST(facultyGetRoomByID(faculty, &rooms_company, 5) == NULL);
    Room room = facultyGetRoomByID(faculty, &rooms_company, 23);

    RoomErrorCode roomError;

    ASSERT_TEST(roomGetID(room) == 23);
    ASSERT_TEST(roomGetNameFaculty(room) == PHYSICS);
    ASSERT_TEST(strcmp(roomGetCompanyEmail(room, &roomError), "abc@") == 0);
    ASSERT_TEST(roomGetDifficulty(room) == 9);

    return true;
}

bool testIsCompanyEmailFaculty() {
    FacultyErrorCode facultyError;
    ASSERT_TEST(isCompanyEmailFaculty(NULL, "ad@") == false);

    Faculty faculty = facultyCreate(PHYSICS, &facultyError);

    ASSERT_TEST(isCompanyEmailFaculty(faculty, NULL) == false);

    ASSERT_TEST(isCompanyEmailFaculty(faculty, "") == false);
    ASSERT_TEST(isCompanyEmailFaculty(faculty, "@@") == false);

    facultyAddCompany(faculty, "abc@");
    facultyAddCompany(faculty, "abc@2");
    facultyAddCompany(faculty, "abc@3");

    ASSERT_TEST(isCompanyEmailFaculty(faculty, "abc@2") == true);
    ASSERT_TEST(isCompanyEmailFaculty(faculty, "abc@") == true);
    ASSERT_TEST(isCompanyEmailFaculty(faculty, "abc@3") == true);

    ASSERT_TEST(isCompanyEmailFaculty(faculty, "c@") == false);

    facultyDestroy(faculty);
    return true;
}

bool testFacultyMostRecommendedRoom() {
    int result, faculty_distance, id;
    FacultyErrorCode facultyError;
    EscaperErrorCode escaperError;
    Escaper escaper = escaperCreate("adi@", PHYSICS, 5, &escaperError);
    Faculty faculty = facultyCreate(PHYSICS, &facultyError);

    facultyAddCompany(faculty, "1@1");
    facultyAddCompany(faculty, "1@2");
    facultyAddCompany(faculty, "1@3");
    facultyAddCompany(faculty, "1@4");

    Company company11 = facultyGetCompanyByEmail(faculty, "1@1", &facultyError);
    Company company12 = facultyGetCompanyByEmail(faculty, "1@2", &facultyError);
    Company company13 = facultyGetCompanyByEmail(faculty, "1@3", &facultyError);
    Company company14 = facultyGetCompanyByEmail(faculty, "1@4", &facultyError);


    companyAddRoom(company11, 111, 4, 7, 10, 20, 2);
    companyAddRoom(company11, 112, 8, 3, 10, 15, 3);
    companyAddRoom(company11, 113, 12, 5, 2, 4, 7);

    companyAddRoom(company12, 121, 4, 5, 10, 20, 10);

    companyAddRoom(company13, 131, 4, 5, 10, 20, 9);
    companyAddRoom(company13, 132, 8, 2, 10, 15, 3);

    companyAddRoom(company14, 141, 4, 2, 10, 20, 1);
    companyAddRoom(company14, 142, 20, 2, 10, 15, 3);
    companyAddRoom(company14, 143, 4, 4, 10, 20, 8);
    companyAddRoom(company14, 144, 12, 0, 10, 15, 3);

    Company rooms_company;
    Room room;

    room = facultyMostRecommendedRoom(faculty, escaper, PHYSICS, 5, 5, &result,
                               &faculty_distance, &id, &rooms_company);

    printf("----%d, %d, %d----\n", result, faculty_distance, id);
    roomGetDifficulty(room);


    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testFacultyCreate);
    RUN_TEST(testFacultyDestroy);
    RUN_TEST(testFacultyAddCompany);
    RUN_TEST(testFacultyRemoveCompany);
    RUN_TEST(testFacultyCompareElements);
    RUN_TEST(testFacultyCopyElement);
    RUN_TEST(testFacultyGetName);
    RUN_TEST(testFacultyEarnings);
    RUN_TEST(testFacultyGetCompanyByEmail);
    RUN_TEST(testFacultyGetRoomByID);
    RUN_TEST(testIsCompanyEmailFaculty);
    RUN_TEST(testFacultyMostRecommendedRoom);

    return 0;
}