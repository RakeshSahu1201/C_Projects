#ifndef RAILWAY_MANAGMENT_SYSTEM_H_INCLUDED
#define RAILWAY_MANAGMENT_SYSTEM_H_INCLUDED

#endif // RAILWAY_MANAGMENT_SYSTEM_H_INCLUDED




#include <string.h>

struct Train
{
    char train_no[12];
    char from[50];
    char to[50];
    int fac_fare;
    int sac_fare;
};

struct Passenger
{
    char P_Name[30];
    char Gender;
    char train_no[10];
    char P_Class;
    char Address[30];
    int Age;
    int ticket_no;
    char mob_no[10];
};

typedef struct Train Train;
typedef struct Passenger Passenger;





/*
 *
 *                         FUNCTIONS
 *
 */



int enterChoice();
void add_Train();
void view_Train();
void book_Train();
Passenger * get_Passenger_Details();
int book_ticket(Passenger ps);
int get_booked_ticket_count(char *trainNo,char Class);
int last_ticket_no();
void view_ticket();
void search_Ticket_Number();
int * get_Ticket_No(char *mobno);
void view_all_tickets(char *mobno,int *p);
void view_all_bookings();
void view_Train_Booking();
void view_Bookings(char * trainno);
void cancel_Ticket();
int cancelling_Ticket(int ticketno);
void cancel_Train();
int cancellling_Train(char * train_no);
void defaultFunction();
void final_Code();

int setPassengerName(Passenger *ps);
int setPassengerGender(Passenger *ps);
int setPassengerTrainNo(Passenger *ps);
int setPassengerTrainClass(Passenger *ps);
int setPassengerAddress(Passenger *ps);
int setPassengerAge(Passenger *ps);
int setPassengerMobileNo(Passenger *ps);
int getPassengerTicketNO();






//int enterChoice();// DONE
//void add_Train(); // DONE
//void view_Train(); // DONE
//Passenger* get_Passenger_Details(); // DONE
//int * get_Ticket_No(char *);  //DONE
//void view_all_bookings();       //DONE
//void view_all_tickets(char *,int *);     // DONE
//void view_Bookings(char *);    //DONE
//int cancel_Ticket(int);     // DONE
//int cancel_Train(char *);
//int get_booked_ticket_count(char *,char); // DONE
//int last_ticket_no();  // DONE
//int book_ticket(Passenger);  // DONE
//int accept_ticket_no();   // DONE
//void view_ticket(int ticket_no);    // DONE
//char * accept_mob_no();  // DONE
//char* accept_train_no();   //DONE
//
//

void Overview(char arr[]);

/*
 *                     VALIDATION FUCTIONS
 *
 */
int isGenderValid(char age);
int isTrainNoValid(char Train_no[]);
int isClassValid(char tclass);
int isAgeValid(int age);
int isMobileNoValid(char mobNo[]);
int isTicketNoValid(int);
















