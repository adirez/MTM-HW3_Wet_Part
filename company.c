//
// Created by Shahak on 06/06/2017.
//

#include "company.h"
#include "utils.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INVALID_PARAMETER -1

struct Company_t {
    TechnionFaculty companyFaculty;
    char *email;
    Set rooms;
};


/**...........................................................................*/
/**-----------------------FUNCTIONS-IMPLEMENTATIONS---------------------------*/
/**...........................................................................*/


Company companyCreate(TechnionFaculty Faculty, char *email,
                      CompanyErrorCode *companyError) {
    if (!isValidCompanyParams(Faculty, email)) {
        *companyError = COMPANY_INVALID_PARAMETER;
        return NULL;
    }
    Company company = malloc(sizeof(*company));
    if (NULL == company) {
        *companyError = COMPANY_OUT_OF_MEMORY;
        return NULL;
    }

    company->email = malloc(strlen(email) + 1);
    if (NULL == company->email) {
        free(company);
        return NULL;
    }
    strcpy(company->email, email);
    company->companyFaculty = Faculty;
    company->rooms = setCreate(roomCopyElement,roomDestroy,roomCompareElements);
    *companyError = COMPANY_SUCCESS;
    return company;
}

void companyDestroy(SetElement element) {
    if (NULL == element) {
        return;
    }
    Company company = element;
    setDestroy(company->rooms);
    free(company->email);
    free(company);
}

CompanyErrorCode companyAddRoom(Company company, int id, int price, int num_ppl,
                                int open_time, int close_time, int difficulty) {
    if (NULL == company || !isValidRoomParams(company->email, id, price,
                                              num_ppl, difficulty)) {
        return COMPANY_INVALID_PARAMETER;
    }
    RoomErrorCode roomError;
    Room room = roomCreate(company->companyFaculty, company->email, id, price,
                        num_ppl, open_time, close_time, difficulty, &roomError);
    if (NULL == room) {
        if (roomError == INVALID_PARAMETER) {
            return COMPANY_INVALID_PARAMETER;
        }
        return COMPANY_OUT_OF_MEMORY;
    }

    SetResult addResult = setAdd(company->rooms, room);
    roomDestroy(room);
    if (addResult == SET_ITEM_ALREADY_EXISTS) {
        return COMPANY_ROOM_ALREADY_EXISTS;
    } else if (addResult == SET_OUT_OF_MEMORY) {
        return COMPANY_OUT_OF_MEMORY;
    }
    return COMPANY_SUCCESS;
}

CompanyErrorCode companyRemoveRoom(Company company, Room room) {
    if (NULL == company || NULL == room) {
        return COMPANY_INVALID_PARAMETER;
    }
    SetResult RemoveResult = setRemove(company->rooms, room);
    if (RemoveResult == SET_ITEM_DOES_NOT_EXIST) {
        return COMPANY_ROOM_DOES_NOT_EXIST;
    }
    return COMPANY_SUCCESS;
}

int companyCompareElements(SetElement company1, SetElement company2) {
    if (NULL == company1 || NULL == company2) {
        return INVALID_PARAMETER;
    }
    Company ptr1 = company1, ptr2 = company2;

    int tmp_cmp = strcmp(ptr1->email, ptr2->email);
    if (tmp_cmp == 0) {
        return 0;
    } else {
        return 1;
    }
}

SetElement companyCopyElement(SetElement src_company) {
    if (NULL == src_company) {
        return NULL;
    }
    CompanyErrorCode companyError;
    Company ptr = src_company;
    Company company = companyCreate(ptr->companyFaculty, ptr->email,
                                    &companyError);
    if (companyError != COMPANY_SUCCESS) {
        return NULL;
    }
    return company;
}

char *companyGetEmail(Company company, CompanyErrorCode *companyError) {
    if (NULL == company) {
        *companyError = COMPANY_INVALID_PARAMETER;
        return NULL;
    }
    char *email = malloc(strlen(company->email) + 1);
    if (NULL == email) {
        *companyError = COMPANY_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(email, company->email);
    *companyError = COMPANY_SUCCESS;
    return email;
}

TechnionFaculty companyGetFaculty(Company company) {
    if (NULL == company) {
        return UNKNOWN;
    }
    return company->companyFaculty;
}

bool isCompanyEmailEqual(Company company, char *email) {
    if (NULL == company || NULL == email) {
        return false;
    }
    if (strcmp(company->email, email) == 0) {
        return true;
    }
    return false;
}

int companyGetMinRoomID(Company company) {
    if (NULL == company) {
        return  INVALID_PARAMETER;
    }
    int min_id = INVALID_PARAMETER;
    Room room_iterator = setGetFirst(company->rooms);
    while (NULL != room_iterator) {
        int tmp_id = roomGetID(room_iterator);
        if (tmp_id < min_id || min_id == INVALID_PARAMETER) {
            min_id = tmp_id;
        }
        room_iterator = setGetNext(company->rooms);
    }
    return min_id;
}

Room companyGetRoomByID(Company company, int id){
    if (NULL == company){
        return NULL;
    }
    Room room_iterator = setGetFirst(company->rooms);

    while (NULL != room_iterator){
        if(roomGetID(room_iterator) == id){
            return room_iterator;
        }
        room_iterator = setGetNext(company->rooms);
    }
    return NULL;
}

Room companyMostRecommendedRoom(Company company, TechnionFaculty escaperFaculty,
                                int P_e, int skill, int *result,
                                int *faculty_distance,
                                int *room_id) {
    Room best_room = NULL;
    int best_result = INVALID_PARAMETER;
    int best_id = INVALID_PARAMETER;
    int best_distance = abs((int)escaperFaculty-(int)(company->companyFaculty));
    Room room_iterator = setGetFirst(company->rooms);
    if (NULL == room_iterator) {
        return NULL;
    }
    while (NULL != room_iterator) {
        int P_r = roomGetNumPpl(room_iterator);
        int difficulty = roomGetDifficulty(room_iterator);
        int tmp_result = calcRoomMatch(P_e, P_r, difficulty, skill);
        if (best_result == INVALID_PARAMETER || tmp_result < best_result) {
            best_room = room_iterator;
            best_result = tmp_result;
            best_id = roomGetID(room_iterator);
        }
        if (tmp_result == best_result ) {
            int temp_id = roomGetID(room_iterator);
            if (temp_id < best_id) {
                best_room = room_iterator;
                best_result = tmp_result;
                best_id = temp_id;
            }
        }
        room_iterator = setGetNext(company->rooms);
    }
    *result = best_result;
    *faculty_distance = best_distance;
    *room_id = best_id;
    return best_room;
}