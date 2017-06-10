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
    char *email;
    TechnionFaculty FacultyOfCompany;
    Set company_rooms;
};

Company companyCreate(char *company_email, TechnionFaculty Faculty,
                      CompanyErrorCode *CompanyError) {
    assert(NULL != company_email);
    if (NULL == company_email || !isEmailValid(company_email) ||
        !isFacultyValid(Faculty)) {
        *CompanyError = COMPANY_INVALID_PARAMETER;
        return NULL;
    }

    Company company = malloc(sizeof(*company));
    if (NULL == company) {
        *CompanyError = COMPANY_OUT_OF_MEMORY;
        return NULL;
    }

    company->email = malloc(strlen(company_email) + 1);
    if (NULL == company->email) {
        free(company);
        *CompanyError = COMPANY_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(company->email, company_email);
    company->FacultyOfCompany = Faculty;
    company->company_rooms = setCreate(roomCopyElement, roomFreeElement,
                                       roomCompareElements);

    *CompanyError = COMPANY_SUCCESS;
    return company;
}

CompanyErrorCode companyDestroy(Company company) {
    if (NULL == company) {
        return COMPANY_INVALID_PARAMETER;
    }
    setDestroy(company->company_rooms);
    free(company->email);
    free(company);
    return COMPANY_SUCCESS;
}

CompanyErrorCode companyAddRoom(Company company, int room_id, int price,
                                int num_ppl, int opening_time, int closing_time,
                                int difficulty) {
    assert(NULL != company && NULL != company_email && NULL != working_hrs);
    if (company == NULL) {
        return COMPANY_INVALID_PARAMETER;
    }
    RoomErrorCode RoomError;
    Room room = roomCreate(company->email, room_id, price, num_ppl,
                           opening_time, closing_time, difficulty, &RoomError);
    if (RoomError == ROOM_INVALID_PARAMETER) {
        return COMPANY_INVALID_PARAMETER;
    } else if (RoomError == ROOM_OUT_OF_MEMORY) {
        return COMPANY_OUT_OF_MEMORY;
    }

    SetResult AddResult = setAdd(company->company_rooms, room);
    roomDestroy(room);
    if (AddResult == SET_NULL_ARGUMENT) {
        return COMPANY_INVALID_PARAMETER;
    } else if (AddResult == SET_ITEM_ALREADY_EXISTS) {
        return COMPANY_ROOM_ALREADY_EXISTS;
    } else if (AddResult == SET_OUT_OF_MEMORY) {
        return COMPANY_OUT_OF_MEMORY;
    }
    return COMPANY_SUCCESS;
}

CompanyErrorCode companyRemoveRoom(Company company, Room room) {
    if (NULL == company || NULL == room) {
        return COMPANY_INVALID_PARAMETER;
    }
    SetResult RemoveResult = setRemove(company->company_rooms, room);
    if (RemoveResult == SET_NULL_ARGUMENT) {
        return COMPANY_INVALID_PARAMETER;
    } else if (RemoveResult == SET_ITEM_DOES_NOT_EXIST) {
        return COMPANY_ROOM_DOES_NOT_EXIST;
    }
    return COMPANY_SUCCESS;
}

int companyCompareElements(SetElement company_1, SetElement company_2) {
    if (NULL == company_1 || NULL == company_2) {
        return INVALID_PARAMETER;
    }
    Company ptr1 = company_1, ptr2 = company_2;

    int tmp_cmp = strcmp(ptr1->email, ptr2->email);
    if (tmp_cmp == 0) {
        return 0;
    } else {
        return 1;
    }
}

void companyFreeElement(SetElement company) {
    if (NULL == company) {
        return;
    }
    companyDestroy(company);
}

SetElement companyCopyElement(SetElement src_company) {
    if (NULL == src_company) {
        return NULL;
    }
    Company ptr = src_company; //to make the code clearer
    CompanyErrorCode CopyResult;
    Company company = companyCreate(ptr->email, ptr->FacultyOfCompany,
                                    &CopyResult);
    if (CopyResult == COMPANY_OUT_OF_MEMORY ||
        CopyResult == COMPANY_INVALID_PARAMETER) {
        return NULL;
    }
    return company;
}

char *companyGetEmail(Company company, CompanyErrorCode *CompanyError) {
    if (NULL == company) {
        *CompanyError = COMPANY_INVALID_PARAMETER;
        return NULL;
    }
    char *output = malloc(strlen(company->email) + 1);
    if (NULL == output) {
        *CompanyError = COMPANY_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(output, company->email);
    *CompanyError = COMPANY_SUCCESS;
    return output;
}

TechnionFaculty companyGetFaculty(Company company,
                                  CompanyErrorCode *CompanyError) {
    if (NULL == company) {
        *CompanyError = COMPANY_INVALID_PARAMETER;
        return UNKNOWN;
    }

    *CompanyError = COMPANY_SUCCESS;
    return company->FacultyOfCompany;
}

Room companyFindRoom(Company company, int room_id,
                     CompanyErrorCode *CompanyError) {
    if (NULL == company || room_id <= 0) {
        *CompanyError = COMPANY_INVALID_PARAMETER;
        return NULL;
    }

    Room room_iterator = setGetFirst(company->company_rooms);
    //TODO should we check NULL?
    while (NULL != room_iterator) {
        RoomErrorCode RoomError;
        bool isEqual = isRoomID(room_iterator, room_id, &RoomError);
        if (RoomError == ROOM_INVALID_PARAMETER) {
            *CompanyError = COMPANY_INVALID_PARAMETER;
            return NULL;
        }
        if (isEqual) {
            *CompanyError = COMPANY_SUCCESS;
            return room_iterator;
        }
        room_iterator = setGetNext(company->company_rooms);
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
    Room room_iterator = setGetFirst(company->company_rooms);
    if (NULL == room_iterator) {
        return false;
    }
    while (NULL != room_iterator) {
        RoomErrorCode RoomError;
        if (roomGetID(room_iterator, &RoomError) == room_id) {
            return true;
        }
        room_iterator = setGetNext(company->company_rooms);
    }
    return false;
}

Room mostRecommendedRoom(Company company, TechnionFaculty EscaperFaculty,
                         int reservation_num_ppl, int escaper_skill_level,
                         int *result, int *faculty_difference, int *room_id) {
    Room room_iterator = setGetFirst(company->company_rooms);
    if (NULL == room_iterator) {
        return NULL;
    }

    Room best_room = NULL;
    int best_result = INVALID_PARAMETER;
    int best_id = INVALID_PARAMETER;
    int best_difference =
            abs((int)EscaperFaculty - (int)(company->FacultyOfCompany));

    while (NULL != room_iterator) {
        RoomErrorCode RoomError;
        int room_num_ppl = roomGetNumPpl(room_iterator, &RoomError);
        int room_difficulty = roomGetDifficulty(room_iterator, &RoomError);
        int tmp_result = calcRoomMatch(room_num_ppl, reservation_num_ppl,
                                       room_difficulty, escaper_skill_level);
        if (best_result == INVALID_PARAMETER || tmp_result < best_result) {
            best_room = room_iterator;
            best_result = tmp_result;
            best_id = roomGetID(room_iterator, &RoomError);
        }
        if (tmp_result == best_result ) {
            int temp_id = roomGetID(room_iterator, &RoomError);
            if (temp_id < best_id) {
                best_room = room_iterator;
                best_result = tmp_result;
                best_id = temp_id;
            }
        }
        room_iterator = setGetNext(company->company_rooms);
    }
    *result = best_result;
    *faculty_difference = best_difference;
    *room_id = best_id;
    return best_room;
}
