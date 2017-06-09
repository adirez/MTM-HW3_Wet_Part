//
// Created by Shahak on 07/06/2017.
//

#include <stdlib.h>
#include <assert.h>

#include "EscapeTechnion.h"
#include "utils.h"

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
 * receives an email and an escapeTechnion system and checks if the email is
 * listed in a reservation as a company's email
 * @param email - the email to be checked
 * @param escapeTechnion - the system to iterate through
 * @return true - if the email exists
 *         false - if the email doesn't exist in the system
 */
static bool isReservationForCompany(char *email,
                                    EscapeTechnion escapeTechnion);

/**
 * receives a room id and an escapeTechnion system and checks if the id is
 * listed in any of the reservations in the system
 * @param room_id - the id to be checked
 * @param escapeTechnion - the system to iterate through
 * @return true - if the id exists
 *         false - if the id doesn't exist in the system
 */
static bool isReservationForRoom(int room_id, EscapeTechnion escapeTechnion);

/**
 * receives an email and an escapeTechnion system and checks if the email is
 * listed in a reservation as an escaper's email
 * @param email - the email to be checked
 * @param escapeTechnion - the system to iterate through
 * @return true - if the email exists
 *         false - if the email doesn't exist in the system
 */

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
 * receives an email of an escaper and an escapeTechnion system and checks if
 * there's a reservation with the escaper's email in the system
 * @param email - the email of the escaper
 * @param escapeTechnion - the system to iterate through
 * @return true - if the email was found in the system
 *         false - if the email wasn't found in the system
 */
static bool isReservationForEscaper(char *email,
                                    EscapeTechnion escapeTechnion);

/**
 * receives an email and an escapeTechnion system and checks if the email is
 * listed as a company's email in the system
 * @param email - the email to be checked
 * @param escapeTechnion - the system to iterate through
 * @return a pointer to the company if found, NULL if not found
 */
static Company findCompany(char *email, EscapeTechnion escapeTechnion);

/**
 * receives a room id and an escapeTechnion system and checks if the id is
 * listed in the system
 * @param room_id - the id to be checked
 * @param escapeTechnion - the system to iterate through
 * @return a pointer to the room if found, NULL if not found
 */
static Room escapeSystemFindRoom(int room_id, TechnionFaculty Faculty,
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
 * receives an escapeTechnion system and an email of an escaper and iterates
 * through the system to erase all of the reservations listed with the escaper's
 * email
 * @param email - the email address of the escaper
 * @param escapeTechnion - the system to iterate through
 */
static void destroyEscaperReservations(char *email,
                                       EscapeTechnion escapeTechnion);

EscapeTechnion escapeTechnionCreate(MtmErrorCode *EscapeTechnionError) {
    EscapeTechnion escapeTechnion = malloc((size_t) sizeof(*escapeTechnion));
    if (NULL == escapeTechnion) {
        *EscapeTechnionError = MTM_OUT_OF_MEMORY;
        return NULL;
    }

    escapeTechnion->faculties_earnings = malloc((size_t) sizeof(int) * UNKNOWN);
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
    if (isCompanyWithEmail(email, escapeTechnion)) {
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
    if (isReservationForCompany(company_email, escapeTechnion)) {
        return MTM_RESERVATION_EXISTS;
    }

    Company company = findCompany(company_email, escapeTechnion);
    if (NULL == company) {
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
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
    if (NULL == escapeTechnion || !isFacultyValid(Faculty)) {
        return MTM_INVALID_PARAMETER;
    }
    if (isReservationForRoom(room_id, escapeTechnion)) {
        return MTM_RESERVATION_EXISTS;
    }
    Company company;
    Room room = escapeSystemFindRoom(room_id, Faculty, escapeTechnion,
                                     &company);
    if (NULL == room || NULL == company) {
        return MTM_ID_DOES_NOT_EXIST;
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

    if (isEscaperWithEmail(escaper_email, escapeTechnion)) {
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
    if (!isReservationForEscaper(email, escapeTechnion)) {
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Escaper escaper = findEscaper(email, escapeTechnion);
    assert(NULL != escaper);

    destroyEscaperReservations(email, escapeTechnion);
    setRemove(escapeTechnion->escapers, escaper);
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

static bool isReservationForCompany(char *email,
                                    EscapeTechnion escapeTechnion) {
    if (NULL == email || NULL == escapeTechnion) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode ReservationError = RESERVATION_SUCCESS;
        if (isReservationCompanyEmailEqual(reservation_iterator, email,
                                           &ReservationError)) {
            return true;
        }
        assert(ReservationError != RESERVATION_INVALID_PARAMETER);
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}

static bool isReservationForRoom(int room_id, EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion || room_id <= 0) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode ReservationError = RESERVATION_SUCCESS;
        if (isReservationRoomIdEqual(reservation_iterator, room_id,
                                     &ReservationError)) {
            return true;
        }
        assert(ReservationError != RESERVATION_INVALID_PARAMETER);
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

static bool isReservationForEscaper(char *email,
                                    EscapeTechnion escapeTechnion) {
    if (NULL == email || NULL == escapeTechnion) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        ReservationErrorCode ReservationError = RESERVATION_SUCCESS;
        if (isReservationEscaperEmailEqual(reservation_iterator, email,
                                           &ReservationError)) {
            return true;
        }
        assert(ReservationError != RESERVATION_INVALID_PARAMETER);
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}

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

static Room escapeSystemFindRoom(int room_id, TechnionFaculty Faculty,
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
            if (companyGetFaculty(company_iterator, &CompanyError) == Faculty) {
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

static void destroyEscaperReservations(char *email,
                                       EscapeTechnion escapeTechnion) {
    if (NULL == email || NULL == escapeTechnion) {
        return;
    }

    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);

    while (NULL != reservation_iterator) {
        ReservationErrorCode ReservationError = RESERVATION_SUCCESS;
        if (isReservationEscaperEmailEqual(reservation_iterator, email,
                                           &ReservationError)) {

            assert(ReservationError != RESERVATION_INVALID_PARAMETER);
            listRemoveCurrent(escapeTechnion->reservations);
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return;
}
