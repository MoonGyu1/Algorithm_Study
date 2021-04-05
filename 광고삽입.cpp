#include <string>
#include <vector>
using namespace std;

//"00:00:00" -> second
int string_to_int(string time) {
	int second;
	second = stoi(time.substr(0, 2)) * 60 * 60
		+ stoi(time.substr(3, 2)) * 60
		+ stoi(time.substr(6, 2));

	return second;
}

//second -> "00:00:00"
string int_to_string(int second) {
	string time = "";

	int h = second / 60 / 60;
	int m = second / 60 % 60;
	int s = second % 60;

	if (h < 10) { //한 자리수인 경우
		time += "0";
	}
	time += to_string(h) + ":";

	if (m < 10) {
		time += "0";
	}
	time += to_string(m) + ":";

	if (s < 10) {
		time += "0";
	}
	time += to_string(s);

	return time;
}

string solution(string play_time, string adv_time, vector<string> logs) {
	string answer = "";

	//영상 길이 == 광고 길이
	if (play_time == adv_time) {
		answer = "00:00:00";
		return answer;
	}


// 1. 주어진 영상 길이, 광고 길이, 재생 구간을 초단위로 변환

	// play_time을 초단위로 변환
	int play_second = string_to_int(play_time);

	// adv_time을 초단위로 변환
	int adv_second = string_to_int(adv_time);

	// logs 시작시간, 종료시간을 초단위로 변환
	vector<int> logs_start(logs.size());
	vector<int> logs_end(logs.size());

	for (int i = 0; i < logs.size(); i++) {
		logs_start[i] = string_to_int(logs[i].substr(0, 8));
		logs_end[i] = string_to_int(logs[i].substr(9, 8));
	}


// 2. 초당 시청자 수 구하기
	int people[360000] = { 0, }; //초당 시청자 수 (최대 360000초)

	for (int i = 0; i < logs.size(); i++) {
		people[logs_start[i]]++; //시청 시작 시간에 +1
		people[logs_end[i]]--; //시청 종료 시간에 -1
	}

	// people에 초당 누적 시청자 수 저장(prefix sum)
	for (int i = 1; i < play_second; i++) {
		people[i] = people[i - 1] + people[i];
	}


// 3. 누적 시청자 수가 가장 많은 구간 찾기
	int start = 0; //광고 삽입 시각(초)

	//testcase 17 에러: 자료형 int -> long
	long now_sum = 0; //현재 누적재생시간
	long max = 0; //최대 누적재생시간(초)

	//now_sum과 max 초기화
	//0초에 광고 삽입할 경우 누적재생시간(초)
	for (int i = 0; i < adv_second; i++) {
		now_sum += people[i];
	}

	max = now_sum;


	//광고 삽입 구간을 1초씩 뒤로 이동하며 최댓값 찾기
	for (int i = 0; i < play_second - adv_second; i++) {
		now_sum -= people[i]; //맨 앞 요소 삭제
		now_sum += people[i + adv_second]; //맨 뒤 요소 추가

		if (now_sum > max) {
			max = now_sum;
			start = i + 1;
		}
	}


// 4. 답을 시각으로 변환하여 반환
	answer = int_to_string(start);

	return answer;
}




//prefix sum 알고리즘을 사용해보자
//-> 원하는 인덱스 구간의 '누적 합'을 구할 수 있음
//전체 동영상 재생시간(최대 360000초)을 초단위로 환산
// -> 1초마다 하나의 인덱스를 나타냄(인덱스: 0 ~ 360000)

//play_time, adv_time을 초 단위로 반환
//logs 시작/종료 시간을 초 단위로 반환

//int people_num[360000]=0

//초단위로 반환한 logs 요소를 탐색하면서
//for i in logs시작시간
// people_num[시작시간[i]] += 1

//for i in logs종료시간
// people_num[종료시간[i]] -= 1

//현재까지 people_num배열에는 각 사람이 영상을 본 시작시간과 종료시간이 표시된 상태
//->이것을 전구간에서 인원수로 바꿔주어야함

//프리픽스 썸 알고리즘 사용
//int people[360000]
//people[i] = people[i-1] + people_num[i]

//->people에는 각 초별 인원수가 담겨있음
//->이제 사람 수가 가장 많은 구간을 뽑아야함
//now_sum = 인덱스0~광고시간만큼(초단위)의 합
//now_sum = now_sum - people[-1] + people[+1]
//현재것이 더 크면 max= 현재것

//return max