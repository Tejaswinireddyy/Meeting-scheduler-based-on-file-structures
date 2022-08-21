#include<iostream>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<unistd.h>
#include <conio.h>
#include <stdlib.h>
#include"admin.cpp"
#include"developer.cpp"

using namespace std;



int main()
{
        int count,i=0;
        string user,u,p,l;
        char ch;
        char pass[30];
        cout<<"\t\t\t\t**********************************************************"<<endl;
        cout<<"\t\t\t\t*                                                        *"<<endl;
        cout<<"\t\t\t\t*                Welcome To V-Meet                       *"<<endl;
        cout<<"\t\t\t\t*                                                        *"<<endl;
        cout<<"\t\t\t\t**********************************************************"<<endl;
        cout<<"\n\n\n\n\t\tUSERNAME :";
        cin>>user;
        cout<<"\n\n\t\tPASSWORD :";
        while((ch= _getch())!=13)
        {
            pass[i]=ch;
            i++;
            printf("*");
        }
        pass[i]='\0';
        system("cls");
        ifstream input1;
        input1.open("database.txt");
        while(input1>>u>>p)
        {
                if(u==user && p==pass)

                {
                        count=1;
                        system("cls");
                }
        }
        if(count !=1){
             input1.close();
             input1.open("data.txt");
             while(input1>>u>>p)
             {
                if(u==user && p==pass)
                {
                        count=2;
                        system("cls");
                }
                input1.close();
             }
          }

        if(count==1)
        {
            ofstream fout;
            fout.open("logs.txt", std::ios::in | std::ios::out | std::ios::ate);
            fout<<user<<endl;
            fout.close();
            action();
            system("cls");
            main();
        }

        else if(count==2)
        {
            ofstream fout;
            fout.open("logs.txt", std::ios::in | std::ios::out | std::ios::ate);
            fout<<user<<endl;
            fout.close();

            actions();
            system("cls");
            main();
        }

        else
        {
            cout<<"\n\nLOGIN ERROR\nPlease check your username and password\n\n\n";
            main();
        }
}

