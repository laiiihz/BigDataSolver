#include "main.h"
#define TIME high_resolution_clock::time_point	//时间对象
#define TIME_NOW high_resolution_clock::now()	//现在的时间
using namespace std;
using namespace chrono;

//void timeCount(时间开始，时间结束)

void timeCount(TIME t1,TIME t2) {
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout<<"用时"<<duration_s.count()<<"秒"<<endl;
}

//返回时间差
int timeCountReturn(TIME t1, TIME t2) {
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	return duration_s.count();
}





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
//返回password条数 
/*by laiiihz*/
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
		i++;
	}
	return i - 1;
}

int questionTwo_CP() {
	ifstream file_read("user.txt", ios::in);
	if (!file_read) {
		cout << "WARING: read \'user.txt\' wrong" << endl;
		return 0;
	}
	int i = 0;
	while (!file_read.eof()) {
		string password_line;
		getline(file_read, password_line);
		users[i].password = password_line.substr(password_line.find('\t') + 1);
		users[i].count = atoi(password_line.substr(0, password_line.find('\t')).c_str());
		i++;
	}
	return i - 1;
}

//返回password条数
/*by gta*/
int openPassword(string FILE_READS) {
	ifstream password(FILE_READS, ios::in);
	if (!password) {
		cout << "WARING: read "<< FILE_READS<<" wrong" << endl;
		return 0;
	}
	int k = 0;
	while (!password.eof()) {
		string password_line;
		getline(password, password_line);
		co[k].password = password_line.substr(0, password_line.find('\t'));
		co[k].count = atoi(password_line.substr(password_line.find('\t') + 1).c_str());
		k++;
	}
	return k;
}

int openPassword_CP(string FILE_READS) {
	ifstream password(FILE_READS, ios::in);
	if (!password) {
		cout << "WARING: read " << FILE_READS << " wrong" << endl;
		return 0;
	}
	int k = 0;
	while (!password.eof()) {
		string password_line;
		getline(password, password_line);
		co[k].password = password_line.substr(password_line.find('\t') + 1);
		co[k].count = atoi(password_line.substr(0, password_line.find('\t')).c_str());
		k++;
	}
	return k;
}

void fileOutPut() {
	ofstream file_out("user_sorted.txt", ios::out);
	if (!file_out) {
		cout << "WARING: write \'password.txt\' wrong" << endl;
		return;
	}
	int a = 0;
	while (a<100) {
		file_out <<users[a].count << endl;
		a++;
	}
}


//排序函数
void questionFour() {
	TIME t1 = TIME_NOW;		//计时起点
	/*Question 4*/
	struct user_list list_user_head = { "\0","\0",NULL };	//链表头指针
	ifstream file_read_user("user.txt", ios::in);
	if (!file_read_user) {
		cout << "WARING: read \'user.txt\' wrong" << endl;
		return ;
	}
	struct user_list *temp_list = &list_user_head;

	int i = 0;
	int data_size = 200;				//修改随机数据大小

	//文件读取放入链表
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
	random_device rd;	//随机数生成器
	int find = 0;
	int not_find = 0;

	for (int i = 0; i < data_size; i++) {
		unsigned int random_number = rd() % 1230000;	//随机数
		user_list *point = &list_user_head;	
		point = point->next;
		while (point->next != NULL) {
			if (atoi(point->user_id.c_str()) == random_number) {
				find++;
				break;

			}
			point = point->next;
		}

		//进度显示
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
	for (int q = 0; q < 1000000; q++) {
		string random_in_string = pfh[rd() % 200000].password_key;
		int temp_int = std_hash_string(random_in_string);
		int temp_data = pfh[temp_int].data;
		int temp_key = std_hash_string(pfh[temp_int].password_key);
		if (temp_int == temp_key && pfh[temp_int].data != 0) {
			cout << pfh[temp_int].password_key << " " << temp_data << endl;
			find++;
		}
	}

	for (int q = 0; q < 1000; q++) {
		string random_in_string = pfh[rd() % 200000].password_key;
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
void Bubblesort(struct counter c[],int n) {
	int i, j, k;
	bool exchange;
	struct counter temp;
	for (i = 0; i < n - 1; i++) {
		exchange = false;
		for (j = n - 1; j > i; j--) {
			if (c[j].count > c[j - 1].count) {
				//temp.count = counter[j].count;
				//temp.password = counter[j].password;
				temp = c[j];
				c[j] = c[j - 1];
				//	counter[j - 1].count = temp.count;
				//	counter[j - 1].password = temp.password;
				c[j - 1] = temp;
				exchange = true;
			}
		}
		if (!exchange)return;
	}
}
void mergeSort(int low, int high) {
	if (low < high) {
		int mid = low + (high - low) / 2;
		mergeSort(low, mid);
		mergeSort(mid + 1, high);
		mergeAlgorithm(low, mid, high);
	}
}
void mergeAlgorithm(int low,int mid,int high) {
	int length_left = mid - low + 1;
	int length_right = high - mid;
	struct counter *temp_left= new struct counter[length_left];
	struct counter *temp_right = new struct counter[length_right];
	for (int i = 0; i < length_left; i++) {
		temp_left[i].count = counter[low + i].count;
		temp_left[i].password = counter[low + i].password;
	}
	for (int i = 0; i < length_right; i++) {
		temp_right[i].count = counter[mid + 1 + i].count;
		temp_right[i].password = counter[mid + 1 + i].password;
	}
	int q = 0;
	int w = 0;
	int e = low;
	while (q < length_left&&w < length_right) {
		if (temp_right[q].count <= temp_left[w].count) {
			counter[e].count = temp_left[q].count;
			counter[e].password = temp_left[q].password;
			q++;
		}
		else {
			counter[e].count = temp_left[w].count;
			counter[e].password = temp_left[w].password;
			w++;
		}
		e++;
		

	}
	while (q < length_left) {
		counter[e].count = temp_left[q].count;
		counter[e].password = temp_left[q].password;
		q++;
		e++;
	}
	while (w < length_right) {
		counter[e].count = temp_right[w].count;
		counter[e].password = temp_right[w].password;

		w++;
		e++;
	}
	delete[]temp_left;
	delete[]temp_right;
}
void shellSort(struct counter c[],int number) {
	struct counter temp;
	int i, j, d;
	d = number / 2;
	while (d > 0) {
		for (i = d; i < number; i++) {
			temp = c[i];
			j = i - d;
			while (j >= 0 && temp.count > co[j].count) {
				c[j + d] = c[j];
				j -= d;
			}
			co[j + d] = temp;
		}
		d = d / 2;
	}
}
int getMax(struct counter c[], int number) {
	int i, max;
	max = c[0].count;
	for (i = 1; i < number; i++)
		if (c[i].count> max)
			max = c[i].count;
	return max;
}
void countSort(struct counter c[], int number, int exp) {    
	struct counter *output;
	output= new struct counter[number];
	int i, buckets[10] = { 0 };
	for (i = 0; i < number; i++)
		buckets[(c[i].count/ exp) % 10] ++;
	for (i = 1; i < 10; i++)
		buckets[i] += buckets[i - 1];
	for (i = number - 1; i >= 0; i--) {
		output[buckets[(c[i].count/ exp) % 10] - 1] = c[i];
		buckets[(c[i].count / exp) % 10] --;
	}
	for (i = 0; i < number; i++)
		c[i] = output[i];
}
void radixSort(struct counter c[], int number) {     //基数排序 
	int exp;
	int max = getMax(c, number);
	for (exp = 1; max / exp > 0; exp *= 10)
		countSort(c, number, exp);
}
void sift(int low, int high) {
	int i = low, j = 2 * i;
	struct counter temp = co[i];
	while (j <= high) {
		if (j<high&&co[j].count>co[j + 1].count)
			j++;
		if (temp.count>co[j].count) {
			co[i] = co[j];
			i = j;
			j = 2 * i;
		}
		else break;
	}
	co[i] = temp;
}
void heapSort(int number) {
	int i;
	for (i = number / 2; i >= 0; i--)
		sift(i, number);
	for (i = number; i >= 1; i--) {
		swap(co[0], co[i]);
		sift(0, i - 1);
	}
}
int partition(struct counter c[], int s, int t) {
	int i = s, j = t;
	struct counter temp = c[i];
	while (i < j) {
		while (j > i&&co[j].count <= temp.count) j--;
		co[i] = co[j];
		while (i < j&&co[i].count >= temp.count) i++;
		co[j] = co[i];
	}
	c[i] = temp;
	return i;
}
void quickSort(struct counter c[], int s, int t) {
	int i;
	if (s < t) {
		i = partition(c, s, t);
		quickSort(c, s, i - 1);
		quickSort(c, i + 1, t);
	}
}

//
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

//二分查找
int binarySearch(int id, int i, int j) {
	while (i<=j) {
		int mid =(i + j) / 2;
		if (user_sorted_int[mid] == id)return mid;
		else if (user_sorted_int[mid] < id)i = mid + 1;
		else j = mid - 1;
	}
	return -1;
}


//计算字符串的哈希值
int std_hash_string(string password){
	hash<string> hash_string;
	string for_hash= password + ",-!~";		//计算两次哈希值解决哈希冲突
	return hash_string(password)%1000000+hash_string(for_hash)%1000000+100000;
}


//代码封装 Q2 排序
void RUN_BUBBLE() {
	int a = openPassword("password.txt");
	TIME t3s = TIME_NOW;
	Bubblesort(co,a);
	TIME t3e = TIME_NOW;
	cout << "Bubble Sort Time:\t";
	timeCount(t3s, t3e);
}
void RUN_SELECTION() {
	int a = questionTwo();
	TIME t2s = TIME_NOW;
	selectionSort(a);
	TIME t2e = TIME_NOW;
	cout << "Selection Sort Time:\t";
	timeCount(t2s, t2e);
}
void RUN_INSERT() {
	int a = questionTwo();
	TIME t1s = TIME_NOW;
	insertSort(a);
	TIME t1e = TIME_NOW;
	cout << "Insert Sort Time:\t";
	timeCount(t1s, t1e);
}
void RUN_SHELL() {
	int a = openPassword("password.txt");
	TIME t4s = TIME_NOW;
	shellSort(co, a);
	TIME t4e = TIME_NOW;
	cout << "Shell Sort Time :\t";
	timeCount(t4s, t4e);
}
void RUN_HEAP() {
	int a = openPassword("password.txt");
	TIME t5s = TIME_NOW;
	heapSort(a);
	TIME t5e = TIME_NOW;
	cout << "Heap   Sort Time:\t";
	timeCount(t5s, t5e);
}
void RUN_QUICK() {
	int a = openPassword("password.txt");
	TIME t1s = TIME_NOW;
	quickSort(co,0,a);
	TIME t1e = TIME_NOW;
	cout << "Quick Sort Time:\t";
	timeCount(t1s, t1e);
}
void RUN_MERGE() {
	int a = questionTwo();
	TIME t1s = TIME_NOW;
	mergeSort(0,a);
	TIME t1e = TIME_NOW;
	cout << "Merge Sort Time:\t";
	timeCount(t1s, t1e);
}


//代码封装 Q3 排序及输出
void RUN_BUBBLE_REVERSE() {
	int a = openPassword_CP("user.txt");
	cout << a << endl;
	a = 1000000;
	TIME t3s = TIME_NOW;
	Bubblesort(users, a);
	TIME t3e = TIME_NOW;
	cout << "Bubble Sort Time:\t(10000 data)";
	timeCount(t3s, t3e);
	cout << "估算1230000" << timeCountReturn(t3s, t3e)*1230000*1230000/10000/10000 << endl;
	fileOutPut();
}
void RUN_SELECTION_REVERSE() {
	int a = questionTwo();
	TIME t2s = TIME_NOW;
	selectionSort(a);
	TIME t2e = TIME_NOW;
	cout << "Selection Sort Time:\t";
	timeCount(t2s, t2e);
}
void RUN_INSERT_REVERSE() {
	int a = questionTwo();
	TIME t1s = TIME_NOW;
	insertSort(a);
	TIME t1e = TIME_NOW;
	cout << "Insert Sort Time:\t";
	timeCount(t1s, t1e);
}
void RUN_SHELL_REVERSE() {
	int a = openPassword_CP("user.txt");
	TIME t4s = TIME_NOW;
	shellSort(co, a);
	TIME t4e = TIME_NOW;
	cout << "Shell Sort Time :\t";
	timeCount(t4s, t4e);
}
void RUN_HEAP_REVERSE() {
	int a = openPassword_CP("user.txt");
	TIME t5s = TIME_NOW;
	heapSort(a);
	TIME t5e = TIME_NOW;
	cout << "Heap   Sort Time:\t";
	timeCount(t5s, t5e);
}
void RUN_QUICK_REVERSE() {
	int a = openPassword_CP("user.txt");
	TIME t1s = TIME_NOW;
	quickSort(co, 0, a);
	TIME t1e = TIME_NOW;
	cout << "Quick Sort Time:\t";
	timeCount(t1s, t1e);
}
void RUN_MERGE_REVERSE() {
	int a = questionTwo();
	TIME t1s = TIME_NOW;
	mergeSort(0, a);
	TIME t1e = TIME_NOW;
	cout << "Merge Sort Time:\t";
	timeCount(t1s, t1e);
}
void RUN_QUESTION_2() {
	
	//RUN_BUBBLE();
	//RUN_SELECTION();
	//RUN_INSERT();
	//RUN_SHELL();
	//RUN_HEAP();
	//RUN_QUICK();
	//RUN_MERGE();
}
void RUN_QUESTION_3() {
	RUN_BUBBLE_REVERSE();
	//RUN_SELECTION_REVERSE();
	//RUN_INSERT_REVERSE();
	//RUN_SHELL_REVERSE();
	//RUN_HEAP_REVERSE();
	//RUN_QUICK_REVERSE();
	//RUN_MERGE_REVERSE();
}

int main() {
	//questionOne();
	//RUN_QUESTION_2();
	//RUN_QUESTION_3();
	//questionFour();
	//questionFive();
	//questionSix();
	//questionSeven();
}