#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    
    if(play_time == adv_time){
        answer = "00:00:00";
        return answer;
    }
    
    vector<int> logs_second_s(logs.size()); //logs 시작시간을 초단위로 변환
    vector<int> logs_second_e(logs.size()); //logs 종료시간을 초단위로 변환
    
    for(int i=0; i<logs.size(); i++){
        logs_second_s[i] = stoi(logs[i].substr(0,2)) * 60 * 60
            + stoi(logs[i].substr(3,2)) * 60
            + stoi(logs[i].substr(6,2));
        
        logs_second_e[i] = stoi(logs[i].substr(9,2)) * 60 * 60
            + stoi(logs[i].substr(12,2)) * 60
            + stoi(logs[i].substr(15,2));
    }
    
    //각각의 log 시작시간에 광고가 시작한다고 가정
    vector<int> accumulate(logs.size()); //각 시작시간 별 누적 재생시간
    int adv_section_s; //실제 광고 시작 시간
    int adv_section_e; //실제 광고 종료 시간
    
    int s; //start
    int e; //end
    
    //adv_time을 초단위로 변환
    int adv_time_second = stoi(adv_time.substr(0,2)) * 60 * 60
            + stoi(adv_time.substr(3,2)) * 60
            + stoi(adv_time.substr(6,2));
    
    for(int i=0; i<logs.size(); i++){
        accumulate[i] = 0; //초기화
        adv_section_s = logs_second_s[i]; //광고 시작 시간
        adv_section_e = logs_second_s[i] + adv_time_second; //광고 종료 시간
        
        for(int j=0; j<logs.size(); j++){
            if(adv_section_s <= logs_second_s[j]){
                s = logs_second_s[j];
            }
            else{
                s = adv_section_s;
            }
            
            if(adv_section_e >= logs_second_e[j]){
                e = logs_second_e[j];
            }
            else{
                e = adv_section_e;
            }
            
            if((e-s) > 0){
                accumulate[i] += (e-s);
            }
        }  
    }
    
    int answer_index = 0;
    for(int i=1; i<accumulate.size(); i++){
        if(accumulate[i] > accumulate[answer_index]){
            answer_index = i;
        }
        else if(accumulate[i] == accumulate[answer_index]){
            if(logs[i] < logs[answer_index]){
                answer_index = i;
            }
        }
    }
    
    answer = logs[answer_index].substr(0,8);
//cout << answer_index <<endl;    
    
//     for(int i=0; i<logs.size(); i++){
//         cout << accumulate[i] <<endl;
//     }
    
    
    return answer;
}

//그리디?
//구간별 누적재생시간을 구하고, 그 값이 가장 큰 위치부터 광고를 시작한다고 가정

// 인풋1의 경우
// 14:41 / 07:58 * 2 / 11:31 / 10:44 / 06:45 * 2 / 07:30 * 3 / 08:15 / 09:01 
    
// -> 구간 3개가 겹치는 07:30 * 3이 누적 재생 시간이 가장 긺
// ->

// 1.logs 구간을 초단위로 바꾸기
// 시간*60*60 + 분*60 +초
// 4815 == 80분 15초 = 1시간 20분 15초

// 광고가 시작하는 시간 = 항상 어떤 시청자의 재생시간의 시작시간과 일치한다고 가정
// 1번 시청자의 시작시간부터 시작한다고 가정, 각각의 누적 재생시간을 구함
// ex) 1번 부터 시작할 경우, 광고 시간이 00:14:15 이므로
// 01:20:15 - 01:34:30 이라는 광고 구간을 얻을 수 있음
// 이때의 누적 재생시간은
// ---
// 각 구간에서 시작할 경우 누적재생시간을 담는 vector[]
// s,e //start, end

// for문 1번 부터
// if 광고 시작시간 <= i의 시작시간
// s=i 시작시간
// else
// s= 광고 시작시간

// ---

// if 광고 끝 시간 >= i의 끝시간
// e= i 끝시간
// else
// e= 광고 끝시간

// e-s가 양수일 경우(음수면 구간이 겹치지 않는 것)
// 1번 시작시간에 광고를 시작할 경우 누적재생시간 += e-s(양수일 경우)