//
// Created by Shahak on 11/06/2017.
//

#include <stdlib.h>
#include <assert.h>

#include "faculty.h"
#include "utils.h"

#define INVALID_PARAMETER -1

struct Faculty_t {
    TechnionFaculty Name;
    Set companies;
    int earnings;
};


/**...........................................................................*/
/**-----------------------FUNCTIONS-IMPLEMENTATIONS---------------------------*/
/**...........................................................................*/


Faculty facultyCreate(TechnionFaculty nameFaculty,
                      FacultyErrorCode *facultyError) {
    if (NULL == facultyError){
        return NULL;
    }
    if (!isValidFacultyName(nameFaculty)){
        *facultyError = FACULTY_INVALID_PARAMETER;
        return NULL;
    }
    Faculty faculty = malloc(sizeof(*faculty));
    if (NULL == faculty) {
        *facultyError = FACULTY_OUT_OF_MEMORY;
        return NULL;
    }

    faculty->companies = setCreate(companyCopyElement, companyDestroy,
                                   companyCompareElements);

    if (NULL == faculty->companies) {
        free(faculty);
        *facultyError = FACULTY_OUT_OF_MEMORY;
        return NULL;
    }

    faculty->Name = nameFaculty;
    faculty->earnings = 0;
    *facultyError = FACULTY_SUCCESS;
    return faculty;
}

void facultyDestroy(SetElement element) {
    if (NULL == element) {
        return;
    }
    Faculty faculty = element;
    setDestroy(faculty->companies);
    free(faculty);
    return;
}

FacultyErrorCode facultyAddCompany(Faculty faculty, char *email) {
    if (NULL == faculty || NULL == email) {
        return FACULTY_NULL_PARAMETER;
    }
    if (!isValidEmail(email)){
        return FACULTY_INVALID_PARAMETER;
    }

    CompanyErrorCode companyError;
    Company company = companyCreate(faculty->Name, email, &companyError);
    if (COMPANY_INVALID_PARAMETER == companyError) {
        return FACULTY_INVALID_PARAMETER;
    } else if (COMPANY_OUT_OF_MEMORY == companyError) {
        return FACULTY_OUT_OF_MEMORY;
    }

    if (NULL == company) {
        return  FACULTY_OUT_OF_MEMORY;
    }

    SetResult setResult = setAdd(faculty->companies, company);
    companyDestroy(company);

    assert(SET_NULL_ARGUMENT != setResult);
    if (SET_ITEM_ALREADY_EXISTS == setResult) {
        return FACULTY_COMPANY_ALREADY_EXISTS;
    } else if (SET_OUT_OF_MEMORY == setResult) {
        return FACULTY_OUT_OF_MEMORY;
    }

    return FACULTY_SUCCESS;
}

FacultyErrorCode facultyRemoveCompany(Faculty faculty, Company company) {
    if (NULL == faculty || NULL == company) {
        return FACULTY_NULL_PARAMETER;
    }

    SetResult setResult = setRemove(faculty->companies, company);
    assert(SET_NULL_ARGUMENT != setResult);

    if (SET_ITEM_DOES_NOT_EXIST == setResult) {
        return FACULTY_COMPANY_DOES_NOT_EXIST;
    }

    return FACULTY_SUCCESS;
}

int facultyCompareElements(SetElement element1, SetElement element2) {
    if (NULL == element1 || NULL == element2){
        return INVALID_PARAMETER;
    }
    Faculty faculty1 = element1, faculty2 = element2;
    return (int)(faculty1->Name) - (int)(faculty2->Name);
}

SetElement facultyCopyElement(SetElement src_faculty) {
    if (NULL == src_faculty) {
        return NULL;
    }
    Faculty ptr = src_faculty;

    FacultyErrorCode facultyError;
    Faculty faculty = facultyCreate(ptr->Name, &facultyError);
    if (NULL == faculty) {
        return NULL;
    }

    setDestroy(faculty->companies);
    faculty->companies = setCopy(ptr->companies);
    if (NULL == faculty->companies) {
        facultyDestroy(faculty);
        return NULL;
    }

    faculty->earnings = ptr->earnings;

    return faculty;
}

TechnionFaculty facultyGetName(Faculty faculty) {
    if (NULL == faculty) {
        return UNKNOWN;
    }

    return faculty->Name;
}

int facultyGetEarnings(Faculty faculty) {
    if (NULL == faculty) {
        return INVALID_PARAMETER;
    }

    return faculty->earnings;
}

void facultyIncEarnings(Faculty faculty, int earnings) {
    faculty->earnings += earnings;
}

Company facultyGetCompanyByEmail(Faculty faculty, char *email,
                                 FacultyErrorCode *facultyError) {
    if(NULL == facultyError){
        return NULL;
    }
    if (NULL == faculty || NULL == email) {
        *facultyError = FACULTY_NULL_PARAMETER;
        return NULL;
    }
    if(!isValidEmail(email)){
        *facultyError = FACULTY_INVALID_PARAMETER;
        return NULL;
    }

    Company company_iterator = setGetFirst(faculty->companies);

    while (NULL != company_iterator) {
        if (isCompanyEmailEqual(company_iterator, email)) {
            *facultyError = FACULTY_SUCCESS;
            return company_iterator;
        }

        company_iterator = setGetNext(faculty->companies);
    }
    *facultyError = FACULTY_COMPANY_DOES_NOT_EXIST;
    return NULL;
}

Room facultyGetRoomByID(Faculty faculty, Company *company, int id,
                        FacultyErrorCode *facultyError) {
    if (NULL == facultyError){
        return NULL;
    }
    if (NULL == company || NULL == faculty){
        *facultyError = FACULTY_NULL_PARAMETER;
        return NULL;
    }
    *company = NULL;
    if (id <= 0) {
        *facultyError = FACULTY_INVALID_PARAMETER;
        return NULL;
    }

    Company company_iterator = setGetFirst(faculty->companies);
    while (NULL != company_iterator)
    {
        Room room = companyGetRoomByID(company_iterator, id);
        if (NULL != room) {
            *facultyError = FACULTY_SUCCESS;
            *company = company_iterator;
            return room;
        }
        company_iterator = setGetNext(faculty->companies);
    }
    *facultyError = FACULTY_ID_DOES_NOT_EXIST;
    return NULL;
}

bool isCompanyEmailFaculty(Faculty faculty, char *email) {
    if (NULL == faculty || NULL == email) {
        return false;
    }
    Company company_iterator = setGetFirst(faculty->companies);
    while (NULL != company_iterator) {
        if (isCompanyEmailEqual(company_iterator, email)) {
            return true;
        }
        company_iterator = setGetNext(faculty->companies);
    }
    return false;
}

Room facultyMostRecommendedRoom(Faculty faculty, Escaper escaper,
                                TechnionFaculty escaperFaculty, int P_e,
                                int skill, int *result, int *faculty_distance,
                                int *room_id, Company *cur_company) {
    if (!isValidDifficultyOrSkill(skill) || P_e <= 0){
        return NULL;
    }
    int min_result = INVALID_PARAMETER, cur_result = INVALID_PARAMETER,
        min_room_id =INVALID_PARAMETER, min_faculty_distance =INVALID_PARAMETER,
        cur_room_id =INVALID_PARAMETER, cur_faculty_distance =INVALID_PARAMETER;

    Room cur_recommended_room = NULL, most_recommended_room = NULL;
    Company company_iterator, most_recommended_company = NULL;

    company_iterator = setGetFirst(faculty->companies);
    while (NULL != company_iterator) {

        cur_recommended_room = companyMostRecommendedRoom(company_iterator,
                                      escaperFaculty, P_e, skill, &cur_result,
                                      &cur_faculty_distance, &cur_room_id);

        checkBetterRoom(escaper, cur_result, cur_room_id, cur_faculty_distance,
                        cur_recommended_room, &min_result, &min_room_id,
                        &min_faculty_distance, &most_recommended_room,
                        &most_recommended_company, company_iterator);
        company_iterator = setGetNext(faculty->companies);
    }
    *result = min_result;
    *faculty_distance = min_faculty_distance;
    *room_id = min_room_id;
    *cur_company = most_recommended_company;

    return most_recommended_room;
}

