#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
    // string str = "KFC";
    // str = "BBQ";
    // if(str == "BBQ") cout << "O" << "\n";

    // 문자열 사이즈
    string str = "KFCKFCBBQ";
    cout << str.length() <<"\n" << str.size() <<"\n";

    // 문자열 합치기
    string a = "KFC";
    string b = "BBQ";
    string c = "MOMS";
    string ans;
    ans = a + b + c;
    string str = (string)"adsgKFC" + "BBQ" + " GASG" ;

    string target = "KFC";
    int ret = str.find(target);
    cout << ret << "\n";

    string vect[4] = {
        "ABBT",
        "BTBT",
        "BBBT",
        "KFC"
    };

    // 일치하는 문자열 찾기
    target = "BB";
    for(int i=0; i<4; i++) {
        if(vect[i].find(target)) cout << "O\n";
        else cout << "X\n";
    }

    // 역순 출력
    for(int i=0; i<4; i++) {
        for(int j=vect[i].size(); j>=0; i--) {
            cout << vect[i][j];
        }
        cout << "\n";
    }

    // 문자열 중 정수로만 이루어진 경우
    // "123123123" -> 123123123
    str = "123123123";
    int ans = stoi(str);
    ans += 999;
    cout << ans;
    int value = 1231000;
    string str2 = to_string(value);
    cout << str2 + "999";

    stringstream(str) >> ans;

    return 0;
}