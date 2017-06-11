//
// Created by Shahak on 06/06/2017.
//

#include "escaper.h"
#include "utils.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INVALID_PARAMETER -1

struct Escaper_t {
    TechnionFaculty escaperFaculty;
    char *email;
    int skill_level;
};

/**...........................................................................*/
/**-----------------------FUNCTIONS-IMPLEMENTATIONS---------------------------*/
/**...........................................................................*/


Escaper escaperCreate(char *email, TechnionFaculty escaperFaculty,
                      int skill_level) {
    assert(isValidEscaperParams(escaperFaculty, email, skill_level));
    if (NULL == email){
        return NULL;
    }
    Escaper escaper = malloc(sizeof(*escaper));
    if (NULL == escaper) {
        return NULL;
    }

    escaper->email = malloc(strlen(email) + 1);
    if (NULL == escaper->email) {
        free(escaper);
        return NULL;
    }
    strcpy(escaper->email, email);
    escaper->escaperFaculty = escaperFaculty;
    escaper->skill_level = skill_level;
    return escaper;
}


void escaperDestroy(SetElement element) {
    if (NULL == element) {
        return;
    }
    Escaper escaper = element;
    free(escaper->email);
    free(escaper);
}


int escaperCompareElements(SetElement escaper_1, SetElement escaper_2) {
    if (NULL == escaper_1 || NULL == escaper_2) {
        return INVALID_PARAMETER;
    }
    Escaper ptr1 = escaper_1, ptr2 = escaper_2;
    int tmp_cmp = strcmp(ptr1->email, ptr2->email);
    if (tmp_cmp == 0) {
        return 0;
    } else {
        return 1;
    }
}

SetElement escaperCopyElement(SetElement src_escaper) {
    if (NULL == src_escaper) {
        return NULL;
    }
    Escaper ptr = src_escaper;
    Escaper escaper = escaperCreate(ptr->email, ptr->escaperFaculty,
                                    ptr->skill_level);
    return escaper;
}

char *escaperGetEmail(Escaper escaper) {
    if (NULL == escaper) {
        return NULL;
    }
    char *email = malloc(strlen(escaper->email) + 1);
    if (NULL == email) {
        return NULL;
    }
    strcpy(email, escaper->email);
    return email;
}

TechnionFaculty escaperGetNameFaculty(Escaper escaper) {
    if (NULL == escaper) {
        return UNKNOWN;
    }
    return escaper->escaperFaculty;
}

int escaperGetSkillLevel(Escaper escaper) {
    if (NULL == escaper) {
        return INVALID_PARAMETER;
    }
    return escaper->skill_level;
}

bool isEscaperEmailEqual(Escaper escaper, char *email) {
    if (NULL == escaper || NULL == email) {
        return false;
    }
    if (strcmp(escaper->email, email) == 0) {
        return true;
    }
    return false;
}
