#include<iostream>
#include<fstream>

using namespace std;

inline void discussion()
{
    while(true){
   string line;
   ifstream infile ("chat.txt");
   system("cls");
              cout<<"**********************************************************"<<endl;
              cout<<"*                                                        *"<<endl;
              cout<<"*                       Discussion                       *"<<endl;
              cout<<"*                                                        *"<<endl;
              cout<<"**********************************************************\n\n\n"<<endl;

  if (infile.is_open())
  {
    while (! infile.eof() )
    {
      getline (infile,line);
      cout << line << endl;
    }
    infile.close();
  }
        ofstream fout;
        char data[2000];
        fout.open("chat.txt", std::ios::in | std::ios::out | std::ios::ate);
        cin >> data;
        fout<<" : "<<data<<endl;
        fout.close();
    }
}
