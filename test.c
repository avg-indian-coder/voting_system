#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//admin mode - set number of voters and the voting options. Allow access with a password you can generate
//voting mode - allow users to vote, then clear the terminal, store info

typedef struct Voter
{
    char name[100];
    int vote;
}voter;

typedef struct Candidate
{
    char name[100];
    int number;
}candidate;

char password[20];
int num_voters,num_candidates;
int admin_f=0,voter_f=0;
candidate *candidates;
voter *voters;

void AdminMode()
{
    int fail=0;
    char ch;
    system("cls");
    if(admin_f)
    {
        char ps1[20];
        printf("\nEntering admin mode...\nEnter password:");
        scanf("%s",ps1);
        if(strcmp(ps1,password))
        {
            printf("incorrect password! try again\n");
            fflush(stdin);
            printf("Press any key to continue \n");
            scanf("%c");
            fail=1;
        }
    }
    else
    {
        printf("\nEntering admin mode...\nEnter password:");
        scanf("%s",password);
    }
    if(fail==0)
    {
        printf("\nEnter number of voters: ");
        scanf("%d",&num_voters);
        printf("Enter number of candidates: ");
        scanf("%d",&num_candidates);

        voters=(voter*)malloc(num_voters*sizeof(voter));
        candidates=(candidate*)malloc(num_candidates*sizeof(candidate));

        printf("\nEnter voting candidates:\n");
        for(int i=1;i<=num_candidates;i++)
        {

            printf("%d. ",i);
            fflush(stdin);
            scanf("%[^\n]s",candidates[i-1].name);
            candidates[i-1].number=0;
            printf("\n");
        }
        printf("The details are:\n");
        printf("The number of voters are: %d \n",num_voters);
        printf("Candidates are: \n");
        for(int i=1;i<=num_candidates;i++)
        {
            printf("%d. %s\n",i,candidates[i-1].name);
        }
        printf("Press any key to continue\n");
        fflush(stdin);
        scanf("%c",&ch);
        admin_f=1;
    }
    system("cls");
}

void VotingMode()
{
    char ch;
    system("cls");
    printf("\n");
    for(int no=0;no<num_voters;no++)
    {
        system("cls");
        printf("\nEnter your name: ",voters[no].name);
        scanf("%s",voters[no].name);
        printf("Enter your vote out of the following candidates:\n");
        for(int i=0;i<num_candidates;i++)
        {
            printf("%d. %s\n",i+1,candidates[i].name);
        }
        int tm;
        while(1)
        {
            while(1){
                printf("\nYour vote here: ");
                scanf("%d",&tm);
                if (tm>0 && tm<=num_candidates) break;
                else printf("Please enter a valid input\n");
            }

            while(1){
                printf("Press Y to confirm vote, or n to redo vote: ");
                fflush(stdin);
                scanf("%c",&ch);
                ch=toupper(ch);
                if(ch=='Y' || ch=='N') break;
                else printf("\nPlease enter valid inputs\n");
            }
            if(ch=='Y')
            {
                voters[no].vote=tm;
                candidates[voters[no].vote-1].number++;
                break;
            }
        }
    }
    voter_f=1;
    system("cls");
}

void DisplayResults()
{
    char ch;
    system("cls");
    for(int i=0;i<num_candidates;i++)
    {
        printf("\n%d. %s - %d votes",i+1,candidates[i].name,candidates[i].number);
    }
    printf("\n");
    fflush(stdin);
    printf("Press any key to continue \n");
    scanf("%c",&ch);
    system("cls");
}

void DV()
{
    char cm;
    printf("Voter->Vote\n\n");
    for(int i=0;i<num_voters;i++)
    {
        printf("%s ->",voters[i].name);
        printf("%s\n",candidates[voters[i].vote-1].name);
    }
    fflush(stdin);
    printf("Press Y to save results in file or press any other key to continue:");
    scanf("%c",&cm);
    cm=toupper(cm);
    if(cm=='Y'){
        FILE *fptr;
        fptr = fopen("voting.txt","w");
        char rxy[]="Voter->Vote";
        int inm=0;
        while(rxy[inm]!='\0')
        {
            fputc(rxy[inm],fptr);
            inm++;
        }
        fputc('\n',fptr);
        fputc('\n',fptr);
        for(int i=0;i<num_voters;i++)
        {
            char x[100];
            strcpy(x,voters[i].name);
            char y[100];
            strcpy(y,candidates[voters[i].vote-1].name);
            char m[]="->";
            strcat(x,m);
            strcat(x,y);
            int jm=0;
            while(x[jm]!='\0')
            {
                fputc(x[jm],fptr);
                jm++;
            }
            fputc('\n',fptr);
        }

        fclose(fptr);
    }
}

void main()
{
    system("cls");
    while(1)
    {
        int choice;
        printf("\n1.Admin mode\n2.Voting mode\n3.Results display\n4.Detailed View\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if(choice==5) break;
        switch(choice)
        {
            case 1:
            AdminMode();
            break;
            case 2:
            if(admin_f) VotingMode();
            else
            {
                printf("Admin not initialized!");
                fflush(stdin);
                printf("Press any key to continue ");
                scanf("%c");
            }
            break;
            case 3:
            if(admin_f && voter_f) DisplayResults();
            else
            {
                printf("Admin or voting not done!");
                fflush(stdin);
                printf("Press any key to continue ");
                scanf("%c");
            }
            break;
            case 4:
            if(admin_f && voter_f) DV();
            else
            {
                printf("Admin or voting not done!");
                fflush(stdin);
                printf("Press any key to continue ");
                scanf("%c");
            }
            break;
            default:
            printf("error! %d",choice);
        }
    }
}
