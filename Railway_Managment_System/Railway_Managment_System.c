#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "conio2.h"
#include "Railway_Managment_System.h"


int enterChoice()
{
    int choice,i;
    gotoxy(21,2);
    textcolor(YELLOW);
    printf("........Railway Reservation System.........\n\n");
    textcolor(LIGHTBLUE);
    for(i=1;i<=80;i++)
        printf("~");
    gotoxy(31,5);
    textcolor(LIGHTGREEN);
    printf("Select An Option\n");
    textcolor(LIGHTBLUE);
    for(i=1;i<=80;i++)
        printf("~");
    gotoxy(31,9);
    textcolor(LIGHTBLUE);
    printf("1.View Train");
    gotoxy(31,10);
    printf("2.Book Train");
    gotoxy(31,11);
    printf("3.View Ticket");
    gotoxy(31,12);
    printf("4.Search Ticket No");
    gotoxy(31,13);
    printf("5.View All Bookings");
    gotoxy(31,14);
    printf("6.View Train Bookings");
    gotoxy(31,15);
    printf("7.Cancel Ticket");
    gotoxy(31,16);
    printf("8.Cancel Train");
    gotoxy(31,17);
    printf("9.!Quit");
    gotoxy(30,20);
    textcolor(LIGHTCYAN);
    printf("Enter Your Choice:");
    textcolor(WHITE);
    scanf("%d",&choice);
    fflush(stdin);
    return choice;
}




void add_Train()
{
    FILE *fp=fopen("D:\\C2020 project_batch\\Railway_Managment_System\\alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]={
            {"123","BPL","GWA",2100,1500},
            {"546","BPL","DEL",3500,2240},
            {"345","HBJ","AGR",1560,1135},
            {"896","HBJ","MUM",4500,3360},
            };
        fp=fopen("D:\\C2020 project_batch\\Railway_Managment_System\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File saved successfully\n");
		fclose(fp);
    }
    else
    {
        printf("File already present\n");
        fclose(fp);
    }

}




void view_Train()
{
    FILE *fp;
    Train Trains;
    int i;
    clrscr();
    gotoxy(21,2);
    textcolor(YELLOW);
    printf("........Railway Reservation System.........");
    gotoxy(1,5);
    textcolor(LIGHTBLUE);
    for(i=1;i<=80;i++)
        printf("~");
    textcolor(LIGHTGREEN);
    gotoxy(33,6);
    printf("All Train Details");
    gotoxy(1,7);
    textcolor(LIGHTBLUE);
    for(i=1;i<=80;i++)
        printf("~");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    printf("Train_No\tFrom\tTo\tFirst_AC_Fair\t\tSecond_AC_Fair");
    gotoxy(1,10);
    textcolor(LIGHTBLUE);
    for(i=1;i<=80;i++)
        printf("~");
    fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\alltrains.dat","rb");
    textcolor(LIGHTGREEN);
    while(fread(&Trains,sizeof(struct Train),1,fp)==1)
    {
        printf("%s\t\t%s\t%s\t%d\t\t\t%d",Trains.train_no,Trains.from,Trains.to,Trains.fac_fare,Trains.sac_fare);
        printf("\n");
    }
    fclose(fp);
    gotoxy(1,20);
    textcolor(LIGHTCYAN);
    printf("Press any key to go to the main screen......");
    getch();
}




void book_Train()
{
    int value;
    Passenger *ps = get_Passenger_Details();
    if(ps != NULL)
    {
        value = book_ticket(*ps);
        if(value == -1)
        {
            clrscr();
            gotoxy(10,16);
            textcolor(YELLOW);
            printf("BOOKING FAILDED..........");
            textcolor(LIGHTMAGENTA);
            gotoxy(12,18);
            printf("Press any key to continue..........");
            getch();
            return;
        }
        gotoxy(1,18);
        textcolor(YELLOW);
        printf("YOUR TICKET NUMBER                      :- %d",value);
        gotoxy(30,22);
        textcolor(LIGHTMAGENTA);
        printf("BOOKING SUCCESSFULLY DONE");
        getch();
    }
}




Passenger * get_Passenger_Details()
{
    clrscr();
    static Passenger pd;
    Overview("Passenger Details");

    if(setPassengerName(&pd))
        return NULL;
    if(setPassengerGender(&pd))
        return NULL;
    if(setPassengerTrainNo(&pd))
        return NULL;
    if(setPassengerTrainClass(&pd))
        return NULL;
    if(setPassengerAddress(&pd))
        return NULL;
    if(setPassengerAge(&pd))
        return NULL;
    if(setPassengerMobileNo(&pd))
        return NULL;
    gotoxy(25,25);
    textcolor(LIGHTCYAN);
    printf("REGISTERATION COMPLETED SUCCESSFULLY...");
    gotoxy(30,27);
    textcolor(LIGHTCYAN);
    printf("Press Any Key To Continue....");
    getch();
    return &pd;
}




int book_ticket(Passenger ps)
{
    int seats;
    int last_ticket;
    seats = get_booked_ticket_count(ps.train_no,ps.P_Class);
    if(seats == 2)
    {
        clrscr();
        gotoxy(10,16);
        textcolor(YELLOW);
        printf("All seats full in train no %s in %c class",ps.train_no,ps.P_Class);
        textcolor(LIGHTMAGENTA);
        gotoxy(12,18);
        printf("Press any key to continue..........");
        getch();
        return -1;
    }
    last_ticket = last_ticket_no();
    last_ticket++;
    ps.ticket_no = last_ticket;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","ab");
    if(fwrite(&ps,sizeof(Passenger),1,fp) != 1)
    {
        clrscr();
        gotoxy(10,16);
        textcolor(YELLOW);
        printf("Sorry some problem occured while booking the ticket....");
        textcolor(LIGHTMAGENTA);
        gotoxy(15,18);
        printf("Press any key to continue..........");
        getch();
    }
    if(fclose(fp) == EOF)
        printf("file closed successfuly...");
    else
        printf("not closed dullcj");
    getch();
    return last_ticket;
}




int get_booked_ticket_count(char *trainNo,char Class)
{
    int count = 0;
    Passenger ps;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        return 0;
    }
    while(fread(&ps,sizeof(struct Passenger),1,fp)==1)
    {
        if(strcmp(ps.train_no,trainNo)==0 && ps.P_Class == Class)
        {
            count++;
        }
    }
    fclose(fp);
    return count;
}




int last_ticket_no()
{
    Passenger ps;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        return 0;
    }

    fseek(fp,-1L*(sizeof(Passenger)),SEEK_END);
    fread(&ps,sizeof(struct Passenger),1,fp);
    fclose(fp);
    getch();
    return ps.ticket_no;
}



void view_ticket()
{
    Passenger pr;
    int found = 0;
    int ticket_no;
    Overview("PASSENGER INFORMATION");
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        gotoxy(33,21);
        textcolor(LIGHTMAGENTA);
        printf("No booking yet");
        gotoxy(20,23);
        printf("Press any key to go back to the main screen");
        getch();
        return;
    }
    ticket_no=getPassengerTicketNO();
    if(ticket_no == 0)
    {
        gotoxy(30,21);
        textcolor(LIGHTMAGENTA);
        printf("Cancelling the process.....");
        gotoxy(20,23);
        printf("Press any key to go back to the main screen");
        getch();
        return;
    }
    gotoxy(1,11);
    textcolor(YELLOW);
    printf("TICKET NO   NAME\tGENDER   TRAIN NO   CLASS   ADDRRESS\tAGE   MOBILE NO.");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    textcolor(GREEN);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticket_no==ticket_no)
        {
//            printf("\nNAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS: %c\nADDRRESS: %s\nAGE: %d\nMOBILE NO: %s\nTICKET NO: %d\n",pr.P_Name,pr.Gender,pr.train_no,pr.P_Class,pr.Address,pr.Age,pr.mob_no,pr.ticket_no);
            printf("%d\t    %s\t\t%c        %s\t    %c\t    %s\t\t%d    %s\n",pr.ticket_no,pr.P_Name,pr.Gender,pr.train_no,pr.P_Class,pr.Address,pr.Age,pr.mob_no);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\n\nNo details of the ticket found");
    }
    fclose(fp);
    textcolor(LIGHTMAGENTA);
    gotoxy(20,23);
    printf("Press any key to go back to the main screen");
    getch();
}




void search_Ticket_Number()
{
    int * Ticket_no;
    Passenger ps;
    Overview("SEARCH TICKET NUMBER");
    if(!setPassengerMobileNo(&ps))
    {
        Ticket_no = get_Ticket_No(ps.mob_no);
        view_all_tickets(ps.mob_no,Ticket_no);
    }
    getch();
}




int * get_Ticket_No(char *mobno)
{
    Passenger pr;
    int count = 0;
    int i = 0;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        gotoxy(33,21);
        textcolor(LIGHTMAGENTA);
        printf("NO BOOKING DONE YET");
        gotoxy(20,23);
        printf("PRESS ANY KEY TO BACK THE MAIN SCREEN...");
        getch();
        return NULL;
    }
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,mobno) == 0)
        {
            count++;
        }
    }
    if(count == 0)
        return NULL;
    int *p = (int *)malloc(sizeof(int)*(count+1));
    rewind(fp);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,mobno) == 0)
        {
            *(p+i) = pr.ticket_no;
            i++;
        }
    }
    *(p+i) = -1;
    return p;
}




void view_all_tickets(char *mobno,int *p)
{
    int i;
    if(p == NULL)
    {
        gotoxy(33,21);
        textcolor(LIGHTMAGENTA);
        printf("NO TICKETS BOOKED AGAINST THE MOBILE NUMBER %s",mobno);
        gotoxy(20,23);
        printf("PRESS ANY KEY TO BACK THE MAIN SCREEN...");
        return;
    }
    gotoxy(1,11);
    textcolor(BLUE);
    printf("Following are tickets booked for mobile no  %s\n",mobno);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    textcolor(YELLOW);
    for(i=0;*(p+i)!=-1;i++)
        printf("\n%d",*(p+i));
    textcolor(WHITE);
    printf("\n\nPRESS ANY KEY TO BACK THE MAIN SCREEN...");
    textcolor(YELLOW);
    getch();
}




void view_all_bookings()
{
    Overview("VIEW ALL BOOKINGS");
    Passenger pr;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        clrscr();
        gotoxy(10,16);
        textcolor(YELLOW);
        printf("NO BOOKINGS DONE YET");
        textcolor(LIGHTMAGENTA);
        gotoxy(12,18);
        printf("Press any key to continue..........");
        getch();
        return;
    }
    textcolor(YELLOW);
    printf("\nTICKET NO   NAME\tGENDER   TRAIN NO   CLASS   ADDRRESS\tAGE   MOBILE NO.");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    textcolor(GREEN);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
//        printf("\nNAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS: %c\nADDRRESS: %s\nAGE: %d\nMOBILE NO: %s\nTICKET NO: %d\n",pr.P_Name,pr.Gender,pr.train_no,pr.P_Class,pr.Address,pr.Age,pr.mob_no,pr.ticket_no);
//        printf("-------------------------------------------------------------------------------\n");
        printf("%d\t    %s\t\t%c        %s\t    %c\t    %s\t\t%d    %s\n",pr.ticket_no,pr.P_Name,pr.Gender,pr.train_no,pr.P_Class,pr.Address,pr.Age,pr.mob_no);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
    fclose(fp);
}




void view_Train_Booking()
{
    Passenger ps;
    Overview("VIEW TRAIN BOOKING");
    if(!setPassengerTrainNo(&ps))
    {
        view_Bookings(ps.train_no);
    }
}



void view_Bookings(char * trainno)
{
    Passenger pr;
    int found = 0;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        clrscr();
        gotoxy(10,16);
        textcolor(YELLOW);
        printf("NO BOOKINGS DONE YET");
        textcolor(LIGHTMAGENTA);
        gotoxy(12,18);
        printf("Press any key to continue..........");
        getch();
        return;
    }
    gotoxy(1,10);
    textcolor(YELLOW);
    printf("TICKET NO   NAME\tGENDER   TRAIN NO   CLASS   ADDRRESS\tAGE   MOBILE NO.");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    textcolor(GREEN);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,trainno)==0)
        {
//            printf("\nNAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS: %c\nADDRRESS: %s\nAGE: %d\nMOBILE NO: %s\nTICKET NO: %d\n",pr.P_Name,pr.Gender,pr.train_no,pr.P_Class,pr.Address,pr.Age,pr.mob_no,pr.ticket_no);
//            printf("-------------------------------------------------------------------------------\n");
            printf("%d\t    %s\t\t%c        %s\t    %c\t    %s\t\t%d    %s\n",pr.ticket_no,pr.P_Name,pr.Gender,pr.train_no,pr.P_Class,pr.Address,pr.Age,pr.mob_no);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            found = 1;
        }
    }
    if(!found)
    {
        printf("No details of the train %s found",trainno);
    }
    fclose(fp);
}




void cancel_Ticket()
{
    Overview("CANCEL TICKET");
    int ticket_No = getPassengerTicketNO();
    if(ticket_No != 0)
    {
        int value = cancelling_Ticket(ticket_No);
        if(value == 0)
        {
            printf("Sorry! No tickets booked agains the ticket number %d",ticket_No);
        }
        else
        {
            printf("Ticket no %d successfully cancelled",ticket_No);
        }
    }
    textcolor(WHITE);
    printf("\nPress any key to go back to the main screen..........");
}




int cancelling_Ticket(int ticketno)
{
    Passenger pr;
    int found = 0;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        printf("NO BOOKINGS DONE YET");
        return -1;
    }
    FILE *fp1 = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\temp.dat","wb");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticket_no != ticketno)
        {
            fwrite(&pr,sizeof(pr),1,fp1);
        }
        else
            found = 1;
    }
    fclose(fp);
    fclose(fp1);
    if(found == 0)
    {
        remove("D:\\C2020 project_batch\\Railway_Managment_System\\temp.dat");
    }
    else if(found == 1)
    {
        remove("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat");
        rename("D:\\C2020 project_batch\\Railway_Managment_System\\temp.dat","D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat");
    }
    return found;
}




void cancel_Train()
{
    Passenger ps;
    int result;
    Overview("CANCEL TRAIN");
    if(!setPassengerTrainNo(&ps))
    {
        result = cancellling_Train(ps.train_no);
        if(!result)
            printf("successfully deleted..........");
    }
}




int cancellling_Train(char * train_no)
{
    Passenger pr;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat","rb");
    if(fp == NULL)
    {
        printf("NO BOOKINGS DONE YET");
        return -1;
    }
    FILE *fp1 = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\temp.dat","wb");
    FILE *fp2 = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\temp1.dat","wb");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no) != 0)
        {
            fwrite(&pr,sizeof(pr),1,fp1);
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    remove("D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat");
    rename("D:\\C2020 project_batch\\Railway_Managment_System\\temp.dat","D:\\C2020 project_batch\\Railway_Managment_System\\bookingTrainDetails.dat");
    fp2 = fopen("D:\\C2020 project_batch\\Railway_Managment_System\\temp1.dat","rb");
    while(fread(&pr,sizeof(pr),1,fp2)==1)
    {
        printf("\nNAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS: %c\nADDRRESS: %s\nAGE: %d\nMOBILE NO: %s\nTICKET NO: %d\n",pr.P_Name,pr.Gender,pr.train_no,pr.P_Class,pr.Address,pr.Age,pr.mob_no,pr.ticket_no);
        printf("-------------------------------------------------------------------------------\n");

    }
    printf("\n Following are the passenger with the train no <%s> found and will be deleted....",train_no);
    fclose(fp2);
    remove("D:\\C2020 project_batch\\Railway_Managment_System\\temp1.dat");
    return 0;
}




void Overview(char arr[])
{
    int i;
    gotoxy(21,2);
    textcolor(YELLOW);
    printf("........Railway Reservation System.........");
    gotoxy(1,5);
    textcolor(LIGHTBLUE);
    for(i=1;i<=80;i++)
        printf("~");
    textcolor(LIGHTGREEN);
    gotoxy(33,6);
    printf("%s",arr);
    gotoxy(1,7);
    textcolor(LIGHTBLUE);
    for(i=1;i<=80;i++)
        printf("~");
    gotoxy(65,8);
    textcolor(DARKGRAY);
    printf("PRESS 0 TO EXIT\n");
}




void defaultFunction()
{
    gotoxy(30,25);
    textcolor(RED);
    printf("You Entered ! Wrong Choice");
    gotoxy(30,26);
    textcolor(BLUE);
    printf("Press Any Key To Continue....");
}




void final_Code()
{
    gotoxy(27,16);
    textcolor(GREEN);
    printf("THANKYOU FOR USING THE APP....");
    gotoxy(1,26);
    textcolor(BLACK);
    exit(0);
}






/*
 *                                  VALIDATION FUCTIONS
 *
 */

int isGenderValid(char gen)
{
    if(gen != 'M' && gen != 'F')
        return 1;
    else
        return 0;
}




int isTrainNoValid(char Train_no[])
{
    Train tr;
    FILE *fp = fopen("D:\\C2020 project_batch\\Railway_System\\alltrains.dat","rb");
    while(fread(&tr,sizeof(struct Train),1,fp)==1)
    {
        if(strcmp(tr.train_no,Train_no)==0)
        {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}




int isClassValid(char tclass)
{
    if(tclass != 'S' && tclass != 'F')
        return 1;
    else
        return 0;
}





int isAgeValid(int age)
{
    if(age >0)
        return 0;
    else
        return 1;
}





int isMobileNoValid(char mobNo[])
{
    int mobno;
    char arr[10];
    int i;
    sscanf(mobNo,"%d",&mobno);
    sprintf(arr,"%d",mobno);
    for(i = 0;arr[i]!='\0';i++);
    if(i == 10)
    {
        return 0;
    }
    return 1;
}





/*
 *                                  SETTER OR GETTER FUCTIONS
 *
 */



int setPassengerName(Passenger *ps)
{
    char *pos;
    gotoxy(1,11);
    textcolor(LIGHTCYAN);
    printf("Enter Passenger Name                    :- ");
    textcolor(WHITE);
    fflush(stdin);
    fgets(ps->P_Name,30,stdin);
    pos=strchr(ps->P_Name,'\n');
    *pos='\0';
    printf("%s",ps->P_Name);
    if(strcmp(ps->P_Name,"0")==0)
    {
        gotoxy(30,25);
        textcolor(RED);
        printf("Cancelling The Registeration....");
        gotoxy(30,26);
        textcolor(LIGHTCYAN);
        printf("Press Any Key To Continue....");
        getch();
        return 1;
    }
    return 0;
}



int setPassengerGender(Passenger *ps)
{
    gotoxy(1,12);
    textcolor(LIGHTCYAN);
    printf("Enter Gender(M/F)                       :- ");
    textcolor(WHITE);
    do
    {
        scanf("%c",&(ps->Gender));
        fflush(stdin);
        if(ps->Gender == '0')
        {
            gotoxy(30,25);
            textcolor(RED);
            printf("Cancelling The Registeration....");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            return 1;
        }
        if(isGenderValid(ps->Gender))
        {
            gotoxy(44,12);
            printf("\t\t\t\t\t\t\t");
            gotoxy(30,25);
            textcolor(RED);
            printf("OOPS ! INVALID GENDER");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            gotoxy(30,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(30,26);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(44,12);
            textcolor(WHITE);
        }
    }while(isGenderValid(ps->Gender) != 0);
    return 0;
}



int setPassengerTrainNo(Passenger *ps)
{
    char *pos;
    gotoxy(1,13);
    textcolor(LIGHTCYAN);
    printf("Enter Train No.                         :- ");

    do
    {
        textcolor(WHITE);
        fflush(stdin);
        fgets(ps->train_no,10,stdin);
        pos=strchr(ps->train_no,'\n');
        *pos='\0';
        fflush(stdin);
        if(strcmp(ps->train_no,"0") == 0)
        {
            gotoxy(30,25);
            textcolor(RED);
            printf("Cancelling The Registeration....");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            return 1;
        }
        if(isTrainNoValid(ps->train_no))
        {
            gotoxy(44,13);
            printf("\t\t\t\t\t\t\t");
            gotoxy(30,25);
            textcolor(RED);
            printf("OOPS ! INVALID TRAIN NO.");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            gotoxy(30,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(30,26);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(44,13);
        }
    }while(isTrainNoValid(ps->train_no));
    return 0;
}



int setPassengerTrainClass(Passenger *ps)
{
    gotoxy(1,14);
    textcolor(LIGHTCYAN);
    printf("Travlling class(First AC-F,Second AC-S) :- ");

    do
    {
        textcolor(WHITE);
        scanf("%c",&(ps->P_Class));
        fflush(stdin);
        if(ps->P_Class == '0')
        {
            gotoxy(30,25);
            textcolor(RED);
            printf("Cancelling The Registeration....");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            return 1;
        }
        if(isClassValid(ps->P_Class))
        {
            gotoxy(44,14);
            printf("\t\t\t\t\t\t\t");
            gotoxy(30,25);
            textcolor(RED);
            printf("OOPS ! INVALID CLASS SECTION");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            gotoxy(30,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(30,26);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(44,14);
        }
    }while(isClassValid(ps->P_Class));
    return 0;
}



int setPassengerAddress(Passenger *ps)
{
    char *pos;
    gotoxy(1,15);
    textcolor(LIGHTCYAN);
    printf("Enter Address                           :- ");
    textcolor(WHITE);
    fgets(ps->Address,30,stdin);
    pos=strchr(ps->Address,'\n');
    *pos='\0';
    fflush(stdin);
    if(strcmp(ps->Address,"0") == 0)
    {
        gotoxy(30,25);
        textcolor(RED);
        printf("Cancelling The Registeration....");
        gotoxy(30,26);
        textcolor(LIGHTCYAN);
        printf("Press Any Key To Continue....");
        getch();
        return 1;
    }
    return 0;
}




int setPassengerAge(Passenger *ps)
{
    gotoxy(1,16);
    textcolor(LIGHTCYAN);
    printf("Enter Age                               :- ");

    do
    {
        textcolor(WHITE);
        scanf("%d",&ps->Age);
        fflush(stdin);
        if(ps->Age== 0)
        {
            gotoxy(30,25);
            textcolor(RED);
            printf("Cancelling The Registeration....");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            return 1;
        }
        if(isAgeValid(ps->Age))
        {
            gotoxy(44,16);
            printf("\t\t\t\t\t\t\t");
            gotoxy(30,25);
            textcolor(RED);
            printf("OOPS ! INVALID AGE");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            gotoxy(30,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(30,26);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(44,16);
            textcolor(WHITE);
        }
    }while(isAgeValid(ps->Age));
    return 0;
}




int setPassengerMobileNo(Passenger *ps)
{
    char *pos;
    gotoxy(1,17);
    textcolor(LIGHTCYAN);
    printf("Enter Phone Number                      :- ");
    do
    {
        textcolor(WHITE);
        fflush(stdin);
        fgets(ps->mob_no,12,stdin);
        pos=strchr(ps->mob_no,'\n');
        *pos='\0';
        fflush(stdin);
        if(strcmp(ps->mob_no,"0")==0)
        {
            gotoxy(30,25);
            textcolor(RED);
            printf("Cancelling The Registeration....");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            return 1;
        }
        if(isMobileNoValid(ps->mob_no))
        {
            gotoxy(44,17);
            printf("\t\t\t\t\t\t\t");
            gotoxy(30,25);
            textcolor(RED);
            printf("OOPS ! INVALID MOBILE NUMBER...");
            gotoxy(30,26);
            textcolor(LIGHTCYAN);
            printf("Press Any Key To Continue....");
            getch();
            gotoxy(30,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(30,26);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(44,17);
        }
    }while(isMobileNoValid(ps->mob_no));
    return 0;
}



int getPassengerTicketNO()
{
    int ticket_no;
    do
    {
        printf("\n\nEnter a valid ticket no. : ");
        scanf("%d",&ticket_no);
        fflush(stdin);
        if(ticket_no == 0)
            return 0;
    }while(ticket_no <0);
    return ticket_no;
}
