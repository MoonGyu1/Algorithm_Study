#include <vector>
#include <iostream>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    vector<int> pocket;
    bool flag = true;

    pocket.push_back(nums[0]);
    for(int i=1; i<nums.size(); i++){
        for(int j=0; j<pocket.size(); j++){
            if(pocket[j] == nums[i]){
                flag = false;
                break;
            }
            else flag = true;
        }
        if(flag)
            pocket.push_back(nums[i]);
    }

    if(pocket.size() > nums.size() / 2)
        answer = nums.size() / 2;
    else
        answer = pocket.size();

    return answer;
}

