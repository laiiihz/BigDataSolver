#include "main.h"
using namespace std;

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
	for (int i = 0; i < number; i++) {
		int nowNumber=counter[i]
	}
}

int main(void) {
	//第一题开始
	//questionOne();

	//第二题开始
	cout<<questionTwo();
	
}