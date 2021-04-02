#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include <mutex>
#include <chrono> 
#include <conio.h>

using namespace std;
mutex mtx;

struct rules
{
    string state;
    char symbol;
    char newsymbol;
    char direction;
    string newstate;
};

void cls(int y) {
    COORD coord;
    coord.X = 0;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void start(string txt, int y) {
    /////INPUT//////////////////////////////////////////////
    rules taisykles[100];
    int head(0);
    string tape;
    int lineCount(0);

    fstream fd(txt.c_str());
    if (!fd)
    {
        cout << "File not found.";
        exit(EXIT_FAILURE);
    }
    else
    {
        fd >> tape;
        fd >> head;
 
        while (!fd.eof())
        {
            fd >> taisykles[lineCount].state;
            fd >> taisykles[lineCount].symbol;
            fd >> taisykles[lineCount].newsymbol;
            fd >> taisykles[lineCount].direction;
            fd >> taisykles[lineCount].newstate;
            lineCount++;
            if (fd.eof())
            {
            fd.close();
            }
        }     
    }
    /////START//////////////////////////////////////////////
    bool test = true;
    string state = "0";
    head--;
    while (test == true)
    {
        mtx.lock();
        cls(y);
        cout << tape << endl;
        Sleep(2);
        mtx.unlock();
        
        for (int i(0); i < lineCount; i++)
        {
            if (taisykles[i].state == state && taisykles[i].symbol == tape[head])
            {
                tape[head] = taisykles[i].newsymbol;
                state = taisykles[i].newstate;
                if (taisykles[i].direction == 'R')
                {
                    head++;
                    break;
                }
                else
                {
                    head--;
                    if (head < 0)
                    {
                        test = false;
                    }
                    break;
                }
                
            }

        }
        int temp(0);
        for (int i(0); i < lineCount; i++)
        {
            if (taisykles[i].state == state)
            {
                temp++;
            }
        }
        if (temp < 1 || _kbhit()) 
        {
            test = false;     
            COORD coord;
            coord.X = 0;
            coord.Y = 8;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
    }
}



int main()
{ 
    string txt1, txt2, txt3, txt4;
    int y1(0), y2(2), y3(4), y4(6);
    int choice;
    bool tmOn = true;
    system("CLS");
    while (tmOn)
    {

       cout << "----------------------------------------------TURING MACHINE SIMULIATOR----------------------------------------------" << endl<<endl
            << "                                       >>>Press any key to stop the machine<<<" << endl << endl
            << " --------------MENU---------------"<< endl << endl
            << " 1 - Start 1 turing machine." << endl
            << " 2 - Start 4 turing machines." << endl
            << " 3 - Exit." << endl
            << "Enter your selection and press ENTER: ";
        cin >> choice;
       
        switch (choice)
        {
        case 1:
        {
            system("CLS");
            cout << "Enter .txt file's name with turing instructions: ";
            cin >> txt1;
            txt1 += ".txt";
            system("cls");
            thread t1(start, txt1, y1);
            t1.join();
            break;
        }
        case 2:
        {
            system("CLS");
            cout << "Enter the first .txt file's name with turing instructions: ";
            cin >> txt1;
            txt1 += ".txt";
            cout << "Enter the second .txt file's name with turing instructions: ";
            cin >> txt2;
            txt2 += ".txt";
            cout << "Enter the third .txt file's name with turing instructions: ";
            cin >> txt3;
            txt3 += ".txt";
            cout << "Enter the fourth .txt file's name with turing instructions: ";
            cin >> txt4;
            txt4 += ".txt";

            system("cls");
            thread t1(start, txt1, y1);
            thread t2(start, txt2, y2);
            thread t3(start, txt3, y3);
            thread t4(start, txt4, y4);
            t1.join();
            t2.join();
            t3.join();
            t4.join();
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Done." << endl;
            tmOn = false;
            break;
        }
        default:
            system("cls");
            cout << "Wrong choice." << endl
                 << "Try again." << endl;
            break;
        }
    }
}