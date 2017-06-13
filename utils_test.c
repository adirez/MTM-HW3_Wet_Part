//
// Created by adire on 09-Jun-17.
//

#include "test_utilities.h"
#include "utils.h"
#include "mtm_ex3.h"
#include <string.h>
#include <stdlib.h>

bool testIsEmailValid() {
    ASSERT_TEST(isValidEmail("") == false);
    ASSERT_TEST(isValidEmail("a") == false);
    ASSERT_TEST(isValidEmail("adirez.ad") == false);
    ASSERT_TEST(isValidEmail(" ") == false);
    ASSERT_TEST(isValidEmail("321") == false);
    ASSERT_TEST(isValidEmail("@") == true);
    ASSERT_TEST(isValidEmail("adirez@gmail.com") == true);
    ASSERT_TEST(isValidEmail("@ @") == false);
    ASSERT_TEST(isValidEmail("adi@") == true);
    ASSERT_TEST(isValidEmail("@rez") == true);
    ASSERT_TEST(isValidEmail("@@") == false);
    ASSERT_TEST(isValidEmail("@rez@") == false);
    ASSERT_TEST(isValidEmail("ad@@rez") == false);

    return true;
}

bool testIsFacultyValid() {
    ASSERT_TEST(isValidFacultyName(CIVIL_ENGINEERING) == true);
    ASSERT_TEST(isValidFacultyName(BIOMEDICAL_ENGINEERING) == true);
    ASSERT_TEST(isValidFacultyName(EDUCATION_IN_TECH_AND_SCIENCE) == true);
    ASSERT_TEST(isValidFacultyName(UNKNOWN) == false);
    ASSERT_TEST(isValidFacultyName((TechnionFaculty) 20) == false);

    return true;
}

bool testIsValidRoomParams() {
    ASSERT_TEST(isValidRoomParams("ad@i", 1, 12, 5, 10) == true);
    ASSERT_TEST(isValidRoomParams("@", 1, 4, 5, 1) == true);
    ASSERT_TEST(isValidRoomParams("@", 1, 12, 5, 2) == true);
    ASSERT_TEST(isValidRoomParams("@", 2017, 12, 5, 1) == true);
    ASSERT_TEST(isValidRoomParams("", 1, 12, 5, 10) == false);
    ASSERT_TEST(isValidRoomParams(NULL, 1, 12, 5, 10) == false);
    ASSERT_TEST(isValidRoomParams("@@", 1, 12, 5, 10) == false);
    ASSERT_TEST(isValidRoomParams("@d@a@", 1, 12, 5, 10) == false);
    ASSERT_TEST(isValidRoomParams("@", 0, 12, 5, 10) == false);
    ASSERT_TEST(isValidRoomParams("@", 1, 0, 5, 10) == false);
    ASSERT_TEST(isValidRoomParams("@", 1, 12, 0, 10) == false);
    ASSERT_TEST(isValidRoomParams("@", 1, 12, 5, 0) == false);
    ASSERT_TEST(isValidRoomParams("@", 1, 11, 5, 10) == false);

    return true;
}

bool testIsValidEscaperParams() {
    ASSERT_TEST(isValidEscaperParams(COMPUTER_SCIENCE, "adi@", 10) == true);
    ASSERT_TEST(isValidEscaperParams(UNKNOWN, "adi@", 10) == false);
    ASSERT_TEST(isValidEscaperParams(COMPUTER_SCIENCE, "adi@", 11) == false);
    ASSERT_TEST(isValidEscaperParams(COMPUTER_SCIENCE, "@@", 10) == false);

    return true;
}

bool testIsValidCompanyParams() {
    ASSERT_TEST(isValidCompanyParams(PHYSICS, "@") == true);
    ASSERT_TEST(isValidCompanyParams(CIVIL_ENGINEERING, "@") == true);
    ASSERT_TEST(isValidCompanyParams(PHYSICS, "a@s") == true);
    ASSERT_TEST(isValidCompanyParams(PHYSICS, "") == false);
    ASSERT_TEST(isValidCompanyParams(PHYSICS, "@@") == false);
    ASSERT_TEST(isValidCompanyParams(UNKNOWN, "@") == false);

    return true;
}

bool testGetHoursFromStr() {
    int opening, closing;
    ASSERT_TEST(getHoursFromStr("10-14", &opening, &closing) == true);
    ASSERT_TEST(opening == 10 && closing == 14);
    ASSERT_TEST(getHoursFromStr("00-02", &opening, &closing) == true);
    ASSERT_TEST(opening == 0 && closing == 2);
    ASSERT_TEST(getHoursFromStr("00-23", &opening, &closing) == true);
    ASSERT_TEST(opening == 0 && closing == 23);
    ASSERT_TEST(getHoursFromStr("23-24", &opening, &closing) == true);
    ASSERT_TEST(opening == 23 && closing == 24);
    ASSERT_TEST(getHoursFromStr("14-10", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("24-01", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("23-00", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("2-14", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("01-5", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("111-14", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("10-10", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("10+14", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("10014", &opening, &closing) == false);
    ASSERT_TEST(getHoursFromStr("23-5", &opening, &closing) == false);
    ASSERT_TEST(getDayAndHourFromStr("-", &opening, &closing)== false);
    ASSERT_TEST(getDayAndHourFromStr("", &opening, &closing)== false);

    return true;
}

bool testGetDayAndHourFromStr(){
    int day, hour;
    ASSERT_TEST(getDayAndHourFromStr("10-14", &day, &hour) == true);
    ASSERT_TEST(day == 10 && hour == 14);
    ASSERT_TEST(getDayAndHourFromStr("00-02", &day, &hour) == true);
    ASSERT_TEST(day == 0 && hour == 2);
    ASSERT_TEST(getDayAndHourFromStr("00-23", &day, &hour) == true);
    ASSERT_TEST(day == 0 && hour == 23);
    ASSERT_TEST(getDayAndHourFromStr("50-10", &day, &hour) == true);
    ASSERT_TEST(day == 50 && hour == 10);
    ASSERT_TEST(getDayAndHourFromStr("00-00", &day, &hour) == true);
    ASSERT_TEST(day == 0 && hour == 0);
    ASSERT_TEST(getDayAndHourFromStr("2-14", &day, &hour) == true);
    ASSERT_TEST(day == 2 && hour == 14);
    ASSERT_TEST(getDayAndHourFromStr("01-5", &day, &hour) == true);
    ASSERT_TEST(day == 1 && hour == 5);
    ASSERT_TEST(getDayAndHourFromStr("111-14", &day, &hour)== true);
    ASSERT_TEST(day == 111 && hour == 14);
    ASSERT_TEST(getDayAndHourFromStr("1535120-14", &day, &hour)== true);
    ASSERT_TEST(day == 1535120 && hour == 14);
    ASSERT_TEST(getDayAndHourFromStr("10+14", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("10014", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("10-14-", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("-10-14", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("10-142", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("-", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("1 -5", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("02 -5", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("1- 5", &day, &hour)== false);
    ASSERT_TEST(getDayAndHourFromStr("1 - 5", &day, &hour)== false);

    return true;
}

bool testCalcRoomMatch() {
    ASSERT_TEST(calcRoomMatch(5,5,2,2) == 0);
    ASSERT_TEST(calcRoomMatch(10,5,2,2) == 25);
    ASSERT_TEST(calcRoomMatch(5,5,7,3) == 16);
    ASSERT_TEST(calcRoomMatch(2,1,4,2) == 5);

    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testIsEmailValid);
    RUN_TEST(testIsFacultyValid);
    RUN_TEST(testIsValidRoomParams);
    RUN_TEST(testIsValidEscaperParams);
    RUN_TEST(testIsValidCompanyParams);
    RUN_TEST(testGetHoursFromStr);
    RUN_TEST(testGetDayAndHourFromStr);
    RUN_TEST(testCalcRoomMatch);

    return 0;
}