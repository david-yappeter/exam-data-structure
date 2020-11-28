#include<stdio.h>

#include "../controllers/patientService.h"

int main(){

    struct Patient *head = NULL;
    struct Patient *tail = NULL;

    int total, cure;
    scanf("%d %d", &total, &cure);
    getchar();

    for(int i = 0; i < total ; i++){
        int day, year;
        char month[50];
        char name[150];

        scanf("%d %s %d %*s%*c%[^\n]%*c", &day, &month, &year, &name);

        struct Patient *NewPatient = CreatePatient((char *) name, day, (char *) month, year);

//		Kalo di Hilangkan Langsung error, ntah kenapa
		printf("");

        PatientPriorityPush(&head, &tail, NewPatient);
    }
    
    for(int i = 0; i < cure; i++){
    	PatientPopFront(&head, &tail);
	}
	
	if(cure - total >= 0){
		printf("All patients get the cure, %d cure left\n", cure - total);
	}
	else{
		printf("Need %d more cure\n", total - cure);
		
    	PatientViewReverse(&tail);
	}	
	
	while(head != NULL){
		PatientPopBack(&head, &tail);
	}

    return 0;
}
