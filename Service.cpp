#include<iostream>
#include<cstdio>
#include<fstream>
#include<iomanip>
#include<string>
#include<stack>
#include<queue>
using namespace std;
int allotment();
void one(int dev,int c);
int previousallot(int dev,int s);
void filll(int i);
int previousallotupdate(int dev,int s);
void cop();

queue<int> general;
stack<int> available;
stack<int> pending;
stack<int> afternoon;
stack<int> night;
int day;
int fallot[5][3];
int offering[3];
int serving[3];
int reading[2];
int mopping[3];
int vessel[4];
/*
1.offering    [0][0]  1   [0][1]  1   [0][2]
2.serving     [1][0]  1   [1][1]  1   [1][2]
3.reading     [2][0]  1   [2][1] [2][2]
4.mopping     [3][0] [3][1] [3][2]
5.vessel      [4][0] [4][1] [4][2]

*/
ofstream preallot1("preallot1.txt");
int main()
{

    int slot=0;

    int dev[15];
//    allo.clear();
    ofstream today("Todays Timetable.txt");
    cout<<"INPUT OF DAY into d and storing the day code in day"<<endl;

    string d;

    cout<<"Today IS:";
    cin>>d;
    if(d=="MONDAY"||d=="monday"||d=="mon"||d=="MON")day=0;
    if(d=="TUESDAY"||d=="tuesday"||d=="tue"||d=="TUE")day=1;
    if(d=="WEDNESDAY"||d=="wednesday"||d=="wed"||d=="WED")day=2;
    if(d=="THRUSDAY"||d=="thrusday"||d=="thu"||d=="THU")day=3;
    if(d=="FRIDAY"||d=="friday"||d=="fri"||d=="FRI")day=4;
    if(d=="SATURDAY"||d=="saturday"||d=="sat"||d=="SAT")day=5;
    if(d=="SUNDAY"||d=="sunday"||d=="sun"||d=="SUN")day=6;

    cout<<"Opening the list of devotees with their codes written in the file devotees list in file infile and taking the attendenceand who is present is pushed into the queue general"<<endl;



        int tt[7][9];
        int slno;
        int attendence;
        string name;
        ifstream infile;
        infile.open("Devotees list.txt");
        if(!infile)
        {
            cout<<"Devotees list Not Found";
            return 1;
        }
        cout<<fixed<<showpoint;
        cout<<setprecision(1);
        infile>>slno>>name;
        cout<<"Attendence Sheet"<<endl;
        while(infile)
        {

            cout<<slno<<"    ";
            cout<<name<<":";
            cin>>attendence;
            if(attendence==1)
                general.push(slno);
            infile>>slno>>name;
        }

       cout<<"input of the timetable of the devottees who are present from the file timetable into an array and alloting them by pushing into stack and queue respectively"<<endl;


       while(1)
        {

            slot++;
            int check;

            if(general.empty())
            {
                cout<<"Queue is Empty";
                break;
            }
            else
            {
                check=general.front();
                cout<<check<<endl;
                general.pop();
                cout<<"poping out a devottee from the queue"<<endl;

                cout<<"storing the timetable of the devottee from the list into the array tt";

                int i,j;
                int c;
                ifstream infile1;
                infile1.open("Timetable.txt");
                if(!infile1)
                {
                        cout<<"Doesnot Exist";
                        return 1;
                }
                cout<<fixed<<showpoint;
                cout<<setprecision(1);
                infile1>>c;

                while(infile1)
                {
                    if(c==check)
                    {
                        infile1>>c;
                        for(i=0;i<7;i++)
                        {
                            for(j=0;j<9;j++)
                            {
                                tt[i][j]=c;
                                infile1>>c;

                            }

                        }
                        cout<<"Showing the stored timetable in tt"<<endl;
                        for(i=0;i<7;i++)
                        {
                            for(j=0;j<9;j++)
                            {
                                cout<<tt[i][j]<<"   ";

                            }
                            cout<<endl;
                        }
                        break;
                    }
                    else
                    {
                       for(i=0;i<7;i++)
                        {
                            for(j=0;j<9;j++)
                            {
                                infile1>>c;

                            }

                        }
                    }
                    infile1>>c;
                }
            }

            cout<<"Everyones todays timetable who are present is stored in a file named  Todays timetable.txt"<<endl;

            int dd,m,n;m=0;n=check;
            today<<check<<endl;
            while(m<9)
            {
                today<<tt[day][m]<<" ";
                m++;
            }
            today<<endl;

       }
       cout<<"Allotment process starts... for the day"<<endl;
       allotment();
        cop();
//        allo.close();


}
int allotment()
{

    int x=1,y=1,w=1,dev,c;
    ifstream allot;
    cout<<"opening file Todays timetable.txt";
   // allot.open("Todays Timetable.txt");
    if(!allot)
    {
        cout<<"Doesnot Exist";
        return 1;
    }
    cout<<fixed<<showpoint;
    cout<<setprecision(1);
    cout<<"loop to generate condition for checking from file todays timetable for each slot separately."<<endl;
    //allot>>c;

    while(y<=9)
    {
        cout<<"y="<<y<<endl;
        allot.open("Todays Timetable.txt");
        allot>>c;
        while(allot)
        {
            dev=c;
            cout<<"devottee:"<<c<<endl;
            while(x<=9)
            {
                allot>>c;
                cout<<c<<"  ";
                if(y==1 && x==1)
                    {cout<<"slot1:"<<c<<endl;one(dev,c);}
                if(y==2 && x==2)
                    {cout<<"slot2:"<<c<<endl;//two(dev,c);
                    }
                if(y==3 && x==3)
                    {cout<<"slot3:"<<c<<endl;//three(dev,c);
                    }
                if(y==4 && x==4)
                    {cout<<"slot4:"<<c<<endl;//four(dev,c);
                    }
                if(y==5 && x==5)
                    {cout<<"slot5:"<<c<<endl;//five(dev,c);
                    }
                if(y==6 && x==6)
                    {cout<<"slot6:"<<c<<endl;//six(dev,c);
                    }
                if(y==7 && x==7)
                    {cout<<"slot7:"<<c<<endl;//seven(dev,c);
                    }
                if(y==8 && x==8)
                    {cout<<"slot8:"<<c<<endl;//eight(dev,c);
                    }
                if(y==9 && x==9)
                    {cout<<"slot9:"<<c<<endl;//nine(dev,c);
                    }
                x++;
            }
            cout<<endl;
            x=1;
            allot>>c;
        }
        allot.close();
        y++;
    }

    return 0;
}
//checking for 8 to 8:50 and alloting for serving,reading with checking of previous allotment of the week.
void one(int dev,int c)
{
        //ofstream allo("preallot1.txt");
        if(c==1)
        {

            if(previousallot(dev,2)==0 && checktimetable(2)==0)
            {

                cout<<"yes";
              //  atlast(dev);
                previousallotupdate(dev,2);
            }
            else if(previousallot(dev,3)==0 && checktimetable(2)==0)
            {
                cout<<"yes";
               // atlast(dev);
                previousallotupdate(dev,3);
            }
            else
                cout<<"no";
                //pending.push(dev);
        }
        else
        {
            cout<<"no";
           // pending.push(dev);
        }
}
int previousallotupdate(int dev,int s)
{

    ifstream preallot("preallot.txt");
    int i,v=1;
    cout<<"Allotment starts";
    while(preallot)
    {
        preallot>>i;
        int j=i;
        int k=i;

        if(j==0)
            break;
        filll(k);
      //  allo<<i<<" ";
        cout<<i<<"-1"<<"v="<<v<<endl;
        while(v<11)
        {
            preallot>>i;
            k=i;
            filll(k);
          //  allo<<i<<" ";
            cout<<i<<"-2"<<"v="<<v<<endl;
            if(dev==j)
            {

                if(s==i)
                {
                    preallot>>i;v++;
                    k=i;
                    if(i==0)
                     {

                        filll(1);
                       // allo<<1<<" ";
                        cout<<i<<"-3"<<"v="<<v<<endl;

                     }
                    else
                     {

                        filll(1);
                      //  allo<<1<<" ";
                        cout<<i<<"-4"<<"v="<<v<<endl;

                     }

                 }
             }
            v++;
         }
        v=1;
    }
//    allo.close();
}
//1        allo<<i<<" ";
int previousallot(int dev,int s)
{
    cout<<"for service:"<<s<<endl;
    ifstream preallot("preallot.txt");
    int i,t=1;
    while(preallot>>i)
    {
        int c;
        int d;
        //preallot>>i;
        cout<<i<<endl;
        int j=i;

        while(t<=10)
        {
            preallot>>i;
            c=i;
            if(dev==j && s==i)
            {

                    preallot>>i;
                    d=i;

                    if(i==0)
                        return 0;
                    else
                        return 1;


            }
            t++;

        }
        t=1;
    }


}
void filll(int x)
{//  ofstream preallot1("preallot1.txt");
    preallot1<<x<<endl;

}
void cop()
{

//    allo.close();
//    preallot.close();
    preallot1.close();
    const static char * fn1="preallot.txt";
    const static char * fn2="preallot1.txt";
    remove(fn1);
    rename(fn2,fn1);
    ifstream preallot2("preallot1.txt");
    preallot2.close();

}
