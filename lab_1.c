/*
Name: Mukesh Kastala
ID: 40646351
ICS 53
LAB 1
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

const char result[100][80];
int _index = 0;

void readToFile(char s[]){
    FILE *ifp;
    ifp = fopen(s, "r");

    if (ifp == NULL)
        printf("%s\n", "Incorrect input name");
    else{
        char element[80];

        while(fgets(element, 80, (FILE*)ifp)){
            if (element[strlen(element) - 1] == '\n')
                element[strlen(element) - 1] = '\0';
            strcpy(result[_index], element);
            _index++;
        }
        fclose(ifp);
    }
}

void writeToFile(char s[]){
    if (_index == 0)
        printf("%s\n", "No records are present");
    else{
        FILE *ofp;
        ofp = fopen(s, "w+");

        for (int i = 0 ; i < _index; i++)
            fprintf(ofp, "%s\n", result[i]);

        fclose(ofp);
    }
}

void print_(){
    if (_index == 0)
        printf("%s\n", "No records are present");
    else{
        for (int i = 0 ; i < _index; i++)
            printf("%d\t%s\n", (i+1), result[i]);
    }

}

void delete_(char c[]){
    if (_index == 0)
        printf("%s\n", "No file has yet been read from");
    else{
        int num = atoi(c);
        if (num > _index || num <= 0)
            printf("%s\n", "No record corresponds with entered integer");
        else{
            for(; num <= _index; ++num)
                strcpy(result[num - 1], result[num]);
            --_index;
        }
    }
}

int main(){

    char input[50];
    char part1[25];
    char part2[25];

    while(true){
        printf("Enter in a command: ");
        gets(input);

        sscanf(input, "%s%s", part1, part2);

        if (strcmp(part1,"read") == 0)
            readToFile(part2);
        else if(strcmp(part1,"write") == 0)
            writeToFile(part2);
        else if(strcmp(part1,"print") == 0)
            print_();
        else if(strcmp(part1,"delete") == 0)
            delete_(part2);
        else if(strcmp(part1,"quit") == 0)
            break;

        strcpy(part1, "");
        strcpy(part2, "");
    }
    return 0;
}

