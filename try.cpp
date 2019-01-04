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

void myQuickSort(vector<set<int> >& v,vector<int>& arr, int start, int end) {
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


int main(void){
	char buff[1024];
	char *pch;
	int uNum=0;
	int sNum=0;
	int best_sol = 999999999;
	int temp_sol = 0;
	int Sum_ans = 0;
	int pre_sum_value = 0;
    int pruning_level = 0;
	clock_t s, e;

	vector<int> subset_cnt;
	vector<set<int> > sets;
	vector<int> answer;
    vector<int> using_added_set;
	//struct node temp1_node;
    vector<int> using_binary_state;
	struct node temp_node;
	// struct 구조 추가
	struct node contents;
	stack<node> tree;

    scanf("%d", &uNum);
	scanf("%d", &sNum);
	sets.resize(sNum);
    subset_cnt.resize(sNum, 0);
	
    cin.ignore();
    
	using_added_set.assign(sNum, 0);

    answer.resize(uNum, 0);


	for (int i = 0; i < sNum; i++) {
		fgets(buff, sizeof(buff), stdin);
		pch = strtok(buff, " ");
		while (pch != NULL) {
			sets[i].insert(atoi(pch));
			pch = strtok(NULL, " ");
			subset_cnt[i]++;
		}
	}
    myQuickSort(sets, subset_cnt, 0, sNum - 1);

	for (int i = 0; i < sNum; i++) {
		if (subset_cnt[i] == 1) {
			pruning_level = i;
			break;
		}
	}

	tree.push(contents);
	temp_node = tree.top();
	// cout << "====================================================" << endl;
	for (int i = 0; i < sNum; i++) {
		cout << temp_node.added_set[i] << " ";
	}
	cout << endl;

	tree.pop();

	temp_node.level++;

	tree.push(temp_node);

	using_binary_state = temp_node.binary_state;
	int count = 0;
	for (auto it = sets[temp_node.level - 1].begin(); it != sets[temp_node.level - 1].end(); it++) {
		if (*it > 0) {
			temp_node.binary_state[*it - 1] = 1;
			count++;
		}
	}

	using_added_set = temp_node.added_set;
	temp_node.added_set[temp_node.level - 1] = 1;
	tree.push(temp_node);

	while (!tree.empty()) {
		// leaf 노드일 때 pop()
		while (temp_node.level == sNum) {
			// cout << "A" << endl;

			tree.pop();
			
			if (tree.empty()) {
				cout <<  best_sol << endl;
				// e = clock();
				// double result = (double)(e - s);
				// cout << "\n수행시간 : " << result << endl;
				return 0;
			}

			temp_node = tree.top();
			// cout << "====================================================" << endl;
			// for (int i = 0; i < sNum; i++) {
			// 	cout << temp_node.added_set[i] << " ";
			// }
			// cout << endl;
		}

		tree.pop();
		if (tree.empty()) {
			cout << best_sol << endl;
			// e = clock();
			// double result = (double)(e - s);
			// cout << "\n수행시간 : " << result << endl;
			return 0;
		}

		// push 조건
		if (condition == 0) {
			// cout << "B" << endl;
			temp_node.level++;

			tree.push(temp_node);

			temp_node = tree.top();

			// cout << "====================================================" << endl;
			// for (int i = 0; i < sNum; i++) {
			// 	cout << temp_node.added_set[i] << " ";
			// }
			// cout << endl;

			using_binary_state = temp_node.binary_state;

			for (auto it = sets[temp_node.level - 1].begin(); it != sets[temp_node.level - 1].end(); it++) {

				if (*it > 0) {
					temp_node.binary_state[*it - 1] = 1;
				}
			}

			using_added_set = temp_node.added_set;
			temp_node.added_set[temp_node.level - 1] = 1;

			tree.push(temp_node);
			temp_node = tree.top();

			// cout << "====================================================" << endl;
			for (int i = 0; i < sNum; i++) {
				cout << temp_node.added_set[i] << " ";
			}

			cout << endl;
		}


		if (temp_node.level == pruning_level) {
			// cout << "C" << endl;
			int count_component = 0;

			for (int i = 0; i < uNum; i++) {
				count_component += temp_node.binary_state[i];
				// subset의 개수
			}

			for (int i = 0; i < sNum; i++) {
				temp_sol += temp_node.added_set[i];
			}

			temp_sol += uNum - count_component;

			if (temp_sol < best_sol && temp_sol != 0) {
				best_sol = temp_sol;
			}
			tree.pop();
			temp_node = tree.top();

			condition = 1;
		}
		else if (temp_node.level != pruning_level) {
			// cout << "D" << endl;
			condition = 0;
		}

		if (using_binary_state == temp_node.binary_state|| using_added_set==temp_node.added_set) {
			// cout << "E" << endl;
			// cout << "temp_node.level: " << temp_node.level << endl;
			tree.pop();
			// cout << "E2" << endl;
			// cout << "Check:" << tree.top().level << endl;
			temp_node = tree.top();
			// cout << "E3" << endl;
			// cout << "====================================================" << endl;
			for (int i = 0; i < sNum; i++) {
				cout << temp_node.added_set[i] << " ";
			}
			cout << endl;

		}

		// 정답일 때
		if (answer == temp_node.binary_state)
		{
			// cout << "F" << endl;
			// added vector 원소의 합
			int count_component = 0;

			for (int i = 0; i < sNum; i++) {
				temp_sol += temp_node.added_set[i];
			}
			//cout << "sol: " << temp_sol << endl;

			if (temp_sol < best_sol && temp_sol != 0) {
				best_sol = temp_sol;
				//cout << "best_sol: " << best_sol << endl;
			}
			condition = 1;
		}
		else if(answer != temp_node.binary_state){
			condition = 0;
		}

	}
	cout << best_sol << endl;

}