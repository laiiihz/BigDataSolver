#include "main.h"
using namespace std;
struct user {
	string user_id;
	string password;
}user[1230000];
struct counter {
	string password;
	int count;
}counter[1230000];
int main(void) {
	//第一题开始
	ifstream file_in("user.txt", ios::in);
	ofstream file_out("password.txt", ios::out);
	if (!file_in) return 0;
	int i = 0;
	while (!file_in.eof()) {
		string one_line;
		getline(file_in, one_line);
		user[i].password = one_line.substr(one_line.find("\t") + 1);
		i++;
	}
	/*for (int i = 0; i < 1230000; i++) {
	cout << user[i].password << endl;
	}*/
	for (int i = 0; i < 1230000; i++) {
		counter[i].password = "\0";
	}
	cout << 11 << endl;
	for (int i = 0; i < 1230000; i++) {//user
		if (i % 100000 == 0)cout << i << endl;
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
	if (!file_out)return 0;
	int a = 0;
	while (counter[a].count>0) {
		file_out << counter[a].password << "\t" << counter[a].count << endl;
		a++;
	}
	cout << 111;
}