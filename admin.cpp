#include<iostream>
#include<fstream>
#include<string>
#include<ostream>
#include <ctime>
#include<bits/stdc++.h>
#include<cstring>
#include<conio.h>
#include <limits>
#include "dirent.h"
#include "meeting.cpp"


using namespace std;


inline void taskbord(){
      system("cls");
      int c;
      char nam[200];
      ofstream infile;
      ifstream inFile;
      cout<< "Choose operation\n\n\t1.Assign a new task\n\t2.View tasks\n\t3.Exit\n\n ";
      cin>>c;
      switch(c){
      case 1:cout<<"\n\tEnter the New Tasks assigned are: \n\n";
             cin >> nam;
             infile.open("tasks.txt",std::ios::out | std::ios::in | std::ios::ate);
             infile<<nam<<endl;
             infile.close();
             taskbord();
             break;

      case 2:string firstWord;
          system("cls");

          inFile.open("tasks.txt");
          while (!inFile.eof())
              {
                 while (inFile >> firstWord)
                    {
                        cout << firstWord<<endl;
                    }
              }

          inFile.close();
          getch();
          taskbord();
          break;
      }
}


inline void requirement(){
      system("cls");
      int c;
      cout<< "Choose an operation : \n\n\t1.Add new requirements \n\t2.View requirements\n\t3.Exit\n\n ";
      cin>>c;
      ofstream infile;
      char name[200];
      ifstream inFile;
      string firstWord;
      switch(c){
      case 1:
             cout<<"\n\tEnter the New Requirement: \n\n";
             cin >> name;
             infile.open("req.txt",std::ios::out | std::ios::in | std::ios::ate);
             infile<<name<<endl;
             infile.close();
             requirement();
             break;


      case 2:
          system("cls");
          cout<<"the requirements to be met are: \n\n";
          inFile.open("req.txt");
          while (!inFile.eof())
              {
                 while (inFile >> firstWord)
                    {
                        cout << firstWord<<endl;
                    }
              }

          inFile.close();
          getch();
          requirement();
          break;

      }
}

inline int dayNumber(int day, int month, int year)
{

	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
					4, 6, 2, 4 };
	year -= month < 3;
	return ( year + year/4 - year/100 +
			year/400 + t[month-1] + day) % 7;
}


inline string getMonthName(int monthNumber)
{
	string months[] = {"none","January", "February", "March",
					"April", "May", "June",
					"July", "August", "September",
					"October", "November", "December"
					};

	return (months[monthNumber]);
}


inline int numberOfDays (int monthNumber, int year)
{
	// January
	if (monthNumber == 1)
		return (31);

	// February
	if (monthNumber == 2)
	{
		// If the year is leap then February has
		// 29 days
		if (year % 400 == 0 ||
				(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}

	// March
	if (monthNumber == 3)
		return (31);

	// April
	if (monthNumber == 4)
		return (30);

	// May
	if (monthNumber == 5)
		return (31);

	// June
	if (monthNumber == 6)
		return (30);

	// July
	if (monthNumber == 7)
		return (31);

	// August
	if (monthNumber == 8)
		return (31);

	// September
	if (monthNumber == 9)
		return (30);

	// October
	if (monthNumber == 10)
		return (31);

	// November
	if (monthNumber == 11)
		return (30);

	// December
	if (monthNumber == 12)
		return (31);
}

// Function to print the calendar of the given year
inline void printCalendar(int year)
{

    time_t ti = time(NULL);
    tm* timePtr = localtime(&ti);
	printf ("		 Calendar - %d\n\n", year);
	int days;
    int i= timePtr->tm_mon;
	// Index of the day from 0 to 6
	int current = dayNumber (1, i, year);

	days = numberOfDays (i, year);

		printf("\n\t\t   ------------%s-------------\n\n",
			getMonthName (i).c_str());

		printf("\t  Sun\t  Mon\t  Tue\t  Wed\t  Thu\t  Fri\t  Sat\n");

		int k;
		for (k = 0; k < current; k++)
			printf("	 ");

		for (int j = 1; j <= days; j++)
		{
			printf("\t%5d", j);

			if (++k > 6)
			{
				k = 0;
				printf("\n");
			}
		}

		if (k)
			printf("\n");

		current = k;
}

inline void printcalendar(int year)
{
	printf ("		 Calendar - %d\n\n", year);
	int days,i;
	cout<<"Enter the month of your choice :\n";
	cin>>i;
	int current = dayNumber (1, i, year);

	days = numberOfDays (i, year);

		printf("\n\t\t  ------------%s-------------\n\n",getMonthName(i).c_str());

		// Print the columns
		printf("\t  Sun\t  Mon\t  Tue\t  Wed\t  Thu\t  Fri\t  Sat\n");

		// Print appropriate spaces
		int k;
		for (k = 0; k < current; k++)
			printf("	 ");

		for (int j = 1; j <= days; j++)
		{
			printf("\t%5d", j);

			if (++k > 6)
			{
				k = 0;
				printf("\n");
			}
		}

		if (k)
			printf("\n");

		current = k;
}

inline void resources(){
    DIR *dir;
struct dirent *ent;
if ((dir = opendir ("C:\\Users\\TEJASWINI\\Documents\\ST LAB\\fsmini\\resources")) != NULL) {
  while ((ent = readdir (dir)) != NULL) {
    printf ("%s\n", ent->d_name);
  }
  closedir (dir);
} else {
  perror ("");
}
}

inline int calendar()
{
    time_t ti = time(NULL);
    tm* timePtr = localtime(&ti);
    int x,month;
	int year = timePtr->tm_year;
	printCalendar(year);

	cout<<"\n\n\n\t\tDo you wish to choose a different month?\n\t\t1.Y \n\t\t2.N \n\n";
	cin>>x;
	switch(x){
	   case 1:system("cls");
	          printcalendar(year);
	          getch();
	          break;
	   case 2:system("cls");
	          printCalendar(year);
	          getch();
	          break;
	        	}
}


inline void account(){
        ofstream fout;
        char user[100];
        char pass[100];

        fout.open("database.txt", std::ios::in | std::ios::out | std::ios::ate);

        cout<<"\n\t\tEnter Username :\n";
        cin>>user;
        cout<<"\n\t\tEnter Password :\n";
        cin>>pass;

        fout<<user<<" "<<pass<<endl;
        cout<<"\n\t\tAccount created successfully..!!\n";
        fout.close();
}


inline void acc(){
   system("cls");
   int y;
   string firstName;
   string firstWord;
   string fullName;
   ifstream inFile;
   cout<<"\n\t\t 1. Admin";
   cout<<"\n\t\t2. Developers\n";
    cout<<"\n\n\t\t Enter your choice : ";
   cin>>y;
   switch(y) {
      case 1:
          system("cls");
          inFile.open("data.txt");
          while (!inFile.eof())
              {
                 while (inFile >> firstWord)
                    {
                        cout << firstWord << endl;
                        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
                 }
              }
          inFile.close();
          getch();
          break;
      case 2:
          system("cls");

          inFile.open("database.txt");
          while (!inFile.eof())
              {
                 while (inFile >> firstWord)
                    {
                        cout << firstWord << endl;
                        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
              }

          inFile.close();
          getch();
          break;
   }
}

inline void del(){
    ifstream fin;
    string firstName;
    string firstWord;
    int n;
          fin.open("database.txt");
          while (!fin.eof())
              {
                 while (fin >> firstWord)
                    {
                        cout << firstWord << endl;
                        fin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
              }

          fin.close();
          fin.open("database.txt");
          ofstream ofs;
    ofs.open("temp.txt", ofstream::out);

    char c;
    int line_no = 1;
    cout<< "\n\n\t\t Enter the Account to be Deleted : ";
    cin >>n;
    while (fin.get(c))
    {
        if (c == '\n')
        line_no++;

        if (line_no != n)
            ofs << c;
    }

    ofs.close();
    fin.close();
    remove("database.txt");
    rename("temp.txt","database.txt");
    cout<<"\n\t\tDelete successful";

}

inline void dashboard(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("C:\\Users\\TEJASWINI\\Documents\\ST LAB\\fsmini\\resources")) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
                printf ("%s\n", ent->d_name);
    }
      closedir (dir);
      }
      else
        {
            perror ("");
        }
}

inline int credentials()
{
    system("cls");
    int x;
    int flag;
    cout << "\n\t\t1.Create a new Account\n\t\t2. View Accounts\n\t\t3. Delete Account\n\t\t4. Exit\n";
    cout<<"\n\n\t\t Enter your choice : ";
    cin >> x;
    switch (x) {
          case 1:  cout<<"Creating a new account";
                   system("cls");
                   account();
                   credentials();
                   break;
          case 2:  system("cls");
                   acc();
                   credentials();
                   break;
          case 3:  system("cls");
                   del();
                   credentials();
                   break;
          case 4:  system("cls");
                   break;
        }
}


inline void discusion()
{
    while(true){
   string line;
   ifstream infile ("chat.txt");
   system("cls");
              cout<<"\t\t\t\t**********************************************************"<<endl;
              cout<<"\t\t\t\t*                                                        *"<<endl;
              cout<<"\t\t\t\t*                       Discussion                       *"<<endl;
              cout<<"\t\t\t\t*                                                        *"<<endl;
              cout<<"\t\t\t\t**********************************************************\n\n\n"<<endl;

  if (infile.is_open())
  {
    while (! infile.eof() )
    {
      getline (infile,line);
      cout << line << endl;
    }
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    infile.close();
  }
       ofstream fout;
      char data[2000];
      fout.open("chat.txt", std::ios::in | std::ios::out | std::ios::ate);
      cin >> data;
      fout<<"Teju"<<" : "<<data<<endl;
      fout.close();
 }
}



inline void actions(){
    int x;
    cout<<"\t\t\t\t**********************************************************"<<endl;
    cout<<"\t\t\t\t*                                                        *"<<endl;
    cout<<"\t\t\t\t*                Logged in as Admin                      *"<<endl;
    cout<<"\t\t\t\t*                                                        *"<<endl;
    cout<<"\t\t\t\t**********************************************************"<<endl;
    cout << "\n\n\n\t\t1.Calendar\n\t\t2.Meeting Schedule\n\t\t3.Dashboard\n\t\t4.Taskboard\n\t\t5.Requirement Analysis\n\t\t6.Discussion\n\t\t7.Credentials\n\t\t8.Exit\n";
    cout<<"\n\n\t\tEnter your choice : ";
    cin >> x;
    switch (x) {
          case 1:
              system("cls");
              calendar();
              system("cls");
              actions();
              break;
          case 2:
              system("cls");
              meeting();
              getch();
              actions();
              break;
          case 3:
              system("cls");
              dashboard();
              getch();
              system("cls");
              actions();
              break;
          case 4:
              system("cls");
              taskbord();
              system("cls");
              actions();
              break;
          case 5:
              system("cls");
              requirement();
              system("cls");
              actions();
              break;
          case 6:
              system("cls");
              discusion();
              system("cls");
              actions();
              break;
          case 7:
              system("cls");
              credentials();
              system("cls");
              actions();
              break;

     }
}

