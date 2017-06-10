//
// Created by Shahak on 07/06/2017.
//

#include <stdlib.h>
#include <assert.h>

#include "escape_technion.h"
#include "utils.h"

#define INVALID_PARAMETER -1

struct EscapeTechnion_t {
    Set companies;
    Set escapers;
    List reservations;

    int *faculties_earnings;
    int current_day;
};

/**
 * receives an email and an escapeTechnion system and checks if the email
 * already exists in the system
 * @param email - the email to be checked
 * @param escapeTechnion - the system to iterate through
 * @return true - if the email is in use
 *         false - if the email doesn't exist in the system
 */
static bool isCompanyWithEmail(char *email, EscapeTechnion escapeTechnion);

/**
 * receives a company and an escapeTechnion system and checks if the company is
 * listed in a reservation in the system
 * @param company - the company to look for
 * @param escapeTechnion - the system to iterate through
 * @return true - if the company was found in the system
 *         false - if the company wasn't found in the system
 */
static bool isReservationForCompany(Company company,
                                    EscapeTechnion escapeTechnion);

/**
 * receives a room and an escapeTechnion system and checks if the room is listed
 * in any of the reservations in the system
 * @param room - the room to look for
 * @param escapeTechnion - the system to iterate through
 * @return true - if the room was found in a reservation in the system
 *         false - if the room wasn't found in a reservation in the system
 */
static bool isReservationForRoom(Room room, EscapeTechnion escapeTechnion);

/**
 * receives an escapeTechnion system and an email address and checks if the
 * email is listed as an escaper's email in the escapers list
 * @param email - email of a client to look for
 * @param escapeTechnion - the system to iterate through
 * @return true - if the email exists in the system
 *         false - if the email doesn't exist in the system
 */
static bool isEscaperWithEmail(char *email, EscapeTechnion escapeTechnion);

/**
 * receives an escaper and an escapeTechnion system and checks if the escaper is
 * listed in any of the reservations in the system
 * @param escaper - the escaper to look for
 * @param escapeTechnion - the system to iterate through
 * @return true - if the escaper was found in the system
 *         false - if the escaper wasn't found in the system
 */
//static bool isReservationForEscaper(Escaper escaper,
//                                    EscapeTechnion escapeTechnion);

/**
 * receives an email and an escapeTechnion system and checks if the email is
 * listed as a company's email in the system
 * @param email - the email to be checked
 * @param escapeTechnion - the system to iterate through
 * @return a pointer to the company if found, NULL if not found
 */
static Company findCompany(char *email, EscapeTechnion escapeTechnion);

/**
 * receives a room id, a faculty and an escapeTechnion system and checks if the
 * id is listed in the system under the specified faculty
 * @param room_id - the id to be checked
 * @param escapeTechnion - the system to iterate through
 * @return a pointer to the room if found, NULL if not found
 */
static Room escapeSystemFindRoom(int room_id, TechnionFaculty FacultyOfRoom,
                                 EscapeTechnion escapeTechnion,
                                 Company *company_of_room);

/**
 * receives an escapeTechnion system room and an email of an escaper, iterates
 * through the system to find an escaper with the specific email
 * @param email - the email we're looking for
 * @param escapeTechnion - the system to iterate through
 * @return the escaper with the requested email or NULL if not found
 */
static Escaper findEscaper(char *email, EscapeTechnion escapeTechnion);

/**
 * receives an escapeTechnion system and an escaper and iterates through the
 * system to erase all of the reservations listed with under this escaper
 * @param escaper - the escaper to look for in the reservations
 * @param escapeTechnion - the system to iterate through
 */
static void destroyEscaperReservations(Escaper escaper,
                                       EscapeTechnion escapeTechnion);

/**
 * receives an escapeTechnion system and an email and checks if the email is
 * already in use by a company or an escaper
 * @param escapeTechnion - the system to iterate through
 * @param email - the email to look for
 * @return MTM_SUCCESS - if the email is not in use
 *         MTM_EMAIL_ALREADY_IN_USE - if the email is in use
 */
static bool isEmailInUse(EscapeTechnion escapeTechnion, char *email);

/**
 * receives the company room and escaper and calculates the final price after
 * discount if available
 * @param company - ptr to the company
 * @param room - ptr to the company
 * @param escaper - ptr to the escaper
 * @return the final price id everything went well.
 *         -1 if something went wrong
 */
static int calculatePricePerPerson(Company company, Room room, Escaper escaper);

static bool isRoomAvailable(EscapeTechnion escapeTechnion, Room room,
                            int reservation_day, int reservation_hour);

static bool isEscaperAvailable(EscapeTechnion escapeTechnion,
                               Escaper escaper, int day, int hour);

EscapeTechnion escapeTechnionCreate(MtmErrorCode *EscapeTechnionError) {
    EscapeTechnion escapeTechnion = malloc(sizeof(*escapeTechnion));
    if (NULL == escapeTechnion) {
        *EscapeTechnionError = MTM_OUT_OF_MEMORY;
        return NULL;
    }

    escapeTechnion->faculties_earnings = malloc(sizeof(int) * UNKNOWN);
    if (NULL == escapeTechnion->faculties_earnings) {
        *EscapeTechnionError = MTM_OUT_OF_MEMORY;
        free(escapeTechnion);
        return NULL;
    }
    initializeArr(escapeTechnion->faculties_earnings, UNKNOWN);

    escapeTechnion->companies = setCreate(companyCopyElement,
                                          companyFreeElement,
                                          companyCompareElements);
    if (NULL == escapeTechnion->companies) {
        *EscapeTechnionError = MTM_OUT_OF_MEMORY;
        free(escapeTechnion->faculties_earnings);
        free(escapeTechnion);
        return NULL;
    }

    escapeTechnion->escapers = setCreate(escaperCopyElement, escaperFreeElement,
                                         escaperCompareElements);
    if (NULL == escapeTechnion->escapers) {
        *EscapeTechnionError = MTM_OUT_OF_MEMORY;
        setDestroy(escapeTechnion->companies);
        free(escapeTechnion->faculties_earnings);
        free(escapeTechnion);
        return NULL;
    }

    escapeTechnion->reservations = listCreate(reservationCopyElement,
                                              reservationFreeElement);
    if (NULL == escapeTechnion->reservations) {
        *EscapeTechnionError = MTM_OUT_OF_MEMORY;
        setDestroy(escapeTechnion->escapers);
        setDestroy(escapeTechnion->companies);
        free(escapeTechnion->faculties_earnings);
        free(escapeTechnion);
        return NULL;
    }

    escapeTechnion->current_day = 0;
    *EscapeTechnionError = MTM_SUCCESS;
    return escapeTechnion;
}

MtmErrorCode escapeTechnionDestroy(EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion) {
        return MTM_NULL_PARAMETER;
    }
    listDestroy(escapeTechnion->reservations);
    setDestroy(escapeTechnion->escapers);
    setDestroy(escapeTechnion->companies);
    free(escapeTechnion->faculties_earnings);
    free(escapeTechnion);
    return MTM_SUCCESS;
}

MtmErrorCode escapeTechnionAddCompany(EscapeTechnion escapeTechnion,
                                      char *email, TechnionFaculty Faculty) {
    if (NULL == escapeTechnion || NULL == email || !isEmailValid(email) ||
        !isFacultyValid(Faculty)) {
        return MTM_INVALID_PARAMETER;
    }
    if (isEmailInUse(escapeTechnion, email)) {
        return MTM_EMAIL_ALREADY_EXISTS;
    }

    CompanyErrorCode CompanyError;
    Company company = companyCreate(email, Faculty, &CompanyError);
    if (CompanyError == COMPANY_INVALID_PARAMETER) {
        return MTM_INVALID_PARAMETER;
    } else if (CompanyError == COMPANY_OUT_OF_MEMORY) {
        return MTM_OUT_OF_MEMORY;
    }
    SetResult SetError = setAdd(escapeTechnion->companies, company);
    companyDestroy(company);
    assert(SetError != SET_ITEM_ALREADY_EXISTS &&
           SetError != SET_NULL_ARGUMENT);
    if (SetError == SET_OUT_OF_MEMORY) {
        return MTM_OUT_OF_MEMORY;
    }
    return MTM_SUCCESS;
}

MtmErrorCode escapeTechnionRemoveCompany(EscapeTechnion escapeTechnion,
                                         char *company_email) {
    if (NULL == escapeTechnion || NULL == company_email ||
        !isEmailValid(company_email)) {
        return MTM_INVALID_PARAMETER;
    }
    Company company = findCompany(company_email, escapeTechnion);
    if (NULL == company) {
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }

    if (isReservationForCompany(company, escapeTechnion)) {
        return MTM_RESERVATION_EXISTS;
    }

    setRemove(escapeTechnion->companies, company);
    return MTM_SUCCESS;
}

MtmErrorCode escapeTechnionAddRoom(EscapeTechnion escapeTechnion,
                                   char *company_email, int room_id, int price,
                                   int num_ppl, char *working_hours,
                                   int difficulty) {
    if (NULL == company_email || NULL == working_hours ||
        NULL == escapeTechnion || !isEmailValid(company_email)) {
        return MTM_INVALID_PARAMETER;
    }

    if (!isPriceMultiplyOfFour(price) ||
        !isValidDifficultyOrSkill(difficulty) ||
        num_ppl <= 0 || room_id <= 0) {
        return MTM_INVALID_PARAMETER;
    }

    int opening_time = 0, closing_time = 0;
    if (!getHoursFromStr(working_hours, &opening_time, &closing_time)) {
        return MTM_INVALID_PARAMETER;
    }

    Company company = findCompany(company_email, escapeTechnion);
    if (NULL == company) {
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }

    CompanyErrorCode CompanyError;
    Room room = companyFindRoom(company, room_id, &CompanyError);
    if (NULL != room) {
        return MTM_ID_ALREADY_EXIST;
    }

    CompanyError = companyAddRoom(company, room_id, price, num_ppl,
                                  opening_time, closing_time, difficulty);
    assert(CompanyError != COMPANY_INVALID_PARAMETER &&
           CompanyError != COMPANY_ROOM_ALREADY_EXISTS);
    if (CompanyError == COMPANY_OUT_OF_MEMORY) {
        return MTM_OUT_OF_MEMORY;
    }
    assert(CompanyError == MTM_SUCCESS);
    return MTM_SUCCESS;
}

MtmErrorCode escapeTechnionRemoveRoom(EscapeTechnion escapeTechnion,
                                      int room_id, TechnionFaculty Faculty) {
    if (NULL == escapeTechnion || !isFacultyValid(Faculty) || room_id <= 0) {
        return MTM_INVALID_PARAMETER;
    }
    Company company;
    Room room = escapeSystemFindRoom(room_id, Faculty, escapeTechnion,
                                     &company);
    if (NULL == room || NULL == company) {
        return MTM_ID_DOES_NOT_EXIST;
    }

    if (isReservationForRoom(room, escapeTechnion)) {
        return MTM_RESERVATION_EXISTS;
    }
    companyRemoveRoom(company, room);
    return MTM_SUCCESS;
}

MtmErrorCode escapeTechnionAddEscaper(EscapeTechnion escapeTechnion,
                                      char *escaper_email, int skill_level,
                                      TechnionFaculty FacultyOfEscaper) {
    if (NULL == escapeTechnion || NULL == escaper_email ||
        !isEmailValid(escaper_email) ||
        !isValidDifficultyOrSkill(skill_level) ||
        !isFacultyValid(FacultyOfEscaper)) {
        return MTM_INVALID_PARAMETER;
    }

    if (isEmailInUse(escapeTechnion, escaper_email)) {
        return MTM_EMAIL_ALREADY_EXISTS;
    }

    EscaperErrorCode EscaperError;
    Escaper escaper = escaperCreate(escaper_email, FacultyOfEscaper,
                                    skill_level, &EscaperError);
    assert(EscaperError != ESCAPER_INVALID_PARAMETER);
    if (EscaperError == ESCAPER_OUT_OF_MEMORY) {
        return MTM_OUT_OF_MEMORY;
    }

    SetResult SetError = setAdd(escapeTechnion->escapers, escaper);
    escaperDestroy(escaper);
    if (SetError == SET_OUT_OF_MEMORY) {
        return MTM_OUT_OF_MEMORY;
    }
    return MTM_SUCCESS;
}

MtmErrorCode escapeTechnionRemoveEscaper(char *email,
                                         EscapeTechnion escapeTechnion) {
    if (NULL == email || NULL == escapeTechnion || !isEmailValid(email)) {
        return MTM_INVALID_PARAMETER;
    }
    Escaper escaper = findEscaper(email, escapeTechnion);
    if (escaper == NULL) {
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    destroyEscaperReservations(escaper, escapeTechnion);
    setRemove(escapeTechnion->escapers, escaper);
    return MTM_SUCCESS;
}

MtmErrorCode escapeTechnionAddReservation(char *escaper_email, int room_id,
                                          TechnionFaculty FacultyOfRoom,
                                          char *time, int num_ppl,
                                          EscapeTechnion escapeTechnion) {
    if (NULL == escaper_email || NULL == time || NULL == escapeTechnion ||
        !isFacultyValid(FacultyOfRoom) || !isEmailValid(escaper_email) ||
        room_id <= 0 || num_ppl <= 0) {
        return MTM_INVALID_PARAMETER;
    }
    int days_till_reservation, reservation_hour;
    if (!getDayAndHourFromStr(time, &days_till_reservation,
                              &reservation_hour)) {
        return MTM_INVALID_PARAMETER;
    }
    if (!isEscaperWithEmail(escaper_email, escapeTechnion)) {
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Company company;
    Room room = escapeSystemFindRoom(room_id, FacultyOfRoom, escapeTechnion,
                                     &company);
    if (room == NULL) {
        return MTM_ID_DOES_NOT_EXIST;
    }
    Escaper escaper = findEscaper(escaper_email, escapeTechnion);
    int price = calculatePricePerPerson(company, room, escaper);
    if (price == INVALID_PARAMETER) {
        return MTM_INVALID_PARAMETER;
    }
    price *= num_ppl;
    int reservation_day = days_till_reservation + escapeTechnion->current_day;
    if (!isEscaperAvailable(escapeTechnion, escaper, reservation_day,
                                   reservation_hour)) {
        return MTM_CLIENT_IN_ROOM;
    }
    if (!isRoomAvailable(escapeTechnion, room, reservation_day,
                         reservation_hour)) {
        return MTM_ROOM_NOT_AVAILABLE;
    }
    ReservationErrorCode reservationErrorCode;
    Reservation reservation = reservationCreate(escaper, company, room,
                                                num_ppl, reservation_day,
                                                reservation_hour, price,
                                                &reservationErrorCode);
    if (reservationErrorCode != RESERVATION_SUCCESS) {
        return MTM_OUT_OF_MEMORY;
    }
    if (listInsertLast(escapeTechnion->reservations, reservation) ==
        LIST_OUT_OF_MEMORY) {
        reservationDestroy(reservation);
        return MTM_OUT_OF_MEMORY;
    }
    reservationDestroy(reservation);
    return MTM_SUCCESS;
}

static bool isCompanyWithEmail(char *email, EscapeTechnion escapeTechnion) {
    if (NULL == email || NULL == escapeTechnion) {
        return false;
    }
    Company company_iterator = setGetFirst(escapeTechnion->companies);
    //TODO should we check NULL separately?
    while (NULL != company_iterator) {
        CompanyErrorCode CompanyError = COMPANY_SUCCESS;
        if (isCompanyEmailEqual(company_iterator, email, &CompanyError)) {
            return true;
        }
        assert(CompanyError != COMPANY_INVALID_PARAMETER);
        company_iterator = setGetNext(escapeTechnion->companies);
    }
    return false;
}

static bool isReservationForCompany(Company company,
                                    EscapeTechnion escapeTechnion) {
    if (NULL == company || NULL == escapeTechnion) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode error;
        if (reservationGetCompany(reservation_iterator, &error) == company) {
            assert(error != RESERVATION_INVALID_PARAMETER);
            return true;
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}

static bool isReservationForRoom(Room room, EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion || NULL == room) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode error;
        if (reservationGetRoom(reservation_iterator, &error) == room) {
            assert(error != RESERVATION_INVALID_PARAMETER);
            return true;
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}

static bool isEscaperWithEmail(char *email, EscapeTechnion escapeTechnion) {
    if (NULL == email || NULL == escapeTechnion) {
        return false;
    }
    Escaper escaper_iterator = setGetFirst(escapeTechnion->escapers);
    while (NULL != escaper_iterator) {
        if (isEscaperEmailEqual(escaper_iterator, email)) {
            return true;
        }
        escaper_iterator = setGetNext(escapeTechnion->escapers);
    }
    return false;
}

/*static bool isReservationForEscaper(Escaper escaper,
                                    EscapeTechnion escapeTechnion) {
    if (NULL == escaper || NULL == escapeTechnion) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode error;
        if (reservationGetEscaper(reservation_iterator, &error) == escaper) {
            assert(error != RESERVATION_INVALID_PARAMETER);
            return true;
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}*/

static Company findCompany(char *email, EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion || NULL == email || !isEmailValid(email)) {
        return NULL;
    }
    Company company_iterator = setGetFirst(escapeTechnion->companies);
    while (NULL != company_iterator) {
        CompanyErrorCode CompanyError = COMPANY_SUCCESS;
        if (isCompanyEmailEqual(company_iterator, email, &CompanyError)) {
            return company_iterator;
        }
        assert(CompanyError != COMPANY_INVALID_PARAMETER);
        company_iterator = setGetNext(escapeTechnion->companies);
    }
    return NULL;
}

static Room escapeSystemFindRoom(int room_id, TechnionFaculty FacultyOfRoom,
                                 EscapeTechnion escapeTechnion,
                                 Company *company_of_room) {
    if (NULL == escapeTechnion || 0 >= room_id) {
        return NULL;
    }
    Company company_iterator = setGetFirst(escapeTechnion->companies);
    while (NULL != company_iterator) {
        CompanyErrorCode CompanyError = COMPANY_SUCCESS;
        Room room = companyFindRoom(company_iterator, room_id, &CompanyError);
        if (NULL != room) {
            if (companyGetFaculty(company_iterator, &CompanyError) ==
                FacultyOfRoom) {
                *company_of_room = company_iterator;
                return room;
            }
        }
        company_iterator = setGetNext(escapeTechnion->companies);
    }

    return NULL;
}

static Escaper findEscaper(char *email, EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion || NULL == email || !isEmailValid(email)) {
        return NULL;
    }

    Escaper escaper_iterator = setGetFirst(escapeTechnion->escapers);
    while (NULL != escaper_iterator) {
        if (isEscaperEmailEqual(escaper_iterator, email)) {
            return escaper_iterator;
        }
        escaper_iterator = setGetNext(escapeTechnion->escapers);

    }
    return NULL;
}

static void destroyEscaperReservations(Escaper escaper,
                                       EscapeTechnion escapeTechnion) {
    if (NULL == escaper || NULL == escapeTechnion) {
        return;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode error;
        if (reservationGetEscaper(reservation_iterator, &error) == escaper) {
            assert(ReservationError != RESERVATION_INVALID_PARAMETER);
            listRemoveCurrent(escapeTechnion->reservations);
            reservation_iterator = listGetFirst(escapeTechnion->reservations);
            continue;
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return;
}

static int calculatePricePerPerson(Company company, Room room,
                                   Escaper escaper) {
    assert(escapeTechnion != NULL && company != NULL && room != NULL &&
           escaper != NULL);
    RoomErrorCode roomErrorCode;
    CompanyErrorCode companyErrorCode;
    EscaperErrorCode escaperErrorCode;
    int original_price;

    original_price = roomGetPrice(room, &roomErrorCode);
    if (roomErrorCode != ROOM_SUCCESS) {
        return INVALID_PARAMETER;
    }

    if ((companyGetFaculty(company, &companyErrorCode) ==
         escaperGetFaculty(escaper, &escaperErrorCode)) &&
        companyErrorCode != COMPANY_SUCCESS) {
        return (original_price * 3) / 4;
    }
    if (companyErrorCode != COMPANY_SUCCESS ||
        escaperErrorCode != ESCAPER_SUCCESS) {
        return INVALID_PARAMETER;
    }
    return original_price;
}

static bool isEmailInUse(EscapeTechnion escapeTechnion, char *email) {
    assert(NULL != escapeTechnion && NULL != email);

    if (isCompanyWithEmail(email, escapeTechnion) ||
        isEscaperWithEmail(email, escapeTechnion)) {
        return true;
    }

    return false;
}

static bool isEscaperAvailable(EscapeTechnion escapeTechnion,
                                       Escaper escaper, int day, int hour) {
    assert(NULL != escapeTechnion && NULL != escaper);
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode ReservationError;
        Escaper tmp_escaper =
                reservationGetEscaper(reservation_iterator, &ReservationError);
        assert(ReservationError != RESERVATION_INVALID_PARAMETER);

        if (tmp_escaper == escaper) {
            int tmp_day, tmp_hour;
            reservationGetHour(reservation_iterator, &tmp_hour);
            reservationGetDay(reservation_iterator, &tmp_day);
            if (tmp_day == day && tmp_hour == hour) {
                return true;
            }
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}

static bool isRoomAvailable(EscapeTechnion escapeTechnion, Room room,
                                    int reservation_day, int reservation_hour) {
    assert(NULL != escapeTechnion && NULL != room);

    RoomErrorCode RoomError;
    if (reservation_hour < roomGetOpeningTime(room, &RoomError) ||
        reservation_hour >= roomGetClosingTime(room, &RoomError)) {
        return false;
    }

    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode ReservationError;
        Room tmp_room =
                reservationGetRoom(reservation_iterator, &ReservationError);
        assert(ReservationError != RESERVATION_INVALID_PARAMETER);

        if (tmp_room == room) {
            int tmp_day, tmp_hour;
            reservationGetHour(reservation_iterator, &tmp_hour);
            reservationGetDay(reservation_iterator, &tmp_day);
            if (tmp_day == reservation_day && tmp_hour == reservation_hour) {
                return true;
            }
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}