//
// Created by Shahak on 06/06/2017.
//

#include "mtm_ex3.h"
#include "escape_technion.h"


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/

/**
 * receives the price per person of a certain room and makes sure it it's a
 * multiply of 4
 * @param price - the integer to be checked
 * @return true - if it's a multiply of 4
 *         false - if it's not a multiply of 4 or if it's not a positive number
 */
bool isValidPrice(int price);

/**
 * receives a difficulty level of a room or a skill level of an escaper and
 * checks if the value is between 1 to 10
 * @param difficulty_or_skill - the input value of the skill / difficulty
 * @return true - if it's between the min level and the max level
 *         false - if it's not in the scale
 */
bool isValidDifficultyOrSkill(int difficulty_or_skill);

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
 * @return true - if it's mentioned in the listed faculties enum
 *         false - it is not mentioned in the listed faculties
 */
bool isValidFacultyName(TechnionFaculty Faculty);

/**
 * receives paramas that a room needs to be inserted to the system and check if
 * they are all in the right values
 * @param company_email - the company's email that the room is in
 *                        checks if the email has exactly 1 @ sign
 * @param id - the id of the room, checks if the id is a positive number
 * @param price - the price per person for entering the room - checks if the
 *                price is a positive number and multiply of 4
 * @param num_ppl - the recommended number of people to enter the room at once
 *                  checks if a positive number
 * @param difficulty - the difficulty of the room, checks if between 1 to 10
 * @return true if all the params are at the correct values false otherwise
 */
bool isValidRoomParams(char *company_email, int id, int price, int num_ppl,
                       int difficulty);
/**
 * receives paramas that an escaper needs to be inserted to the system and
 * check if they are all in the right values
 * @param email - the escapers email, needs to have exactly 1 @ sign
 * @param escaperFaculty - the name of the faculty of the escaper
 *                         checks if its in the right values in the enum given
 *                         at the before the program begins
 * @param skill_level - the skill level of the escaper - checks if between 1
 * to 10
 * @return true if all the params are at the correct values false otherwise
 */
bool isValidEscaperParams(TechnionFaculty escaperFaculty, char *email,
                          int skill_level);
/**
 * receives paramas that a company needs to be inserted to the system and
 * check if they are all in the right values
 * @param companyFaculty - the faculty name to be checked, checks if it's
 *                         mentioned in the listed faculties enum
 * @param email - the company's email, needs to have exactly 1 @ sign
 * @return true if all the params are at the correct values false otherwise
 */
bool isValidCompanyParams(TechnionFaculty companyFaculty, char *email);

/**
 * receives paramas that a reservation needs to be inserted to the system and
 * check if they are all in the right values
 * @param num_ppl - number of people in the reservation - checks if positive
 * @param price - the price to be paid, checks if positive and multiply of 4
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
 * receives params of to rooms, one is the current best match and the other
 * is the one that being checked if better than the first
 * @param escaper - the escaper that is looking for the best matched room
 * @param cur_result - the current calculated result
 * @param cur_room_id - the current room id
 * @param cur_faculty_diff - the current faculty difference
 * @param cur_recommended_room - the current most recommended room
 * @param min_result - ptr to get the min result after calculation
 * @param min_room_id - ptr to get the min room id
 * @param min_faculty_diff - ptr to get the min faculty diff after calculation
 * @param most_recommended_room - ptr to get the most recommended room
 * @param most_recommended_company - ptr to get the company of the most
 * recommende room
 * @param cur_company - the current company
 */

void checkBetterRoom(Escaper escaper, int cur_result, int cur_room_id,
                     int cur_faculty_diff, Room cur_recommended_room,
                     int *min_result, int *min_room_id,
                     int *min_faculty_diff, Room *most_recommended_room,
                     Company *most_recommended_company,
                     Company cur_company);
