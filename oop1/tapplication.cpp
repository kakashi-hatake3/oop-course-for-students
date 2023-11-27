
#include "tapplication.h"
#include <iostream>
#include "number.h"
#include "tmatrix.h"


using namespace std;

TApplication::TApplication()
{

}

int TApplication::exec()
{
    int ch;
    number a=1,b=2,c=3,d=4;
    while(true){
        ch = menu();
        switch(ch)
        {

        case 0:
            return 0;
        case 1:
            cout << "Enter values" << endl;
            cin >> a;
            cout << "[0][0] = " << a << endl;
            cin >> b;
            cout << "[0][1] = " << b << endl;
            cin >> c;
            cout << "[1][0] = " << c << endl;
            cin >> d;
            cout << "[1][1] = " << d << endl;
            break;
        case 2:
            cout << "Determination of matrix" << endl << a * d - b * c << endl;
            break;
        case 3:
        {
            TMatrix matrix(a, c, b, d);
            cout << matrix << endl;
        }
        break;
        case 4:
            if (a * d - b * c == 0){
                cout << "Rank of matrix" << endl << 1 << endl;
            }
            else{
                cout << "Rank of matrix" << endl << 2 << endl;
            }
            break;
        case 5:
        {
            TMatrix matrix(a, b, c, d);
            cout << matrix << endl;
        }
        break;
        default:
            break;
        }
    }
}


int TApplication::menu(){
    int ch;
    cout << "1 - input" << endl;
    cout << "2 - determination" << endl;
    cout << "3 - trans" << endl;
    cout << "4 - rank" << endl;
    cout << "5 - output" << endl;
    cout << "0 - exit" << endl << "> ";
    cin >> ch;
    return ch;
}
