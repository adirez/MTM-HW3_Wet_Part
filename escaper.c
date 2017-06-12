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
                      int skill_level, EscaperErrorCode *escaperError) {
    if(NULL == escaperError){
        return NULL;
    }
    if(NULL == email){
        *escaperError = ESCAPER_NULL_PARAMETER;
        return NULL;
    }
    if(!isValidEscaperParams(escaperFaculty, email, skill_level)){
    *escaperError = ESCAPER_INVALID_PARAMETER;
    return NULL;
    }
    Escaper escaper = malloc(sizeof(*escaper));
    if (NULL == escaper) {
        *escaperError = ESCAPER_OUT_OF_MEMORY;
        return NULL;
    }

    escaper->email = malloc(strlen(email) + 1);
    if (NULL == escaper->email) {
        free(escaper);
        *escaperError = ESCAPER_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(escaper->email, email);
    escaper->escaperFaculty = escaperFaculty;
    escaper->skill_level = skill_level;
    *escaperError = ESCAPER_SUCCESS;
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


int escaperCompareElements(SetElement element1, SetElement element2) {
    Escaper escaper1 = element1, escaper2 = element2;
    return  strcmp(escaper1->email, escaper2->email);
}

SetElement escaperCopyElement(SetElement src_escaper) {
    if (NULL == src_escaper) {
        return NULL;
    }
    EscaperErrorCode escaperError;
    Escaper ptr = src_escaper; //to make the code clearer
    Escaper escaper = escaperCreate(ptr->email, ptr->escaperFaculty,
                                 ptr->skill_level, &escaperError);
    if(escaperError != ESCAPER_SUCCESS){
        return NULL;
    }
    return escaper;
}

char *escaperGetEmail(Escaper escaper, EscaperErrorCode *escaperError) {
    if(NULL == escaperError){
        return NULL;
    }
    if (NULL == escaper) {
        *escaperError = ESCAPER_NULL_PARAMETER;
        return NULL;
    }
    char *email = malloc(strlen(escaper->email) + 1);
    if (NULL == email) {
        *escaperError = ESCAPER_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(email, escaper->email);
    *escaperError = ESCAPER_SUCCESS;
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
