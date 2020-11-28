#ifndef PATIENT_SERVICE_PARAM
#define PATIENT_SERVICE_PARAM 1

#include"../models/models.h"
#include<stdlib.h>
#include<string.h>

int MonthSmallerThan(char *a, char* b){
    char arr[12][50] = {
        "january",
        "february",
        "march",
        "april",
        "may",
        "juny",
        "july",
        "august",
        "september",
        "october",
        "november",
        "december",
    };

    int index1,index2;

    for(int i = 0; i < 12; i++){
        if(strcasecmp(a, arr[i]) == 0){
            index1 = i;
        }
        if(strcasecmp(b, arr[i]) == 0){
            index2 = i;
        }
    }
    if(index1 == index2){
        return 2;
    }
    else if(index1 > index2){
        return 1;
    }
    else{
        return 0;
    }
}

bool OlderThan(struct Patient **a, struct Patient **b){
    if((*a)->year < (*b)->year){
        return true;
    }
    else if((*a)->year > (*b)->year){
        return false;
    }
    else{
        if(MonthSmallerThan((*a)->month, (*b)->month) == 1){
            return true;
        }
        else if(MonthSmallerThan((*a)->month, (*b)->month) == 0){
            return false;
        }
        else{
            if((*a)->day < (*b)->day){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

struct Patient* InitializePatient(){
    return (struct Patient *) malloc(sizeof(struct Patient));
}

struct Patient* CreatePatient(char *name, int day, char* month, int year){
    struct Patient *temp = InitializePatient();
    
	temp->name = strdup(name);
	temp->month = strdup(month);
	
//	Masalah Segmentation Fault, makanya pake strdup()
//    strcpy(temp->name, name);
//    strcpy(temp->month, month);
    temp->day = day;
    temp->year = year;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void PatientPopFront(struct Patient **head, struct Patient **tail){
	if((*head) == NULL){
        return;
    }
    if((*head) == (*tail)){
        (*head) = (*tail) = NULL;
    }
    else{
        struct Patient *curr = (*head);
        curr = curr->next;
        curr->prev = NULL;
        (*head) = NULL;
        free((*head));
        (*head) = curr;
    }
}

void PatientPopBack(struct Patient **head, struct Patient **tail){
    if((*head) == NULL){
        return;
    }
    if((*head) == (*tail)){
        (*head) = (*tail) = NULL;
    }
    else{
        struct Patient *curr = (*tail);
        curr = curr->prev;
        curr->next = NULL;
        (*tail) = NULL;
        free((*tail));
        (*tail) = curr;
    }
}

void PatientPriorityPush(struct Patient **head, struct Patient **tail, struct Patient *inserted){
    if((*head) == NULL){
        (*head) = (*tail) = inserted;
    }
    else if(OlderThan(head, &inserted) == false){
        inserted->next = (*head);
        (*head)->prev = inserted;
        (*head) = inserted;
    }
    else if(OlderThan(&inserted, tail) == false){
        inserted->prev = (*tail);
        (*tail)->next = inserted;
        (*tail) = inserted;
    }
    else{
        struct Patient *curr = (*head);

        while(OlderThan(&inserted, &curr) == false){
            curr = curr->next;
        }

        inserted->next = curr;
        inserted->prev = curr->prev;
        curr->prev->next = inserted;
        curr->prev = inserted;
    }
}

void PatientView(struct Patient **head){
    struct Patient *curr = (*head);

    while(curr != NULL){
        printf("%d %s %d - %s\n", curr->day, curr->month, curr->year, curr->name);
        curr = curr->next;
    }
}

void PatientViewReverse(struct Patient **tail){
    struct Patient *curr = (*tail);

    while(curr != NULL){
        printf("%d %s %d - %s\n", curr->day, curr->month, curr->year, curr->name);
        curr = curr->prev;
    }
}

#endif
