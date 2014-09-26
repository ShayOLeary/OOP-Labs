/*
Date: 24/4/14
Author: Seamus O Leary
Program to write to a create and manage an employee database with
a menu giving add, list, delete, compact and exit options to the user that will
be displayed constantly. Program will display appropriate error messages when 
they occur
*/
//importing necessary libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
//defining symbolic constants
#define FILENAMELENGTH 41
#define EMPLOYEE_MAX_NUMBER 100
//declaring function prototypes
void add();
void list();
void deleteRec();
void startFile();
void exitProgram(unsigned short);
void fileOpenError();
char filename[FILENAMELENGTH];
void menu();
void compact();
void sort();
//defining some global variables
FILE * fd,*ft;
int empty=0;
//declaring structures
struct database
{
    int index; 
    char empNum[6];
    char lastName[16];
    char firstName[16];
    char address[26];
    char departmentCode[10];
    char duration[2];
   } employee[EMPLOYEE_MAX_NUMBER];
struct headerRecord
{
    short numRecords;
    short delRecords;
}header;
    
main()
{   
    startFile();
    menu();
    getchar();
}

//void function accepting no parameters to compact records
//records with * in the first field (employee number) will be 
//removed by copying the active records into a temporary file 
//and then renaming that file that file to the original filename
void compact()
{
    //counting deleting records
    int deletedRec=0;
    int i,status;
    //opening file
    if((fd=fopen(filename,"rb"))==NULL)
    {
        printf("Error in opening file %s\n",filename);
        fileOpenError();
    }
    else if((ft=fopen("temp.dat","w+b"))!=NULL)
    {
        fread(&header,sizeof(header),1,fd);
        fwrite(&header,sizeof(header),1,ft);  
        fread(&employee,sizeof(employee),1,fd);
        //looping through records
        for(i=0;i<header.numRecords;i++)
        {
            //if there are any deleted records
            if(strcmp(employee[i].empNum,"* ")==0)
            {
                deletedRec++;
                //skip this iteration of the loop to ignore the deleted records
                continue;
            }
            fwrite(&employee[i],sizeof(employee[i]),1,ft);      
        }//ending outer loop
        //reducting number of records
        header.numRecords= header.numRecords-deletedRec;
        //going to start of file
        rewind(ft);
        fwrite(&header,sizeof(header),1,ft); 
        puts("Records have been compacted");
    }
    else
    {
        puts("Error is opening temp.dat!");
    }
    //closing files
    fclose(ft);
    fclose(fd);
    
    //creating variable to store result of removing the file
    status=remove(filename);
    if(status!=0)
    {
        puts("The file couldn't be removed!\n");
        //appropriate error message
        perror("Error");
    }
    //changing filename from temp to original filename
    rename("temp.dat",filename);
    //outputting list without deleted record
    list();  
}
 
//void function accepting no parameters to add a record
//function adds a new record to a file after reading in all of 
//the fields from standard input
//if the employee number is already taken, an error message
//will be outputted and the menu() will be called
void add()
{
    //creating string to hold employee number
    char uniq[6];
    int i;
    empty=0;
    if((fd=fopen(filename,"w+b"))==NULL)
    {
        printf("Error in opening file %s",filename);
        //outputting error message
        fileOpenError();
    }
    else
    {
        //go to start of file
        rewind(fd);
        //incremement the number of records
        header.numRecords++;
        fwrite(&header,sizeof(header),1,fd); 
        //setting the position to the start of the file
        fseek(fd,sizeof(header), SEEK_SET);
        fread(&employee,sizeof(employee),1,fd);
        puts("Enter next employee's empNum");
        gets(uniq);
        for(i=0;i<header.numRecords;i++)
        {
            //if the field is the same as an already inputted employee number
            if(strcmp(uniq,employee[i].empNum)==0)
            {
                //output error message
                printf("That employee number is already taken - ");
                "choose another option from the menu or add an ";
                "employee with a unique employee number.";
                header.numRecords--;
                menu();
            }//ending if statement
        }//ending for loop
        //getting employee field values
        puts("Enter next employee's First Name");
        gets(employee[header.numRecords-1].firstName);
        puts("Enter next employee's Last Name");
        gets(employee[header.numRecords-1].lastName);
        puts("Enter next employee's Address");
        gets(employee[header.numRecords-1].address);
        puts("Enter next employee's Department Code");
        gets(employee[header.numRecords-1].departmentCode);
        puts("Enter next employee's Duration");
        gets(employee[header.numRecords-1].duration);
        strcpy(employee[header.numRecords-1].empNum,uniq);
        fwrite(&employee,sizeof(employee),1,fd); 
    } 
    //close file
    fclose(fd);
}

//void function accepting no parameters to delete record
//function to fill the first byte of the field with an asterisk and 
//make the other fields blank of a chosen record
void deleteRec()
{   
    //creating string to hold employee number
    char del[6];
    int i;
    //creating boolean
    int notFound=0;
    //opening file
    if((fd=fopen(filename,"w+b"))==NULL)
    {
        printf("Error in opening file %s",filename);
        //outputting error message
        fileOpenError();
    }
    else
    {
        fwrite(&header,sizeof(header),1,fd);
        //setting the position to the start of the file
        fseek(fd,sizeof(header), SEEK_SET);
        fread(&employee,sizeof(employee),1,fd);
        puts("Enter the employee number of the employee to be deleted");
        gets(del);
        for(i=0;i<header.numRecords;i++)
        {
            //if the matching record has been found
            if(!strcmp(del,employee[i].empNum))
            {
                strcpy(employee[i].empNum,"* "); 
                strcpy(employee[i].lastName,"  ");
                strcpy(employee[i].firstName,"  ");
                strcpy(employee[i].address,"  "); 
                strcpy(employee[i].departmentCode,"  "); 
                strcpy(employee[i].duration,"  "); 
                header.delRecords++;
            }
            else notFound++;
        }//ending loop
        //if no records have been found
        if(notFound==header.numRecords)
        {
            puts("Employee record could not be found");
        }
        fwrite(&employee,sizeof(employee),1,fd);
    }
    //close file
    fclose(fd);
}

//void function accepting no parameters to list record
//list records by looping through them and outputting error 
//message if record can't be found
void list()
{
    int i;
    if(!empty)
    {
        if((fd=fopen(filename,"rb"))==NULL)
        {
            printf("Error in opening file %s",filename);
            //outputtign appropriate error message
            fileOpenError();
        }
        else
        {
            //set position to the start of the file
            fseek(fd,sizeof(header), SEEK_SET);
            fread(&employee,sizeof(employee),1,fd);
            //output database
            printf("\n\n== Employee Data ==\n\n");  
            for (i=0;i<header.numRecords;i++)
            {
                printf("Index: %d | ", i+1);
                printf("EmployeeNumber: %s | ",employee[i].empNum);
                printf("LastName: %s | ",employee[i].lastName);
                printf("FirstName: %s | \n",employee[i].firstName);
                printf("Address: %s | ",employee[i].address);
                printf("DepartmentCode: %s | ",employee[i].departmentCode);
                printf("Duration: %s | \n\n",employee[i].duration);
            }
            printf("Header Data:\nNumber of Records=%d\n",header.numRecords);
            printf("Number of Deleted Records=%d\n",header.delRecords);
        }  
    //close file
    fclose(fd);
    }
    else
    {
        puts("Empty File");
    }
}

//void function accepting no parameters to start a file
//function opens file and outputs appropriate error message
void startFile()
{
    int i;
    puts("Please enter the name of the file");
    gets(filename);
    if((fd=fopen(filename,"rb"))==NULL)
    { 
        printf("The file %s doesn't exist so it will be created for you\n",filename);
        //setting global boolean to signify that the file is empty
        empty=1;
    }
    else
    {
        fread(&header,sizeof(header),1,fd);
        //set position to start of file
        fseek(fd,sizeof(header), SEEK_SET);
        fread(&employee,sizeof(employee),1,fd);
        
        //output header record
        printf("Header Data:\nNumber of Records=%d\n",header.numRecords);
        header.delRecords=0;
        for(i=0;i<header.numRecords;i++)
        {
            //increment number of records if the records passed through in the for loop are active
            if(!strcmp(employee[i].empNum,"* "))
            {
                header.delRecords++;
            }
        }
        printf("Number of Deleted Records=%d\n",header.delRecords);
    }
}

//void function accepting no parameters to display a never ending menu
void menu()
{
    //forever loop to allow the user play the game as long as they want
    while(1)
    {
        char menuChoice;
        
        //outputting main interface
        puts("********************************************************");
        printf("\t\t*** MAIN MENU ***\n\n");
        printf("Your Options");
        printf("\n_____________\n\n");
        printf("1: Add Employee\n");
        printf("2: Delete Employee\n");
        printf("3: List Employees\n");
        printf("4: Compact Records\n");
        printf("5: Exit Program\n\n");
        puts("********************************************************");
       
        scanf("%c",&menuChoice);
        flushall();
       
        //applying choice to different function calls
        switch(menuChoice)
        {
            case '1':
            {
                add();
                break;
            }
            case '2':
            {
                deleteRec();
                break;
            }
            case '3':
            {
                list();
                break;
            }
            case '4':
            { 
                compact();
                break;
            }
            case '5':
            {
                exitProgram(1000);
                break;
            }
            default:
            {//if no appropriate options have been chosen
                puts("Choose a valid menu option please!");
            }
        } 
    } 
}

//void function accepting no parameters to output error message
//this function handles errors and informs the user that an error has
//occured while opening a file and allows them to exit the program or try
//to open a file again
void fileOpenError()
{
    char input,enter1;
    puts("\nError in opening file.\nYou can try again by pressing 't' or quit the program by pressing 'q'\n");
    scanf("%c%c",&input,&enter1);
    flushall();
    //if the second character is enter
    if(enter1=='\n')
    {
        switch(input)
        {
            case 'q':
            {//exit the program if q is entered
                exitProgram(1000);
                break;
            }
            case 't':
            {
                startFile();
                break;
            }
            default:
            {//no valid option chosen
                puts("That was not a valid choice");
            }
        }
    }
    else
    {//no valid option chosen ending in a newline character
        puts("That was not a valid choice");
    }
}

//void function accepting unsigned integer to exit the program
//this function causes the graceful termination of the program
//by taking in a time in milliseconds to be counted down to delay the
//program from terminating to allow the user sufficient time to read 
//the information message
void exitProgram(unsigned short time)
{
    printf("The program will now exit.\nThank you for participating");
    //system call
    Sleep(time);
    //exiting program gracefully
    exit(0);
}

