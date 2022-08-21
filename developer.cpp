#include<iostream>
#include<fstream>
#include<conio.h>
#include <ctime>
#include<bits/stdc++.h>
#include "dirent.h"

#include "meetings.cpp"


using namespace std;


inline void taskboard(){
      system("cls");
      int c;
      char nam[200];
      ofstream infile;
      ifstream inFile;
      cout<< "Choose operation\n\n 1.Assign a new task\n 2.View tasks\n 3.Exit\n\n ";
      cin>>c;
      switch(c){
      case 1:cout<<"\nEnter the New Tasks assigned are: \n\n";
             cin >> nam;
             infile.open("tasks.txt",std::ios::out | std::ios::in | std::ios::ate);
             infile<<nam<<endl;
             infile.close();
             taskboard();
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
          taskboard();
          break;
      }

}

     inline void requiremen(){
      system("cls");
      ifstream inFile;
      string firstWord;
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
          requiremen();

}

inline void discussion()
{
    while(true){
   string line;
   ifstream infile ("chat.txt");
   system("cls");
              cout<<"\t\t\t**********************************************************"<<endl;
              cout<<"\t\t\t*                                                        *"<<endl;
              cout<<"\t\t\t*                       Discussion                       *"<<endl;
              cout<<"\t\t\t*                                                        *"<<endl;
              cout<<"\t\t\t**********************************************************\n\n\n"<<endl;

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
        fout<<"Abhi"<<" : "<<data<<endl;
        fout.close();
    }
}

inline void dasboard(){
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



inline void resourc(){
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
int c;
printf("\n\n\nChoose an operation to be performed\n\t1.Open a file\n\t2.Create a file\n\t3.Delete a file\n\t4. Exit\n\n ");
scanf("%d",&c);
switch (c){
    case 1:fstream file;
    file.open(".txt",ios::out);
}
}

inline int daNumber(int day, int month, int year)
{

	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
					4, 6, 2, 4 };
	year -= month < 3;
	return ( year + year/4 - year/100 +
			year/400 + t[month-1] + day) % 7;
}


inline string getMontName(int montNumber)
{
	string months[] = {"none","January", "February", "March",
					"April", "May", "June",
					"July", "August", "September",
					"October", "November", "December"
					};

	return (months[montNumber]);
}


inline int numberODays (int montNumber, int year)
{
	if (montNumber == 1)
		return (31);

	if (montNumber == 2)
	{
		if (year % 400 == 0 ||
				(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}

	// March
	if (montNumber == 3)
		return (31);

	// April
	if (montNumber == 4)
		return (30);

	// May
	if (montNumber == 5)
		return (31);

	// June
	if (montNumber == 6)
		return (30);

	// July
	if (montNumber == 7)
		return (31);

	// August
	if (montNumber == 8)
		return (31);

	// September
	if (montNumber == 9)
		return (30);

	// October
	if (montNumber == 10)
		return (31);

	// November
	if (montNumber == 11)
		return (30);

	// December
	if (montNumber == 12)
		return (31);
}

// Function to print the calendar of the given year
inline void printClendar(int year)
{

    time_t ti = time(NULL);
    tm* timePt = localtime(&ti);
	printf ("		 Calendar - %d\n\n", year);
	int days;
    int i= timePt->tm_mon;
	// Index of the day from 0 to 6
    int current = daNumber (1, i, year);

	// i --> Iterate through all the months
	// j --> Iterate through all the days of the
	//	 month - i
	days = numberODays (i, year);

		// Print the current month name
		printf("\n\t\t  ------------%s-------------\n\n",getMontName (i).c_str());

		// Print the columns
		printf(" \t  Sun\t  Mon\t  Tue\t  Wed\t  Thu\t  Fri\t  Sat\n");

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

inline void printclendar(int year)
{
	printf ("\n	 Calendar - %d\n\n", year);
	int days,i;
	cout<<"\t\tEnter the month of your choice :\n";
	cin>>i;
    // Index of the day from 0 to 6
	int current = daNumber (1, i, year);

	// i --> Iterate through all the months
	// j --> Iterate through all the days of the
	//	 month - i
	days = numberODays (i, year);

		// Print the current month name
		printf("\n\t\t  ------------%s-------------\n\n",getMontName (i).c_str());

		// Print the columns
		printf(" \t  Sun\t  Mon\t  Tue\t  Wed\t  Thu\t  Fri\t  Sat\n");

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

// Driver Program to check above functions
inline int clendar()
{

    time_t ti = time(NULL);
    tm* timePt = localtime(&ti);
    int x,month;
	int year = timePt->tm_year;
	printClendar(year);

	cout<<"\n\n\t\tDo you wish to choose a different month?\n\t1.Y \n\t2.N \n\n";
	cin>>x;
	switch(x){
	   case 1:system("cls");
	          printclendar(year);
	          getch();
	          break;
	   case 2:system("cls");
	          printClendar(year);
	          getch();
	          break;
	        	}
}

inline void action()
{
    int x;
    cout<<"\t\t\t\t**********************************************************"<<endl;
    cout<<"\t\t\t\t*                                                        *"<<endl;
    cout<<"\t\t\t\t*                Logged in as Developer                  *"<<endl;
    cout<<"\t\t\t\t*                                                        *"<<endl;
    cout<<"\t\t\t\t**********************************************************"<<endl;
    cout << "\n\n\n\t\t1.Calendar\n\t\t2.Meeting Schedule\n\t\t3.Dashboard\n\t\t4.Taskboard\n\t\t5.Requirement Analysis\n\t\t6.Discussion\n\t\t7.Credentials\n\t\t8.Exit\n";
    cout<<"\n\n\t\tEnter your choice : ";
    cin >> x;
    switch (x) {
          case 1:
              system("cls");
              clendar();
              system("cls");
              action();
              break;
          case 2:
              system("cls");
              meting();
              system("cls");
              action();
              break;
          case 3:
              system("cls");
              dasboard();
              getch();
              system("cls");
              action();
              break;
          case 4:
              system("cls");
              taskboard();
              system("cls");
              action();
              break;
          case 5:
              system("cls");
              requiremen();
              system("cls");
              action();
              break;
          case 6:
              system("cls");
              discussion();
              system("cls");
              action();
              break;

    }
}
