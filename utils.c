//
// Created by Shahak on 06/06/2017.
//

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"
#include "mtm_ex3.h"
#include "utils.h"

#define INVALID_PARAMETER -1
#define AT_SYMBOL '@'
#define HYPHEN '-'
#define MIN_DIFFICULTY_OR_SKILL 1
#define MAX_DIFFICULTY_OR_SKILL 10
#define MIN_NUMBER 48 //represents '0' in ASCII
#define MAX_NUMBER 57 //represents '9' in ASCII
#define MIN_HOUR 0
#define MAX_HOUR 24
#define HOURS_STR_LEN 5 //according to the format "HH-HH"
#define DAY_HOUR_MIN_LEN 3 //according to the format "D-H"

bool isEmailValid(char *email) {
    if (NULL == email) {
        return false;
    }
    if (strlen(email) == 0) {
        return false;
    }
    int count = 0;
    for (int i = 0; i < strlen(email) + 1; ++i) {
        if (email[i] == AT_SYMBOL) {
            count++;
            if (count > 1) {
                return false;
            }
        }
    }
    if (count == 1) {
        return true;
    }
    return false;
}

bool isFacultyValid(TechnionFaculty Faculty) {
    if (Faculty < CIVIL_ENGINEERING || Faculty >= UNKNOWN) {
        return false;
    }

    return true;
}

bool getHoursFromStr(char *hours_str, int *opening_time, int *closing_time) {
    int tmp_opening = 0, tmp_closing = 0;
    if (NULL == hours_str || strlen(hours_str) != HOURS_STR_LEN) {
        return false;
    }
    char tmp_char = hours_str[0];
    if (tmp_char < MIN_NUMBER || tmp_char > MAX_NUMBER) {
        return false;
    }
    tmp_opening = 10 * atoi(&tmp_char);
    tmp_char = hours_str[1];
    if (tmp_char < MIN_NUMBER || tmp_char > MAX_NUMBER) {
        return false;
    }
    tmp_opening += atoi(&tmp_char);

    tmp_char = hours_str[2];
    if (tmp_char != HYPHEN) {
        return false;
    }

    tmp_char = hours_str[3];
    if (tmp_char < MIN_NUMBER || tmp_char > MAX_NUMBER) {
        return false;
    }
    tmp_closing = 10 * atoi(&tmp_char);
    tmp_char = hours_str[4];
    if (tmp_char < MIN_NUMBER || tmp_char > MAX_NUMBER) {
        return false;
    }
    tmp_closing += atoi(&tmp_char);

    if (tmp_opening < MIN_HOUR || tmp_opening > MAX_HOUR ||
        tmp_closing < MIN_HOUR || tmp_closing > MAX_HOUR ||
        tmp_opening >= tmp_closing) {
        return false;
    }

    *opening_time = tmp_opening;
    *closing_time = tmp_closing;
    return true;
}

static bool isThereHyphen(char *src_str) {
    int hyphen_counter = 0, i;
    for (i = 0; src_str[i] != '\0'; ++i) {
        if (src_str[i] == HYPHEN) {
            hyphen_counter++;
        }
        if (hyphen_counter > 1) {
            return false;
        }
    }
    if (hyphen_counter == 0) {
        return false;
    }
    if (src_str[i-1] == HYPHEN) {
        return false;
    }
    return true;
}

static bool isLegalDayHourInput(char *src_str) {
    for (int i = 0; src_str[i] != '\0'; ++i) {
        //TODO: check if space and tabs and stuff are legal
        if ((src_str[i] < MIN_NUMBER || src_str[i] > MAX_NUMBER) &&
            src_str[i] != HYPHEN) {
            return false;
        }
    }

    if (isThereHyphen(src_str) == false) {
        return false;
    }

    return true;
}

bool getDayAndHourFromStr(char* src_str, int *day, int *hour) {
    if (NULL == src_str || strlen(src_str) < DAY_HOUR_MIN_LEN) {
        return false;
    }
    if (isLegalDayHourInput(src_str) == false) {
        return false;
    }
    char source_string[MAX_LEN];
    strcpy(source_string, src_str);
    char *token;
    char buffer[2] = "-";
    token = strtok(source_string, buffer);
    *day = atoi(token);
    token = strtok(NULL, buffer);
    *hour = atoi(token);
    if(*day < 0){
        return false;
    }
    if(*hour < MIN_HOUR || *hour > MAX_HOUR){
        return false;
    }

    return true;
}

bool isPriceMultiplyOfFour(int price) {
    if (price <= 0) {
        return false;
    }

    if (price % 4 == 0) {
        return true;
    }

    return false;
}

bool isValidDifficultyOrSkill(int difficulty_or_skill) {
    if (difficulty_or_skill < MIN_DIFFICULTY_OR_SKILL ||
        difficulty_or_skill > MAX_DIFFICULTY_OR_SKILL) {
        return false;
    }
    return true;
}

void initializeArr(int *arr, int n) {
    for (int idx = 0; idx < n; idx++) {
        *(arr + idx) = 0;
    }
    return;
}
