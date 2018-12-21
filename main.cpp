#include <fstream>
#include "qn.h"

using namespace std;

int main() {
    ifstream ik;
    ofstream ok;
    qn qn1 = qn(0, 0);
    string c;
    while (c != "q") {
        getline(cin, c);
        if (c == "r") {
            string s;
            ik.open("input.txt");
            if (!ik.is_open()) {
                setlocale(LC_ALL, "");
                wcout << L"Не получилось открыть input.txt\n\n\n";
                setlocale(LC_ALL, comma);
            }
            else {
                getline(ik, s);
                ik.close();
                qn1 = qn(s);
                cout << endl << qn1.str() << "\n\n\n";
            }
        }
        else if (c == "s") {
            ok.open("output.txt");
            cout << "\n\n\n";
            ok << qn1.str();
            ok.close();
        }
        else if (c == ".") {
            comma = const_cast<char *>("C");
            setlocale(LC_ALL, comma);
            cout << "\n\n\n";
        }
        else if (c == ",") {
            comma = const_cast<char *>("");
            setlocale(LC_ALL, comma);
            cout << "\n\n\n";
        }
        else if (c != "q") {
            qn1 = qn(c);
            cout << endl << qn1.str() << "\n\n\n";
        }
    }
    return 0;
}