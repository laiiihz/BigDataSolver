#include "main.h"
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
		if (i % 1000 == 0)cout << counter[i].count << "\t" << counter[i].password << endl;
		i++;
	}
	return i - 1;
}
void questionFour() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	/*Question 4*/
	struct user_list list_user_head = { "\0","\0",NULL };
	ifstream file_read_user("user.txt", ios::in);
	if (!file_read_user) {
		cout << "WARING: read \'user.txt\' wrong" << endl;
		return ;
	}
	struct user_list *temp_list = &list_user_head;

	int i = 0;
	int data_size = 200;				//修改随机数据大小
	while (!file_read_user.eof()) {
		string one_line;
		getline(file_read_user, one_line);
		struct user_list *point_user_list = new user_list;
		point_user_list->password = one_line.substr(one_line.find('\t') + 1);
		point_user_list->user_id = one_line.substr(0, one_line.find('\t'));
		point_user_list->next = NULL;
		temp_list->next = point_user_list;
		temp_list = temp_list->next;
		i++;
	}
	//using list_user_head to use list
	random_device rd;	//real radom numbers generator
	int find = 0;
	int not_find = 0;

	for (int i = 0; i < data_size; i++) {
		unsigned int random_number = rd() % 1230000;
		user_list *point = &list_user_head;
		point = point->next;
		while (point->next != NULL) {
			if (atoi(point->user_id.c_str()) == random_number) {
				find++;
				break;

			}
			point = point->next;
		}
		if (i % (data_size / 10) == 0) {
			system("cls");
			cout << (i + 0.0) / 200 * 100 << "%" << endl;
		}
		if (point->next == NULL)cout << "not Find" << endl;
	}
	for (int i = 0; i < data_size; i++) {
		unsigned int random_number_bigger = rd() % 1230000 + 2000000;
		user_list *point = &list_user_head;
		point = point->next;
		while (point->next != NULL) {
			if (atoi(point->user_id.c_str()) == random_number_bigger) {
				find++;
				break;
			}
			point = point->next;
		}
		if (i % (data_size / 10) == 0) {
			system("cls");
			cout << (i + 0.0) / 200 * 100 << "%" << endl;
		}
		if (point->next == NULL)not_find++;
	}
	cout << not_find << endl;
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout << duration_s.count() << " seconds" << std::endl;
}
void questionFive() {
	ifstream file_read_user("user.txt", ios::in);
	if (!file_read_user) {
		cout << "WARING: read \'user.txt\' wrong" << endl;
		return ;
	}
	struct user_two_bit_node *root;
	root = NULL;
	int i = 0;

	while (!file_read_user.eof()) {
		string one_line;
		getline(file_read_user, one_line);
		int temp_id = atoi(one_line.substr(0, one_line.find('\t')).c_str());
		string temp_psw = one_line.substr(one_line.find('\t') + 1);
		insertTwoBitNode(&root, temp_id, temp_psw);
		i++;
		if (i % 10000 == 0)cout << i << endl;
	}
	int a = 0;
	int find = 0;
	int not_find = 0;
	int data_size = 2000;
	random_device rd;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int j = 0; j < data_size; j++) {
		unsigned int random_number = rd() % 1230000;
		if (binaryTreeSearch(root, random_number) != NULL)find++;
		else not_find++;
	}
	for (int j = 0; j < data_size; j++) {
		unsigned int random_number = rd() % 1230000 + 2000000;
		if (binaryTreeSearch(root, random_number) != NULL)find++;
		else not_find++;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout << duration_s.count() << " seconds" << std::endl;
	cout << find << " " << not_find;
	cout << find << " " << not_find << endl;		//输出查找结果

}
void questionSix() {
	ifstream  file_read_user_sorted("user_sorted.txt", ios::in);
	if (!file_read_user_sorted) {
		cout << "WARING: read \'user_sorted.txt\' wrong" << endl;
		return ;		
	}
	//struct user_sorted_struct USS[1230000];
	int i = 0;
	while (!file_read_user_sorted.eof()) {
		string one_line;
		getline(file_read_user_sorted, one_line);
		user_sorted_int[i] = atoi(one_line.c_str());
		i++;

		if (i % 10000 == 0) {
			system("cls");
			cout << i / 12300 << endl;
		}
	}
	int find = 0;
	int not_find = 0;
	int data_size = 2000;
	random_device rd;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int j = 0; j < data_size; j++) {
		unsigned int random_number = rd() % 1230000;
		if (binarySearch(random_number, 0, 1230000) != -1)find++;
		else not_find++;
	}
	for (int j = 0; j < data_size; j++) {
		unsigned int random_number = rd() % 1230000 + 2000000;
		if (binarySearch(random_number, 0, 1230000) != -1)find++;
		else not_find++;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout << duration_s.count() << " seconds" << std::endl;
	cout << find << " " << not_find;
}
void questionSeven() {
	ifstream	file_read_psw("password.txt", ios::in);
	if (!file_read_psw) {
		cout << "WARING: read \'password.txt\' wrong" << endl;
		return ;
	}



	int i = 0;
	while (!file_read_psw.eof()) {
		string one_line;
		getline(file_read_psw, one_line);
		int temp_data = atoi(one_line.substr(one_line.find('\t') + 1).c_str());
		string temp_password_key = one_line.substr(0, one_line.find('\t'));
		int temp_int = std_hash_string(temp_password_key);
		pfh[temp_int].data = temp_data;
		pfh[temp_int].password_key = temp_password_key;
		i++;
		if (i % 1000 == 0) {
			system("cls");
			cout << i / 380 << endl;
		}
	}
	int find = 0;
	int not_find = 0;
	random_device rd;
	for (int q = 0; q < 2000; q++) {
		string random_in_string = pfh[rd() % 100000].password_key;
		int temp_int = std_hash_string(random_in_string);
		int temp_data = pfh[temp_int].data;
		int temp_key = std_hash_string(pfh[temp_int].password_key);
		if (temp_int == temp_key && pfh[temp_int].data != 0) {
			cout << pfh[temp_int].password_key << " " << temp_data << endl;
			find++;
		}
	}

	for (int q = 0; q < 1000; q++) {
		string random_in_string = pfh[rd() % 100000].password_key;
		random_in_string += "1habw;,.45r5";
		int temp_int = std_hash_string(random_in_string);
		int temp_data = pfh[temp_int].data;
		int temp_key = std_hash_string(pfh[temp_int].password_key);
		//cout << "temp_int" << temp_int<<" temp_key"<<temp_key<<endl;
		//Sleep(700);
		if (temp_int == temp_key && pfh[temp_int].data != 0) {
			cout << pfh[temp_int].password_key << " " << temp_data << endl;
			find++;
		}
	}
	cout << find << " " << not_find;
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

void insertTwoBitNode(user_two_bit_node ** root,int id,string user_password) {
	user_two_bit_node *temp = NULL;
	if (!(*root)) {
		temp = new user_two_bit_node;
		temp->lchind = NULL;
		temp->rchind = NULL;
		temp->user_id = id;
		temp->password = user_password;
		*root = temp;
		return;
	}
	if (id < (*root)->user_id) {
		insertTwoBitNode(&(*root)->lchind, id, user_password);
	}
	else if (id > (*root)->user_id) {
		insertTwoBitNode(&(*root)->rchind, id, user_password);
	}
}


//binarySearch(二叉树指针,节点数据【用户账号ID】)
//返回是否查找到	true for find ，false for not find
user_two_bit_node* binaryTreeSearch(user_two_bit_node *root,int id) {
	if (root == NULL)return NULL;
	if (id == root->user_id)return root;
	else if (id < root->user_id)
		return binaryTreeSearch(root->lchind, id);
	else if (id > root->user_id)
		return binaryTreeSearch(root->rchind, id);
}

int binarySearch(int id, int i, int j) {
	while (i<=j) {
		int mid =(i + j) / 2;
		if (user_sorted_int[mid] == id)return mid;
		else if (user_sorted_int[mid] < id)i = mid + 1;
		else j = mid - 1;
	}
	return -1;
}

int std_hash_string(string password){
	hash<string> hash_string;
	return hash_string(password)%100000;
}

int main() {
	//questionOne();
	//questionTwo();
	//questionTree();
	//questionFour();
	//questionFive();
	//questionSix();
	//questionSeven();
	
	
}