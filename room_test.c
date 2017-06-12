//
// Created by adire on 09-Jun-17.
//
#include "test_utilities.h"
#include "room.h"
#include <string.h>
#include <stdlib.h>


bool testRoomCreate() {

    ASSERT_TEST(roomCreate(UNKNOWN , "adi@g", 123, 4, 20, 1, 2, 1) == NULL);
    ASSERT_TEST(roomCreate(PHYSICS , NULL, 123, 4, 20, 1, 2, 1) == NULL);
    ASSERT_TEST(roomCreate(PHYSICS, "adi", 123, 4, 20, 1, 2, 1) == NULL);
    ASSERT_TEST(roomCreate(PHYSICS, "adi@g", 0, 4, 20, 1, 2, 1) == NULL);
    ASSERT_TEST(roomCreate(PHYSICS, "adi@g", 123, 10, 20, 1, 2, 1) == NULL);
    ASSERT_TEST(roomCreate(PHYSICS, "adi@g", 123, 4, -10, 1, 2, 1) == NULL);
    ASSERT_TEST(roomCreate(PHYSICS, "adi@g", 123, 4, 20, 1, 2, 11) == NULL);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(room != NULL);

    roomDestroy(room);
    return true;
}

bool testRoomDestroy() {
    roomDestroy(NULL);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    roomDestroy(room);

    return true;
}

bool testRoomCompareElements() {
    Room room1 = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    Room room2 = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(roomCompareElements(room1, room2) == 0);

    roomDestroy(room2);
    Room room3 = roomCreate(BIOLOGY, "adi@gmail", 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(roomCompareElements(room1, room3) != 0);
    roomDestroy(room3);

    Room room4 = roomCreate(PHYSICS, "adi@gmail", 12, 12, 20, 1, 2, 1);
    ASSERT_TEST(roomCompareElements(room1, room4) != 0);
    roomDestroy(room4);

    roomDestroy(room1);
    return true;
}

bool testRoomCopyElement() {
    ASSERT_TEST(roomCopyElement(NULL) == NULL);

    Room room1 = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    Room room2 = roomCopyElement(room1);

    ASSERT_TEST(roomCompareElements(room1, room2) == 0);

    roomDestroy(room1);
    roomDestroy(room2);
    return true;
}

bool testRoomGetCompanyEmail() {
    ASSERT_TEST(roomGetCompanyEmail(NULL) == NULL);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    char *email = roomGetCompanyEmail(room);
    ASSERT_TEST(strcmp(email, "adi@gmail") == 0);

    free(email);
    roomDestroy(room);
    return true;
}

bool testRoomGetID() {
    ASSERT_TEST(roomGetID(NULL) == -1);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    int id = roomGetID(room);
    ASSERT_TEST(id == 123);

    roomDestroy(room);
    return true;
}

bool testRoomGetPrice() {
    ASSERT_TEST(roomGetPrice(NULL) == -1);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    int price = roomGetPrice(room);
    ASSERT_TEST(price == 12);

    roomDestroy(room);
    return true;
}

bool testRoomGetNumPpl() {
    ASSERT_TEST(roomGetNumPpl(NULL) == -1);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    int num_ppl = roomGetNumPpl(room);
    ASSERT_TEST(num_ppl == 20);

    roomDestroy(room);
    return true;
}


bool testRoomGetDifficulty() {
    ASSERT_TEST(roomGetDifficulty(NULL) == -1);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    int difficulty = roomGetDifficulty(room);
    ASSERT_TEST(difficulty == 1);

    roomDestroy(room);
    return true;
}

bool testRoomGetOpeningTime() {
    ASSERT_TEST(roomGetOpeningTime(NULL) == -1);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    int opening = roomGetOpeningTime(room);
    ASSERT_TEST(opening == 1);

    roomDestroy(room);
    return true;
}

bool testRoomGetClosingTime() {
    ASSERT_TEST(roomGetClosingTime(NULL) == -1);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    int closing = roomGetClosingTime(room);
    ASSERT_TEST(closing == 2);

    roomDestroy(room);
    return true;
}

bool testIsRoomID() {
    ASSERT_TEST(isRoomID(NULL, 123) == false);

    Room room = roomCreate(PHYSICS ,"adi@gmail", 123, 12, 20, 1, 2, 1);
    ASSERT_TEST(isRoomID(room, 123) == true);
    ASSERT_TEST(isRoomID(room, 12) == false);

    roomDestroy(room);
    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testRoomCreate);
    RUN_TEST(testRoomDestroy);
    RUN_TEST(testRoomCompareElements);
    RUN_TEST(testRoomCopyElement);
    RUN_TEST(testRoomGetCompanyEmail);
    RUN_TEST(testRoomGetID);
    RUN_TEST(testRoomGetPrice);
    RUN_TEST(testRoomGetNumPpl);
    RUN_TEST(testRoomGetDifficulty);
    RUN_TEST(testRoomGetOpeningTime);
    RUN_TEST(testRoomGetClosingTime);
    RUN_TEST(testIsRoomID);

    return 0;
}