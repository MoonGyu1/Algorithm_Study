#include <string>
#include <vector>

using namespace std;

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    bool flag;
    int before;
    int after;
    
    //스킬트리 하나씩 탐색
    for(int i = 0; i < skill_trees.size(); i++){
        flag = true;
        
        //선행 스킬 순서
        for(int j = 0; j < skill.length()-1; j++){
            //스킬의 인덱스 반환(없을 경우 -1)
            before = skill_trees[i].find( skill[j] );
            after = skill_trees[i].find( skill[j+1] );
            
            //1. 선행 스킬을 나중에 배운 경우
            if( (before != -1 && after != -1 && after < before)
                //2. 선행 스킬을 안 배운 경우
               or (before == -1 && after != -1) ){
                flag = false;
                break;
            }
        }
        
        //가능한 스킬트리인 경우
        if(flag == true)
            answer++;
    }
    
    return answer;
}




// #include <string>
// #include <vector>

// using namespace std;

// int solution(string skill, vector<string> skill_trees) {
//     int answer = 0;
//     bool flag = true;
//     int front;
//     int end;
    
//     for(int i=0; i<skill_trees.size(); i++){
//         flag = true;
//         for(int j=0; j<skill.length()-1; j++){
//             front = skill_trees[i].find(skill[j]);
//             end = skill_trees[i].find(skill[j+1]);
            
//             if(front != -1 && end != -1 && front < end)
//                 flag=true;
//             else if(front != -1 && end == -1)
//                 flag=true;
//             else if(front == -1 && end == -1)
//                 flag = true;
//             else{
//                 flag = false;
//                 break;
//             }
//         }
        
//         if(flag==true)
//             answer++;
//     }
    
//     return answer;
// }