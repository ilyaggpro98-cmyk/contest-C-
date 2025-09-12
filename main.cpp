#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

ld answerBase2toBase10(string &a, string &b) {
    ld res = 0;
    for (char c : a)
        res = res * 2 + (c - '0');
    ld f = 1;
    for (char c : b) {
        f /= 2;
        res += (c - '0') * f;
    }
    return res;
}

ld answerBase8toBase10(string &a, string &b) {
    ld res = 0;
    for (char c : a)
        res = res * 8 + (c - '0');
    ld f = 1;
    for (char c : b) {
        f /= 8;
        res += (c - '0') * f;
    }
    return res;
}

ld answerBase16toBase10(string &a, string &b) {
    ld res = 0;
    for (char c : a) {
        ll d = isdigit(c) ? c - '0' : toupper(c) - 'A' + 10;
        res = res * 16 + d;
    }
    ld f = 1;
    for (char c : b) {
        f /= 16;
        ll d = isdigit(c) ? c - '0' : toupper(c) - 'A' + 10;
        res += d * f;
    }
    return res;
}

string ten(ld x) {
    ostringstream oss;
    oss << fixed << setprecision(6) << x;
    string s = oss.str();
    if (s.find('.') != string::npos) {
        while (!s.empty() && s.back() == '0') s.pop_back();
        if (!s.empty() && s.back() == '.') s.pop_back();
    }
    return s;
}

string transver(ld x, ll base) {
    char num[] = "0123456789ABCDEF";
    ll ip = (ll)floor(x + 1e-15);
    ld frac = x - ip;
    if (ip < 0) ip = 0;
    string s;
    if (ip == 0) {
        s = "0";
    } else {
        while (ip) {
            s += num[ip % base];
            ip /= base;
        }
        reverse(s.begin(), s.end());
    }

    s += ',';
    for (ll i = 0; i < 6; i++) {
        frac *= base;
        ll d = (ll)floor(frac + 1e-15);
        s += num[d];
        frac -= d;
    }
    return s;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    string s;
    ll base;
    cin >> s >> base;

    string ip, fp;
    bool dot = false;
    for (char c : s) {
        if (c == '.' || c == ',') {
            dot = true;
            continue;
        }
        if (!dot) ip += c;
        else       fp += c;
    }


    ld dec = 0;
    if (base == 2) {
        dec = answerBase2toBase10(ip, fp);
    } else if (base == 8) {
        dec = answerBase8toBase10(ip, fp);
    } else if (base == 16) {
        dec = answerBase16toBase10(ip, fp);
    } else if (base == 10) {

        string tmp = s;
        for (char &c : tmp) if (c == ',') c = '.';
        dec = stold(tmp);
    }


    string b2  = transver(dec, 2);
    string b8  = transver(dec, 8);
    string d10 = ten(dec);
    string b16 = transver(dec, 16);

    cout << b2  << ' '
         << b8  << ' '
         << d10 << ' '
         << b16 << "\n";

}

//Дата 08.09.2025
