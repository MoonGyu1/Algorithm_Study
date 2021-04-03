#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    vector<int> days; //남은 작업 일수
    
    //1. 벡터 days에 작업 완료까지 남은 일수 저장
    for(int i = 0; i < progresses.size(); i++){
        
        //작업 일수가 나누어 떨어지는 경우
        if( (100-progresses[i]) % speeds[i] == 0 ){
            days.push_back( (100-progresses[i]) / speeds[i] );
        }
        //나누어 떨어지지 않는 경우
        else{
            days.push_back( (100-progresses[i]) / speeds[i] + 1 );
        }
    }
    
    //2. 벡터 days를 이용하여 첫 번째 기능부터 내보내기
    int num; //한 번에 배포되는 기능의 수
    int now; //맨 앞 기능의 남은 작업 일수
    
    while(!days.empty()){ //모든 기능이 배포될 때까지
        num = 0;
        now = days[0];
        
        //벡터 days의 요소값 갱신
        for(int i = 0; i < days.size(); i++){
            days[i] -= now;
        }
       
        //요소값이 0이하인 경우 작업이 완료되었음을 의미
        while(!days.empty() && days[0] <= 0){
            num++; //맨 앞 요소 배포
            days.erase(days.begin()); //맨 앞 요소 갱신됨
        }
        
        answer.push_back(num);
    }
    
    return answer;
}


// 93, 30, 55 -> 7, 3, 9
//               0 -4/ 2
//                     0/

// 95, 90, 99, 99, 80, 99 -> 5, 10, 1, 1, 20, 1
//                           0/  5 -4 -4  15 -4
//                               0 -9 -9/ 10 -9
//                                        0 -19/

//     배포가 같이 이루어질 수 있는 것을 찾기 위해
//     현재 가장 먼저 배포되어야 하는 기능의 작업 일수만큼 모두 빼기
//     모두 뺐을 때 0보다 작거나 같으면 , 가장 먼저 배포되어야 하는 기능이 완성되었을 때 뒤에 있는 기능도 완성 된 것을 의미하므로, 같이 배포함 , 그렇지 않고 0보다 크다면, 아직 작업일수가 더 남았음을 의미하므로 배포하지 않음