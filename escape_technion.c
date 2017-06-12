//
// Created by Shahak on 07/06/2017.
//

#include <stdlib.h>
#include <assert.h>

#include "escape_technion.h"
#include "utils.h"

#define INVALID_PARAMETER -1

struct EscapeTechnion_t {
    Set faculties;
    Set escapers;
    List reservations;

    int current_day;
};

/**
 *
 * @param escapeTechnion
 * @return
 */
static EscapeTechnionErrorCode initializeFaculties(EscapeTechnion escapeTechnion);

/**
 *
 * @param escapeTechnion
 */
static void destroyFaculties(EscapeTechnion escapeTechnion);

/**
 * receives an email and an escapeTechnion system and checks if the email
 * already exists in the system wheather in another escaper or company
 * @param escapeTechnion - the system to iterate through
 * @param email - the email to be checked
 * @return true - if the email is in use
 *         false - if the email doesn't exist in the system
 */
static bool isCompanyWithEmail(EscapeTechnion escapeTechnion, char *email);

/**
 * receives a company and an escapeTechnion system and checks if the company is
 * listed in a reservation in the system
 * @param company - the company to look for
 * @param escapeTechnion - the system to iterate through
 * @return true - if the company was found in the system
 *         false - if the company wasn't found in the system
 */
static bool isReservationForCompany(EscapeTechnion escapeTechnion,
                                    Company company);

/**
 * receives a room and an escapeTechnion system and checks if the room is listed
 * in any of the reservations in the system
 * @param room - the room to look for
 * @param escapeTechnion - the system to iterate through
 * @return true - if the room was found in a reservation in the system
 *         false - if the room wasn't found in a reservation in the system
 */
static bool isReservationForRoom(EscapeTechnion escapeTechnion, Room room);

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
 * receives an escapeTechnion system room and an email of an escaper, iterates
 * through the system to find an escaper with the specific email
 * @param email - the email we're looking for
 * @param escapeTechnion - the system to iterate through
 * @return the escaper with the requested email or NULL if not found
 */
static Escaper findEscaper(EscapeTechnion escapeTechnion, char *email);

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
 * @param escaper_faculty - ptr to the company
 * @param room - ptr to the company
 * @param escaper - ptr to the escaper
 * @return the final price id everything went well.
 *         -1 if something went wrong
 */
static int calculatePricePerPerson(Escaper escaper, Room room);

/**
 * receives an escapeTechnion system, a room and reservation time and checks if
 * the room is available at the given time
 * @param escapeTechnion - the system to which the room belongs
 * @param room - the room in the reservation
 * @param reservation_day - the day of the reservation
 * @param reservation_hour - the hour of the reservation
 * @return true - if the room is available at the specified time
 *         false - if the room is taken at the specified time
 */
static bool isRoomAvailable(EscapeTechnion escapeTechnion, Room room,
                            int reservation_day, int reservation_hour);

/**
 * receives an escapeTechnion system, an escaper and reservation time and checks
 * if the room is available at the given time
 * @param escapeTechnion - the system to which the room belongs
 * @param escaper - the escaper in the reservation
 * @param reservation_day - the day of the reservation
 * @param reservation_hour - the hour of the reservation
 * @return true - if the escaper is available at the specified time
 *         false - if the escaper is taken at the specified time
 */
static bool isEscaperAvailable(EscapeTechnion escapeTechnion,
                               Escaper escaper, int day, int hour);

//TODO add comments to everything
static EscapeTechnionErrorCode reserveRoom(EscapeTechnion escapeTechnion, Escaper escaper,
                                Company company, Room room, int num_ppl,
                                int day, int hour);

static EscapeTechnionErrorCode findClosestTime(EscapeTechnion escapeTechnion, Room room,
                                    Escaper escaper, int *day, int *hour);

static Company getCompanyByEmail(EscapeTechnion escapeTechnion, char *email,
                                Faculty *company_faculty);

/**
 *
 * @param escapeTechnion
 * @param nameFaculty
 * @param id
 * @return
 */
static Room getRoomByID(EscapeTechnion escapeTechnion,
                        TechnionFaculty nameFaculty, int id);

static Faculty getBetterFaculty(Faculty faculty_1, int earnings_1,
                                Faculty faculty_2, int earnings_2);

static void findBestFaculties(Faculty *cur_first, int *first_earnings,
                              Faculty *cur_second, int *second_earnings,
                              Faculty *cur_third, int *third_earnings,
                              Faculty faculty, int faculty_earnings);

static int getEscapeTechnionEarnings(EscapeTechnion escapeTechnion);


static void escapeTechnionBestFaculties(EscapeTechnion escapeTechnion,
                                        Faculty *first_faculty,
                                        int *first_faculty_earnings,
                                        Faculty *second_faculty,
                                        int *second_faculty_earnings,
                                        Faculty *third_faculty,
                                        int *third_faculty_earnings);


/**---------------------------------------------------------------------------*/


EscapeTechnion escapeTechnionCreate() {
    EscapeTechnion escapeTechnion = malloc(sizeof(*escapeTechnion));
    if (NULL == escapeTechnion) {
        return NULL;
    }

    escapeTechnion->faculties = setCreate(facultyCopyElement, facultyDestroy,
                                          facultyCompareElements);
    if (NULL == escapeTechnion->faculties) {
        free(escapeTechnion);
        return NULL;
    }

    EscapeTechnionErrorCode errorCode = initializeFaculties(escapeTechnion);
    assert(errorCode != ESCAPE_TECHNION_INVALID_PARAMETER);
    if (errorCode == ESCAPE_TECHNION_OUT_OF_MEMORY) {
        return NULL;
    }

    escapeTechnion->escapers = setCreate(escaperCopyElement, escaperDestroy,
                                         escaperCompareElements);
    if (NULL == escapeTechnion->escapers) {
        setDestroy(escapeTechnion->faculties);
        free(escapeTechnion);
        return NULL;
    }

    escapeTechnion->reservations = listCreate(reservationCopyElement,
                                              reservationDestroy);
    if (NULL == escapeTechnion->reservations) {
        setDestroy(escapeTechnion->escapers);
        setDestroy(escapeTechnion->faculties);
        free(escapeTechnion);
        return NULL;
    }

    escapeTechnion->current_day = 0;
    return escapeTechnion;
}

void escapeTechnionDestroy(EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion){
        return;
    }
    listDestroy(escapeTechnion->reservations);
    setDestroy(escapeTechnion->escapers);
    setDestroy(escapeTechnion->faculties);
    free(escapeTechnion);
}

EscapeTechnionErrorCode escapeTechnionAddCompany(EscapeTechnion escapeTechnion,
                                                 TechnionFaculty nameFaculty,
                                                 char *email) {
    //TODO: change the check fo NULL and check faculty
    if (NULL == escapeTechnion || NULL == email ||
        !isValidCompanyParams(nameFaculty, email)) {
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    if (isEmailInUse(escapeTechnion, email)) {
        return ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS;
    }

    Faculty faculty = getFacultyByName(escapeTechnion, nameFaculty);
    assert(NULL != faculty);

    FacultyErrorCode errorCode = facultyAddCompany(faculty, email);
    assert(errorCode != FACULTY_INVALID_PARAMETER);

    if (errorCode == FACULTY_OUT_OF_MEMORY) {
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    } else if (errorCode == FACULTY_COMPANY_ALREADY_EXISTS) {
        return ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS;
    }

    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionRemoveCompany(EscapeTechnion escapeTechnion,
                                                    char *company_email) {
    if (NULL == escapeTechnion || NULL == company_email ||
        !isValidEmail(company_email)) {
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    Faculty company_faculty;
    Company company = getCompanyByEmail(escapeTechnion, company_email,
                                        &company_faculty);
    if (NULL == company) {
        return ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST;
    }

    if (isReservationForCompany(escapeTechnion, company)) {
        return ESCAPE_TECHNION_RESERVATION_EXISTS;
    }

    FacultyErrorCode errorCode = facultyRemoveCompany(company_faculty, company);
    if (errorCode == FACULTY_INVALID_PARAMETER) {
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }

    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionAddRoom(EscapeTechnion escapeTechnion,
                                   char *company_email, int room_id, int price,
                                   int num_ppl, char *working_hours,
                                   int difficulty) {
    if (NULL == escapeTechnion || NULL == company_email ||
        NULL == working_hours ||
        !isValidRoomParams(company_email, room_id, price, num_ppl, difficulty)){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }

    int opening_time = 0, closing_time = 0;
    if (!getHoursFromStr(working_hours, &opening_time, &closing_time)) {
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }

    Faculty room_faculty;
    Company company = getCompanyByEmail(escapeTechnion, company_email,
                                        &room_faculty);
    if (NULL == company) {
        return ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST;
    }

    TechnionFaculty nameFaculty = companyGetFaculty(company);
    Room room = getRoomByID(escapeTechnion, nameFaculty, room_id);

    if (NULL != room) {
        return ESCAPE_TECHNION_ID_ALREADY_EXIST;
    }

    CompanyErrorCode errorCode = companyAddRoom(company, room_id, price,
                                                num_ppl, opening_time,
                                                closing_time, difficulty);
    assert(errorCode != COMPANY_INVALID_PARAMETER &&
           errorCode != COMPANY_ROOM_ALREADY_EXISTS);

    if (errorCode == COMPANY_OUT_OF_MEMORY) {
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionRemoveRoom(EscapeTechnion escapeTechnion,
                                                 int room_id,
                                                 TechnionFaculty nameFaculty) {
    if (NULL == escapeTechnion || !isValidFacultyName(nameFaculty) ||
            room_id <= 0){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    Faculty faculty = getFacultyByName(escapeTechnion, nameFaculty);
    Company company;
    Room room = facultyGetRoomByID(faculty, &company, room_id);
    if (NULL == room) {
        return ESCAPE_TECHNION_ID_DOES_NOT_EXIST;
    }

    if (isReservationForRoom(escapeTechnion, room)) {
        return ESCAPE_TECHNION_RESERVATION_EXISTS;
    }

    companyRemoveRoom(company, room);
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionAddEscaper(EscapeTechnion escapeTechnion,
                                                  char *email, int skill,
                                                  TechnionFaculty nameFaculty) {
    if (NULL == escapeTechnion || NULL == email ||
            !isValidEscaperParams(nameFaculty, email, skill)){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }

    if (isEmailInUse(escapeTechnion, email)) {
        return ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS;
    }

    EscaperErrorCode escaperError;
    Escaper escaper = escaperCreate(email, nameFaculty, skill, &escaperError);
    assert(escaperError != ESCAPER_INVALID_PARAMETER);

    if (escaperError == ESCAPER_OUT_OF_MEMORY) {
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }

    SetResult SetError = setAdd(escapeTechnion->escapers, escaper);
    escaperDestroy(escaper);
    if (SetError == SET_OUT_OF_MEMORY) {
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionRemoveEscaper(EscapeTechnion escapeTechnion,
                                                    char *email) {
    if (NULL == email || NULL == escapeTechnion || !isValidEmail(email)) {
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    Escaper escaper = findEscaper(escapeTechnion, email);
    if (escaper == NULL) {
        return ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    destroyEscaperReservations(escaper, escapeTechnion);
    setRemove(escapeTechnion->escapers, escaper);
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionReservationReceived(EscapeTechnion
                                               escapeTechnion,
                                               char *escaper_email, int room_id,
                                               TechnionFaculty nameFaculty,
                                               char *time, int num_ppl) {

    if (NULL == escaper_email || NULL == time || NULL == escapeTechnion ||
        !isValidFacultyName(nameFaculty) || !isValidEmail(escaper_email) ||
        room_id <= 0 || num_ppl <= 0) {
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    int days_till_reservation, reservation_hour;
    if (!getDayAndHourFromStr(time, &days_till_reservation, &reservation_hour)){
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }
    if (!isEscaperWithEmail(escaper_email, escapeTechnion)) {
        return ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Faculty faculty = getFacultyByName(escapeTechnion, nameFaculty);
    Company company;
    Room room = facultyGetRoomByID(faculty, &company, room_id);
    if (NULL == room) {
        return ESCAPE_TECHNION_ID_DOES_NOT_EXIST;
    }
    Escaper escaper = findEscaper(escapeTechnion, escaper_email);

    int reservation_day = days_till_reservation + escapeTechnion->current_day;
    if (!isEscaperAvailable(escapeTechnion, escaper, reservation_day,
                            reservation_hour)) {
        return ESCAPE_TECHNION_CLIENT_IN_ROOM;
    }
    if (!isRoomAvailable(escapeTechnion, room, reservation_day,
                         reservation_hour)) {
        return ESCAPE_TECHNION_ROOM_NOT_AVAILABLE;
    }
    return reserveRoom(escapeTechnion, escaper, company, room, num_ppl,
                       reservation_day, reservation_hour);
}

EscapeTechnionErrorCode escapeTechnionRecommendedRoom(EscapeTechnion
                                                    escapeTechnion, int num_ppl,
                                                    char *escaper_email) {
    if (NULL == escaper_email || NULL == escapeTechnion ||
        !isValidEmail(escaper_email) || num_ppl <= 0) {
        return ESCAPE_TECHNION_INVALID_PARAMETER;
    }

    Escaper escaper = findEscaper(escapeTechnion, escaper_email);
    if(escaper == NULL){
        return ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }

    int skill = escaperGetSkillLevel(escaper);
    TechnionFaculty escapersFaculty = escaperGetNameFaculty(escaper);
    int min_result = INVALID_PARAMETER, min_faculty_diff = INVALID_PARAMETER,
        min_room_id = INVALID_PARAMETER, cur_result = INVALID_PARAMETER,
        cur_faculty_diff = INVALID_PARAMETER, cur_room_id = INVALID_PARAMETER;

    Room cur_recommended_room, most_recommended_room = NULL;
    Company cur_company, most_recommended_company = NULL;
    Faculty faculty_iterator = setGetFirst(escapeTechnion->faculties);
    while (NULL != faculty_iterator) {
        cur_recommended_room = facultyMostRecommendedRoom(faculty_iterator,
                                                          escaper,
                                                          escapersFaculty,
                                                          num_ppl, skill,
                                                          &cur_result,
                                                          &cur_faculty_diff,
                                                          &cur_room_id,
                                                          &cur_company);
        if (NULL == cur_recommended_room) {
            faculty_iterator = setGetNext(escapeTechnion->faculties);
            continue;
        }
        checkBetterRoom(escaper, cur_result, cur_room_id, cur_faculty_diff,
                        cur_recommended_room, &min_result, &min_room_id,
                        &min_faculty_diff, &most_recommended_room,
                        &most_recommended_company, cur_company);
        faculty_iterator = setGetNext(escapeTechnion->faculties);
    }
    if (NULL == most_recommended_room) {
        return ESCAPE_TECHNION_NO_ROOMS_AVAILABLE;
    }
    int day, hour;
    findClosestTime(escapeTechnion, most_recommended_room, escaper, &day,&hour);
    return reserveRoom(escapeTechnion, escaper, most_recommended_company,
                       most_recommended_room, num_ppl, day, hour);
}

EscapeTechnionErrorCode escapeTechnionReportDay(EscapeTechnion escapeTechnion,
                                     FILE *output_channel) {
    if (NULL == escapeTechnion || NULL == output_channel) {
        return ESCAPE_TECHNION_NULL_PARAMETER; //TODO or MTM_CANNOT_OPEN_FILE?
    }
    int system_day = escapeTechnion->current_day, num_events;
    List ended_reservations = listFilter(escapeTechnion->reservations,
                                         isReservationDueDate, &system_day);
    num_events = listGetSize(ended_reservations);
    mtmPrintDayHeader(stdout, system_day, num_events);
    List new_reservation_list = listFilter(escapeTechnion->reservations,
                                           isReservationRelevant, &system_day);
    listDestroy(escapeTechnion->reservations);
    escapeTechnion->reservations = new_reservation_list;
    listSort(ended_reservations, reservationCompareForPrint);
    LIST_FOREACH(Reservation, iterator, ended_reservations) {
        Escaper escaper = reservationGetEscaper(iterator);
        EscaperErrorCode escaperError;
        char *escaper_email = escaperGetEmail(escaper, &escaperError);
        if (escaperError == ESCAPER_OUT_OF_MEMORY) {
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
        }
        int escaper_skill = escaperGetSkillLevel(escaper);
        TechnionFaculty escaper_Faculty = escaperGetNameFaculty(escaper);
        Company company = reservationGetCompany(iterator);
        CompanyErrorCode companyError;
        char *company_email = companyGetEmail(company, &companyError);
        if (companyError == COMPANY_OUT_OF_MEMORY) {
            free(escaper_email);
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
        }
        TechnionFaculty company_faculty = companyGetFaculty(company);
        Room room = reservationGetRoom(iterator);
        int room_id = roomGetID(room);
        int room_difficulty = roomGetDifficulty(room);
        int hour = reservationGetHour(iterator);
        int num_ppl = reservationGetNumPpl(iterator);
        int price = reservationGetPrice(iterator);
        Faculty tmpFaculty = getFacultyByName(escapeTechnion, company_faculty);
        facultyIncEarnings(tmpFaculty, price);
        mtmPrintOrder(stdout, escaper_email, escaper_skill,
                      escaper_Faculty, company_email, company_faculty,
                      room_id, hour, room_difficulty, num_ppl, price);
        free(escaper_email);
        free(company_email);
    }
    listDestroy(ended_reservations);
    mtmPrintDayFooter(output_channel, escapeTechnion->current_day);
    escapeTechnion->current_day += 1;
    return ESCAPE_TECHNION_SUCCESS;
}

EscapeTechnionErrorCode escapeTechnionReportBest(EscapeTechnion escapeTechnion,
                                                 FILE *output_channel) {
    if (NULL == escapeTechnion || NULL == output_channel) {
        return ESCAPE_TECHNION_NULL_PARAMETER; //TODO or MTM_CANNOT_OPEN_FILE?
    }

    int num_faculties = (int)UNKNOWN;
    int num_days = escapeTechnion->current_day;
    int total_revenue = getEscapeTechnionEarnings(escapeTechnion);
    mtmPrintFacultiesHeader(output_channel, num_faculties, num_days,
                            total_revenue);
    Faculty faculty1, faculty2, faculty3;
    int earnings1, earnings2, earnings3;
    escapeTechnionBestFaculties(escapeTechnion, &faculty1, &earnings1,
                                &faculty2, &earnings2, &faculty3, &earnings3);
    if (NULL != faculty1) {
        TechnionFaculty nameFaculty1 = facultyGetName(faculty1);
        mtmPrintFaculty(output_channel, nameFaculty1, earnings1);
    }
    if (NULL != faculty2) {
        TechnionFaculty nameFaculty2 = facultyGetName(faculty2);
        mtmPrintFaculty(output_channel, nameFaculty2, earnings2);
    }
    if (NULL != faculty3) {
        TechnionFaculty nameFaculty3 = facultyGetName(faculty3);
        mtmPrintFaculty(output_channel, nameFaculty3, earnings3);
    }
    mtmPrintFacultiesFooter(output_channel);
    return ESCAPE_TECHNION_SUCCESS;
}


/**...........................................................................*/
/**--------------------------STATIC-FUNCTIONS---------------------------------*/
/**...........................................................................*/


static EscapeTechnionErrorCode initializeFaculties(EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion) {
        return ESCAPE_TECHNION_NULL_PARAMETER;
    }
    FacultyErrorCode facultyError;

    for (int idx = 0; idx < (int)UNKNOWN; idx++) {
        Faculty faculty = facultyCreate((TechnionFaculty)idx, &facultyError);
        if (NULL == faculty) {
            destroyFaculties(escapeTechnion);
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
        }

        SetResult setResult = setAdd(escapeTechnion->faculties, faculty);
        facultyDestroy(faculty);

        assert(setResult != SET_NULL_ARGUMENT &&
               setResult != SET_ITEM_ALREADY_EXISTS);

        if (setResult == SET_OUT_OF_MEMORY) {
            destroyFaculties(escapeTechnion);
            return ESCAPE_TECHNION_OUT_OF_MEMORY;
        }
    }

    return ESCAPE_TECHNION_SUCCESS;
}

static void destroyFaculties(EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion) {
        return;
    }

    setDestroy(escapeTechnion->faculties);
}
static EscapeTechnionErrorCode reserveRoom(EscapeTechnion escapeTechnion,
                                           Escaper escaper, Company company,
                                           Room room, int num_ppl,
                                           int day, int hour) {
    assert(NULL != escapeTechnion && NULL != escaper && NULL != company &&
                   NULL != room);
    int price = calculatePricePerPerson(escaper, room);
    price *= num_ppl;
    ReservationErrorCode reservationError;
    Reservation reservation = reservationCreate(escaper, company, room, num_ppl,
                                           day, hour, price, &reservationError);
    if (reservation == NULL) {
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    if (listInsertLast(escapeTechnion->reservations, reservation) ==
        LIST_OUT_OF_MEMORY) {

        reservationDestroy(reservation);
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }
    reservationDestroy(reservation);
    return ESCAPE_TECHNION_SUCCESS;
}

static bool isCompanyWithEmail(EscapeTechnion escapeTechnion, char *email) {
    if (NULL == escapeTechnion || NULL == email) {
        return false;
    }
    Faculty faculty_iterator = setGetFirst(escapeTechnion->faculties);
    while (NULL != faculty_iterator) {
        if (isCompanyEmailFaculty(faculty_iterator, email)) {
            return true;
        }
        faculty_iterator = setGetNext(escapeTechnion->faculties);
    }
    return false;
}

static bool isReservationForCompany(EscapeTechnion escapeTechnion,
                                    Company company) {
    if (NULL == company || NULL == escapeTechnion) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        if (reservationGetCompany(reservation_iterator) == company) {
            return true;
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return false;
}

static bool isReservationForRoom(EscapeTechnion escapeTechnion, Room room) {
    if (NULL == escapeTechnion || NULL == room) {
        return false;
    }
    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        if (reservationGetRoom(reservation_iterator) == room) {
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


static Escaper findEscaper(EscapeTechnion escapeTechnion, char *email) {
    if (NULL == escapeTechnion || NULL == email || !isValidEmail(email)) {
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
        if (reservationGetEscaper(reservation_iterator) == escaper) {
            listRemoveCurrent(escapeTechnion->reservations);
            reservation_iterator = listGetFirst(escapeTechnion->reservations);
            continue;
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return;
}

static int calculatePricePerPerson(Escaper escaper, Room room) {
    assert(NULL != room && NULL != escaper);
    int original_price;

    original_price = roomGetPrice(room);
    if (INVALID_PARAMETER == original_price) {
        return INVALID_PARAMETER;
    }

    if (roomGetNameFaculty(room) == escaperGetNameFaculty(escaper)){
        return (original_price * 3) / 4;
    }
    return original_price;
}

static bool isEmailInUse(EscapeTechnion escapeTechnion, char *email) {
    assert(NULL != escapeTechnion && NULL != email);

    if (isCompanyWithEmail(escapeTechnion, email) ||
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
        Escaper tmp_escaper =
                reservationGetEscaper(reservation_iterator);

        if (tmp_escaper == escaper) {
            int tmp_day, tmp_hour;
            tmp_day = reservationGetDay(reservation_iterator);
            tmp_hour = reservationGetHour(reservation_iterator);
            if (tmp_day == day && tmp_hour == hour) {
                return false;
            }
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return true;
}

static bool isRoomAvailable(EscapeTechnion escapeTechnion, Room room,
                                    int reservation_day, int reservation_hour) {
    assert(NULL != escapeTechnion && NULL != room);
    if (reservation_hour < roomGetOpeningTime(room) ||
        reservation_hour >= roomGetClosingTime(room)) {
        return false;
    }

    Reservation reservation_iterator;
    reservation_iterator = listGetFirst(escapeTechnion->reservations);
    while (NULL != reservation_iterator) {
        Room tmp_room = reservationGetRoom(reservation_iterator);

        if (tmp_room == room) {
            int tmp_day, tmp_hour;
            tmp_day = reservationGetDay(reservation_iterator);
            tmp_hour = reservationGetHour(reservation_iterator);
            if (tmp_day == reservation_day && tmp_hour == reservation_hour) {
                return false;
            }
        }
        reservation_iterator = listGetNext(escapeTechnion->reservations);
    }
    return true;
}

static EscapeTechnionErrorCode findClosestTime(EscapeTechnion escapeTechnion,
                                               Room room, Escaper escaper,
                                               int *day, int *hour) {

    ListResult listResult = listSort(escapeTechnion->reservations,
                                     reservationCompareElements);
    if (listResult != LIST_SUCCESS) {
        return ESCAPE_TECHNION_OUT_OF_MEMORY;
    }

    int tmp_day = 0;
    bool trigger = true;
    while (trigger) {
        for (int tmp_hour = 0; tmp_hour < 24; tmp_hour++) {
            if (isEscaperAvailable(escapeTechnion, escaper, tmp_day, tmp_hour)
                && isRoomAvailable(escapeTechnion, room, tmp_day, tmp_hour)) {
                *day = tmp_day;
                *hour = tmp_hour;
                trigger = false;
                break;
            }
        }
        tmp_day++;
    }
    return ESCAPE_TECHNION_SUCCESS;
}

Faculty getFacultyByName(EscapeTechnion escapeTechnion,
                         TechnionFaculty nameFaculty) {
    if (NULL == escapeTechnion) {
        return NULL;
    }

    Faculty faculty_iterator = setGetFirst(escapeTechnion->faculties);
    if (NULL == faculty_iterator) {
        return NULL;
    }

    TechnionFaculty tmpName;
    while (NULL != faculty_iterator) {
        tmpName = facultyGetName(faculty_iterator);
        assert(tmpName != UNKNOWN);

        if (tmpName == nameFaculty) {
            return faculty_iterator;
        }
        faculty_iterator = setGetNext(escapeTechnion->faculties);
    }
    return NULL;
}

static Company getCompanyByEmail(EscapeTechnion escapeTechnion, char *email,
                                Faculty *company_faculty) {
    assert(email != NULL);
    Faculty faculty_iterator = setGetFirst(escapeTechnion->faculties);

    FacultyErrorCode facultyError;
    while(NULL != faculty_iterator){
        Company company = facultyGetCompanyByEmail(faculty_iterator, email,
                                                   &facultyError);
        if(NULL != company){
            *company_faculty = faculty_iterator;
            return company;
        }
        faculty_iterator = setGetNext(escapeTechnion->faculties);
    }
    *company_faculty = NULL;
    return NULL;
}

static Room getRoomByID(EscapeTechnion escapeTechnion,
                        TechnionFaculty nameFaculty,
                        int id) {
    if (NULL == escapeTechnion || !isValidFacultyName(nameFaculty) || id <= 0) {
        return NULL;
    }

    Faculty faculty = getFacultyByName(escapeTechnion, nameFaculty);
    if (NULL == faculty) {
        return NULL;
    }

    Company company;
    return facultyGetRoomByID(faculty, &company, id);
}

static void escapeTechnionBestFaculties(EscapeTechnion escapeTechnion,
                                        Faculty *first_faculty,
                                        int *first_faculty_earnings,
                                        Faculty *second_faculty,
                                        int *second_faculty_earnings,
                                        Faculty *third_faculty,
                                        int *third_faculty_earnings) {
    int faculty_1_earnings = INVALID_PARAMETER,
        faculty_2_earnings = INVALID_PARAMETER,
        faculty_3_earnings = INVALID_PARAMETER;
    Faculty faculty_1 = NULL, faculty_2 = NULL, faculty_3 = NULL;
    Faculty faculty_iterator = setGetFirst(escapeTechnion->faculties);
    while (NULL != faculty_iterator) {
        int tmp_earnings = facultyGetEarnings(faculty_iterator);
        findBestFaculties(&faculty_1, &faculty_1_earnings,
                          &faculty_2, &faculty_2_earnings,
                          &faculty_3, &faculty_3_earnings,
                          faculty_iterator, tmp_earnings);
        faculty_iterator = setGetNext(escapeTechnion->faculties);
    }

    *first_faculty = faculty_1;
    *first_faculty_earnings = faculty_1_earnings;
    *second_faculty = faculty_2;
    *second_faculty_earnings = faculty_2_earnings;
    *third_faculty = faculty_3;
    *third_faculty_earnings = faculty_2_earnings;
    return;
}

static void findBestFaculties(Faculty *cur_first, int *first_earnings,
                               Faculty *cur_second, int *second_earnings,
                               Faculty *cur_third, int *third_earnings,
                               Faculty faculty, int faculty_earnings) {
    assert(NULL != faculty && faculty_earnings >= 0);
    if (NULL == *cur_first) {
        *cur_first = faculty;
        *first_earnings = faculty_earnings;
        return;
    }

    if (getBetterFaculty(*cur_first, *first_earnings, faculty, faculty_earnings)
        == faculty) {

        *cur_third = *cur_second;
        *third_earnings = *second_earnings;

        *cur_second = *cur_first;
        *second_earnings = *first_earnings;

        *cur_first = faculty;
        *first_earnings = faculty_earnings;
        return;
    }

    if (getBetterFaculty(*cur_second, *second_earnings, faculty, faculty_earnings)
        == faculty) {

        *cur_third = *cur_second;
        *third_earnings = *second_earnings;

        *cur_second = faculty;
        *second_earnings = faculty_earnings;
        return;
    }

    if (getBetterFaculty(*cur_third, *third_earnings, faculty, faculty_earnings)
        == faculty) {

        *cur_third = faculty;
        *third_earnings = faculty_earnings;
        return;
    }
    return;
}

static Faculty getBetterFaculty(Faculty faculty_1, int earnings_1,
                                 Faculty faculty_2, int earnings_2) {
    assert(! (NULL == faculty_1 && NULL == faculty_2));
    if (NULL == faculty_1) {
        return faculty_2;
    } else if (NULL == faculty_2) {
        return faculty_1;
    }

    if (earnings_1 > earnings_2) {
        return faculty_1;
    } else if (earnings_1 < earnings_2) {
        return faculty_2;
    }

    TechnionFaculty nameFaculty1 = facultyGetName(faculty_1);
    TechnionFaculty nameFaculty2 = facultyGetName(faculty_2);

    if ((int)nameFaculty1 < (int)nameFaculty2) {
        return faculty_1;
    }

    return faculty_2;
}

static int getEscapeTechnionEarnings(EscapeTechnion escapeTechnion) {
    if (NULL == escapeTechnion) {
        return INVALID_PARAMETER;
    }

    int total_earnings = 0;
    Faculty faculty_iterator = setGetFirst(escapeTechnion->faculties);
    while (NULL != faculty_iterator) {
        int faculty_earnings = facultyGetEarnings(faculty_iterator);
        total_earnings += faculty_earnings;
        faculty_iterator = setGetNext(escapeTechnion->faculties);
    }

    return total_earnings;
}