//
// Created by Shahak on 06/06/2017.
//

#include "company.h"
#include "utils.h"
#include "set.h"

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


Company companyCreate(TechnionFaculty Faculty, char *email) {
    assert(isValidCompanyParams(Faculty, email));
    if (NULL == email) {
        return NULL;
    }
    Company company = malloc(sizeof(*company));
    if (NULL == company) {
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
    return company;
}

void companyDestroy(Company company) {
    if (NULL == company) {
        return;
    }
    setDestroy(company->rooms);
    free(company->email);
    free(company);
}

CompanyErrorCode companyAddRoom(Company company, int id, int price,
                                int num_ppl, int open_time, int close_time,
                                int difficulty) {
    assert(isValidRoomParams(company->companyFaculty, company->email, id,
                             price, num_ppl, difficulty));
    if (NULL == company) {
        return COMPANY_INVALID_PARAMETER;
    }
    Room room = roomCreate(company->companyFaculty, company->email, id, price,
                           num_ppl, open_time, close_time, difficulty);
    if (NULL == room) {
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
    Company ptr = src_company;
    Company company = companyCreate(ptr->companyFaculty, ptr->email);
    return company;
}

char *companyGetEmail(Company company) {
    if (NULL == company) {
        return NULL;
    }
    char *email = malloc(strlen(company->email) + 1);
    if (NULL == email) {
        return NULL;
    }
    strcpy(email, company->email);
    return email;
}

TechnionFaculty companyGetFaculty(Company company) {
    if (NULL == company) {
        return UNKNOWN;
    }
    return company->companyFaculty;
}

Room companyFindRoom(Company company, int room_id,
                     CompanyErrorCode *CompanyError) {
    if (NULL == company || room_id <= 0) {
        *CompanyError = COMPANY_INVALID_PARAMETER;
        return NULL;
    }

    Room room_iterator = setGetFirst(company->rooms);
    //TODO should we check NULL?
    while (NULL != room_iterator) {
        bool isEqual = isRoomID(room_iterator, room_id);
        if (isEqual) {
            *CompanyError = COMPANY_SUCCESS;
            return room_iterator;
        }
        room_iterator = setGetNext(company->rooms);
    }
    *CompanyError = COMPANY_ROOM_DOES_NOT_EXIST;
    return NULL;
}

bool isCompanyEmailEqual(Company company, char *email,
                         CompanyErrorCode *CompanyError) {
    if (NULL == company || NULL == email) {
        *CompanyError = COMPANY_INVALID_PARAMETER;
        return false;
    }
    *CompanyError = COMPANY_SUCCESS;

    if (strcmp(company->email, email) == 0) {
        return true;
    }
    return false;
}

bool isRoomIdInCompany(Company company, int room_id) {
    if (NULL == company || room_id <= 0) {
        return false;
    }
    Room room_iterator = setGetFirst(company->rooms);
    if (NULL == room_iterator) {
        return false;
    }
    while (NULL != room_iterator) {
        RoomErrorCode RoomError;
        if (roomGetID(room_iterator) == room_id) {
            return true;
        }
        room_iterator = setGetNext(company->rooms);
    }
    return false;
}

Room mostRecommendedRoom(Company company, TechnionFaculty EscaperFaculty,
                         int reservation_num_ppl, int escaper_skill_level,
                         int *result, int *faculty_difference, int *room_id) {
    Room room_iterator = setGetFirst(company->rooms);
    if (NULL == room_iterator) {
        return NULL;
    }

    Room best_room = NULL;
    int best_result = INVALID_PARAMETER;
    int best_id = INVALID_PARAMETER;
    int best_difference =
            abs((int)EscaperFaculty - (int)(company->companyFaculty));

    while (NULL != room_iterator) {
        RoomErrorCode RoomError;
        int room_num_ppl = roomGetNumPpl(room_iterator);
        int room_difficulty = roomGetDifficulty(room_iterator);
        int tmp_result = calcRoomMatch(room_num_ppl, reservation_num_ppl,
                                       room_difficulty, escaper_skill_level);
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
    *faculty_difference = best_difference;
    *room_id = best_id;
    return best_room;
}

int companyGetminRoomID(Company company) {
    if (NULL == company) {
        return  INVALID_PARAMETER;
    }
    int min_id = INVALID_PARAMETER;
    Room room_iterator = setGetFirst(company->rooms);
    while (NULL != room_iterator) {
        RoomErrorCode RoomError;
        int tmp_id = roomGetID(room_iterator);
        if (tmp_id < min_id || min_id == INVALID_PARAMETER) {
            min_id = tmp_id;
        }
        room_iterator = setGetNext(company->rooms);
    }
    return min_id;
}


