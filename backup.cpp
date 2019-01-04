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
������ ��
1. sets �� ������ �迭 vector�μ� ǥ���ϱ�.
2. ���� ���� üũ�ϴ� ���� vector �����?
3. 1�� set�� �ְ�, 2�� set�� ������ �ʳ����� �˰����� ���� ��, �߰�
	-  �������� �� ���� �Ŀ��� ���� solv���� �۴� �׷��� ���� �κ� ó��
4. best solv���?������ �ֱ�
*/

struct node {

	vector <int> binary_state; // ���� state �������� ǥ��
	vector <int> added_set; // �߰��� level üũ.
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
	int uNum;
	int sNum;
	int best_sol = 999999999;
	int temp_sol = 0;
	int Sum_ans = 0;
	int pre_sum_value = 0;

	vector<int> subset_cnt;
	vector<set<int> > sets;
	vector<int> answer;
	vector<int> temp2;
	//struct node temp1_node;
	struct node temp_node;
	// struct ���� �߰�
	struct node contents;
	stack<node> tree;

	// uNUM: N���� ���?���� ����, sNUM: subset ����
	scanf("%d", &uNum);
	scanf("%d", &sNum);
	sets.resize(sNum);
	subset_cnt.resize(sNum, 0);
	// clear buffer
	cin.ignore();

	// answer initialize.
	answer.resize(uNum, 0);
	/*cout << "Check_answer:";*/
	for (int i = 0; i < uNum; i++) {
		answer[i] = 1;
		Sum_ans += i + 1;
		//cout << answer[i] << " ";
		//cout << Sum_ans << endl;
	}

	// buff�� ���� �Է��Ѵ�.
	for (int i = 0; i < sNum; i++) {
		fgets(buff, sizeof(buff), stdin);
		pch = strtok(buff, " ");
		while (pch != NULL) {
			sets[i].insert(atoi(pch));
			pch = strtok(NULL, " ");
			subset_cnt[i]++;
		}
	}

	// quick sort�ϴ� ���?
	/*for (int i = 0; i < sNum; i++) {
		for (int j = 0; j < sNum - 1; j++) {
			int temp = sets[j].size();
			if (temp < sets[j + 1].size()) {
				sets[j + 1].swap(sets[j]);
			}
		}
	}*/
	myQuickSort(sets, subset_cnt, 0, sNum - 1);
	//cout << "sets.size()" << sets.size() << endl;

	contents.binary_state.assign(uNum, 0);
	contents.added_set.assign(sNum, 0);

	// stack�� node �ϳ��� �������?�����ϱ�.
	// contents.binary_state �� �ֱ�

	// first �ƹ��͵� �������?���� ���� node2

	// level 1������ �����ϱ�
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



	pre_sum_value = temp_node.current_sum;
	temp_node.current_sum = 0;

	for (int i = 0; i < uNum; i++) {
		temp_node.current_sum += temp_node.binary_state[i] * (i + 1);
	}
	temp_node.added_set[temp_node.level - 1] = 1;
	tree.push(temp_node);

	while (!tree.empty()) {

		// ���� : while�� ������ �������� pop �Ǵ� ���?�������?�ʾҴ�.
		// ���� ����
		if (answer == temp_node.binary_state)
		{
			// added vector ������ ��
			temp_sol = 0;
			for (int i = 0; i < sNum; i++) {
				temp_sol += temp_node.added_set[i];
			}

			if (temp_sol < best_sol && temp_sol != 0) {
				best_sol = temp_sol;
			}

			//cout << "best_sol: "<<best_sol<<endl ;
		// ===================================================================
		}

		// �����?����, ���� solution���� �� ���� solution�� ���?
		if (pre_sum_value == temp_node.current_sum) {
			//cout << "Before left push stack.size: " << tree.size() << endl;
			tree.pop();
			//cout << "After left push stack size: " << tree.size() << endl;
			temp_node = tree.top();
			//cout << "5. stack size : " << tree.size() << endl;
		}

		while (temp_node.level == sNum || Sum_ans < temp_node.current_sum) {

			if (temp_node.level == sNum) {
				/*cout << "temp1_node.level :" << temp1_node.level << endl;
				cout << "temp_node.level :" << temp_node.level << endl;
				*/
				//cout << "level pop()" << endl;
			}
			if (Sum_ans < temp_node.current_sum)
			{
				//cout << "Sum_ans pop()" << endl << endl << endl;
			}

			//cout << "Before left push stack.size: " << tree.size() << endl;
			tree.pop();
			//cout << "After left push stack size: " << tree.size() << endl;



			if (tree.empty()) {
				cout << best_sol << endl;
				return 0;
			}
			temp_node = tree.top();
			//cout << "6. stack size : " << tree.size() << endl;
			//cout << "Z : " << temp_node.level << endl;
		}



		tree.pop();
		temp_node.level++;
		tree.push(temp_node);

		//================================struct component update================================

		for (auto it = sets[temp_node.level - 1].begin(); it != sets[temp_node.level - 1].end(); it++) {
			// struct component 1
			//cout << "temp_node level:"<< temp_node.level<< endl;
			if (*it > 0) {
				temp_node.binary_state[*it - 1] = 1;
			}
		}

		// struct component 4

		pre_sum_value = temp_node.current_sum;
		temp_node.current_sum = 0;
		for (int i = 0; i < uNum; i++) {
			temp_node.current_sum += temp_node.binary_state[i] * (i + 1);
		}

		//cout << "temp_node.current_sum: " << temp_node.current_sum << endl;

		// struct component 3
		//cout << "temp_node.level" << temp_node.level << endl;
		temp_node.added_set[temp_node.level - 1] = 1;
		//====================================================================================



		tree.push(temp_node);
		temp_node = tree.top();
		// ============================= ���� =================================

		// level�� sNum �κ� ������ �������� ������

		// ������ ���� ���ص� �ȵǴ� ���?pop


	}

	//cout << contents.binary_state[0] << "\n";
	cout << best_sol << endl;

	return 0;
}