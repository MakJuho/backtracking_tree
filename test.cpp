#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <functional>
#include <stack>
#include <cstring>
#include <fstream>
#include <string>
#include <stdio.h>
#include <set>
#include <typeinfo>
#include <time.h>

using namespace std;

/*
구현할 것
1. sets 한 묶음을 배열 vector로서 표현하기.
2. 현재 상태 체크하는 변수 vector 만들기
3. 1번 set을 넣고, 2번 set을 넣을지 않넣을지 알고리즘을 구현 후, 추가
	-  나머지를 다 넣은 후에도 값이 solv보다 작다 그러면 다음 부분 처리
4. best solv라는 값으로 넣기
*/

struct node {

	vector <int> binary_state; // 현재 state 이진수로 표시
	vector <int> added_set; // 추가된 level 체크.
	int current_sum = 0;
	int level = 0;
};

void myQuickSort(vector<set<int> >& v, vector<int>& arr, int start, int end) {
	if (start >= end) return;
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	int temp;

	while (i <= j) {
		while (i <= end && arr[i] >= arr[pivot]) {
			i++;
		}
		while (j > start && arr[j] <= arr[pivot]) {
			j--;
		}

		if (i > j) {
			temp = arr[j];
			arr[j] = arr[pivot];
			arr[pivot] = temp;
			v[j].swap(v[pivot]);
		}
		else {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			v[i].swap(v[j]);
		}


	}
	myQuickSort(v, arr, start, j - 1);
	myQuickSort(v, arr, j + 1, end);

	return;
}


int main(void) {
	char buff[1024];
	char *pch;
	int uNum = 0;
	int sNum = 0;
	int best_sol = 999999999;
	int temp_sol = 0;
	int Sum_ans = 0;
	int pre_sum_value = 0;
	clock_t s, e;

	vector<int> subset_cnt;
	vector<set<int> > sets;
	vector<int> answer;
	vector<int> using_subset_cnt;

	//struct node temp1_node;
	struct node temp_node;
	// struct 구조 추가
	struct node contents;
	stack<node> tree;

	vector<int> using_added_set;

	


	// uNUM: N까지 모든 양의 정수, sNUM: subset 개수
	scanf("%d", &uNum);
	scanf("%d", &sNum);
	sets.resize(sNum);

	// clear buffer
	cin.ignore();

using_added_set.assign(sNum, 0);

	// answer initialize.
	answer.resize(uNum, 0);
	// for (int i = 0; i < uNum; i++) {
	// 	answer[i] = 1;
	// 	Sum_ans += i+1;
	// }
	

	// buff에 열을 입력한다.
	for (int i = 0; i < sNum; i++) {
		fgets(buff, sizeof(buff), stdin);
		pch = strtok(buff, " ");
		while (pch != NULL) {
			sets[i].insert(atoi(pch));
			pch = strtok(NULL, " ");
		}
	}
	myQuickSort(sets, subset_cnt, 0, sNum - 1);
	
	contents.binary_state.assign(uNum, 0);
	contents.added_set.assign(sNum, 0);

	tree.push(contents);
	temp_node = tree.top();
	
	tree.pop();

	temp_node.level++;

	tree.push(temp_node);


	for (auto it = sets[temp_node.level - 1].begin(); it != sets[temp_node.level - 1].end(); it++) {
		if (*it > 0) {
			temp_node.binary_state[*it - 1] = 1;
		}
	}

	//cout << "after binary_state:";

	/*for (int i = 0; i < uNum; i++) {
		cout << temp_node.binary_state[i] << " ";
	}
	cout << endl;
	cout << "===============================================" << endl;*/



	//cout << "current_sum: " << temp_node.current_sum << endl;
	using_added_set = temp_node.added_set;
	temp_node.added_set[temp_node.level - 1] = 1;
	//cout << "level : " << temp_node.level << endl;
	//cout << "Before left push stack.size: " << tree.size() << endl;
	tree.push(temp_node);
	//cout << "level : " << temp_node.level << endl;
	//cout << "After left push stack size: " << tree.size() << endl;
	
	
	while (!tree.empty()) {
		//cout << "HI" << endl;
		// 정리 : while문 내에서 연속으로 pop 되는 경우가 고려되지 않았다.
		// 이전 상태
		// added_set
		if (answer == temp_node.binary_state)
		{
			// added vector 원소의 합
			temp_sol = 0;
			for (int i = 0; i < sNum; i++) {
				temp_sol += temp_node.added_set[i];
			}
			//cout << "sol: " << temp_sol << endl;

			if (temp_sol < best_sol && temp_sol != 0) {
				best_sol = temp_sol;
				//cout << "best_sol: " << best_sol << endl;
			}

			//cout << "sol_pop()" << endl;
		// ===================================================================
		}

		if (temp_node.added_set == using_added_set) {
			//cout << "Before left push stack.size: " << tree.size() << endl;
			tree.pop();
			//cout << "After left push stack size: " << tree.size() << endl;
			temp_node = tree.top();
	
			//cout << "5. pop stack size : " << tree.size() << endl;
		}

		while (temp_node.level == sNum ) {

			if (temp_node.level == sNum) {
				/*cout << "temp1_node.level :" << temp1_node.level << endl;
				cout << "temp_node.level :" << temp_node.level << endl;
				*/
				//cout << "level pop()" << endl;
			}


			//cout << "Before left push stack.size: " << tree.size() << endl;
			tree.pop();
			//cout << "After left push stack size: " << tree.size() << endl;



			if (tree.empty()) {
				cout << best_sol << endl;

				return 0;
			}

			temp_node = tree.top();
			
			//cout << "6. pop stack size : " << tree.size() << endl;
			//cout << "Z : " << temp_node.level << endl;
		}

		
		//cout << "Before left push stack.size: " << tree.size() << endl;
		tree.pop();
		//cout << "After left push stack size: " << tree.size() << endl;
		//cout << "tree.pop()" << endl;
		temp_node.level++;
		//cout << "level : " << temp_node.level << endl;
		//cout << "Before right stack size: " << tree.size() << endl;
		tree.push(temp_node);
		//cout << "level : " << temp_node.level << endl;
		//cout << "After right stack size: " << tree.size() << endl;
		temp_node = tree.top();
		
		//cout << "3. push stack size : " << tree.size() << endl;
		//cout << "Z : " << temp_node.level << endl;
		//================================struct component update================================

		//cout << "before binary_state:";
		//for (int i = 0; i < uNum; i++) {
		//	cout << temp_node.binary_state[i] << " ";
		//}
		//cout << endl;
		//cout << "temp_node.levelA : " << temp_node.level << endl;
		for (auto it = sets[temp_node.level - 1].begin(); it != sets[temp_node.level - 1].end(); it++) {
			// struct component 1
			//cout << "temp_node level:"<< temp_node.level<< endl;
			if (*it > 0) {
				temp_node.binary_state[*it - 1] = 1;
			}
		}

		//cout << "after binary_state:";
		//for (int i = 0; i < uNum; i++) {
		//	cout << temp_node.binary_state[i] << " ";

		//}
		//cout << endl;
		// struct component 4

	
		//cout << "temp_node.current_sum: " << temp_node.current_sum << endl;

		// struct component 3
		//cout << "temp_node.level" << temp_node.level << endl;
		//cout << "temp2_level: " << (temp_node.level - 1) << endl;
		/*if (temp_node.level == 11) {
			return 0;
		}*/
		using_added_set = temp_node.added_set;
		temp_node.added_set[temp_node.level - 1] = 1;
		//====================================================================================


		/*cout << "level : " << temp_node.level << endl;
		cout << "Before left push stack.size: " << tree.size() << endl;*/
		
		tree.push(temp_node);
		temp_node = tree.top();
		
		//cout << "4. push stack size : " << tree.size() << endl;
		/*cout << "Z : " << temp_node.level << endl;
		cout << "level : " << temp_node.level << endl;
		cout << "After left push stack.size: " << tree.size() << endl;
*/
		//cout << "===============================================" << endl;

		// ============================= 정답 =================================

		// level이 sNum 부분 집합의 개수보다 많으면

		// 나머지 수를 더해도 안되는 경우 pop

		// 정답과 같고, 기존 solution보다 더 나은 solution일 경우.
		/*cout << "temp_node.level: " << temp_node.level << endl;
		cout << "Sum_ans: " << Sum_ans << endl;
		cout << "temp_node.current_sum: " << temp_node.current_sum << endl;
		cout << "pre_sum_value: " << pre_sum_value << endl;
*/
		

	}

	//cout << contents.binary_state[0] << "\n";
	cout <<  best_sol << endl;

	return 0;
}