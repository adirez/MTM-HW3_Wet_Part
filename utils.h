//
// Created by Shahak on 06/06/2017.
//

#include "mtm_ex3.h"
#include "escape_technion.h"


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/

//TODO: add comments
/**
 *
 * @param roomFaculty
 * @param company_email
 * @param id
 * @param price
 * @param num_ppl
 * @param difficulty
 * @return
 */
bool isValidRoomParams(char *company_email, int id, int price, int num_ppl,
                       int difficulty);
/**
 *
 * @param email
 * @param escaperFaculty
 * @param skill_level
 * @return
 */
bool isValidEscaperParams(TechnionFaculty escaperFaculty, char *email,
                          int skill_level);
/**
 *
 * @param email
 * @param Faculty
 * @return
 */
bool isValidCompanyParams(TechnionFaculty Faculty, char *email);

/**
 *
 * @param num_ppl
 * @param price
 * @return
 */
bool isValidReservationParams(int num_ppl, int price);

/**
 * receives a string representing operation hours in the format "hh-hh" and
 * returns the opening time and the closing time as integers
 * @param hours_str - the original string
 * @param opening_time - the output of the calculated opening time
 * @param closing_time - the output of the calculated closing time
 * @return true - if the string is valid
 *         false - if the string contains illegal chars, too short / long or if
 *         it is NULL
 */
bool getHoursFromStr(char *hours_str, int *opening_time, int *closing_time);

/**
 * receives a string representing a day and an hour in the format "dd-hh" and
 * returns the day and the hour as integers
 * @param src_str - the source string
 * @param day - the output of the calculated day
 * @param hour - the output of the calculated hour
 * @return true - if the string is valid
 *         false - if the string contains illegal chars, too short / long or if
 *         it is NULL
 */
bool getDayAndHourFromStr(char *src_str, int *day, int *hour);

/**
 * receives room's difficulty and recommended number of people, escaper's skill
 * level and number of people for the reservation and returns a calculation of
 * the formula to find the best room
 * @param room_num_ppl - the recommended number of people for the room
 * @param reservation_num_ppl - the number of people in the reservation
 * @param room_difficulty - the difficulty level of the room
 * @param escaper_skill_level - the skill level of the escaper
 * @return an integer representing the result of the calculation formula
 */
int calcRoomMatch(int room_num_ppl, int reservation_num_ppl,
                  int room_difficulty, int escaper_skill_level);

/**
 * receives an email and checks if it's valid
 * @param email - the email address to be checked
 * @return true - contains only one '@'
 *         false - containes more / less than one '@' or NULL
 */
bool isValidEmail(char *email);
/**
 * receives a faculty name and checks if it's valid
 * @param Faculty - the faculty name to be checked
 * @return true - if it's mentioned in the listed faculties
 *         false - it is not mentioned in the listed faculties
 */
bool isValidFacultyName(TechnionFaculty Faculty);