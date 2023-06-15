#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CAR.h"
#include "conio2.h"

int main()
{
     gotoxy(25,10);
     textcolor(YELLOW);
     printf("WELCOME TO CAR RENTAL SYSTEM");
     gotoxy(20,13);
     textcolor(LIGHTGREEN);
     printf("* RENT A CAR AND GO WHEREVER YOU NEED *");
     _getch();
     textcolor(YELLOW);
     addAdmin();
     User *usr;
     int result;
     int choice,i;
     int type;
     while(1)
     {
         clrscr();
         textcolor(LIGHTRED);
         gotoxy(32,2);
         printf("CAR RENTAL SYSTEM");
         gotoxy(65,7);
         textcolor(LIGHTGREEN);
         printf("Press 0 to exit");
         //upper line
         gotoxy(1,8);
         textcolor(YELLOW);
         for(i=0;i<80;i++)
                  printf("*");
             //lower line
             gotoxy(1,17);
             for(i=0;i<80;i++)
                printf("*");
             gotoxy(32,10);
             textcolor(YELLOW);
             printf("1.ADMIN");
             gotoxy(32,12);
             printf("2.EMPLOYEE");
             gotoxy(32,14);
             textcolor(WHITE);
             int k;
             printf("select your role :");
             do
             {
                scanf("%d",&type);
                k=0;
            if(type==1)
              {
                do
                {
                    usr=getinput();


                    if(usr!=NULL)
                    {
                       k=checkUserExist(*usr,"admin"); //code for validating userid password
                    }
                    else
                    {
                        break;
                    }                                 //code for handling admin login
              }while(k==0);

              if(k==1)
              {
                  gotoxy(30,14);
                  textcolor(LIGHTGREEN);
                  printf("Login Accepted");
                  gotoxy(1,20);
                  textcolor(WHITE);
                  printf("Press any key to continue...");
                  getch();

                  while(1)
                  {
                      clrscr();
                      choice=adminMenu();
                      if(choice==7)
                      {
                          clrscr();
                          break;
                      }
                      switch(choice)
                      {
                      case 1:
                        clrscr();
                        addEmployee();
                        break;
                      case 2:
                          clrscr();
                          addCarDetails();
                        break;
                          case 3:
                              clrscr();
                              viewEmployee();
                              break;
                          case 4:
                              clrscr();
                              showCarDetails();
                              break;
                         case 5:
                             clrscr();
                             result=deleteEmp();
                             if(result==0)
                             {
                                 gotoxy(15,14);
                                 textcolor(LIGHTRED);
                                 printf("Sorry! NO employee found with the given employee ID!");
                                 textcolor(WHITE);
                                 printf("\npress any key to go back to the main menu...");
                                 getch();

                             }
                             else if(result==1)
                             {
                                 gotoxy(25,14);
                                 textcolor(LIGHTGREEN);
                                 printf("REcord Deleted Successfully!");
                                 textcolor(WHITE);
                                 printf("\n\npress any key to go back to the main menu...");
                                 getch();

                             }
                        break;
                          case 6:
                              clrscr();
                             result=deleteCarModel();
                               if(result==0)
                             {
                                 gotoxy(15,14);
                                 textcolor(LIGHTRED);
                                 printf("Sorry! NO car found with the given car ID");
                                 textcolor(WHITE);
                                 printf("\npress any key to go back to the main menu");
                                 getch();

                             }
                             else if(result==1)
                             {
                                 gotoxy(25,14);
                                 textcolor(LIGHTGREEN);
                                 printf("REcord Deleted Successfully");
                                 textcolor(WHITE);
                                 printf("\n\npress any key to go back to the main menu");
                                 getch();

                             }
                        break;
                          default:
                            printf("Incorrect Choice!");
                            fflush(stdin);
                            getch();
                        }//switch close
                  }
              }
              }

              else if(type==2)
              {
                   do
                {
                    usr=getinput();
                    if(usr!=NULL)
                    {
                       k=checkUserExist(*usr,"emp"); //code for validating userid password
                    }
                    else
                    {
                        break;
                    }                                                       //code for handling employee login
              }while(k==0);
              if(k==1)
              {
                  gotoxy(30,14);
                  textcolor(LIGHTGREEN);
                  printf("login accepted!");
                  gotoxy(1,20);
                  textcolor(WHITE);
                  printf("press any key to continue.....");
                  getch();
                  while(1)
                  {

                      clrscr();
                      choice=empMenu();
                      if(choice==6)
                      {
                          clrscr();
                          break;
                      }
                      switch(choice)
                      {
                       case 1:
                                clrscr();
                                int j;
                                do
                                {
                                clrscr();
                                j=rentCar();
                                if(j==0)
                                    printf("Booking Cancelled\nTry again");
                                _getch();
                                }while (j==0);
                                break;
                       case 2:
                                clrscr();
                                bookedCarDetails();
                                _getch();
                                break;

                       case 3:
                                clrscr();
                                availableCarDetail();
                                getch();
                                break;

                       case 4:
                                clrscr();
                                showCarDetails();
                                break;

                       case 5:
                                clrscr();
                                recount();
                                getch();
                                break;

                       default:
                                printf("Wrong choice");
                                getch();
                                fflush(stdin);
                      }
                  }
              }
              }
              else if(type==0)
              {
                  gotoxy(28,19);
                  textcolor(LIGHTGREEN);
                  printf("****HAVE A GOOD DAY****");
                  textcolor(BLACK);
                  exit(0);

              }
                else
              {
                  textcolor(LIGHTRED);
                  gotoxy(30,20);
                  printf("Invalid User Type");
                  getch();
                  gotoxy(30,20);
                  printf("\t\t\t");
                  gotoxy(50,14);
                  printf("\t");
                  gotoxy(50,14);
                  textcolor(WHITE);
                  fflush(stdin);

              }
             }
         while(type!=1&&type!=2);


     }
     return 0;
}
