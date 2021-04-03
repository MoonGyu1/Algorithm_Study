#include <string>
#include <vector>

using namespace std;

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    vector<bool> visited;
    visited.assign(k, false);

    for(int i=0; i<room_number.size(); i++){
        if(!visited[room_number[i]-1]){
            answer.push_back(room_number[i]);
            visited[room_number[i]-1] = true;
        }else{
            long long j = room_number[i];
            while(visited[j-1]){
                j++;
            }
            answer.push_back(j);
            visited[j-1] = true;
        }
    }

    return answer;
}
