#include<iostream>
#include<cstdio>
#include<fstream>
#include<iomanip>
#include<string>
#include<stack>
#include<queue>
using namespace std;
void allotment();
void one(int,int);
void two(int,int);
int previousallot(int,int);
void filll(int);
int previousallotupdate(int,int);
void cop();
void allotone();
void allottwo();
queue<int> general;
stack<int> available;
stack<int> pending;
stack<int> stackone;
stack<int> stacktwo;
int day;
int s[6][3];
int noofdev=0;
int noofser=0;
int demoser[0][0];
/*
1.offering    [0][0]  1   [0][1]  1   [0][2]
2.serving     [1][0]  1   [1][1]  1   [1][2]
3.reading     [2][0]  1   [2][1]  1   [2][2]
4.mopping     [3][0]  1   [3][1]  1   [3][2]
5.vessel      [4][0]  1   [4][1]  1   [4][2]
6.vessel      [5][0]  1   [5][1]  1   [5][2]
*/
ofstream preallot1("preallot1.txt");
int main()
{
//**********************************OPERATION 1******************************************************

        int z,w;
        for(z=1;z<=6;z++)
        {
            for(w=1;w<=3;w++)
            {
                s[z][w]=0;
            }
        }

        ofstream today("Todays Timetable.txt");
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
        noofser=15;
        int tt[7][9];
//***************************************************************************************************
/*--------------------------------------------OPERATION 2 STARTS----------------------------------------------------------------*/
/*OPERATION 1:  a.Read te file devottee list until end.
                b.Take input the attendence push into a queue general.*/
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
            noofdev++;
        }
        demoser[noofdev][noofser];
        int j=0,i=0;
        for(j=1;j<=noofdev;j++)
        {
            for(i=1;i<=noofser;i++)
            {
                demoser[i][j]=0;
            }
        }
/*-----------------------------------------------OPERATION 2 END--------------------------------------------------------------*/

//------------------------------------------------------------------------------------------------------------------------------

/*------------------------------------------------OPERATION 3 STARTS-----------------------------------------------------------*/

        int slot=0;
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

            int dd,m,n;m=0;n=check;
            today<<check<<endl;
            while(m<9)
            {
                today<<tt[day][m]<<" ";
                m++;
            }
            today<<endl;

        }
}
/*-----------------------------------------------OPERATION 3 ENDS-------------------------------------------------------------*/

//-----------------------------------------------------------------------------------------------------------------------------

/*-----------------------------------------------OPERATION 4 STARTS------------------------------------------------------------*/
       cout<<"Allotment process starts... for the day"<<endl;
       allotment();
//mon
       // cop();
        /*for(z=1;z<=6;z++)
        {
            for(w=1;w<=3;w++)
            {
                cout<<s[z][w]<<"    ";
            }
            cout<<endl;
        }*/

        for(j=1;j<=noofdev;j++)
        {
            for(i=1;i<=noofser;i++)
            {
                cout<<demoser[i][j]<<"  ";
            }
            cout<<endl;
        }

}




void allotment()
{


    int x=1,y=1,w=1,dev,c;
    /*------------------------------------------------OPERATION 3.1------------------------------------------------------------*/
    //--------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------
    ifstream allot;
 //   cout<<"opening file Todays timetable.txt";
    allot.open("Todays Timetable.txt");
    if(!allot)
    {
        cout<<"Doesnot Exist";
        return;
    }
    cout<<fixed<<showpoint;
    cout<<setprecision(1);
   // cout<<"loop to generate condition for checking from file todays timetable for each slot separately."<<endl;
    //allot>>c;

    while(y<=9)
    {
        //cout<<"\ny="<<y<<endl;
        //allot.open("Todays Timetable.txt");
        allot>>c;
        if(!allot)
        {
            cout<<"Todays Timetable.txt Doesnot Exist";
            return;
        }
        while(allot)
        {
            dev=c;
            //cout<<"\ndevottee:"<<c<<endl;
            while(x<=9)
            {
                allot>>c;

                if(y==1 && x==1)
                    {
                        if(c==0)
                            stackone.push(dev);
                    }
                if(y==2 && x==2)
                    {
                       // if(c==0)
                        //    stacktwo.push(dev);
                    }
                if(y==3 && x==3)
                    {
                       // cout<<"slot3:"<<c<<endl;//three(dev,c);
                    }
                if(y==4 && x==4)
                    {
                        //cout<<"slot4:"<<c<<endl;//four(dev,c);
                    }
                if(y==5 && x==5)
                    {
                        //cout<<"slot5:"<<c<<endl;//five(dev,c);
                    }
                if(y==6 && x==6)
                    {
                        //cout<<"slot6:"<<c<<endl;//six(dev,c);
                    }
                if(y==7 && x==7)
                    {
                        //cout<<"slot7:"<<c<<endl;//seven(dev,c);
                    }
                if(y==8 && x==8)
                    {
                        //cout<<"slot8:"<<c<<endl;//eight(dev,c);
                    }
                if(y==9 && x==9)
                    {
                        //cout<<"slot9:"<<c<<endl;//nine(dev,c);
                    }
                x++;
            }

            //cout<<endl;
            x=1;
            allot>>c;
        }
        allot.close();
        if(y==1)
         {
             allotone();
             //cop();
         }
        /*if(y==2)
          {
              allottwo();
          }*/
        y++;

    }
    /*------------------------------------------------------OPERATION 3 ENDS-----------------------------------------------------*/
    //---------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------------------
    y=1;
    return;

}


void allotone()
{
    int dd;
    if(stackone.empty())
        return;
    while(!stackone.empty())
    {
        dd=stackone.top();
        stackone.pop();

                demoser[3][dd]=demoser[3][dd]+1;
                demoser[4][dd]=demoser[4][dd]+1;
        if(previousallot(dd,3)==0)
                demoser[3][dd]=demoser[3][dd]+1;
        if(previousallot(dd,4)==0)
                demoser[4][dd]=demoser[4][dd]+1;

    }
}
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



