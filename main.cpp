

 #include<iostream>
#include<vector>
#include<string.h>
#include<windows.h>
#include<fstream>
using namespace std;
struct time
{
int hh;
int mm;
int ss;
char col1;
char col2;
};
struct date
{
    int day;
    int month;
    int year;
    char sym1;
    char sym2;
};
class vehicle
{
    string pltno;
	int type;
    date dt;
    time arrive;
    time departure;
public:
void addvehicle();
void deletevehicle();
void printvehicle(vehicle v);
void show();
};
vector<vehicle> veh(100);
int static totalvehicle=0,totaltruck=0,totalamt=0,totalcar=0,i=0;
fstream file;
void vehicle::addvehicle()
{
    vehicle *v=new vehicle;
    cout<<"Enter vehicle type(1 for car/2 for trucks)::";
    cin>>v->type;
    cout<<"Enter vehicle number plate::";
    cin>>v->pltno;
    cout<<"Enter arrival time in hours,minutes and seconds::";
    cin>>v->arrive.hh>>v->arrive.col1>>v->arrive.mm>>v->arrive.col2>>v->arrive.ss;
    cout<<"Enter date in day,month and year::";
    cin>>v->dt.day>>v->dt.sym1>>v->dt.month>>v->dt.sym2>>v->dt.year;
    veh.at(i).pltno=v->pltno;
    veh.at(i).type=v->type;
    veh.at(i).arrive.hh=v->arrive.hh;
    veh.at(i).arrive.mm=v->arrive.mm;
    veh.at(i).arrive.ss=v->arrive.ss;
    veh.at(i).dt.day=v->dt.day;
    veh.at(i).dt.month=v->dt.month;
    veh.at(i).dt.year=v->dt.year;
    i++;
    totalvehicle++;
    if(v->type==1)
    {
    	totalcar++;
	}
	else
	{
		totaltruck++;
	}
    cout<<"\nVehicle added successfully"<<endl;
}
int computeTimeDifference(time t1,time t2)
{
    int sec1,sec2,totalsec;
    time t3;
    sec1=t1.hh*60*60+t1.mm*60+t1.ss;
    sec2=t2.hh*60*60+t2.mm*60+t2.ss;
    totalsec=sec2-sec1;
    t3.mm=totalsec/60;
    t3.hh=t3.mm/60;
    t3.mm=t3.mm%60;
     t3.ss=totalsec%60;
     return t3.hh;
}
void vehicle::deletevehicle()
{
string pno;
int typ;
time depart;
int time_diff;
double charge=0.00;
cout<<"Enter vehicle type(1 for car/2 for truck)::";
cin>>typ;
cout<<"Enter vehicle number plate::";
cin>>pno;
cout<<"Enter departure time in hours,minutes & seconds::"<<endl;
cin>>depart.hh>>depart.col1>>depart.mm>>depart.col2>>depart.ss;
for(int j=0;j<=i;j++)
{
    if((veh.at(j).pltno==pno)&&(veh.at(j).type==typ))
    {
veh.at(j).departure.hh=depart.hh;
veh.at(j).departure.mm=depart.mm;
veh.at(j).departure.ss=depart.ss;
    time_diff=computeTimeDifference(veh.at(j).arrive,depart);
    if(veh.at(j).type==1)
    {
        totalcar--;
    if(time_diff<0.5)
    {
        charge=0.00;
    }
    else
        if((time_diff>0.5)&&(time_diff<1))
    {
        charge=1.50;
    }
    else
        if((time_diff>1)&&(time_diff<2))
    {
        charge=3.00;
    }
    else
        if((time_diff>2)&&(time_diff<4))
    {
        charge=5.00;
    }
    else{
        if((time_diff>4)&&(time_diff<8))
    {
        charge=15.00;
    }
    else
        {
            charge=30.00;
        }
    }
    }
    else
    {
        totaltruck--;
        if(time_diff<0.5)
    {
        charge=0.00;
    }
    else
        if((time_diff>0.5)&&(time_diff<1))
    {
        charge=1.50;
    }
    else
        if((time_diff>1)&&(time_diff<2))
    {
        charge=3.00;
    }
    else
        if((time_diff>2)&&(time_diff<4))
    {
        charge=5.00;
    }
    else{
        if((time_diff>4)&&(time_diff<8))
    {
        charge=15.00;
    }
    else
        {
            charge=30.00;
        }
    }
    }

    cout<<"\nVehicle having number plate "<<veh.at(j).pltno<<" has left the parking after paying "<<charge<<" Euros"<<endl;
    file.open("parkingDatabase.txt",ios::app);
    if(!file)
    {
        cerr<<"Error:file could not be opened"<<endl;
        exit(1);
    }
    file<<veh.at(j).type<<"\t\t\t"<<veh.at(j).pltno<<"\t\t\t"<<veh.at(j).dt.day<<"/"<<veh.at(j).dt.month<<"/"<<veh.at(j).dt.year<<"\t\t\t"<<endl;
    file.close();
    veh.erase(veh.begin()+j);
    i--;
    totalvehicle--;
    totalamt=totalamt+charge;
    break;
}

if(j==1)
{
    cout<<"\nWrong Entry,Try Again "<<endl;
    cout<<"Departure :"<<endl;
    deletevehicle();
}
}
}
void vehicle::printvehicle(vehicle v)
{
cout<<v.type<<"\t\t\t"<<v.pltno<<"\t\t\t"<<v.dt.day<<"/"<<v.dt.month<<"/"<<v.dt.year<<"\t"<<v.arrive.hh<<":"<<v.arrive.mm<<":"<<v.arrive.ss<<endl;
}
void vehicle::show()
{
cout<<"vehicle Type\t\tVehicle Number\t\tDate\t\tArrival Time"<<endl;
for(int j=0;j<i;j++)
{
    printvehicle(veh[j]);
}
}
void totalveh()
{
    cout<<"Total number of Car parked :"<<totalcar<<endl;
    cout<<"Total number of Truck parked :"<<totaltruck<<endl;
}
void totalamount()
{
    cout<<"Total Money collected till now :"<<totalamt<<endl;
}
int main()
{
    int choice;
	char ans;
	while(true)
	{
	system ("cls");
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"            CAR PARKING MANAGEMENT SYSTEM               "<<endl;
	cout<<"1.Add a vehicle to the parking"<<endl;
    cout<<"2.Total number of car parked"<<endl;
	cout<<"3.Remove a car from parking"<<endl;
	cout <<"4.Total amount collected"<<endl;
    cout <<"5.Display"<<endl;
	cout<<"6.Exit"<<endl;
	cout <<"========================================================"<<endl;
	cout <<"please enter your choice::"<<endl;
    cin>>choice;
switch(choice)
{
 case 1: system("cls");
         cout<<"Add"<<endl;
         veh.at(i).addvehicle();
	     break;
 case 2:system("cls");
        totalveh();
        break;
 case 3:system("cls");
       cout<<"Departure :"<<endl;
       veh.at(i).deletevehicle();
       break;
 case 4:system("cls");
         totalamount();
         break;
 case 5:system("cls");
        veh.at(i).show();
        break;
case 6:exit(0);
       break;

}
cout<<"Do you want to continue..press y/n"<<endl;
cin>>ans;
if(ans=='n')
{
	break;
}
else
{
	continue;
}
	}
	}
