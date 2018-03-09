#include "main.h"
using namespace std;
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
		if (i % 1000 == 0)cout << counter[i].count << "\t" << counter[i].password << endl;
		i++;
	}
	return i - 1;
}