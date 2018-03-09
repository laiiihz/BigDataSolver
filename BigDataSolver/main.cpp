#include "main.h"
using namespace std;
using namespace chrono;



void insertSort(int number) {
	for (int i = 1; i < number; i++) {
		int nowCount = counter[i].count;
		string nowPsd = counter[i].password;
		int j = i - 1;
		while (j >= 0 && counter[j].count < nowCount) {
			counter[j+1] = counter[j];
			j--;
		}
		counter[j+1].count = nowCount;
		counter[j+1].password = nowPsd;
	}
}
void selectionSort(int number) {
	for (int i = 0; i < number; i++) {
		int MAX = counter[i].count;
		int MAX_DOWN = i;
		for (int j = i; j < number; j++) {
			if (counter[j].count >= MAX) {
				MAX = counter[j].count;
				MAX_DOWN = j;
			}
		}
		temp = counter[MAX_DOWN];
		counter[MAX_DOWN] = counter[i];
		counter[i] = temp;
	}
}

void Merge( int s, int m, int e){
	int n1, n2;
	n1 = m - s + 1;
	n2 = e - m;
	int *l = new int[n1 + 1];
	int *h = new int[n2 + 1];
	int temp = s;
	for (int i = 0; i<n1; i++)
	{
		l[i] = counter[temp++].count;
	}
	temp = m + 1;
	for (int i = 0; i<n2; i++)
	{
		h[i] = counter[temp++].count;
	}
	for (int i = 0, j = 0, k = s; k <= e; k++)
	{
		if (l[i] >= h[j])
		{
			counter[k].count = l[i++];

		}
		else
		{
			counter[k].count = h[j++];
		}
	}
	delete[] l;
	delete[] h;

}
void MergeSort( int s, int e){
	if (e>s){
		int p = (s + e) / 2;
		MergeSort( s, p);
		MergeSort( p + 1, e);
		Merge( s, p, e);
	}

}
void mergeSort(int number) {
	MergeSort(0, number);
}
void shellSort( int number) {
	
	if (number <= 1)return;
	for (int div = number / 2; div >= 1; div = div / 2) {
		for (int i = 0; i <= div; ++i) {
			for (int j = i; j<number - div; j += div)
				for (int k = j; k<number; k += div)
					if (counter[j].count<counter[k].count) {
						temp = counter[j];
						counter[j] = counter[k];
						counter[k] = temp;
					}
		}
	}
}

//not finish
void radixSort(int number){
	int max_bit = countMaxBit(number);
	int bucket[10][10] = { 0 };
	int order[10] = { 0 };
	for (int r = 1; max_bit>0; max_bit--, r *= 10) {
		for (int i = 0; i<number; i++) {
			int lsd = (counter[i].count / r) % 10;
			bucket[lsd][order[lsd]++] = counter[i].count;
		}
		int k = 0;
		for (int i = 0; i<10; i++) {
			if (order[i] != 0) {
				for (int j = 0; j<order[i]; j++)
					counter[k++].count = bucket[i][j];
			}
			order[i] = 0;
		}
	}
}

int countMaxBit(int number) {
	int max_bit=1;
	int multi = 10;
	for (int i = 0; i < number;i++) {
		while (counter[i].count >= multi) {
			multi *= 10;
			max_bit++;
		}
	}
	return max_bit;
}

void heapSort(int number){

}

void questionFour() {

}

int main(void) {
	//第一题开始
	//questionOne();
	//第二题开始
	//int a=questionTwo();
	//cout << a << endl;
	/*high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//insertSort(a);
	//quickSort(a);
	//cout<<"max_bit"<<countMaxBit(a);
	//shellSort(a);
	//radixSort(a);
	//mergeSort(a);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	cout << "in seconds time:";
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout << duration_s.count() << " seconds" << std::endl;
	cout << counter[0].count << endl;
	cout << counter[1].count << endl;
	cout << counter[2].count << endl;*/


	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	/*Question 4*/
	struct user_list list_user_head = {"\0","\0",-1,NULL};
	ifstream file_read_user("user.txt", ios::in);
	if (!file_read_user) {
		cout << "WARING: read \'user.txt\' wrong" << endl;
		return 0;
	}
	struct user_list *temp_list =&list_user_head;
	
	int i = 0;
	while (!file_read_user.eof()) {
		string one_line;
		getline(file_read_user, one_line);
		struct user_list *point_user_list=new user_list;
		point_user_list->my_count = i;
		point_user_list->password = one_line.substr(one_line.find('\t')+1);
		point_user_list->user_id =one_line.substr(0,one_line.find('\t')) ;
		point_user_list->next = NULL;
		temp_list->next = point_user_list;
		temp_list = temp_list->next;
		i++;
	}
	//using list_user_head to use list
	random_device rd;	//real radom numbers generator
	for (int i = 0; i < 2000; i++) {
		unsigned int random_number = rd() % 1230000;
		user_list *point=&list_user_head;
		point = point->next;
		while (point->next != NULL) {
			if (atoi(point->user_id.c_str()) == random_number) {
				if(i%50==0)cout << "find!\tid:" << point->user_id << "\t\tpsw:" << point->password << endl;
				break;
			}
			point = point->next;
		}
		if(point->next==NULL)cout << "not find" << endl;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout << duration_s.count() << " seconds" << std::endl;
}