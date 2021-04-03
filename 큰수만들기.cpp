#include <string>
using namespace std;

string solution(string number, int k) {
    string answer = "";
    
   for(int i = 0; i < k; i++){ // k 개의 수 제거
       for(int j = 0; j < number.length(); j++){
           if(j == number.length() - 1){ // 마지막 인덱스
               number.erase(number.begin() + j);
           }
           else if(number[j] < number[j+1]){ //앞 자리를 최대한 크게 유지
               number.erase(number.begin() + j);
               break;
           }
       }
   }
    
    answer = number;
    
    return answer;
}



//부문 문제(k = 1, 2, ..., k-1)의 최적해 유지 -> 최적해

//앞자리가 클 수록 큰 숫자
//규칙: 현재 숫자보다 뒤의 숫자가 더 크면 현재 숫자를 삭제

//4177252841
//477252841
//77252841
//7752841
//775841

//1924
//924
//94

//1231234
//231234
//31234
//3234