//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2

int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection,place_num,i,input_patient;
    char input_place[40];
    int age_max,age_min;
    int index;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    //fp = fopen(argv[1], "r");
    fp = fopen("patientInfo_sample.txt","r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
  
    //1-2. loading each patient informations
    
    
    while ( 3 == fscanf( fp, "%d %d %d", &pIndex, &age, &time)) 
    {
	    int i;
	    printf("\n");
	    printf("%d %d %d ", pIndex, age, time);
    	for(i=0;i<5;i++) {
    		if (i!= 4){
				fscanf(fp, "%d", &placeHist[i]);
			}
			else {
				fscanf(fp, "%d\n", &placeHist[i]);
			}
			printf("%d ",placeHist[i]);
		
		}

		ifct_element = ifctele_genElement(pIndex, age, time, placeHist);
		
		ifctdb_addTail(ifct_element);
		printf("\n");
	}
	
    
    //1-3. FILE pointer close
    fclose(fp);
    
    
	/*
    	int place1, place2;
    	
		place1 = 3;
    	place2 = 15;
    	
    	printf("The first place is %s\n", ifctele_getPlaceName(place1)) ;
    	printf("The second place is %s\n", ifctele_getPlaceName(place2)) ;
	*/
	
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT: //프로그램 종료  
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT: //특정 환자에 대한 정보 출력  
            	
            	printf("Insert Patient Info : ");
            	scanf("%d",&index);  
            	
            	ifctele_printElement(ifctdb_getData(index));
                break;
                
            case MENU_PLACE: //특정 장소에서 감염이 확인된 환자 관련 정보 출력
            	printf("Place Info : ");
                scanf("%s",&input_place);
                
                for(i = 0; i < ifctdb_len() ; i++) {
                	place_num = ifctele_getHistPlaceIndex(ifctdb_getData(i), 4); //환자가 마지막으로 들린 장소 
                	if ( strcmp(ifctele_getPlaceName(place_num), input_place)==0 ){
                			printf("\npatient %d are detected in %s.\n",i,ifctele_getPlaceName(place_num));
                			printf("Information of patient %d\n",i);
                			ifctele_printElement(ifctdb_getData(i)); //환자 관련 정보 출력  
                			break;
                		}
                }
                break;
                
            case MENU_AGE: //특정 범위의 나이에 해당하는 환자 관련 정보 출력  
                printf("Age Max : ");
            	scanf("%d",&age_max);
            	printf("Age Min : ");
            	scanf("%d",&age_min);
            	
            	for (i = 0; i <  ifctdb_len() ; i++) {
            		index = ifctele_getAge(ifctdb_getData(i));
            		if(index <= age_max && index >= age_min){
            			printf("patient %d is in age minmax range!!\n",i);
            			ifctele_printElement(ifctdb_getData(i));
					} 
				}
                break;
                
                
            /*    
            case MENU_TRACK: //감염 경로 및 최초 전파자 추적  
                printf("Patient Info : ");
            	scanf("%d",&index);
            	
            	//1. 입력한 환자의 경로 추적  
            	
				//2. 입력한 환자 외의 다른 환자들 경로 추적  
				
				//3.  1-2 비교후 동일한 time, place 추적  
				int infector[]; if_time[], first_infector;
				char if_place;
				
				for(){
			    printf("-->[TRAKING] patient %d is infected by %d. (time : %d, place : %s)\n", index, infector[], if_time[], if_place[]);
				}
				
				//4. 최초 전파자 출력 
				if (index != first_infector) 
				printf("the first infector of %d is %d", index, first_infector);
			
				//4-1. 입력한 전파자와 4에서 추적한 최초 전파자가 동일한 경우 
			    else
					printf("%d patient is the first infector!!", index); 
        
                break;
            */
        
        
        
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}



