#include <stdio.h>
#include "conio2.h"
#include <stdlib.h>
#include "Railway_Managment_System.h"

int main()
{
    int choice;
    add_Train();
    while(1)
    {
        clrscr();
        choice = enterChoice();
        switch(choice)
        {
        case 1:
            view_Train();
            break;
        case 2:
            clrscr();
            book_Train();
            break;
        case 3:
            clrscr();
            view_ticket();
            break;
        case 4:
            clrscr();
            search_Ticket_Number();
            break;
        case 5:
            clrscr();
            view_all_bookings();
            getch();
            break;
        case 6:
            clrscr();
            view_Train_Booking();
            getch();
            break;
        case 7:
            clrscr();
            cancel_Ticket();
            getch();
            break;
        case 8:
            clrscr();
            cancel_Train();
            getch();
            break;
        case 9:
            clrscr();
            final_Code();
        default:
            defaultFunction();
            getch();
        }
    }
    return 0;
}
