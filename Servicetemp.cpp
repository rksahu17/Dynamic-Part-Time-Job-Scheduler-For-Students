#include<iostream>
#include<cstdio>
#include<fstream>
#include<iomanip>
#include<string>
#include<stack>
#include<queue>
using namespace std;
int allotment();
void one(int,int);
void two(int,int);
int previousallot(int,int);
void filll(int);
int previousallotupdate(int,int);
void cop();
int isalloted(int);
void allotone();
void allottwo();
queue<int> general;
stack<int> available;
stack<int> pending;
stack<int> afternoon;
stack<int> night;
stack<int> stackone;
stack<int> stacktwo;
queue<int> alloteddev;
int day;
int fallot[5][3];
int offering[3];
int serving[3];
int reading[2];
int mopping[3];
int vessel[4];
int s[6][3];
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

    int z,w;
    for(z=1;z<=6;z++)
    {
        for(w=1;w<=3;w++)
        {
            s[z][w]=0;
        }
    }
    int slot=0;

    int dev[15];
//    allo.clear();
    ofstream today("Todays Timetable.txt");
    //cout<<"INPUT OF DAY into d and storing the day code in day"<<endl;

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

    //cout<<"Opening the list of devotees with their codes written in the file devotees list in file infile and taking the attendenceand who is present is pushed into the queue general"<<endl;



        int tt[7][9];
//-------------------------------------------------------------------------------------------------------------------------------

/*--------------------------------------------OPERATION 1 STARTS----------------------------------------------------------------*/
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
        }
/*-----------------------------------------------OPERATION 1 END--------------------------------------------------------------*/

//------------------------------------------------------------------------------------------------------------------------------

/*------------------------------------------------OPERATION 2 STARTS-----------------------------------------------------------*/
      // cout<<"input of the timetable of the devottees who are present from the file timetable into an array and alloting them by pushing into stack and queue respectively"<<endl;


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
        //        cout<<"poping out a devottee from the queue"<<endl;

          //      cout<<"storing the timetable of the devottee from the list into the array tt";

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
            //            cout<<"Showing the stored timetable in tt"<<endl;
              /*          for(i=0;i<7;i++)
                        {
                            for(j=0;j<9;j++)
                            {
                                cout<<tt[i][j]<<"   ";

                            }
                            cout<<endl;
                        }*/
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

           // cout<<"Everyones todays timetable who are present is stored in a file named  Todays timetable.txt"<<endl;

            int dd,m,n;m=0;n=check;
            today<<check<<endl;
            while(m<9)
            {
                today<<tt[day][m]<<" ";
                m++;
            }
            today<<endl;

       }

/*-----------------------------------------------OPERATION 2 ENDS-------------------------------------------------------------*/

//-----------------------------------------------------------------------------------------------------------------------------

/*-----------------------------------------------OPERATION 3 STARTS------------------------------------------------------------*/
       cout<<"Allotment process starts... for the day"<<endl;
       allotment();
//mon
        cop();
        for(z=1;z<=6;z++)
        {
            for(w=1;w<=3;w++)
            {
                cout<<s[z][w]<<"    ";
            }
            cout<<endl;
        }



}
int allotment()
{
    cout<<"\n*********************************************************CHECK FROM HERE\n";

    int x=1,y=1,w=1,dev,c;
    /*------------------------------------------------OPERATION 3.1------------------------------------------------------------*/
    //--------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------
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
        cout<<"\ny="<<y<<endl;
        allot.open("Todays Timetable.txt");
        allot>>c;
        if(!allot)
        {
            cout<<"Doesnot Exist";
            return 1;
        }
        while(allot)
        {
            dev=c;
            cout<<"\ndevottee:"<<c<<endl;
            while(x<=9)
            {
                allot>>c;
                //cout<<c<<"  ";
                if(y==1 && x==1)
                    {
                        cout<<"slot1:"<<c<<endl;
                        cout<<"\nCALLING ONE FOR DEVOTEE:"<<dev;
                        //--------------------------------------------------------------OPERATION 3.2-------------------------
                        one(dev,c);
                    }
                if(y==2 && x==2)
                    {
                        cout<<"ENTERED\n";

                        cout<<"slot2:"<<c<<endl;
                        cout<<"\nCALLING ONE FOR DEVOTEE:"<<dev;
                        two(dev,c);

                    }
            /* if(y==3 && x==3)
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
                    }*/
                x++;
            }

            cout<<endl;
            x=1;
            allot>>c;
        }
        allot.close();
        if(y==1)
         {
             allotone();
             //cop();
         }
        if(y==2)
          {
              allottwo();
          }
        y++;
    }

    /*------------------------------------------------------OPERATION 3 ENDS-----------------------------------------------------*/
    //---------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------------------
    y=1;
/*while(y<=9)
  {
        if(y==1)
            {
                cout<<"\nSTACKONE SHOWING\n";
                while(stackone.empty())
                {
                    cout<<stackone.top()<<endl;
                    stackone.pop();
                }
                cout<<"\nCALLING ALLOTONE";
                allotone();
            }
            y++;
  }
*/
    return 0;
}
//checking for 8 to 8:50 and alloting for serving,reading with checking of previous allotment of the week.
void one(int dev,int c)
{
        cout<<"\ENTERED FUNC ONE FOR DEVOTEE:"<<dev;
        //ofstream allo("preallot1.txt");
        if(c==0)
        {       cout<<"\nCALLING ISALLOT FOR CHECKING DEV IS ALLOTED PREV OR NOT\n";
                if(isalloted(dev)==0)
                {
                    cout<<"\nYES THE DEVOTEE IS FREE:"<<dev;
                    cout<<"\nPUSHING into StackOne:"<<dev<<endl;
                    stackone.push(dev);
                    cout<<"\n######## showing the devotee is PUSHED into stackone: "<<stackone.top();
                }
        }
        else
        {
            cout<<"\nPUSHING INTO PENDING AS THE DEVOTEE IS NOT FREE"<<dev;
            pending.push(dev);
            cout<<"\n##### showing the devotee is pushed into pending:"<<pending.top();
        }
}
int isalloted(int dev)
{
    int z,w,m=0;
    int devx;int o=1;
    stack<int> temp;int q=0;
    cout<<"\nENTERED INTO ISALLOTED";
        for(z=1;z<=6;z++)
        {
            for(w=1;w<=3;w++)
            {
                if(s[z][w]==dev)
                    m=1;

            }

        }

    if(alloteddev.empty())
        return 0;
    int dx=999;
    while(dx!=devx)
    {

        devx=alloteddev.front();
         cout<<"\nalloteddev"<<devx<<endl;
        if(o==1)
            dx=devx;
        alloteddev.pop();
        if(dev!=devx)
        {
            alloteddev.push(devx);
        }
        else
        {
            q=1;

        }
    }
    if(q==1 && m==0)
        return 0;
    else
        return 1;

}
void allotone()
{
    cout<<"\n********************Entered allotone***********************************\n";
    /*while(!stackone.empty())
    {
        cout<<stackone.top()<<endl;
        stackone.pop();
    }*/
    int dd;
    stack<int> temp;
    stack<int> temp1;

    //cout<<stackone.top();
    if(stackone.empty())
        return;
    while(!stackone.empty())
    {
        dd=stackone.top();
        cout<<"\n********************************************ENTERED WHILE for devotee   "<<dd<<endl;
        //cout<<dd<<endl;
        //temp.push(dd);
        stackone.pop();
        cout<<"\n###### BEFORE CONDITION ######\n";
        cout<<"\n###### previousalloted #######"<<previousallot(dd,2)<<endl;
        cout<<"\n###### ALLOTED TODAY #######"<<isalloted(dd)<<endl;
        if(s[2][1]==0)
        {
            if(previousallot(dd,2)==0 && isalloted(dd)==0)
            {
                if(previousallot(dd,2)==0)
                cout<<"\n###### NOT previousalloted"<<endl;
                if(isalloted(dd)==0)
                cout<<"\n###### NOT ALLOTED TODAY"<<endl;
                s[2][1]=dd;
                previousallotupdate(dd,2);
                alloteddev.push(dd);
                temp.push(dd);
            }
            else
                temp.push(dd);

        }
        else
        {
            temp.push(dd);
        }
    }
    //cout<<"!!!!!!!!!!!!!!!!!!!\n";
   /* while(!temp.empty())
    {
        cout<<temp.top()<<endl;
        temp.pop();
    }*/
    while(!temp.empty())
    {
        int k=temp.top();
        stackone.push(k);
        temp.pop();
    }
    //cout<<"!!!!!!!!!!!!!!!!!!!\n";
    /*while(!stackone.empty())
    {
        cout<<stackone.top()<<endl;
        stackone.pop();
    }*/
    while(!stackone.empty())
    {
        dd=stackone.top();
        cout<<"\n********************************************ENTERED WHILE for devotee   "<<dd<<endl;

        stackone.pop();
        cout<<"\n###### BEFORE CONDITION ######\n";
        cout<<"\n###### previousalloted #######"<<previousallot(dd,3)<<endl;
        cout<<"\n###### ALLOTED TODAY #######"<<isalloted(dd)<<endl;

        if(s[3][1]==0)
        {
            if(previousallot(dd,3)==0 && isalloted(dd)==0)
            {
                if(dd!=s[2][1])
                {
                    s[3][1]=dd;
                    previousallotupdate(dd,3);
                    alloteddev.push(dd);
                    temp.push(dd);
                }

            }
            else
            {
                    temp.push(dd);
            }

        }
        else
        {
            temp.push(dd);
        }
    }
    while(!temp.empty())
    {
        int k=temp.top();
        stackone.push(k);
        temp.pop();
    }

}
void two(int dev,int c)
{
        cout<<"\ENTERED FUNC ONE FOR DEVOTEE:"<<dev;
        //ofstream allo("preallot1.txt");
        if(c==0)
        {       cout<<"\nCALLING ISALLOT FOR CHECKING DEV IS ALLOTED PREV OR NOT\n";
                if(isalloted(dev)==0)
                {
                    cout<<"\nYES THE DEVOTEE IS FREE:"<<dev;
                    cout<<"\nPUSHING into StackOne:"<<dev<<endl;
                    stacktwo.push(dev);
                    cout<<"\n######## showing the devotee is PUSHED into stackone: "<<stackone.top();
                }
        }
        else
        {
            cout<<"\nPUSHING INTO PENDING AS THE DEVOTEE IS NOT FREE"<<dev;
            pending.push(dev);
            cout<<"\n##### showing the devotee is pushed into pending:"<<pending.top();
        }
}
void allottwo()
{
    cout<<"\n********************Entered allotone***********************************\n";
    /*while(!stackone.empty())
    {
        cout<<stackone.top()<<endl;
        stackone.pop();
    }*/
    int dd;
    stack<int> temp;
    stack<int> temp1;

    //cout<<stackone.top();
    if(stacktwo.empty())
        return;
    while(!stacktwo.empty())
    {
        dd=stacktwo.top();
        cout<<"\n********************************************ENTERED WHILE for devotee   "<<dd<<endl;
        //cout<<dd<<endl;
        //temp.push(dd);
        stacktwo.pop();
        cout<<"\n###### BEFORE CONDITION ######\n";
        cout<<"\n###### previousalloted #######"<<previousallot(dd,4)<<endl;
        cout<<"\n###### ALLOTED TODAY #######"<<isalloted(dd)<<endl;
        if(s[4][1]==0)
        {
            if(previousallot(dd,4)==0 && isalloted(dd)==0)
            {
                if(previousallot(dd,4)==0)
                cout<<"\n###### NOT previousalloted"<<endl;
                if(isalloted(dd)==0)
                cout<<"\n###### NOT ALLOTED TODAY"<<endl;

                    s[4][1]=dd;
                    previousallotupdate(dd,4);
                    alloteddev.push(dd);
                    temp.push(dd);

            }
            else
                temp.push(dd);

        }
        else
        {
            temp.push(dd);
        }
    }
    //cout<<"!!!!!!!!!!!!!!!!!!!\n";
   /* while(!temp.empty())
    {
        cout<<temp.top()<<endl;
        temp.pop();
    }*/
    while(!temp.empty())
    {
        int k=temp.top();
        stacktwo.push(k);
        temp.pop();
    }
    //cout<<"!!!!!!!!!!!!!!!!!!!\n";
    /*while(!stackone.empty())
    {
        cout<<stackone.top()<<endl;
        stackone.pop();
    }*/
    while(!stacktwo.empty())
    {
        dd=stacktwo.top();
        cout<<"\n********************************************ENTERED WHILE for devotee   "<<dd<<endl;

        stacktwo.pop();
        cout<<"\n###### BEFORE CONDITION ######\n";
        cout<<"\n###### previousalloted #######"<<previousallot(dd,5)<<endl;
        cout<<"\n###### ALLOTED TODAY #######"<<isalloted(dd)<<endl;

        if(s[5][1]==0)
        {
            if(previousallot(dd,5)==0 && isalloted(dd)==0)
            {
                if(dd!=s[4][1])
                {
                    s[5][1]=dd;
                    previousallotupdate(dd,5);
                    alloteddev.push(dd);
                    temp.push(dd);
                }
            }
            else
            {
                    temp.push(dd);
            }

        }
        else
        {
            temp.push(dd);
        }
    }
    while(!temp.empty())
    {
        int k=temp.top();
        stacktwo.push(k);
        temp.pop();
    }

}

int previousallotupdate(int dev,int s)
{

    ifstream preallot("preallot.txt");
    int i,v=1;
    //cout<<"Allotment starts";
    while(preallot)
    {
        preallot>>i;
        int j=i;
        int k=i;

        if(j==0)
            break;
        filll(k);
      //  allo<<i<<" ";
     //   cout<<i<<"-1"<<"v="<<v<<endl;
        while(v<11)
        {
            preallot>>i;
            k=i;
            filll(k);
          //  allo<<i<<" ";
        //    cout<<i<<"-2"<<"v="<<v<<endl;
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
             //           cout<<i<<"-3"<<"v="<<v<<endl;

                     }
                    else
                     {

                        filll(1);
                      //  allo<<1<<" ";
                //        cout<<i<<"-4"<<"v="<<v<<endl;

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
