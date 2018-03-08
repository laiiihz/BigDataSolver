#include "main.h"
#include <chrono>
#include <ratio>
using namespace std;
using namespace chrono;

void questionOne() {
	ifstream file_in("user.txt", ios::in);		
	ofstream file_out("password.txt", ios::out);
	if (!file_in) {
		cout << "WARING: read \'user.txt\' wrong" << endl;
		return;
	}
	int i = 0;
	while (!file_in.eof()) {
		string one_line;
		getline(file_in, one_line);
		user[i].password = one_line.substr(one_line.find("\t") + 1);
		i++;
	}

	for (int i = 0; i < 1230000; i++) {
		counter[i].password = "\0";
	}
	cout << 11 << endl;
	for (int i = 0; i < 1230000; i++) {//user
		if (i % 10000 == 0) {
			system("cls");
			cout << i / 12300 << "%" << endl;
		}
		for (int j = 0; j < 1230000; j++) {//counter
			if (user[i].password.compare(counter[j].password) == 0) {
				counter[j].count++;
				break;
			}
			else {
				if (counter[j].password.compare("\0") == 0) {
					counter[j].password = user[i].password;
					counter[j].count = 1;
					break;
				}




			}
		}
	}
	if (!file_out) {
		cout << "WARING: write \'password.txt\' wrong" << endl;
		return;
	}
	int a = 0;
	while (counter[a].count>0) {
		file_out << counter[a].password << "\t" << counter[a].count << endl;
		a++;
	}
	cout << 111;
}

int questionTwo() {
	ifstream file_read("password.txt", ios::in);
	if (!file_read) {
		cout << "WARING: read \'password.txt\' wrong" << endl;
		return 0;
	}
	int i = 0;
	while (!file_read.eof()) {
		string password_line;
		getline(file_read, password_line);
		counter[i].password = password_line.substr(0, password_line.find('\t'));
		counter[i].count = atoi(password_line.substr(password_line.find('\t') + 1).c_str());
		if (i % 1000 == 0)cout << counter[i].count<<"\t"<<counter[i].password << endl;
		i++;
	}
	return i-1;
}



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



int main(void) {
	//第一题开始
	//questionOne();
	//第二题开始
	int a=questionTwo();
	cout << a << endl;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//insertSort(a);
	//quickSort(a);
	//cout<<"max_bit"<<countMaxBit(a);
	//shellSort(a);
	//radixSort(a);
	mergeSort(a);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	cout << "in seconds time:";
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout << duration_s.count() << " seconds" << std::endl;
	cout << counter[0].count << endl;
	cout << counter[1].count << endl;
	cout << counter[2].count << endl;

}