#ifndef QUATERNION_QUATERLIB_H
#define QUATERNION_QUATERLIB_H

#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

char *comma = const_cast<char *>("C");

class qn {
public:
    qn(double s, double i, double j = 0, double k = 0) {
        this->s = s;
        this->i = i;
        this->j = j;
        this->k = k;
    }
    
    explicit qn(const string &);
    
    qn sqrt();
    
    string str(bool spaces = true);
    
    double s, i, j, k;
};

qn qn::sqrt() {
    double s = std::sqrt(
            (this->s + std::sqrt(pow(this->s, 2) + pow(this->i, 2) + pow(this->j, 2) + pow(this->k, 2))) / 2);
    double i = this->i / 2 / s;
    double j = this->j / 2 / s;
    double k = this->k / 2 / s;
    return {s, i, j, k};
}

qn operator+(qn a, qn b) {
    return {a.s + b.s, a.i + b.i, a.j + b.j, a.k + b.k};
}

qn operator-(qn a, qn b) {
    return {a.s - b.s, a.i - b.i, a.j - b.j, a.k - b.k};
}

qn operator*(qn a, qn b) {
    double s = a.s * b.s - a.i * b.i - a.j * b.j - a.k * b.k;
    double i = a.i * b.s + a.s * b.i + a.j * b.k - a.k * b.j;
    double j = a.j * b.s + a.s * b.j + a.k * b.i - a.i * b.k;
    double k = a.k * b.s + a.s * b.k + a.i * b.j - a.j * b.i;
    return {s, i, j, k};
}

qn operator/(qn a, qn b) {
    double s = (a.s * b.s + a.i * b.i + a.j * b.j + a.k * b.k) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    double i = (a.i * b.s - a.s * b.i) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    double j = (a.j * b.s - a.s * b.j) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    double k = (a.k * b.s - a.s * b.k) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    return {s, i, j, k};
}


void operator+=(qn &a, qn b) {
    a.s += b.s;
    a.i += b.i;
    a.j += b.j;
    a.k += b.k;
}

void operator-=(qn &a, qn b) {
    a.s -= b.s;
    a.i -= b.i;
    a.j -= b.j;
    a.k -= b.k;
}

void operator*=(qn &a, qn b) {
    double s = a.s * b.s - a.i * b.i - a.j * b.j - a.k * b.k;
    double i = a.i * b.s + a.s * b.i + a.j * b.k - a.k * b.j;
    double j = a.j * b.s + a.s * b.j + a.k * b.i - a.i * b.k;
    double k = a.k * b.s + a.s * b.k + a.i * b.j - a.j * b.i;
    a = {s, i, j, k};
}

void operator/=(qn &a, qn b) {
    double s = (a.s * b.s + a.i * b.i + a.j * b.j + a.k * b.k) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    double i = (a.i * b.s - a.s * b.i) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    double j = (a.j * b.s - a.s * b.j) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    double k = (a.k * b.s - a.s * b.k) / (b.s * b.s + b.i * b.i + b.j * b.j + b.k * b.k);
    a = {s, i, j, k};
}

qn::qn(const string &w) {
    string str;
    for (char c : w)
        if (c != ' ' && c != '\t' && c != '\n')
            str += c;
    bool fl = false;
    int left = 0;
    qn k = qn(0, 0);
    for (unsigned int i = 0; i < str.length() && not fl; i++) {
        if (str[i] == '(')
            left++;
        else if (str[i] == ')')
            left--;
        else if (str[i] == '+' && left == 0) {
            if (i == 0)
                k = qn(str.substr(1, str.length() - 1));
            else
                k = qn(str.substr(0, i)) + qn(str.substr(i + 1, str.length() - i));
            fl = true;
        }
        else if (str[i] == '-' && left == 0) {
            if (i == 0) {
                int pos1 = -1;
                int left1 = 0;
                for (unsigned int j = i + 1; j < str.length() && pos1 == -1; j++) {
                    if (str[j] == '(')
                        left1++;
                    else if (str[j] == ')')
                        left1--;
                    else if (str[j] == '+' && left1 == 0) {
                        pos1 = j;
                    }
                    else if (str[j] == '-' && left1 == 0) {
                        pos1 = j;
                    }
                }
                if (pos1 == -1)
                    k = qn(0, 0) - qn(str.substr(1, str.length() - 1));
                else
                    k = qn(0, 0) - qn(str.substr(1, static_cast<unsigned int>(pos1) - 1)) +
                        qn(str.substr(static_cast<unsigned int>(pos1), str.length()));
            }
            else {
                k = qn(str.substr(0, i)) + qn(str.substr(i, str.length() - i));
            }
            fl = true;
        }
    }
    if (!fl)
        for (unsigned int i = 0; i < str.length() && not fl; i++) {
            if (str[i] == '(')
                left++;
            else if (str[i] == ')')
                left--;
            else if (str[i] == '*' && left == 0) {
                k = qn(str.substr(0, i)) * qn(str.substr(i + 1, str.length() - i));
                fl = true;
            }
            else if (str[i] == '/' && left == 0) {
                int pos1 = -1;
                int left1 = 0;
                for (unsigned int j = i + 1; j < str.length() && pos1 == -1; j++) {
                    if (str[j] == '(')
                        left1++;
                    else if (str[j] == ')')
                        left1--;
                    else if (str[j] == '*' && left1 == 0) {
                        pos1 = j;
                    }
                }
                string s1 = str.substr(i + 1, pos1 - i - 1);
                left1 = 0;
                for (char &j : s1) {
                    if (j == '(')
                        left1++;
                    else if (j == ')')
                        left1--;
                    else if (j == '/' && left1 == 0) {
                        j = '*';
                    }
                }
                if (pos1 == -1)
                    k = qn(str.substr(0, i)) / qn(s1);
                else
                    k = qn(str.substr(0, i)) / qn(s1) *
                        qn(str.substr(static_cast<unsigned int>(pos1 + 1), str.length() - pos1 - 1));
                fl = true;
            }
        }
    if (!fl) {
        int left2 = 0;
        int st = str.find("sqrt(");
        if (st != -1)
            for (char c: str.substr(0, static_cast<unsigned int>(st))) {
                if (c == '(')
                    left2++;
                else if (c == ')')
                    left2--;
            }
        if (st != -1 && left2 == 0) {
            int left1 = 1;
            int right = -1;
            for (int i = st + 5; i < str.length() && left1 != 0; i++) {
                if (str[i] == '(')
                    left1++;
                else if (str[i] == ')')
                    left1--;
                if (left1 == 0)
                    right = i;
            }
            if (right != -1) {
                if (st == 0 && right == str.length() - 1)
                    k = qn(str.substr(5, str.length() - 6)).sqrt();
                else if (st == 0)
                    k = qn(str.substr(5, static_cast<unsigned int>(right - 5))).sqrt() * qn(str.substr(
                            static_cast<unsigned int>(right + 1), str.length() - right - 1));
                else if (right == str.length() - 1)
                    k = qn(str.substr(0, static_cast<unsigned int>(st))) *
                        qn(str.substr(static_cast<unsigned int>(st + 5), str.length() - st - 6)).sqrt();
                else
                    k = qn(str.substr(0, static_cast<unsigned int>(st))) *
                        qn(str.substr(static_cast<unsigned int>(st + 5),
                                      static_cast<unsigned int>(right - st - 5))).sqrt() *
                        qn(str.substr(static_cast<unsigned int>(right + 1), str.length() - right));
                fl = true;
            }
        }
    }
    if (!fl) {
        int st = -1;
        for (unsigned int i = 0; i < str.length() && not fl; i++) {
            if (str[i] == '(') {
                if (st == -1)
                    st = i;
                left++;
            }
            else if (str[i] == ')' and --left == 0) {
                if (st == 0 && i == str.length() - 1)
                    k = qn(str.substr(1, str.length() - 2));
                else if (st == 0)
                    k = qn(str.substr(1, i - 1)) * qn(str.substr(i + 1, str.length() - i));
                else if (i == str.length() - 1)
                    k = qn(str.substr(0, static_cast<unsigned int>(st))) *
                        qn(str.substr(static_cast<unsigned int>(st + 1), str.length() - st - 2));
                else
                    k = qn(str.substr(0, static_cast<unsigned int>(st))) *
                        qn(str.substr(static_cast<unsigned int>(st + 1), i - st - 1)) *
                        qn(str.substr(i + 1, str.length() - i));
                
                fl = true;
            }
        }
    }
    if (!fl) {
        int ijk = 0;
        bool err = false;
        string x;
        if (str.empty())
            err = true;
        for (auto c: str) {
            if (c == 'i')
                if (ijk == 0 || ijk == 1)
                    ijk = 1;
                else
                    err = true;
            else if (c == 'j')
                if (ijk == 0 || ijk == 2)
                    ijk = 2;
                else
                    err = true;
            else if (c == 'k')
                if (ijk == 0 || ijk == 3)
                    ijk = 3;
                else
                    err = true;
            else if (string("1234567890.,").find(c) != -1)
                x += c;
            else
                err = true;
        }
        if (err) {
            setlocale(LC_ALL, "");
            wcout << L"Неправильный формат ввода кватерниона\n";
            setlocale(LC_ALL, comma);
            k = {0, 0, 0, 0};
        }
        else {
            if (x.empty())
                x = "1";
            switch (ijk) {
                case 0:
                    k = qn(stod(x), 0);
                    break;
                case 1:
                    k = qn(0, stod(x));
                    break;
                case 2:
                    k = qn(0, 0, stod(x));
                    break;
                default:
                    k = qn(0, 0, 0, stod(x));
                    break;
            }
        }
    }
    this->s = k.s;
    this->i = k.i;
    this->j = k.j;
    this->k = k.k;
}

string qn::str(bool spaces) {
    if (spaces)
        return to_string(s) + " + " + to_string(i) + "i + " + to_string(j) + "j + " + to_string(k) + "k";
    else
        return to_string(s) + "+" + to_string(i) + "i+" + to_string(j) + "j+" + to_string(k) + "k";
}


#endif //QUATERNION_QUATERLIB_H
