
#include "application.h"
#include "matrix.h"
#include <iostream>

using namespace std;

Application::Application()
{
}
int Application::exec()
{
    int ch;
    number num;
    while(true) {
        ch = menu();
        switch(ch){
        case 1: {
            for(int i = 0; i < m._size; i++) {
                for(int j = 0; j < m._size; j++) {
                    system("cls");
                    cout<<"Enter number " <<i + 1<<" "<<j + 1<<endl;
                     cin>>num;
                    m.enter(num, i, j);
                }
            }
            system("cls");
            break;
        }
        case 2: {

            number res = m.activateDet();
            cout<<"det = "<<res << endl;
             break;}
        case 3:
             m.transpose();
             cout<<m;
            break;
        case 4: {
            int res = m.findRank();
            cout<< "rank = " <<res << endl;
            break;}
        case 5:
            cout<<m;
            break;
        case 6:
            int s;
            cout<<"Enter size "<<endl;
            cin>>s;
            if(s > 10 || s <= 0) {
                s = 3;
            }
            m.enterSize(s);
            m.reSize();
            break;
        case 0:
            cout<<"To exit press Enter";
            return 0;
        default:
            break;
        }
    }
    return 0;
}
int Application::menu()
{
    int ch;
    cout<< "1 - Enter matrix"<<endl;
    cout<< "2 - Find determinant"<<endl;
    cout<< "3 - Matrix transposition"<<endl;
    cout<< "4 - Find rank"<<endl;
    cout<< "5 - Show Matrix"<<endl;
     cout<< "6 - Enter Matrix size"<<endl;
    cout<< "0 - Exit"<<endl;
    cin>>ch;
    return ch;



}

