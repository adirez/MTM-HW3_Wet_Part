//
// Created by adire on 09-Jun-17.
//

#include "test_utilities.h"
#include "utils.h"
#include "mtm_ex3.h"
#include <string.h>
#include <stdlib.h>

bool testIsEmailValid() {

    ASSERT_TEST(isEmailValid("") == false);
    ASSERT_TEST(isEmailValid("a") == false);
    ASSERT_TEST(isEmailValid("adirez.ad") == false);
    ASSERT_TEST(isEmailValid(" ") == false);
    ASSERT_TEST(isEmailValid("321") == false);
    ASSERT_TEST(isEmailValid("@") == true);
    ASSERT_TEST(isEmailValid("adirez@gmail.com") == true);
    ASSERT_TEST(isEmailValid("@ @") == false);
    ASSERT_TEST(isEmailValid("adi@") == true);
    ASSERT_TEST(isEmailValid("@rez") == true);
    ASSERT_TEST(isEmailValid("@@") == false);
    ASSERT_TEST(isEmailValid("@rez@") == false);
    ASSERT_TEST(isEmailValid("ad@@rez") == false);

    return true;
}

bool testIsFacultyValid() {
    ASSERT_TEST(isFacultyValid(CIVIL_ENGINEERING) == true);
    ASSERT_TEST(isFacultyValid(BIOMEDICAL_ENGINEERING) == true);
    ASSERT_TEST(isFacultyValid(EDUCATION_IN_TECH_AND_SCIENCE) == true);
    ASSERT_TEST(isFacultyValid(UNKNOWN) == false);
    ASSERT_TEST(isFacultyValid((TechnionFaculty) 20) == false);

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
    ASSERT_TEST(getHoursFromStr("14-10", &opening, &closing) == false);
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
    ASSERT_TEST(getDayAndHourFromStr("", &day, &hour)== false);


    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testIsEmailValid);
    RUN_TEST(testIsFacultyValid);
    RUN_TEST(testGetHoursFromStr);
    RUN_TEST(testGetDayAndHourFromStr);

    return 0;
}