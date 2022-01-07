/*
 * This file gives full implementation of a few functions and gives headers for the rest of the functions that you
 * are required to implement.
 * You may also find all of these functions as part of the TODO list
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "household.h"
// sorting function required for ranking of data
void sortSelection(LocationCountPair arr[], int arrSize){
    int min = 0, temp = 0;
    char tempStr[20];

    for (int i = 0; i < arrSize ; i++)
    {
        min = i;  // record the position of the smallest
        for (int j = i + 1; j < arrSize; j++)
        {
            // update min when finding a smaller element
            if (arr[j].count > arr[min].count)
                min = j;
        }
        // put the smallest element at position i
        temp = arr[i].count;
        arr[i].count = arr[min].count;
        arr[min].count = temp;
        strcpy(tempStr, arr[i].town);
        strcpy(arr[i].town, arr[min].town);
        strcpy(arr[min].town, tempStr);
    }
}
/**
 * This is a generic validation function that takes the upper bound of valid options up to 8 and returns 9 if the user
 * opts to go back to the previous menu instead of providing valid data. Therefore 9 should not be a valid choice!!
 * @param upperbound
 * @return
 */
int dataValidation(int upperbound){
    int n = 0, num;
    char temp[40];
    while (1)
    {
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%d", &num);
        if (num == 9) return num;
        else if(num >= 0 && num <= upperbound && n == 1) return num;
        else
        {
            printf("Invalid data, Enter an integer 0 through %d or enter 9 to go back to the main menu. Try again \n",upperbound );
            continue;
        }

    } //while loop ends
}// dataValidation function ends

// full implementation of regionMapping function is given as a sample to help write other matching functions, if required.
/**
 *
 * @param x Takes an integer representing a region
 * @return and returns the corresponding region's name
 */
char* regionMapping(int x)
{
    char* str;
    switch(x)
    {
        case 0:
            str = "Durham";
            break;
        case 1:
            str = "Peel";
            break;
        case 2:
            str = "York";
            break;
        default:
            str = "York";
    }
    return str;
}// ends regionMapping function
/**
 * Full implementation of the menu function is provided that implements entire main user interface of the application.
 * Students are required to implement various functions called in this menu.
 * A list of ToDos is also given for easier development
 * @param top of the list to be provided by reference.
 */
void menu(NodePtr* top)
{
    int optionTopLevel = 0;
    while (1)
    {
        // Display a menu to the user
        char temp[120];
        char option[120];
        int valid = 0;
        puts("Menu:");
        printf("Enter your choice to\n");
        printf("1. display households of a race\n");
        printf("2. display households of a region\n");
        printf("3. display households of a town\n");
        printf("4. display households of a region with a given minimum number of people tested positive for Covid-19\n");
        printf("5. display the regions town-wise ranking of number of people fully vaccinated positive for Covid-19\n");
        printf("6. add a record\n");
        puts("7. delete all records of a region, town and race triplet");
        puts("8. display updated data");
        puts("9. store data to a file");
        puts("10. display data from file");
        puts("0. to exit the program");
        scanf("%d", &optionTopLevel);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { } // input stream flushing

        if (optionTopLevel == 0)
        {
            printf("\nThank you");
            return;
        }
        else if (optionTopLevel > 10)
        {
            printf("Invalid selection, enter an integer 0 through 10, try again\n");
            continue;
        }
        int regionOption = 0, townOption = 0, raceOption = 0, numberTested, numberTestedPos;
        char filename[120] = "..//data//";
        char strTemp[120];
        switch( optionTopLevel) {
            case 1:
                puts("Enter an integer for race: CAUCASIAN (0), INDIGENOUS(1), AFRO AMERICAN(2), ASIAN(3), and OTHER(4)");
                if((raceOption=dataValidation(4)) == 9 ) break;
                displayRecordsOfOneRace(*top, raceMapping(raceOption));
                break;
            case 2:
                puts("Enter an integer for region: Durham (0), Peel(1), and York(2):");
                if((regionOption=dataValidation(2)) == 9 ) break;
                displayRecordsOfOneRegion(*top, regionMapping(regionOption));
                break;
            case 3:
                puts("Enter an integer for town: OSHAWA(0), WHITBY(1), BRAMPTON(2), MISSISSAUGA(3), MAPLE(4) and VAUGHAN(5)");
                if((townOption=dataValidation(5)) == 9 ) break;
                displayRecordsOfOneTown(*top, townMapping(townOption));
                break;
            case 4:
                puts("Enter an integer for region: Durham (0), Peel(1), and York(2):");
                if((regionOption=dataValidation(2)) == 9 ) break;
                while(valid != 1) {
                    puts("Enter lowerbound of number of Covid-19 positive cases per household in the region\n");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &numberTestedPos);
                    if (numberTestedPos <= 0) {
                        puts("Invalid data, enter a positive integer, try again");
                        continue;
                    }
                    else valid = 1; // setting valid flag
                }
                valid = 0; // resetting valid flag for next iteration
                displayRecordsOfRegionWithPositiveCases(*top, regionMapping(regionOption), numberTestedPos);
                break;
            case 5:
                regionsTownWiseRankingVaccinated(*top);
                break;
            case 6:
                addNode(top, userInteractionForRecordAddition());
                break;
            case 7:
                puts("Enter region: 0 for Durham, 1 for Peel, 2 for York");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &regionOption);
                if(regionOption == 0){
                    puts("Enter town: 0 for Oshawa, 1 for Whitby");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                }
                else if(regionOption == 1){
                    puts("Enter town: 0 for Brampton, 1 for Mississauga");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                }
                else {
                    puts("Enter town: 0 for Maple, 1 for Vaughan");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                }
                puts("Enter race");
                puts("Enter 0 for Caucasian, 1 for indigenous, 2 for African_American, 3 for Asian, 4 for Other");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &raceOption);
                deleteNodesGivenCriteria(top, regionMapping(regionOption), townMappingRegionBased(regionOption, townOption),
                                         raceMapping(raceOption));
                break;
            case 8:
                printList(*top);
                break;
            case 9:
                puts("Enter file name with extension, for example clients.txt");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%s", strTemp);
                writeListToFile(*top, strcat(filename, strTemp));
                break;
            case 10:
                //deleteAllNodes(top); // test
                puts("Enter file name with extension, for example clients.txt");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%s", strTemp);
                displayRecordsFromFile(strcat(filename, strTemp));
                break;
            default:
                puts("Invalid option");
        } // switch block ends here

    } // while loop ends

}// menus function ends
/**
 * This function takes region integer and town integer, town integer actually represents its town number within that region
 * So if there are three towns in a region, town number 0 corresponds to the first town in that region.
 * Read the header file and carefully go through the ordering of elements of regionArr and townArr. regionArr's elements
 * are in alphabetical order, but try to figure out what is the order of townArr elements?
 * @param region an integer value representing a region
 * @param x representing index value from townsArr array (refer to the header file)
 * @return
 */
char* townMappingRegionBased(int region, int x){
    //TODO 10 implement townMappingRegionBased function
    char* str;
    switch(region) {
        case 0:
            switch (x) {
                case 0:
                    str = "OSHAWA";
                    break;
                case 1:
                    str = "WHITBY";
                    break;
            }
            break;
        case 1:
            switch (x) {
                case 0:
                    str = "BRAMPTON";
                    break;
                case 1:
                    str = "MISSISSAUGA";
                    break;
            }
            break;
        case 2:
            switch (x) {
                case 0:
                    str = "MAPLE";
                    break;
                case 1:
                    str = "VAUGHAN";
                    break;
            }
            break;
    }
    return str;

}// ends townMappingRegionBased function
/**
 * This is a simple mapping function, just like regionMapping function
 * @param x is an integer corresponding to the townArr index
 * @return char array representing name of the town
 */
char* townMapping(int x){
    //TODO 11 implement townMapping function
    char* str;
    switch(x)
    {
        case 0:
            str = "Oshawa";
            break;
        case 1:
            str = "Whitby";
            break;
        case 2:
            str = "Brampton";
            break;
        case 3:
            str = "Mississauga";
            break;
        case 4:
            str = "Maple";
            break;
        case 5:
            str = "Vaughan";
            break;
        default:
            str = "Vaughan";
    }
    return str;
}// ends townMapping function
/**
 *
 * @param x
 * @return
 */
char* raceMapping(int x)
{
    //TODO 12 implement raceMapping function
    //{"CAUCASIAN", "INDIGENOUS", "AFRO-AMERICAN", "ASIAN", "OTHER"};
    char* str;
    switch(x)
    {
        case 0:
            str = "Caucasian";
            break;
        case 1:
            str = "Indigenous";
            break;
        case 2:
            str = "Afro-American";
            break;
        case 3:
            str = "Asian";
            break;
        case 4:
            str = "Other";
            break;
        default:
            str = "Other";
    }
    return str;

}// ends raceMapping function
/**
 * It populates the linked list with valid random data. The top of the list is passed as a reference i.e. address of the pointer!
 * @param top top is passed by reference i.e. address of the pointer top is passed in the call!
 */
void initializeData(NodePtr* top) {
    // This function populates the linked list with random data.
    // TODO 01: Implement initializeData function.
    *top = NULL;
    char race[RACE_NAME_LEN];
    char region[REGION_NAME_LEN];
    char town[TOWN_NAME_LEN];
    int familySize;
    int fullyVaccinated;
    int testedPositive;

    srand(time(NULL));
    for ( int dex = 0; dex < SIZE; dex++) {
        // Number of people in the household—must be an integer greater than 0 and less than 12.
        familySize = rand() %  MAX_FAMILYSIZE + 1;
        // Number of people fully vaccinated must not be more than number of people in the household.
        fullyVaccinated = rand() %  (familySize + 1);
        // Number of people tested positive for Covid-19 must not be more than number of people in the household.
        testedPositive = rand() % (familySize + 1);
        int r = rand() % ARR_REGION_LEN;
        strcpy(region, regionsArr[r]);
        // assume equal amount of towns per each region (ARR_TOWN_LEN / ARR_REGION_LEN)
        int t = rand() % ARR_TOWN_LEN / ARR_REGION_LEN ;
        strcpy(town, townMappingRegionBased(r, t));
        strcpy(race, racesArr[rand() % ARR_RACE_LEN]);

        Household h = makeHousehold(race, region, town, familySize, testedPositive, fullyVaccinated);

        if (top == NULL) {
            makeNode(h);
        }
        else {
            addNode(top, h);
        }
    }
} //initializeData ends
/**
 *
 * @param top is the top of the list
 * @param region is the region that all the displayed records should belong to
 */
void displayRecordsOfOneRegion(NodePtr top, char region[]) {
    // TODO 02: implement displayRecordsOfOneRegion function
    NodePtr curr = top;
    int count = 0;
    int key, ctr;

    if (curr == NULL) {
        puts("----------------List is empty----------------\n");
        return;
    }
    printf("Records with region: %s\n", region);
    printHeader();
    while (curr != NULL ) {
        if (curr != NULL) {
            ctr = 0;
            for (int dex = 0; dex < strlen(region); dex++) {
                //if criteria is matching
                if (curr->data.region[dex] == toupper(region[dex])) {
                    ctr++;
                    key = 0;
                } else { key = -1; }
            }
            if (key == 0 && ctr == strlen((region))) {
                count++;
                printRecord(count, curr);
            }
            top = top->next; // move the top
            curr = top;
        }
    }
    if (count == 0) {
        puts("----------------Record not found----------------\n");
    }
} //ends displayRecordsOfOneRegion
/**
 *
 * @param top
 * @param town
 */
void displayRecordsOfOneTown(NodePtr top, char town[]) {
    // TODO 03: implement displayRecordsOfOneTown function
    NodePtr curr = top;
    int count = 0;
    int key, ctr;

    if (curr == NULL) {
        puts("----------------List is empty----------------\n");
        return;
    }
    printf("Records with town: %s\n", town);
    printHeader();
    // if the series of nodes at the top hold the given criteria
    while (curr != NULL ) {
        if (curr != NULL) {
            ctr = 0;
            for (int dex = 0; dex < strlen(town); dex++) {
                    // if criteria is matching
                    if (curr->data.town[dex] == toupper(town[dex])) {
                        ctr++;
                        key = 0;
                    } else { key = -1; }
            }
            if (key == 0 && ctr == strlen((town))) {
                count++;
                printRecord(count, curr);
            }
            top = top->next; // move the top
            curr = top;
        }
    }
    if (count == 0) {
        puts("----------------Record not found----------------\n");
    }
} //ends displayRecordsOfOneTown
/**
 *
 * @param top
 * @param race
 */
void displayRecordsOfOneRace(NodePtr top, char race[]) {
    // TODO 04: implement displayRecordsOfOneRace function
    NodePtr curr = top;
    int count = 0;
    int key, ctr;

    if (curr == NULL) {
        puts("----------------List is empty----------------\n");
        return;
    }
    printf("Records with race: %s\n", race);
    printHeader();
    // if the series of nodes at the top hold the given criteria
    while (curr != NULL ) {
        if (curr != NULL) {
            ctr = 0;
            for (int dex = 0; dex < strlen(race); dex++) {
                // compare if strings are equal
                if (curr->data.race[dex] == toupper(race[dex])) {
                    ctr++;
                    key = 0;
                } else { key = -1; }
            }
            if (key == 0 && ctr == strlen((race))) {
                count++;
                printRecord(count, curr);
            }
            top = top->next; // move the top
            curr = top;
        }
    }
    if (count == 0) {
        puts("----------------Record not found----------------\n");
    }
} //ends displayRecordsOfOneTown
/**
 *
 * @param top
 * @param region
 * @param numOfPositiveCases
 */
void displayRecordsOfRegionWithPositiveCases(NodePtr top, char region[], int numOfPositiveCases){
    // TODO 05: implement displayRecordsOfRegionWithPositiveCases function
    NodePtr curr = top;
    int count = 0;
    char upperRegion[strlen(region)];

    if (curr == NULL) {
        puts("----------------List is empty----------------\n");
        return;
    }
    printHeader();

    // Convert to upper case to map to array data
    int i =0;
    while (region[i])
    {
        upperRegion[i]= toupper(region[i]);
        i++;
    }
    // if the series of nodes at the top hold the given criteria
    while (curr != NULL ) {
        if (strcmp(curr->data.region, upperRegion) == 0 && curr->data.testedPositive >= numOfPositiveCases) {
            count++;
            printRecord(count, curr);
        }
        top = top->next; // move the top
        curr = top;
    }
    if (count == 0) {
        puts("----------------Records not found----------------\n");
    }
}

/**
 * This function ranks all the towns in descending order of total number of people vaccinated
 * @param top
 */
void regionsTownWiseRankingVaccinated(NodePtr top){
    // TODO 06: implement regionsTownWiseRankingVaccinated function
    NodePtr curr = top;
    LocationCountPair lcpTown[ARR_TOWN_LEN] = {0};
    LocationCountPair lcpRegion[ARR_REGION_LEN] = {0};

    while (curr != NULL ) {
        for (int dex = 0; dex < ARR_REGION_LEN; dex++) {
            if (strcmp(curr->data.region, regionsArr[dex]) == 0) {
                strcpy(lcpRegion[dex].town, curr->data.region);
                lcpRegion[dex].count = lcpRegion[dex].count + curr->data.fullyVaccinated;
            }
        }
        for (int dex = 0; dex < ARR_TOWN_LEN; dex++) {
            if (strcmp(curr->data.town, townsArr[dex]) == 0){
                strcpy(lcpTown[dex].town, curr->data.town);
                lcpTown[dex].count = lcpTown[dex].count + curr->data.fullyVaccinated;
            }
        }
        top = top->next; // move the top
        curr = top;
    }
    sortSelection(lcpRegion, ARR_REGION_LEN);
    sortSelection(lcpTown, ARR_TOWN_LEN);
    puts("Total vaccinated:");
    puts("Region-wise ranking:");
    for (int dex = 0; dex < ARR_REGION_LEN; dex++) {
        printf("%18s : %d\n", lcpRegion[dex].town, lcpRegion[dex].count);
    }
    puts("Town-wise ranking:");
    for (int dex = 0; dex < ARR_TOWN_LEN; dex++) {
        printf("%18s : %d\n", lcpTown[dex].town, lcpTown[dex].count);
    }
} // function regionsTownWiseRankingVaccinated ends
/**
 * This function gets validated data from the user for adding a record and then invokes makeHousehold function as part
 * of the return statement
 * @return  it returns a household instance that this function creates based on validated user input
 */
Household userInteractionForRecordAddition() {
    // TODO 07: implement userInteractionForRecordAddition function
    int raceOption, regionOption, townOption;
    char race[RACE_NAME_LEN];
    char region[REGION_NAME_LEN];
    char town[TOWN_NAME_LEN];
    int familySize;
    int fullyVaccinated;
    int testedPositive;

    puts("Enter an integer for race: CAUCASIAN (0), INDIGENOUS(1), AFRO AMERICAN(2), ASIAN(3), and OTHER(4):");
    raceOption=dataValidation(4);
    while (raceOption==9) {
        puts("Go back to the main menu is not available at this moment. Please make a selection.\n"
             "Enter an integer for race: CAUCASIAN (0), INDIGENOUS(1), AFRO AMERICAN(2), ASIAN(3), and OTHER(4):");
        raceOption=dataValidation(4);
    }
    strcpy(race, racesArr[raceOption]);

    puts("Enter an integer for region: Durham (0), Peel(1), and York(2):");
    if (regionOption=dataValidation(2));
    while (regionOption==9) {
        puts("Go back to the main menu is not available at this moment. Please make a selection.\n"
             "Enter an integer for region: Durham (0), Peel(1), and York(2):");
        regionOption=dataValidation(2);
    }
    strcpy(region, regionsArr[regionOption]);

    switch (regionOption)
   {
        case 0:
            puts("Enter an integer for town: OSHAWA(0), WHITBY(1):");
            townOption=dataValidation(1);
           while (townOption==9) {
               puts("Go back to the main menu is not available at this moment. Please make a selection.\n"
                    "Enter an integer for town: OSHAWA(0), WHITBY(1):");
               townOption=dataValidation(1);
           }
            strcpy(town, townsArr[townOption]);
            break;
        case 1:
            puts("Enter an integer for town: BRAMPTON(0), MISSISSAUGA(1):");
            townOption=dataValidation(1);
           while (townOption==9) {
               puts("Go back to the main menu is not available at this moment. Please make a selection.\n"
                    "Enter an integer for town: BRAMPTON(0), MISSISSAUGA(1):");
               townOption=dataValidation(1);
           }
            strcpy(town, townsArr[townOption + regionOption + 1]);
            break;
        case 2:
            puts("Enter an integer for town: MAPLE(0), VAUGHAN(1):");
            townOption=dataValidation(1);
           while (townOption==9) {
               puts("Go back to the main menu is not available at this moment. Please make a selection.\n"
                    "Enter an integer for town: MAPLE(0), VAUGHAN(1):");
               townOption=dataValidation(1);
           }
            strcpy(town, townsArr[townOption + regionOption + 1]);
            break;
    }
    puts("Please enter");
    puts("1-total people in the household,");
    puts("2-people fully vaccinated,");
    puts("3-people tested Covid positive");
    puts("* separated by space/tab and make sure all of these are valid integers");
    scanf("%d %d %d", &familySize, &fullyVaccinated, &testedPositive);
    while (familySize <= 0 || familySize > MAX_FAMILYSIZE || fullyVaccinated < 0 || fullyVaccinated > familySize ||
            testedPositive < 0 || testedPositive > familySize) {
        printf("Total people in the household has to be from 1 to %d "
               "and can't be less than total vaccinated or total Covid positive cases.\n"
               "Please re-enter values:\n", MAX_FAMILYSIZE);
        scanf("%d %d %d", &familySize, &fullyVaccinated, &testedPositive);
    };

    Household h = makeHousehold(race, region, town, familySize, testedPositive, fullyVaccinated);
    puts("----------------Record added successfully----------------\n");
    return h;
}
/**
 *
 * @param top top of the list to be passed by reference
 * @param region passed as a character array
 * @param town passed as a character array
 * @param race passed as a character array
 */
void deleteNodesGivenCriteria(NodePtr* top, char region[], char town[], char race[]) {
    //TODO 08: implement deleteNodesGivenCriteria function
    NodePtr curr = *top;
    int key;

    if (curr == NULL) {
        puts("----------------List is empty----------------\n");
        return;
    }
    key = getKey(curr, region, town, race);
    int count = 0;
    // if the series of nodes at the top hold the given criteria
    while (curr != NULL && key == 0) {
        *top = (*top)->next; // move the top
        free(curr); // to ensure no memory leak
        count++;
        curr = *top;
        if( curr != NULL) {
            key = getKey(curr, region, town, race);
        }
    }
    if (curr == NULL) {
        if (count == 0) {
            puts("----------------Record not found----------------\n");
            return;
        }
        else {
            printf("%d matching records deleted\n", count);
            return;
        }
    }
    while (curr != NULL) {
        NodePtr prev;
        // iterating through the list
        while (curr != NULL && key != 0) {
            prev = curr;
            curr = curr->next;
            if( curr != NULL) {
                key = getKey(curr, region, town, race);
            }
        } // end outer while loop that checks end of the list
        if (curr == NULL) {
            if (count == 0) {
                puts("----------------Record not found----------------\n");
                return;
            }
            else {
                printf("%d matching records deleted\n", count);
                return;
            }
        }
        prev->next = curr->next;
        free(curr);
        count++;
        curr = prev->next;
        if (curr != NULL) {
            key = getKey(curr, region, town, race);
        }
        else {
            printf("%d matching records deleted\n", count);
            return;
        }
    } // end outer while loop
}// deleteNodeCriteria function ends
/**
 *
 * @param top top of the list to be passed by reference
 * @param region passed as a character array
 * @param town passed as a character array
 * @param race passed as a character array
 */
int getKey(NodePtr top, char region[], char town[], char race[]) {
    NodePtr curr = top;
    int ctr = 0;
    int key;

    for(int dex = 0; dex < strlen(region); dex++) {
        if (curr->data.region[dex] == toupper(region[dex])) {
            ctr++;
            key = 0;
        } else { return -1; }
    }
    if (key == 0 && ctr == strlen((region))) {
        key = 0;
    } else { return -1; }

    ctr = 0;
    for(int dex = 0; dex < strlen(town); dex++) {
        if (curr->data.town[dex] == toupper(town[dex])) {
            ctr++;
            key = 0;
        } else { return -1; }
    }
    if (key == 0 && ctr == strlen((town))) {
        key = 0;
    } else { return -1; }

    ctr = 0;
    for(int dex = 0; dex < strlen(race); dex++) {
        if (curr->data.race[dex] == toupper(race[dex])) {
            ctr++;
            key = 0;
        } else { return -1; }
    }
    if (key == 0 && ctr == strlen((race))) {
        return 0;
    } else { return -1; }
}
/**
 * This function prints the entire list of data. It invokes printRecord function
 * @param ptr is the top of the list
 */
void printList(NodePtr ptr) {
    // TODO 09: implement printList function
    if(ptr == NULL){
        puts("----------------List is empty----------------\n");
        return;
    }
    int count = 0;
    printHeader();
    while (ptr != NULL) {
        count++;
        printRecord(count, ptr); //function printRecord is invoked
        ptr = ptr->next;
    }
    puts("");
}
/**
 * It prints a single record starting with a serial number to keep a count of number of records printed
 * @param ctr serial number of the record
 * @param ptr top of the list
 */
void printRecord(int ctr, NodePtr ptr){
    // TODO 13: implement printRecord function
    printf("%6d %6d %18d %23d %20s %20s %20s\n", ctr, ptr->data.familySize, ptr->data.fullyVaccinated,
                        ptr->data.testedPositive, ptr->data.race, ptr->data.region, ptr->data.town);
}
/**
 * This function takes data items of a Household record and sets members of a locally declared Household instance and returns it
 * @param race
 * @param region
 * @param town
 * @param familySize
 * @param totPosCovid
 * @param fullyVac
 * @return a Household instance
 */
Household makeHousehold(char race[], char region[], char town[], int familySize, int totPosCovid, int fullyVac ){
    // TODO 14: implement makeHousehold function
    Household h;
    strcpy(h.race, race);
    strcpy(h.region, region);
    strcpy(h.town, town);
    h.familySize = familySize;
    h.testedPositive = totPosCovid;
    h.fullyVaccinated = fullyVac;
    return h;
}
/**
 * makeNode function allocates dynamic memory to create a node, populates with the data based on its argument of type Household
 * and returns the populated node
 * @param num
 * @return
 */
NodePtr makeNode(Household num){
    // TODO 15: implement makeNode function
    NodePtr ptr = malloc(sizeof(Node));
    if(ptr == NULL){
        puts("----------------Memory allocation failure----------------\n");
        return NULL;
    }
    strcpy(ptr->data.race, num.race);
    strcpy(ptr->data.region, num.region);
    strcpy(ptr->data.town, num.town);
    ptr->data.familySize = num.familySize;
    ptr->data.fullyVaccinated = num.fullyVaccinated;
    ptr->data.testedPositive = num.testedPositive;
    ptr->next = NULL;
    return ptr;
}
/**
 * Add node takes a Household instance, creates a node from it and then adds it to the front of the list that it takes as
 * its other argument
 * @param tom
 * @param num
 */
void addNode(NodePtr* top, Household num){
    // TODO 16: implement makeNode function
/*    NodePtr ptr = malloc(sizeof(Node));
    strcpy(ptr->data.race, num.race);
    strcpy(ptr->data.region, num.region);
    strcpy(ptr->data.town, num.town);
    ptr->data.familySize = num.familySize;
    ptr->data.fullyVaccinated = num.fullyVaccinated;
    ptr->data.testedPositive = num.testedPositive;*/

    NodePtr ptr = makeNode(num);
    ptr->next = *top;
    *top = ptr;
}
/**
 * THis function deletes a node from the list
 * @param tom takes top of the list as a reference
 */
void deleteNode(NodePtr* tom) {
    // TODO 17: implement deleteNode function
    NodePtr temp = *tom; // deleting a node
    *tom = (*tom)->next;
    free(temp);
    temp = NULL;
}
/**
 * This function deletes all nodes (records) of the list
 * @param tom
 */
void deleteAllNodes(NodePtr* tom){
    // TODO 18: implement deleteNode function
    NodePtr curr = *tom;
    NodePtr next = NULL;

    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *tom = NULL;
    puts("----------------All records deleted----------------\n");
}
/**
 * It write all the records to a file. As a sample, clients.txt file is saved in the data folder as part of the project folder
 * @param top
 * @param fileName
 */
void writeListToFile(NodePtr top, char fileName[]){
    // TODO 19: implement writeListToFile function
    int numOfRecords = 0;
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        puts("----------------File could not be opened----------------\n");
        return;
    }

    // File was opened

    // Process the file
    // write the list of records into the file
    while (top != NULL) {
        fprintf(file, "%s %s %s %d %d %d\n", top->data.race, top->data.region, top->data.town,
                top->data.familySize, top->data.testedPositive, top->data.fullyVaccinated);
        top = top->next;
        numOfRecords++;
    }
    // last line
    fprintf(file, "%s %s %s %d %d %d", "Last", "Record", "None", 0, 0, 0);
    // close the file on success
    fclose(file);
    printf("%d records and the sentinel record were written to %s successfully.\n", numOfRecords, fileName);
}
/**
 * It reads all records from a file
 * @param fileName
 */
void displayRecordsFromFile(char fileName[]){
    // TODO 20: implement displayRecordsFromFile function
    char race[RACE_NAME_LEN];
    char region[REGION_NAME_LEN];
    char town[TOWN_NAME_LEN];
    int familySize;
    int fullyVaccinated;
    int testedPositive;
    int count = 0;

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        puts("----------------File could not be opened----------------\n");
        return;
    }
    puts("----------------Printing records----------------\n");
    // File was opened
    printHeader();
    // Read the file until EOF
    while (fscanf(file, "%s %s %s %d %d %d", &race, &region, &town, &familySize,
                  &testedPositive, &fullyVaccinated) != EOF) {
        // Print a single record starting with a serial number to keep a count of number of records printed
        count++;
        printf("%6d %6d %18d %23d %20s %20s %20s\n", count, familySize, fullyVaccinated,
               testedPositive, race, region, town);
    }
    // close the file on success
    fclose(file);
}
void printHeader() {
    printf("%6s %6s %18s %23s %20s %20s %20s\n", "S.no", "Size", "Total Vaccinated",
           "Total tested positive", "Race", "Region", "Town");
    puts("");
}

