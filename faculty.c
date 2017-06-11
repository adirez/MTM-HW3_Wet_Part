//
// Created by Shahak on 11/06/2017.
//

#include "faculty.h"
#include "utils.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INVALID_PARAMETER -1

struct Faculty_t {
    TechnionFaculty Name;
    Set companies;
    int earnings;
};


/**...........................................................................*/
/**-----------------------FUNCTIONS-IMPLEMENTATIONS---------------------------*/
/**...........................................................................*/


Faculty facultyCreate(TechnionFaculty nameFaculty) {
    assert(isValidFacultyName(nameFaculty));
    Faculty faculty = malloc(sizeof(*faculty));
    if (NULL == faculty) {
        return NULL;
    }

    faculty->companies = setCreate(facultyCopyElement, facultyDestroy,
                                   facultyCompareElements);

    if (NULL == faculty->companies) {
        free(faculty);
        return NULL;
    }

    faculty->Name = nameFaculty;
    faculty->earnings = 0;
    return faculty;
}

void facultyDestroy(SetElement faculty) {
    if (NULL == faculty) {
        return;
    }

    Faculty ptr = faculty;
    setDestroy(ptr->companies);
    free(ptr);
    return;
}

FacultyErrorCode facultyAddCompany(Faculty faculty, char *email) {
    if (NULL == faculty || NULL == email) {
        return FACULTY_INVALID_PARAMETER;
    }

    Company company = companyCreate(faculty->Name, email);

    if (NULL == company) {
        return  FACULTY_OUT_OF_MEMORY;
    }

    SetResult setResult = setAdd(faculty->companies, company);
    companyDestroy(company);

    assert(setResult != SET_NULL_ARGUMENT);
    if (setResult == SET_ITEM_ALREADY_EXISTS) {
        return FACULTY_COMPANY_ALREADY_EXISTS;
    } else if (setResult == SET_OUT_OF_MEMORY) {
        return FACULTY_OUT_OF_MEMORY;
    }

    return FACULTY_SUCCESS;
}

FacultyErrorCode facultyRemoveCompany(Faculty faculty, Company company) {
    if (NULL == faculty || NULL == company) {
        return FACULTY_INVALID_PARAMETER;
    }

    SetResult setResult = setRemove(faculty->companies, company);
    assert(setResult != SET_NULL_ARGUMENT);

    if (setResult == SET_ITEM_DOES_NOT_EXIST) {
        return FACULTY_COMPANY_DOES_NOT_EXIST;
    }

    return FACULTY_SUCCESS;
}

int facultyCompareElements(SetElement faculty_1, SetElement faculty_2) {
    if (NULL == faculty_1 || NULL == faculty_2) {
        return INVALID_PARAMETER;
    }

    Faculty ptr1 = faculty_1, ptr2 = faculty_2;

    int name_1 = (int)(ptr1->Name), name_2 = (int)(ptr2->Name);

    if (name_1 == name_2) {
        return 0;
    }

    return 1;
}

SetElement facultyCopyElement(SetElement src_faculty) {
    if (NULL == src_faculty) {
        return NULL;
    }

    Faculty ptr1 = src_faculty;
    TechnionFaculty src_name = ptr1->Name;

    Faculty faculty = facultyCreate(src_name);
    if (NULL == faculty) {
        return NULL;
    }

    Set companies = setCopy(ptr1->companies);
    if (NULL == companies) {
        facultyDestroy(faculty);
        return NULL;
    }

    faculty->Name = ptr1->Name;
    faculty->companies = companies;
    faculty->earnings = ptr1->earnings;

    return faculty;
}

int facultyGetMinRoomID(Faculty faculty) {
    if (NULL == faculty) {
        return INVALID_PARAMETER;
    }

    int min_id = INVALID_PARAMETER;
    Company company_iterator = setGetFirst(faculty->companies);

    while (NULL != company_iterator) {
        int tmp_id = companyGetMinRoomID(company_iterator);
        if (tmp_id < min_id || min_id == INVALID_PARAMETER) {
            min_id = tmp_id;
        }
        company_iterator = setGetNext(faculty->companies);
    }

    return min_id;
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

Company facultyGetCompanyByEmail(Faculty faculty, char *email) {
    if (NULL == faculty || NULL == email) {
        return NULL;
    }

    Company company_iterator = setGetFirst(faculty->companies);

    while (NULL != company_iterator) {
        if (isCompanyEmailEqual(company_iterator, email)) {
            return company_iterator;
        }

        company_iterator = setGetNext(faculty->companies);
    }
    return NULL;
}
