//
// Created by adire on 09-Jun-17.
//
#include "test_utilities.h"
#include "room.h"
#include <string.h>


bool testRoomCreate() {

    RoomErrorCode errorCode;

    ASSERT_TEST(roomCreate(NULL, 123, 4, 20, 1, 2, 1, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);
    ASSERT_TEST(roomCreate("adi", 123, 4, 20, 1, 2, 1, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);
    ASSERT_TEST(roomCreate("adi@g", 0, 4, 20, 1, 2, 1, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);
    ASSERT_TEST(roomCreate("adi@g", 123, 10, 20, 1, 2, 1, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);
    ASSERT_TEST(roomCreate("adi@g", 123, 4, -10, 1, 2, 1, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);
    ASSERT_TEST(roomCreate("adi@g", 123, 4, 20, 1, 2, 11, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    return true;
}

bool testRoomDestroy() {

    ASSERT_TEST(roomDestroy(NULL) == ROOM_INVALID_PARAMETER);

    RoomErrorCode errorCode;
    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(roomDestroy(room) == ROOM_SUCCESS);

    return true;
}

bool testRoomCompareElements() {
    RoomErrorCode errorCode;
    Room room1 = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    Room room2 = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    ASSERT_TEST(roomCompareElements(room1, room2) == 0);

    roomDestroy(room2);
    Room room3 = roomCreate("adi@gmai", 123, 12, 20, 1, 2, 1, &errorCode);
    ASSERT_TEST(roomCompareElements(room1, room3) != 0);
    roomDestroy(room3);

    Room room4 = roomCreate("adi@gmail", 12, 12, 20, 1, 2, 1, &errorCode);
    ASSERT_TEST(roomCompareElements(room1, room4) != 0);
    roomDestroy(room4);

    roomDestroy(room1);
    return true;
}

bool testRoomCopyElement() {
    RoomErrorCode errorCode;
    Room room1 = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    Room room2 = roomCopyElement(room1);

    ASSERT_TEST(roomCompareElements(room1, room2) == 0);

    roomDestroy(room1);
    roomDestroy(room2);

    return true;
}

bool testGetCompanyEmail() {
    RoomErrorCode errorCode;
    ASSERT_TEST(roomGetCompanyEmail(NULL, &errorCode) == NULL);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    char *email = roomGetCompanyEmail(room, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(strcmp(email, "adi@gmail") == 0);

    roomDestroy(room);
    return true;
}

bool testRoomGetID() {
    RoomErrorCode errorCode;
    ASSERT_TEST(roomGetID(NULL, &errorCode) == -1);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    int id = roomGetID(room, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(id == 123);

    return true;
}

bool testRoomGetPrice() {
    RoomErrorCode errorCode;
    ASSERT_TEST(roomGetPrice(NULL, &errorCode) == -1);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    int price = roomGetPrice(room, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(price == 12);

    roomDestroy(room);
    return true;
}

bool testRoomGetNumPpl() {
    RoomErrorCode errorCode;
    ASSERT_TEST(roomGetNumPpl(NULL, &errorCode) == -1);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    int num_ppl = roomGetNumPpl(room, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(num_ppl == 20);

    return true;
}


bool testRoomGetDifficulty() {
    RoomErrorCode errorCode;
    ASSERT_TEST(roomGetDifficulty(NULL, &errorCode) == -1);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    int difficulty = roomGetDifficulty(room, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(difficulty == 1);

    roomDestroy(room);
    return true;
}

bool testRoomGetOpeningTime() {
    RoomErrorCode errorCode;
    ASSERT_TEST(roomGetOpeningTime(NULL, &errorCode) == -1);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    int opening = roomGetOpeningTime(room, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(opening == 1);

    roomDestroy(room);
    return true;
}

bool testRoomGetClosingTime() {
    RoomErrorCode errorCode;
    ASSERT_TEST(roomGetClosingTime(NULL, &errorCode) == -1);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    int closing = roomGetClosingTime(room, &errorCode);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(closing == 2);

    roomDestroy(room);
    return true;
}

bool testIsRoomID() {
    RoomErrorCode errorCode;
    ASSERT_TEST(isRoomID(NULL, 123, &errorCode) == false);
    ASSERT_TEST(errorCode == ROOM_INVALID_PARAMETER);

    Room room = roomCreate("adi@gmail", 123, 12, 20, 1, 2, 1, &errorCode);
    ASSERT_TEST(isRoomID(room, 123, &errorCode) == true);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);
    ASSERT_TEST(isRoomID(room, 12, &errorCode) == false);
    ASSERT_TEST(errorCode == ROOM_SUCCESS);

    roomDestroy(room);
    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testRoomCreate);
    RUN_TEST(testRoomDestroy);
    RUN_TEST(testRoomCompareElements);
    RUN_TEST(testRoomCopyElement);
    RUN_TEST(testGetCompanyEmail);
    RUN_TEST(testRoomGetID);
    RUN_TEST(testRoomGetPrice);
    RUN_TEST(testRoomGetNumPpl);
    RUN_TEST(testRoomGetDifficulty);
    RUN_TEST(testRoomGetOpeningTime);
    RUN_TEST(testRoomGetClosingTime);
    RUN_TEST(testIsRoomID);

    return 0;
}