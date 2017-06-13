//
// Created by Shahak on 06/06/2017.
//



/**...........................................................................*/
/**---------------------------DEFINES-&-INCLUDES------------------------------*/
/**...........................................................................*/



#ifndef HW3_ROOM_H
#define HW3_ROOM_H

#include "mtm_ex3.h"
#include "set.h"


/**...........................................................................*/
/**-----------------------------STRUCTURE-------------------------------------*/
/**...........................................................................*/



/**
 * Room will be implemented in this file as a set
 */
typedef struct Room_t *Room;

/**
 * a type used to return error codes related to Room
 */
typedef enum {
    ROOM_SUCCESS,
    ROOM_NULL_PARAMETER,
    ROOM_INVALID_PARAMETER,
    ROOM_OUT_OF_MEMORY
} RoomErrorCode;


/**...........................................................................*/
/**-------------------------FUNCTIONS-DECLARATIONS----------------------------*/
/**...........................................................................*/


/**
 * creates a new room according to the relevant input parameters and returns
 * the relevant result code.
 * @param company_email - the email of the company the rooms will be listed
 *        under
 * @param id - the id of the room
 * @param price - entry price per person (must be a multiple of 4)
 * @param num_ppl - recommended number of people for this specific room
 * @param open_time - the calculated opening time
 * @param close_time - the calculated closing time
 * @param difficulty - the difficulty level of the room
 * @param roomError - enum to get the result of the func:
 *                    ROOM_SUCCESS - room created successfully
 *                    ROOM_INVALID_PARAMETER - one of the params is Invalid
 *                    ROOM_OUT_OF_MEMORY - Allocation problem occurred
 * @return Room - a pointer to the new room if everything went well
 *         NULL - if the allocation was not successful or company_email is NULL
 */
Room roomCreate(TechnionFaculty roomFaculty, char *company_email, int id,
                int price, int num_ppl, int open_time, int close_time,
                int difficulty, RoomErrorCode *roomError);

/**
 * destroys a room and all of it's components. releases all relevant
 * allocated memory.
 * @param element - a pointer to the relevant room to be destroyed
 */
void roomDestroy(SetElement element);

/**
 * a comparison of two rooms by faculty and id
 * @param element1 - the first room
 * @param element2 - the second room
 * @return 0 if same, positive num if the first is greater, negative otherwise
 *         if one of the elements is NULL returns -1
 */
int roomCompareElements(SetElement element1, SetElement element2);

/**
 * receives a source room element and copies it's data into a newly created
 * room element
 * @param src_room - the source room that needs to be copied
 * @return pointer to the new allocated room or NULL if the allocation failed
 */
SetElement roomCopyElement(SetElement src_room);

/**
 * receives a room and returns the name of the faculty its under
 * @param room - the requested room
 * @return the faculty name
 */
TechnionFaculty roomGetNameFaculty(Room room);

/**
 * receives a room and returns the email of the company that the room is listed
 * under
 * @param room - the requested room
 * @param roomError - enum to get the result of the func:
 *                    ROOM_SUCCESS - email returned successfully
 *                    ROOM_NULL_PARAMETER - ptr to room is NULL
 * @return a pointer to the email if the allocation worked and NULL if failed
 */
char *roomGetCompanyEmail(Room room, RoomErrorCode *roomError);

/**
 * receives a room and returns it's ID
 * @param room - the requested room
 * @return the id of the room or -1 if the room ptr is NULL
 */
int roomGetID(Room room);

/**
 * receives a room and returns it's price
 * @param room - the requested room
 * @return the price of the room or -1 if the room ptr is NULL
 */
int roomGetPrice(Room room);

/**
 * receives a room and returns the recommended number of people to participate
 * @param room - the requested room
 * @return the recommended number of people or -1 if the room ptr is NULL
 */
int roomGetNumPpl(Room room);

/**
 * receives a room and returns it's difficulty level
 * @param room - the requested room
 * @return the difficulty level of the room or -1 if the room ptr is NULL
 */
int roomGetDifficulty(Room room);

/**
 * receives a room and returns it's opening time
 * @param room - the requested room
 * @return the opening time of the room or -1 if the room ptr is NULL
 */
int roomGetOpeningTime(Room room);

/**
 * receives a room and returns it's closing time
 * @param room - the requested room
 * @return the closing time of the room or -1 if the room ptr is NULL
 */
int roomGetClosingTime(Room room);

/**
 * receives a room and an id and returns true if the room's id and the received
 * id are equal
 * @param room - the room to be checked
 * @param id - the id we're looking for
 * @return true - if the room's id equals 'id'
 *         false - if the room's id is different than 'id' or room is NULL
 */
bool isRoomID(Room room, int id);

#endif //HW3_ROOM_H
