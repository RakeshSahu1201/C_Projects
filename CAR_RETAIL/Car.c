#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "CAR.h"
#include "conio2.h"

void addAdmin()
{
   FILE *fp=fopen("admin.bin","rb");
 if(fp==NULL)
 {
     fp=fopen("admin.bin","wb");
     User u[2]={{"admin","abc","ramesh"},{"aftab","abc","MD Aftab Ahmad"}};
     fwrite(u,sizeof(u),1,fp);
     fclose(fp);
     _getch();
     printf("file saved successfully");

}
else
{
    fclose(fp);
}
}



User *getinput()
{
    int i;
    clrscr();
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM");
    gotoxy(1,2);
    for(i=0;i<80;i++)
    printf("%c",247);
    gotoxy(32,5);
    printf("*LOGIN PANEL*");
    gotoxy(1,7);
    textcolor(LIGHTCYAN);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(60,8);
    textcolor(WHITE);
    printf("press 0 to exit");
    gotoxy(25,10);
    textcolor(LIGHTCYAN);
    printf("Enter user :");
    fflush(stdin);
    textcolor(WHITE);
    static User usr;
    fgets(usr.userid,20,stdin);
    char *pos;
    pos=strchr(usr.userid,'\n');
    *pos='\0';
    if(strcmp(usr.userid,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("LOGIN Cancelled!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    gotoxy(25,11);
    textcolor(LIGHTCYAN);
    printf("Enter Password: ");
    fflush(stdin);
    i=0;
    textcolor(WHITE);
    for(;;)
    {
        usr.pwd[i]=getch();
        if(usr.pwd[i]==13)
        {
            break;
        }

          if(usr.pwd[i]==8)
        {
            if(i>0)
            {
                printf("\b \b");
            i--;
            continue;
            }
        }
        else
        {
            printf("*");
            i++;
        }


    }
usr.pwd[i]='\0';
if(strcmp(usr.pwd,"0")==0)
{
    textcolor(LIGHTRED);
    gotoxy(30,17);
    printf("Login Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;

}
return &usr;
}



int checkUserExist(User u,char *usertype)
{
    if(strcmp(u.userid,"")==0||strcmp(u.pwd,"")==0)
    {
      gotoxy(28,20);
      textcolor(LIGHTRED);
      printf("BOTH FIELDS ARE MANDATORY...");
      getch();
      gotoxy(28,20);
      printf("\t\t\t\t\t\t\t\t\t");
      gotoxy(39,10);
      return 0;

    }
    int found=0;
    if(!(strcmp(usertype,"admin")))
    {
        FILE *fp=fopen("admin.bin","rb");
        User user;
        while (fread(&user,sizeof(User),1,fp)==1)
        {
            if(strcmp(u.userid,user.userid)==0&&strcmp(u.pwd,user.pwd)==0)
            {
                found=1;
                break;
            }
        }
        if(!found)
        {
            gotoxy(27,20);
            textcolor(LIGHTRED);
            printf("INVALID USERNAME OR PASSWORD");
            getch();
            fclose(fp);
            return 0;

        }

        fclose(fp);
        return 1;

    }
else if(!(strcmp(usertype,"emp")))
    {
        FILE *fp=fopen("emp.bin","rb");
        User user;
        while (fread(&user,sizeof(User),1,fp)==1)                                      //code for reading emp.bin
        {
            if(strcmp(u.userid,user.userid)==0 && strcmp(u.pwd,user.pwd)==0)
            {
                found=1;
                break;
            }
        }
        if(!found)
        {
            gotoxy(27,20);
            textcolor(LIGHTRED);
            printf("INVALID USERNAME OR PASSWORD!");
            getch();
            fclose(fp);
            return 0;

        }

        fclose(fp);
        return 1;
     }
return 1;
}



int adminMenu()
{
    int choice,i;
    textcolor(LIGHTGREEN);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,5);
    printf("ADMIN MENU\n");
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1.Add Employee");
    gotoxy(32,9);
    printf("2.Add Car Detail");
    gotoxy(32,10);
    printf("3.Show Employee");
    gotoxy(32,11);
    printf("4.Show Car Detail");
    gotoxy(32,12);
    printf("5.Delete Employee");
    gotoxy(32,13);
    printf("6.Delete Car Detail");
    gotoxy(32,14);
    printf("7.Exit");
    gotoxy(32,16);
    printf("Enter Choice: ");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}



void addEmployee()
{
    FILE *fp=fopen("emp.bin","rb");
    int id;
    char uchoice;
    char emp[10]="EMP-";
    char empid[10];
    User u,ur;
    if(fp==NULL)
    {
        fp=fopen("emp.bin","ab");
        id=1;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");

    }
    else
    {
        fp=fopen("emp.bin","ab+");
        fseek(fp,-60,SEEK_END);
        fread(&ur,sizeof(ur),1,fp);
        char sub[3];
        char str[20];
        strcpy(str,ur.userid);
        sub_str(str,sub,'-');
        id=atoi(sub);
        id++;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");

    }
    do
    {
        clrscr();
        gotoxy(32,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL APP");
        textcolor(LIGHTGREEN);
        int i;
        gotoxy(1,3);
        for(i=0;i<80;i++)
        {
            printf("~");

        }
        textcolor(WHITE);
        gotoxy(25,5);
        printf("*******ADD EMPLOYEE DETAILS******");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Employee Name");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.name,20,stdin);
        char *pos;
        pos=strchr(u.name,'\n');
        *pos='\0';
        textcolor(YELLOW);
        printf("Enter Employee PWD");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.pwd,20,stdin);
        pos=strchr(u.pwd,'\n');
        *pos='\0';
        textcolor(YELLOW);
        fseek(fp,0,SEEK_END);
        fwrite(&u,sizeof(User),1,fp);
        gotoxy(30,15);
        textcolor(LIGHTGREEN);
        printf("EMPLOYEE ID IS:%s ",u.userid);
        getch();
        gotoxy(1,20);
        textcolor(LIGHTRED);
        printf("DO YOU WANT TO ADD MORE EMPLOYEE(Y/N):");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&uchoice);
        id++;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");



    }
    while(uchoice=='Y'||uchoice=='y');
    fclose(fp);

}



void sub_str(char *str,char *sub,char c)
{
    int i,f=0,j=0;
    for(i=0;str[i]!=c;i++)
    {
        f++;                 // for searching hypen(-);
    }
    for(i=++f;str[i]!='\0';i++)
    {
        sub[j]=str[i];
        j++;
    }
    sub[j]='\0';
}



void viewEmployee()
{
    FILE *fp=fopen("emp.bin","rb");
    User ur;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAIL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",247);

    }
    gotoxy(31,5);
    textcolor(YELLOW);
    printf("*EMPLOYEE DETAILS*");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
    {
        printf("%c",247);

    }
    gotoxy(1,8);
    printf("Employee ID\t\t\tName\t\t\tPassword");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    int x=10;
    textcolor(YELLOW);
    while(fread(&ur,sizeof(ur),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%s",ur.userid);
        gotoxy(33,x);
        printf("%s",ur.name);
        gotoxy(57,x);
        printf("%s",ur.pwd);
        x++;

    }
    fclose(fp);
    getch();
}



int deleteEmp()
{
    FILE *fp1=fopen("emp.bin","rb");
    char empid[10];
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAIL SYSTEM\n");
    for(i=1;i<80;i++)
        printf("%c",247);
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("*DELETE EMPLOYEE RECOND");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<80;i++)
        printf("%c",247);
    gotoxy(1,12);
    for(i=1;i<80;i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNO employee added yet!");
        return -1;

    }
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Employee ID to delete the record:");
    textcolor(WHITE);
    scanf("%s",empid);
    User U;
    int found=0;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.userid,empid)!=0)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
        else
        {
            found=1;

        }
    }
    fclose(fp1);
    if(found==1)
    {
        rewind(fp2);
        fp1=fopen("emp.bin","wb");
        while(fread(&U,sizeof(U),1,fp2)==1)
        {
            fwrite(&U,sizeof(U),1,fp1);

        }
        fclose(fp1);
    }
        fclose(fp2);
        remove("temp.bin");
        return found;
    }



int empMenu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(34,2);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
        printf("*");
    gotoxy(35,6);
    printf("EMPLOYEE MENU:\n");
    for(i=0;i<80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1.rent a car");
    gotoxy(32,9);
    printf("2.booking detail");
    gotoxy(32,10);
    printf("3.available car detail");
    gotoxy(32,11);
    printf("4.show all car detail");
    gotoxy(32,12);
    printf("5.Recount");
    gotoxy(32,13);
    printf("6.Exit");
    gotoxy(32,16);
    printf("enter choice:");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;

}



int selectCarModel()
{
    int flag;
    FILE *fp=fopen("car.bin","rb");
    Car C;
    int choice,x=9;

    gotoxy(34,x);
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
            printf("%d. %s",C.car_id,C.car_name);
            gotoxy(34,++x);
        }
    }
    gotoxy(34,x+2);
    printf("Enter your choice:");
    while(1)
    {
        flag=0;
        scanf("%d",&choice);
        rewind(fp);
        while(fread(&C,sizeof(C),1,fp)==1)
        {
            if(C.car_id==choice)
            {
                flag=1;
                break;

            }
        }
        if(flag==1)
        {
            fclose(fp);
            return choice;
        }
        else
        {
            gotoxy(37,x+4);
            textcolor(LIGHTRED);
            printf("Wrong Input");
            _getch();
            gotoxy(35,x+4);
            printf("\t\t");
            gotoxy(52,x+2);
            printf("\t");
            gotoxy(52,x+2);
            textcolor(WHITE);
            fflush(stdin);
        }
    }

}



int isValidDate(struct tm dt)
{
    if(dt.tm_year>=2020 && dt.tm_year<=2022)
    {
        //check month
        if(dt.tm_mon>=1 && dt.tm_mon<=12)
        {
            //check days
            if((dt.tm_mday>=1 && dt.tm_mday<=31) && (dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon==5 || dt.tm_mon==7 || dt.tm_mon==8 || dt.tm_mon==10 || dt.tm_mon==12))
               return 1;
            else if((dt.tm_mday>=1 && dt.tm_mday<=30) && (dt.tm_mon==4 || dt.tm_mon==6 || dt.tm_mon==9 || dt.tm_mon==11))
               return 1;
            else if((dt.tm_mday>=1 && dt.tm_mday<=28) && (dt.tm_mon==2))
                return 1;
            else if(dt.tm_mday==29 && dt.tm_mon==2 && (dt.tm_year%400==0 ||(dt.tm_year%4==0 && dt.tm_year%100!=0)))
               return 1;
            else
               return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

}



void updateCarCount(int c)
{

    FILE *fp1=fopen("car.bin","rb");
    FILE *fp2=fopen("car2.bin","rb");
    Car C;
    if(fp2==NULL)    //handle the car id
    {
    fp2=fopen("car2.bin","wb");
     while(fread(&C,sizeof(Car),1,fp1)==1)
     {
       fwrite(&C,sizeof(Car),1,fp2);

     }
     fclose(fp2);
    }
    /*else
    {
    fseek(fp1,-1*sizeof(Car),SEEK_END);
    fread(&C,sizeof(Car),1,fp1);
    int car_1id=C.car_id;
    fseek(fp2,-1*sizeof(Car),SEEK_END);
    fread(&C,sizeof(Car),1,fp2);
    int car_2id=C.car_id;
    if(car_2id<car_1id)    //handle the car id
    {
  //      printf("nullbale else ka if chala hai");
    //    getch();
     fp2=fopen("car2.bin","ab");
     while(fread(&C,sizeof(Car),1,fp1)==1)
     {
        fwrite(&C,sizeof(Car),1,fp2);

     }
     fclose(fp2);
    }
    }*/
    fclose(fp1);
    fclose(fp2);
    FILE *fp=fopen("car2.bin","rb+");
    while(fread(&C,sizeof(Car),1,fp)==1)
    {
       if(C.car_id==c)
        {

            //changers
            int cc_new=C.car_count-1;
            fseek(fp,-1*sizeof(long double),SEEK_CUR);
            fwrite(&cc_new,sizeof(int),1,fp);
            break;
        }
    }
fclose(fp);
}




char * getCarName(int car_id)
{
    FILE *fp=fopen("car.bin","rb");
    static Car C;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id==car_id)
        {
             break;
        }
    }
    fclose(fp);
    return C.car_name;

}




void bookedCarDetails()
{
    clrscr();
    FILE *fp=fopen("customer.bin","rb");
    Customer_Car_Details CC;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1; i<=80; i++)
        printf("%c",247);
    gotoxy(31,5);
    textcolor(YELLOW);
    printf("* BOOKED CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1; i<=80; i++)
        printf("%c",247);
    gotoxy(1,8);
    printf("Model\t    Cust_Name\t  Pick Up\t   Drop\t\t S_Date\t     E_Date");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1; i<=80; i++)
        printf("%c",247);
    int x=10;
    textcolor(YELLOW);

    while(fread(&CC,sizeof(Customer_Car_Details),1,fp)==1)
    {
        gotoxy(1,x);
        printf("%s",getCarName(CC.car_id));
        gotoxy(13,x);
        printf("%s",CC.cust_name);
        gotoxy(27,x);
        printf("%s",CC.pick);
        gotoxy(44,x);
        printf("%s",CC.drop);
        gotoxy(58,x);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);
        gotoxy(70,x);
        printf("%d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);
        x++;

    }
    fclose(fp);
}




int rentCar()
{

    Customer_Car_Details CC;
    int c,i;
    Car C;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);

    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0; i<80; i++)
    {
        printf("*");
    }

    textcolor(YELLOW);
    gotoxy(32,8);
    c=selectCarModel();
    CC.car_id=c;
    clrscr();
    int a=0;
    FILE *fp1=fopen("car2.bin","rb");
    if(a==0)
    {
      while(fread(&C,sizeof(Car),1,fp1)==1)
    {

       if(C.car_id==CC.car_id && C.car_count<=0)
        {
         printf("Sorry! this car cannot be given for rent....");
          a=1;
          return 0;
        }
    }
    fclose(fp1);
    }
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0; i<80; i++)
    {
        printf("*");
    }
    gotoxy(1,17);
    for(i=0; i<80; i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(27,9);
    printf("Enter Customer Name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos=strchr(CC.cust_name,'\n');
    *pos='\0';
    gotoxy(27,10);
    textcolor(YELLOW);
    printf("Enter Pickup Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.pick,30,stdin);
    pos=strchr(CC.pick,'\n');
    *pos='\0';
    gotoxy(27,11);
    textcolor(YELLOW);
    printf("Enter Drop Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.drop,30,stdin);
    pos=strchr(CC.drop,'\n');
    *pos='\0';
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date (dd/m/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
        int datevalid=isValidDate(CC.sd);
        if(datevalid==0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong Date");
            _getch();
            gotoxy(27,18);
            printf("\t\t");
            gotoxy(56,12);
            printf("\t\t\t");
            gotoxy(56,12);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    gotoxy(27,13);
    textcolor(YELLOW);
    printf("Enter end date (dd/m/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
        int datevalid=isValidDate(CC.ed);
        if(!(datevalid==0))
        {
          if(CC.ed.tm_year<CC.sd.tm_year)
          {
            datevalid=0;
          }
          else if(CC.ed.tm_year==CC.sd.tm_year)
          {
          if(CC.ed.tm_mon<CC.sd.tm_mon)
            datevalid=0;
          else if(CC.ed.tm_mon==CC.sd.tm_mon && CC.ed.tm_mday<=CC.sd.tm_mday)
            datevalid=0;
          else
            datevalid=1;
          }                    //"""""""UPDATE THE END DATE SYSTEM IN RENT FILE;""""""
          else
            datevalid=1;
        }
        if(datevalid==0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong Date");
            _getch();
            gotoxy(27,18);
            printf("\t\t");
            gotoxy(54,13);
            printf("\t\t\t");
            gotoxy(54,13);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);

    FILE *fp;
    fp=fopen("customer.bin","ab");
    fwrite(&CC,sizeof(Customer_Car_Details),1,fp);
    printf("\nPress any key to continue...");
    _getch();
    fclose(fp);
    updateCarCount(c);
    bookedCarDetails();
    return 1;

}




void addCarDetails()
{

    FILE *fp=fopen("car.bin","rb");
    FILE *fp1=fopen("car2.bin","ab+");
    Car cr;
    int carid;
    char uchoice;
    if(fp==NULL)
    {
        fp=fopen("car.bin","ab");                   //problem in car_id no system to slove/po
        carid=1;
        cr.car_id=carid;
    }
    else
    {
        fp=fopen("car.bin","ab+");
        fseek(fp,-1*sizeof(Car),SEEK_END);
        fread(&cr,sizeof(Car),1,fp);
        carid=cr.car_id;
        carid++;
        cr.car_id=carid;
    }
    do
    {
        clrscr();
        gotoxy(32,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL APP");
        textcolor(LIGHTGREEN);
        int i;
        gotoxy(1,3);
        for(i=0;i<80;i++)
        {
            printf("~");

        }
        textcolor(WHITE);
        gotoxy(25,5);
        printf("*******ADD CAR DETAILS******");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Car Name:");
        fflush(stdin);
        textcolor(WHITE);
        fgets(cr.car_name,50,stdin);
        char *pos;
        pos=strchr(cr.car_name,'\n');
        *pos='\0';
        textcolor(YELLOW);
        printf("Enter car capacity:");
        textcolor(WHITE);
        scanf("%d",&cr.capacity);
        textcolor(YELLOW);
        printf("Enter car count:");
        textcolor(WHITE);
        scanf("%d",&cr.car_count);
        textcolor(YELLOW);
        printf("Enter price per day:");
        textcolor(WHITE);
        scanf("%d",&cr.price);
        printf("car added successfully!");
        printf("car id is %d",cr.car_id);
        fseek(fp,0,SEEK_END);
        fseek(fp1,0,SEEK_END);
        fwrite(&cr,sizeof(Car),1,fp);
        fwrite(&cr,sizeof(Car),1,fp1);
        carid++;
        cr.car_id=carid;
        gotoxy(1,20);
        textcolor(LIGHTRED);
        printf("DO YOU WANT TO ADD MORE CAR(Y/N):");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&uchoice);

    }
    while(uchoice=='Y'||uchoice=='y');
    fclose(fp);
    fclose(fp1);

}




void showCarDetails()
{
    FILE *fp=fopen("car.bin","rb");
    Car c;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAIL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",247);

    }
    gotoxy(34,5);
    textcolor(YELLOW);
    printf("*CAR DETAILS*");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
    {
        printf("%c",247);

    }
    gotoxy(1,8);
    printf("CAR ID\t\tName\t\t capacity\tcount\t\tprice");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    int x=10;
    textcolor(YELLOW);
    while(fread(&c,sizeof(c),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%d",c.car_id);
        gotoxy(17,x);
        printf("%s",c.car_name);
        gotoxy(34,x);
        printf("%d",c.capacity);
        gotoxy(49,x);
        printf("%d",c.car_count);
        gotoxy(65,x);
        printf("%d",c.price);
        x++;

        //printf("%d\t\t%s\t\t%d\t\t%d\t\t%d",c.car_id,c.car_name,c.capacity,c.car_count,c.price);      //OPEN POS COMMENT

    }
    fclose(fp);
    getch();
}




int deleteCarModel()
{
    FILE *fp1=fopen("car.bin","rb");
    int carid;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAIL SYSTEM\n");
    for(i=1;i<80;i++)
        printf("%c",247);
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("*DELETE CAR RECOND");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<80;i++)
        printf("%c",247);
    gotoxy(1,12);
    for(i=1;i<80;i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNO car added yet!");
        return -1;

    }
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter car ID to delete the record:");
    textcolor(WHITE);
    scanf("%d",&carid);
    Car c;
    int found=0;
    while(fread(&c,sizeof(c),1,fp1)==1)
    {
        if(carid!=c.car_id)
        {
            fwrite(&c,sizeof(c),1,fp2);
        }
        else
        {
            found=1;

        }
    }
    fclose(fp1);
    if(found==1)
    {
        rewind(fp2);
        fp1=fopen("car.bin","wb");
        while(fread(&c,sizeof(c),1,fp2)==1)
        {
            fwrite(&c,sizeof(c),1,fp1);

        }
        fclose(fp1);
    }
        fclose(fp2);
        remove("temp.bin");
        return found;

}




void availableCarDetail()
{
    FILE *fp1=fopen("car.bin","rb");
    FILE *fp2=fopen("car2.bin","rb");
    Car C;
    if(fp2==NULL)
    {
    fp2=fopen("car2.bin","wb");
     while(fread(&C,sizeof(Car),1,fp1)==1)
     {
       fwrite(&C,sizeof(Car),1,fp2);

     }
     fclose(fp2);
    }
    fclose(fp1);
    fclose(fp2);
    FILE *fp=fopen("car2.bin","rb");
    Car c;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAIL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",247);

    }
    gotoxy(34,5);
    textcolor(YELLOW);
    printf("*CAR DETAILS*");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
    {
        printf("%c",247);

    }
    gotoxy(1,8);
    printf("CAR ID\t\tName\t\t capacity\tcount\t\tprice");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    int x=10;
    textcolor(YELLOW);
    while(fread(&c,sizeof(c),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%d",c.car_id);
        gotoxy(17,x);
        printf("%s",c.car_name);
        gotoxy(34,x);
        printf("%d",c.capacity);
        gotoxy(49,x);
        printf("%d",c.car_count);
        gotoxy(65,x);
        printf("%d",c.price);
        x++;

        //printf("%d\t\t%s\t\t%d\t\t%d\t\t%d",c.car_id,c.car_name,c.capacity,c.car_count,c.price);      //OPEN POS COMMENT

    }
    fclose(fp);
}




void recount()
{
    FILE *fp=fopen("car2.bin","rb+");
    int i;
    Car c;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAIL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",247);

    }
    gotoxy(34,5);
    textcolor(YELLOW);
    printf("*CAR DETAILS*");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
    {
        printf("%c",247);

    }
    gotoxy(34,14);
    printf("Enter Car ID:");
    textcolor(WHITE);
    scanf("%d",&i);
    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        if(c.car_id==i)
        {
            fseek(fp,-3*sizeof(int),SEEK_CUR);
            printf("Enter Car Count To Increase:");
            scanf("%d",&c.car_count);
            fwrite(&c.car_count,sizeof(int),1,fp);
            printf("Car Count Increased Successfully!");
            break;
        }
    }
    fclose(fp);
    getch();
    clrscr();
    availableCarDetail();

}




