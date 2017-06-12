//
// Created by Shahak on 06/06/2017.
//

#include "room.h"
#include "utils.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INVALID_PARAMETER -1

struct Room_t {
    TechnionFaculty roomFaculty;
    char *company_email;
    int id;
    int price;
    int num_ppl;
    int open_time;
    int close_time;
    int difficulty;
};

/**...........................................................................*/
/**-----------------------FUNCTIONS-IMPLEMENTATIONS---------------------------*/
/**...........................................................................*/


Room roomCreate(TechnionFaculty roomFaculty, char *company_email, int id,
                int price, int num_ppl, int open_time, int close_time,
                int difficulty, RoomErrorCode *roomError) {
    if(NULL == roomError){
        return NULL;
    }
    if (!isValidRoomParams(company_email, id, price, num_ppl, difficulty) ||
            !isValidFacultyName(roomFaculty)){
        *roomError = ROOM_INVALID_PARAMETER;
        return NULL;
    }
    Room room = malloc(sizeof(*room));
    if (NULL == room) {
        *roomError = ROOM_OUT_OF_MEMORY;
        return NULL;
    }

    room->roomFaculty = roomFaculty;
    room->company_email = malloc(strlen(company_email) + 1);
    if (NULL == room->company_email) {
        free(room);
        return NULL;
    }
    strcpy(room->company_email, company_email);
    room->id = id;
    room->price = price;
    room->num_ppl = num_ppl;
    room->open_time = open_time;
    room->close_time = close_time;
    room->difficulty = difficulty;
    *roomError = ROOM_SUCCESS;
    return room;
}

void roomDestroy(SetElement element) {
    if (NULL == element) {
        return;
    }
    Room room = element;
    free(room->company_email);
    free(room);
}

int roomCompareElements(SetElement element1, SetElement element2) {
    if (NULL == element1 || NULL == element2){
        return INVALID_PARAMETER;
    }
    Room room1 = element1, room2 = element2;
    int id_cmp = room1->id - room2->id;
    if (id_cmp != 0){
        return id_cmp;
    }
    assert(id_cmp == 0);
    return (int)room1->roomFaculty - (int)room2->roomFaculty;
}


SetElement roomCopyElement(SetElement src_room) {
    if (NULL == src_room) {
        return NULL;
    }
    RoomErrorCode roomError;
    Room ptr = src_room; //to make the code clearer
    Room room = roomCreate(ptr->roomFaculty, ptr->company_email, ptr->id,
                           ptr->price, ptr->num_ppl, ptr->open_time,
                           ptr->close_time, ptr->difficulty, &roomError);
    if(roomError != ROOM_SUCCESS){
        return NULL;
    }
    return room;
}

TechnionFaculty roomGetNameFaculty(Room room) {
    if (NULL == room) {
        return UNKNOWN;
    }
    return room->roomFaculty;
}

char *roomGetCompanyEmail(Room room, RoomErrorCode *roomError) {
    if (NULL == roomError){
        return NULL;
    }
    if (NULL == room) {
        *roomError = ROOM_NULL_PARAMETER;
        return NULL;
    }
    char *output = malloc(strlen(room->company_email) + 1);
    if (NULL == output) {
        *roomError = ROOM_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(output, room->company_email);
    *roomError = ROOM_SUCCESS;
    return output;
}

int roomGetID(Room room) {
    if (NULL == room) {
        return INVALID_PARAMETER;
    }
    return room->id;
}

int roomGetPrice(Room room) {
    if (NULL == room) {
        return INVALID_PARAMETER;
    }
    return room->price;
}

int roomGetNumPpl(Room room) {
    if (NULL == room) {
        return INVALID_PARAMETER;
    }
    return room->num_ppl;
}

int roomGetDifficulty(Room room) {
    if (NULL == room) {
        return INVALID_PARAMETER;
    }
    return room->difficulty;
}

int roomGetOpeningTime(Room room) {
    if (NULL == room) {
        return INVALID_PARAMETER;
    }
    return room->open_time;
}

int roomGetClosingTime(Room room) {
    if (NULL == room) {
        return INVALID_PARAMETER;
    }
    return room->close_time;
}

bool isRoomID(Room room, int id) {
    if (NULL == room) {
        return false;
    }

    if (id == room->id) {
        return true;
    }
    return false;
}