# include<iostream.h>
# include<conio.h>
# include<stdio.h >
# include<string.h>
# include<fstream.h>
# include<iomanip.h>
# include<stdlib.h>
int day, month ,year;
class pharmacy
{char dname[25]; int year,month,dstock; float dprice;
public: void read_dname()
{
cout<<"\n\n\t\t\tEnter the name of the medicine  ";
gets(dname);}
void read_date()
{
cout<<"\n\n\t\t\tEnter the date of expiry (mm yy) ";                                                                                
 cin>>month>>year;}
 void getdata()
 {
 cout<<"\n\n\t\t\tEnter the quantity of medicine ";
 cin>>dstock;
 cout<<"\n\n\t\t\tEnter the price of the medicine ";
 cin>>dprice; }
 char*retdname()
 {return dname;}
 int retyear()
 {return year;}
 int retmonth()
 {return month;
}
int retdstock  ()
{return dstock;
int retdprice()
{return dprice;
}
void putdata()
{gotoxy(5,5);
cout<<"NAME";
 gotoxy(20,5);
cout<<"QUANTITY";
 gotoxy(40,5);
cout<<"PRICE";
gotoxy(60,5);
cout<<"DATE OF EXPIRY";}
void assign_2()
{dstock=0;}
void assign_3(int quantity)
{dstock-=quantity ;}
void assign_4(int qty)
{dstock=qty;
}
void assign_5(float price)
{dprice=price;}
};
class prescription
{char pname[25]; int pstock,pcode;
public:
void get_prescode ()
{
cout<<"\n\n\t\t\tEnter the prescription code ";
cin>>pcode; }
void read_pname()
{cout<<"\n\n\t\tEnter the name of the medicine you wish to purchase ";
cin>>pname;
}
void read_pstock()
{cout<<"\n\n\t\t\tEnter the quantity of the medicine ";
cin>>pstock;
}
char* retpname()
{return pname;
}
int retpstock()
{return pstock;}
void assign_1(int qty)
{pstock=qty;}
int retpcode()
{return pcode;}
void putdata()
{gotoxy(5,5);
cout<<"PRESCRIPTION CODE";
gotoxy( 30,5);
cout<<"MEDICINE PRESCRIBED";
gotoxy(60,5);
cout<<"QUANTITY";
}
};
 void check_expiry(int cmonth,int cyear)
{pharmacy p;
ifstream fin("pharmacy.dat",ios::binary);
ofstream fout("temp.dat",ios::binary);
while(fin.read((char*)&p,sizeof(p)))
{if (p.retyear()<cyear)
;
else if((p.retyear()==cyear)&&(p.retmonth()<cmonth))
;
else
fout.write((char*)&p,sizeof(p));}
fin.close();
fout.close();
remove("pharmacy.dat");
rename("temp.dat","pharmacy.dat");
}
int check_medname(char mname[])
{pharmacy p; int x=0;
ifstream fin("pharmacy.dat",ios::binary);
while(fin.read((char*)&p,sizeof(p)))
{if(strcmpi(p.retdname(),mname)==0)
{x=1;
break;
}}
return x;}
void writing()
{pharmacy p; int x; char ans;
clrscr();
do
{do
{ p.read_dname();
x=check_medname(p.retdname());
 if(x==1)
 cout<<"\n\n\t\t\t Medicine already exists in the file"<<"\n\n\t\t\t Please try again"<<"\n" ;
 }while (x==1);
p.getdata();
do{
p.read_date();
if(p.retmonth()>=13)
cout<<"\n\n\t\t\tInvalid date!"<<"\n\n\t\t\tPlease try again"<<"\n";
}while(p.retmonth()>=13);
fstream file("pharmacy.dat",ios::binary|ios::app);
file.write((char*)&p,sizeof(p));
file.close();
do{
cout<<"\n\n\t\t\tDo you wish to enter any more records?(y/n) ";
cin>>ans;
if (ans!='Y'&&ans!='y'&&ans!='n' && ans!='N')
cout<<"\n\t\t\tInvalid answer!"<<"\n";
}while( ans!='Y'&&ans!='y'&&ans!='n' && ans!='N')  ;
}while(ans=='y'||ans=='Y');
getch();}
void display()
{pharmacy p; int i=6;
clrscr();
ifstream fin("pharmacy.dat",ios::binary);
p.putdata();
while (fin.read((char*)&p,sizeof(p)))
{gotoxy(5,i);
cout<<p.retdname();
gotoxy(23,i);
cout<<p.retdstock();
gotoxy(40,i);
cout<<p.retdprice();
gotoxy(63,i);
cout<<p.retmonth()<<"/"<<p.retyear()<<"\n";
i++;
}
fin.close();
getch();}
int check_dstock(char mname[])
{pharmacy p;   int f=0;
ifstream fin("pharmacy.dat",ios::binary);
while(fin.read((char*)&p,sizeof(p)))
if (strcmpi(mname,p.retdname())==0)
{f=1;
break;
}
if(f==1)
return p.retdstock();
else return 0;}
void get_pres()
{prescription pr;
 char ans,ch; int y, x,f,z,stock;
 clrscr();
ofstream fout("prescription.dat",ios::binary|ios::app);
pr.get_prescode();
do{
y=1;
do{
pr.read_pname();
x=check_medname(pr.retpname());
if(x==0)
cout<<"\n\n\t\t\tThe medicine does not exist in the file"<<"\n\n\t\t\tPlease try again"<<"\n";
}while(x==0);
pr.read_pstock();
stock = check_dstock(pr.retpname());
if(stock==0)
{cout<<"\n\n\t\t\t"<<pr.retpname()<<" is out of stock";
y=0;}
else if (pr.retpstock()>stock)
{do
{f=0;
cout<<"\n\n\t\t\tRequired quantity of "<<pr.retpname()<<" not available"<<"\n\n\t\t\tWould you like to purchase "<<stock<<" pieces (y/n) ";
cin>>ans;
if(ans!='y'&& ans!='Y' && ans!='n' &&ans!='N')
{f=1;
cout<<"\n\n\t\t\tINVALID CHOICE!";
}
}while(f==1);
if (ans=='y'||ans=='y')
pr.assign_1(stock);
else y=0;
}
if (y==1)
fout.write((char*)&pr,sizeof(pr));
do{
z=0;
cout<<"\n\n\t\t\tDo you wish to enter anymore records?(y/n) ";
cin>>ch;
if( ch!='y'&& ch!='Y' && ch!='n' && ch!='N'  )
{z=1;
cout<<"\n\n\t\t\tINVALID CHOICE";
}
}while(z==1);
}while(ch=='y'||ch=='Y');
fout.close();
getch();}
int check_prescode(int code)
{
prescription pr; int x=0;
ifstream fin("prescription.dat",ios::binary);
while(fin.read((char*)&pr,sizeof(pr)))
if(pr.retpcode()==code)
{x=1;
break;
}
if(x==1)
return 0;
}
void display_pres(int code)
{prescription pr; int i=6 ;
  clrscr();
pr.putdata();
ifstream fin("prescription.dat",ios::binary);
while(fin.read((char*)&pr,sizeof(pr)))
{if(pr.retpcode()==code)
gotoxy( 8,i);
cout<<pr.retpcode();
  gotoxy( 33,i);
cout<<pr.retpname();
gotoxy( 63,i);
cout<<pr.retpstock();
i++;
}
fin.close();
getch();}
float check_medprice(char mname[25])
{pharmacy p;  int f=0;
ifstream fin ("pharmacy.dat",ios::binary);
while(fin.read((char*)&p ,sizeof(p)))
if (strcmpi(mname,p.retdname())==0)
{f=1;
break;
}
fin.close();
if(f==1)
return p.retdprice();
else
return 0;
}
void change_dstock(int qty,char mname[50])
{pharmacy p;
fstream file("pharmacy.dat",ios::binary|ios::in|ios::out);
while(file.read((char*)&p,sizeof(p)))
{
if(strcmpi(mname,p.retdname())==0)
{if(qty>=p.retdstock())
{p.assign_2();
file.seekg(-sizeof(p),ios::cur);
file.write((char*)&p,sizeof(p));
}
else
{p.assign_3(qty);
file.seekg(-sizeof(p),ios::cur);
file.write((char*)&p,sizeof(p));
}
}
}
file.close();
}
void modify_quantity()
{pharmacy p;  int found=0,qty; char name[25];
  clrscr();
cout<<"\n\n\t\t\tEnter the name of the medicine to modify ";
gets(name);
fstream file("pharmacy.dat",ios::binary|ios::in|ios::out);
while(file.read((char*)&p,sizeof(p)))
if(strcmpi(p.retdname(),name)==0)
{
cout<<"\n\n\t\t\tEnter new quantity of "<<p.retdname()<<"  ";
cin>>qty;
p.assign_4(qty);
file.seekg(-sizeof(p),ios::cur);
file.write((char*)&p,sizeof(p));
found++;
}
file.close();
if(found==0)
cout<<"\n\n\t\t\tInvalid medicine name"<<"\n\n\t\t\tPlease try again";
else
 cout<<"\n\t\t\t"<<found<<" record modified";
getch();}
 void modify_price()
 {pharmacy p; int found=0; float price; char name[25];
  clrscr();
  cout<<"\n\n\t\t\tEnter the name of the medicine to modify ";
gets(name);
fstream file("pharmacy.dat",ios::binary|ios::in|ios::out);
while(file.read((char*)&p,sizeof(p)))
if(strcmpi(p.retdname(),name)==0)
{cout<<"\n\t\t\tEnter the new price of "<<p.retdname()<<" " ;
 cin>>price;
  p.assign_5(price);
  file.seekg(-sizeof(p),ios::cur);
 file.write((char*)&p,sizeof(p));
  found++;
}
 file.close();
 if(found==0)
 cout<<"\n\n\t\t\tINVALID MEDICINE NAME "<<"\n\n\t\t\tPlease try again";
 else
 cout<<"\n\n\t\t\t"<<found<<" record modified";
 getch();}
 void modify_menu()
{char ch;
clrscr();
cout<<"\n\n\t\t\tTo modify quantity, Press Q"<<"\n\n\t\t\tTo modify price, Press P"<<"\n\n\t\t\tEnter your choice";
cin>>ch;
switch(ch)
{case 'Q':
case 'q':modify_quantity();
break;
case'P':
case'p':modify_price();
break;
default: cout<<"\n\n\t\t\tInvalid choice!";
break;
}
getch();}
void delete_medicine()
{pharmacy p;  char name[25]; int found=0;
  clrscr();
ifstream fin("pharmacy.dat",ios::binary);
ofstream fout("temp.dat",ios::binary);
cout<<"\n\n\t\t\tEnter the name of the medicine to delete ";
gets(name);
while(fin.read((char*)&p,sizeof(p)))
{if(strcmpi(p.retdname(),name)==0)
found++;
else
fout.write((char*)&p,sizeof(p));
}
fin.close();
fout.close();
if(found==0)
cout<<"\n\n\t\t\t No records deleted";
else
cout<<"\n\n\t\t\t"<<found<<" record deleted";
remove("pharmacy.dat");
rename("temp.dat","pharmacy.dat");
getch();}
void billing (int code)
{
prescription pr; char ans ; int x,w=0,i=6,qty; float price,total=0;
clrscr();
cout<<"\n\n\t\t\tDo you have medical insurance?(y/n) ";
cin>>ans;
if(ans=='Y'||ans=='y')
cout<<"\n\n\t\t\tThe medical insurance covers 25% of your bill ";
getch();
ifstream fin("prescription.dat",ios::binary);
clrscr();
cout<<"\n\t\t\t\tJFR PHARMACY";
cout<<"\nPRESCRIPTION CODE: "<<code;
while(fin.read((char*)&pr,sizeof(pr)))
{if(pr.retpcode()==code)
{x=1;
price= check_medprice(pr.retpname());
qty=check_dstock(pr.retpname());
if(w==0)
{
gotoxy(5,5) ;
cout<<"MEDICINE PRESCRIBED";
gotoxy(30,5);
cout<<"QUANTITY" ;
gotoxy(45,5);
cout<<"UNIT PRICE";
gotoxy(60,5);
cout<<"TOTAL";
w=1;
}
gotoxy (8,i);
cout<<pr.retpname();
if(qty!=0)
{
gotoxy(33,i);
cout<<pr.retpstock();
gotoxy(48,i);
cout<<price  ;
gotoxy(63,i);
cout<<pr.retpstock()*price;
i++;
total= total +pr.retpstock()*price;
change_dstock(pr.retpstock(),pr.retpname());
}
else
{ gotoxy(33,i);
cout<<"0";
gotoxy(48,i);
cout<<price ;
gotoxy(63,i);
cout<<0;
total= total+0;
change_dstock(0,pr.retpname());}
}
}
if(x==1)
{
if(ans=='Y'||ans=='y')
total =total-(25.0/100*total);
cout<<"\n\n\t\t\t\t\tTOTAL: "<<total<<"\n\n\n\n";
}
fin.close();
getch();}
void admin_menu()
{ int ch;
  clrscr();
do{  cout<<"\n\n\n";
cout<<"\n\n\t\t\t1. Add medicines ";
cout<<"\n\n\t\t\t2. Display records ";
cout<<"\n\n\t\t\t3. Modify records ";
cout<<"\n\n\t\t\t4. Delete medicines ";
cout<<"\n\n\t\t\t5. Return to the previous menu ";
cout<<"\n\n\t\t\t   Enter your choice ";
cin>>ch;
switch(ch)
{case 1: writing();
         check_expiry(month,year);
         break;
 case 2: display();
         break;
 case 3: modify_menu();
         break;
 case 4: delete_medicine();
         break;
 case 5: break;
 default: cout<<"\n\n\t\t\tINVALID CHOICE!"<<"\n\n\t\t\tPlease try again";
          break;
 }
 }while(ch!=5);
 getch();}
void main()
{
char choice; int ch;
int x,y,code;
 clrscr();
do
{
cout<<"\n\n\t\t\tEnter today's date(dd mm yy) ";
cin>>day>>month>>year;
switch(month)
{case 1:
 case 3:
 case 5:
 case 7:
 case 10:
 case 12:if(day>31)
 {x=1;
 cout<<"\n\n\t\t\tINVALID DATE!";
 }
 break;
 case 2:if(day>28)
 {x=1;
 cout<<"\n\n\t\t\tINVALID DATE!";
 }
 break;
 case 4:
 case 6:
 case 9:
 case 11:if(day>30)
 {x=1;
 cout<<"\n\n\t\t\tINVALID DATE!";
 }
 break;
 default: if(month>12)
 {x=1;
 cout<<"\n\n\t\t\tINVALID DATE!";
 }
 getch();}
 check_expiry(month,year);
 }while(x==1);
 do{
 clrscr();
 cout<<"\n\n\t\t\tFor Admin Menu, press A " <<"\n\n\t\t\tFor User Menu, press U "
     <<"\n\n\t\t\tTo Exit, press E"<<"\n\n\t\t\tEnter your choice ";
     cin>>choice;
     switch(choice)
     {case 'U':
      case 'u':  do{ cout<<"\n\n\n";
                 cout<<"\n\n\t\t\t1.Buy Medicines ";
                 cout<<"\n\n\t\t\t2.Display Prescription";
                 cout<<"\n\n\t\t\t3.Generate Bill";
                 cout<<"\n\n\t\t\t4.Return to main menu";
                 cout<<"\n\n\t\t\t  Enter your choice: ";
                 cin>>ch;
      switch(ch)
      {case 1: clrscr();get_pres();getch();
      break;
      case 2:
      clrscr();
      do{
      cout<<"\n\n\t\t\tEnter the prescription code ";
      cin>>code;
      y=check_prescode(code);
      if(y==0)
      display_pres(code);
      else
     { cout<<"\n\n\t\t\tInvalid Prescription code";
     cout<<"\n\n\t\t\tPlease try again";}
     }while(y!=0);
     getch();
     break;
     case 3:clrscr();
     do{
     cout<<"\n\n\t\t\tEnter the Prescription code ";
     cin>>code;
     y= check_prescode(code);
     if(y==0)
     billing (code);
     else
     cout<<"\n\n\t\t\tINVALID PRESCRIPTION CODE"<<"\n\n\t\t\tPlease try again";
     }while(y!=0);
     getch();
     break;
     case 4: break;
 default : cout<<"\n\n\t\t\tINVALID CHOICE!";
           cout<<"\n\n\t\t\tPlease try again";
           }
           }while(ch!=4);
       break;
       case 'A' :
        case 'a' : clrscr();admin_menu(); getch();
         break; 
        case 'E':
        case 'e': exit(0);
     default: cout<<"\n\n\t\t\t INVALID CHOICE";
      }
      }while(choice!='X' && choice!='x');
      getch();
      }
