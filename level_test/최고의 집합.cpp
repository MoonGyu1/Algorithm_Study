#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    int a;
    int b;

    if(n > s){
        answer.push_back(-1);
    }
    else if(n == 2 && s%n == 0){
        a = s/n;
        answer.push_back(a);
        answer.push_back(a);
    }
    else if(n == 2 && s%n != 0){
        a = s/n;
        answer.push_back(a);
        answer.push_back(a+1);
    }
    else if(s%n == 0){
        a = s/(n-1);
        b = s%(n-1);
        for(int i=0; i<n-1; i++){
            answer.push_back(a);
        }
        answer.push_back(b);
    }
    else{
        a = s / (n-1);
        b = s % (n-1);
        for(int i=0; i<n-1; i++){
            answer.push_back(a);
        }
        answer.push_back(b);
    }

    sort(answer.begin(), answer.end());

    return answer;
}
