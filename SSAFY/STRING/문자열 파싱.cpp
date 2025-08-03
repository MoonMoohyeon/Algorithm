#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
    // 문자열 중 특정 위치 파싱
    string str = "DFS[12345]SSADF";
    // str.find()로 찾은 후 str.substr(시작 위치, 글자 수)로 잘라내기
    int index = str.find('[');
    string ans = str.substr(index + 1, 5); // 시작 위치 포함
    cout << ans;

    // str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(char i='A'; i<='Z'; i++) str += i;
    index = str.find('C');
    ans = str.substr(index, 4);

    string vect[4] = {
        "ABCD",
        "B[7]A",
        "CDSE",
        "BT[23]"
    };

    // 숫자만 찾기
    for(int i=0; i<4; i++) {
        for(int j=0; j<vect[i].size(); j++) {
            if(vect[i][j] >= '0' && vect[i][j] <= '9') {
                ans += vect[i][j];
            }
        }
        ans += 'a';
    }

    // 함수, params = string, return = string
    int aa = str.find('[');
    int bb = str.find(']');
    int size = bb - aa - 1;
    string temp = str.substr(aa+1, size);
    // return temp;

    str = "BAS[45]ASD[345]KFC";
    aa = str.find('[');
    bb = str.find(']');
    size = bb - aa - 1;
    temp = str.substr(aa+1, size);
    int sum = stoi(temp);
    aa = str.find('[', bb+1);
    bb = str.find(']', aa+1);
    size = bb - aa - 1;
    temp = str.substr(aa+1, size);
    sum += stoi(temp);


    // 대상 문자열에서 타겟 문자열을 모두 찾기
    int cnt = 0;
    int aaa = -1; // 초기 탐색 시작 위치
    while(1) {
        int bbb=str.find("[KFC]", aaa+1);
        if(aaa==-1) break;
        cnt += 1;
        aaa = bbb+1;
    }
    cout << cnt;


    string v[3] = {
        "BTSGOLD",
        "GOLDGOLD",
        "GOLDBARGOLD"
    };
    int cnt = 0;
    int pos = -1; // 초기 탐색 시작 위치
    string str;
    for (int i = 0; i < 3; i++) {
        pos = -1;
        str = v[i];
        while (1) {
            int start = str.find("GOLD", pos + 1);
            if (start == -1) break;
            cnt += 1;
            pos = start + 1;
        }
    }

    cout << cnt;

    // 특정 문자를 기준으로 잘라내기
    string str = "-123-123-123-123-123-12345";
    str +='-'; // - 기준으로 파싱하면 마지막 문자가 추출되지 않으므로
    // 마지막에 -를 붙여준다.
    int q,w,answer;
    q=w=answer=0;
    while(1) {
        w=str.find('-', q);
        if(w==-1) break;
        string temp = str.substr(q,w-q);
        cout << temp << "\n";
        answer += stoi(temp);

        q=w+1;
    }

    // erase, insert
    str = "ASDFSD_BBQ";
    // erase와 insert를 이용하여 str.replace(BBQ,KFC)를 만들기
    // C++에서 제공하지 않음
    str.replace(2,5,"KFC"); // 시작위치, 글자 수, 해당 값으로 변경
    
    str.erase(3,3); // 시작위치(포함), 지울 글자 수
    str.insert(1,"<HI>"); // 시작위치(포함), 넣을 문자열

    

    return 0;
}