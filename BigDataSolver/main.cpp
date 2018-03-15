#include "main.h"
#define TIME high_resolution_clock::time_point	//ʱ�����
#define TIME_NOW high_resolution_clock::now()	//���ڵ�ʱ��
using namespace std;
using namespace chrono;

//void timeCount(ʱ�俪ʼ��ʱ�����)
//����ʱ���
void timeCount(TIME t1,TIME t2) {
	duration<double, ratio<1, 1>> duration_s(t2 - t1);
	cout<<"��ʱ"<<duration_s.count()<<"��"<<endl;
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
//����password���� 
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

//����password����
/*by gta*/
int openPassword() {
	ifstream password("password.txt", ios::in);
	if (!password) {
		cout << "WARING: read \'password.txt\' wrong" << endl;
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
void questionFour() {
	TIME t1 = TIME_NOW;		//��ʱ���
	/*Question 4*/
	struct user_list list_user_head = { "\0","\0",NULL };	//����ͷָ��
	ifstream file_read_user("user.txt", ios::in);
	if (!file_read_user) {
		cout << "WARING: read \'user.txt\' wrong" << endl;
		return ;
	}
	struct user_list *temp_list = &list_user_head;

	int i = 0;
	int data_size = 200;				//�޸�������ݴ�С

	//�ļ���ȡ��������
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
	random_device rd;	//�����������
	int find = 0;
	int not_find = 0;

	for (int i = 0; i < data_size; i++) {
		unsigned int random_number = rd() % 1230000;	//�����
		user_list *point = &list_user_head;	
		point = point->next;
		while (point->next != NULL) {
			if (atoi(point->user_id.c_str()) == random_number) {
				find++;
				break;

			}
			point = point->next;
		}

		//������ʾ
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
	cout << find << " " << not_find << endl;		//������ҽ��

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
void Bubblesort(int n) {
	int i, j, k;
	bool exchange;
	struct counter temp;
	for (i = 0; i < n - 1; i++) {
		exchange = false;
		for (j = n - 1; j > i; j--) {
			if (co[j].count > co[j - 1].count) {
				//temp.count = counter[j].count;
				//temp.password = counter[j].password;
				temp = co[j];
				co[j] = co[j - 1];
				//	counter[j - 1].count = temp.count;
				//	counter[j - 1].password = temp.password;
				co[j - 1] = temp;
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

void undefineHuajiFunc() {
	                                                                                    
  /*
                                                                                    
                                                                                                                                                       
                                                                                                                                             
                                                            .....```````````......                                                           
                                                 ..``-~~"";;======================;;"""~_`..                                                 
                                  .....    .._~";============================================;"~`.     ....                                  
                             ~rayP([AAK[(Ljevr==================================================xIe9Z/EA22[(P9!='                            
                           ~v?Ir===xI*e{oABMVS7r;=============================================IPpJJBK59eaIxr=rx!3v~                          
                           `.  `:";===;;;=rvZ&O|3;===========================================j&0B7v==;;;==;;"'.  .`                          
                           .:;=rr===========;*pVG;==========================================rp|BI;===========r=="-.                          
                        .~;===================XM3;==========================================={bG;================r="-.                       
                      _"=rr===================?<==============================================3!======================"`                     
                   .:=rrr============================================================================================rr=;_                   
                ..:;;""""~~~~~~~~~~~~~~~~""""";;;====================================;=====;"~"""~~~~~~~~~~~~~~~~""""";;==;-                 
            .;vjlw(5cx"`_________________________-:~"";============================;relw}w){<=``_________________________'~"-..              
         .`-ep6CAKEEA6[=`______________________________'~";=====================;"-r[2K[u[EA6XI______________________________-__`.           
        _'-'eXA[u/[[AGE=`_______---''''''---_______________"==================="```rCC[///[KGX<_________--'''''''---___________'--_.         
        .`_`'relw}}PL3=~"""";;;=============;;;;"""~~''':~";===================;~''_;*Tw(((Z1r~"""";;;;;============;;;"""~~:'':~:.          
           ~=;;==rr==;==============================================================;;;=rrr=;=====================================-          
          ~=========rrrrrrrrrrrrrrrrr================================================================rrrrrrrrrrrrrrrrrr============-         
         _======rrrrrrrrrrrrrrrrrrrrrrrr==========================================================rrrxrrrrrrrrrrrrrrrrrrrr==========`        
        .=======xxrrrrrrrrrrrrrrrrrrrxxxr========================================================rxxrrrrrrrrrrrrrrrrrrxxxxr=========;.       
        ~r=======rrrrrrrrrrrrrrrrrrrrrr============================================================rrrrrrrrrrrrrrrrrrrrrr============-       
       .;===================rr=======================================================================================================".      
       `==============================================================================================================================.      
       _==============================================================================================================================`      
       _=============r==================================================================================================r=============`      
       _=============rI================================================================================================vx=============`      
       .==============v!==============================================================================================v<=============;.      
       ."==============<3============================================================================================!3==============~       
        `===============!{r;=======================================================================================r13===============.       
         "===============v7*======================================================================================<7I===============:        
         ."===============r9fv==================================================================================v7yr===============".        
          .;================<)9v==============================================================================Is7<===============r"          
           ."r================?)L<r========================================================================ralZa================r"           
            ."=================ra5Pcv===================================================================rIyoL<==================~            
              _=================;=vy}Z4vr============================================================rIjP)1x==================;_             
               ."===================r<sP)9*xr====================================================rv3Tw)jIr===================~.              
                 `"====================rI1lwo93Ixr==========================================rx<4fww7evr=;==================".                
                   _"=r====================r<cLP}o7c3Ixrr============================rrv<3yLP})s3vr======================"`                  
                     `"=rr==================;==rv!e95P}wolTy43?!IIvvvvvvvvvII<*3ej{75P}wwly3Ixr======================r=~.                    
                       .:;===========================rxI*ej97l5PwPwwww}}}}}}wwP)LT{13<vrr========================rr="-.                      
                          `~;=================================rrrxxxxxxxxxxxrrrr=====;;========================r=;:.                         
                             .:"==========================================================================rr=="-.                            
                                .`~;======================================================================"~`.                               
                                    .`:";============================================================;"-`.                                   
                                         .`'~";====rr====================================rr====;"~-..                                        
                                               ..`'~"";;===============================;""~'`..                                              
                                                       ...``__'~~~~"""""""~~~~:-__`....                                                      
                                                                                                  
                                                                                    
*/


/*

                          .~xyAp$$p/e=_                                                                                                      
                       ~IKN#%%%%%%%%%Wh|s=.           .`_-~"~""""""""""""""""""~~:__.                    .'";;"~`                            
                    ~wW%%%%%%%%%%%%%%%%%%%%JI..'";=r==;;"~-_....             ...`-~";===r=;~`       "IubW%%%%%%%%%h|s=`                      
                   e%%%%%%%%%%%%%%%%%%%%%%%%%Pr="_.                                     ._";rrr;-~yQ%%%%%%%%%%%%%%%%%%WBr                    
                  3%%%%%%%%%%%%%%%%%%%%%%U7=.                                                 `"=lW%%%%%%%%%%%%%%%%%%%%%%@"                  
                 _W%%%%%%%%%%%%%%%%%%%W};                                                          "9U%%%%%%%%%%%%%%%%%%%%W~                 
                 v%%%%%%%%%%%%%%%%%%W3`                                                               =B%%%%%%%%%%%%%%%%%%%B                 
                 =%%%%%%%%%%%%%%%%%7.                                                                   ;|%%%%%%%%%%%%%%%%%h`                
                  [%%%%%%%%%%%%%%Wr                              __.        ._`                           vW%%%%%%%%%%%%%%%h.                
                   xb%%%%%%%%%%%Q"                          `"I7wT9<"_   -;;=PQBI-                         ~b%%%%%%%%%%%%%%y                 
                     ;}W%%%%%%%K.                    ."=x<jw/wZZlLEPI"  ."rr=;=v!fe=`                       .p%%%%%%%%%%%#3                  
                       .=(h%%Wx                       "r<cLw}5[|HQSE};  -=xr;;""_.~=I<=.                      8%%%%%%%WSr.                   
                           <Q:                      .;L0@UQUhWWW#Q/ox.  ."~rK|)LQUUnf}A3-                      $%%%h[r`                      
                          "[_                       .-"~---~"=;==;;".     ..-"";=rxI3a;'.                      _hj~                          
                         ~n~                                   `'~~.           .`..                             vj                           
                        `p"                                 ."r;`.                                               p;                          
                        [x                               .-""_=<9GnlI=;=r="'._;"`                                x)                          
                       v}                             ."rv=_   :;rv<3e!I<Ir;. ."xr-                              `p_                         
                      ~0'                            `;rv/8EG6GX2Z3r;;===="-_`  _I3=~_`.                          P;                         
                    =8%E                             ..."#%j~`           .``:=3fjrr="~'.                          ep"                        
                 .<Q%%%s                                 y%53f)wwye1jevxvr;"~`~U%=....                            3%%C:                      
               ~7W%%%%%u                                  3%%%%%%%%%%%%%%%%%%%W6"                                 4%%%%j.                    
              :W%%%%%%%W:                                  "5[m||Nhh#WWWhU#WWA;                                   B%%%%%Hr                   
              ~W%%%%%%%%b`                                  ..         ._:=r_                                    ~%%%%%%%%S'                 
              ~W%%%%%%%%%H=                                 .~""~'__`...```                                      m%%%%%%%%%W!                
              ~W%%%%%%%%%%%B;                                  .......                                         '|%%%%%%%%%%%%J"              
              ~W%%%%%%%%%%%%%Jv`                                                                             `4W%%%%%%%%%%%%%%Q              
              ~W%%%%%%%%%%%%%%%Wpv'                                                                       .;wW%%%%%%%%%%%%%%%%Q              
              ~W%%%%%%%%%%%%%%%%%%%Q}r:                                                               .~vA#%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%#pjr~.                                                    ."xf|W%%%%%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%WMKer;_.                                     ._"r<)BUW%%%%%%%%%%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%W#NOXwfe<xr=;""~~:'''':~~"";=rx<e7/BJUW%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Q              
              ~W%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%N              
               -''''''''''''''''''''''''''''''''-__`~":-':`_'__:'''''':__''__``~"_`__-''''''''''''''''''''''''''''''''''''''':_  

*/	
}

//binarySearch(������ָ��,�ڵ����ݡ��û��˺�ID��)
//�����Ƿ���ҵ�	true for find ��false for not find
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
	string for_hash= password + ",-!~";		//�������ι�ϣֵ�����ϣ��ͻ
	return hash_string(password)%1000000+hash_string(for_hash)%1000000+100000;
}

void RUN_BUBBLE() {
	int a = openPassword();
	TIME t3s = TIME_NOW;
	Bubblesort(a);
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
	int a = openPassword();
	TIME t4s = TIME_NOW;
	shellSort(co, a);
	TIME t4e = TIME_NOW;
	cout << "Shell Sort Time :\t";
	timeCount(t4s, t4e);
}
void RUN_HEAP() {
	int a = openPassword();
	TIME t5s = TIME_NOW;
	heapSort(a);
	TIME t5e = TIME_NOW;
	cout << "Heap   Sort Time:\t";
	timeCount(t5s, t5e);
}
void RUN_QUICK() {
	int a = openPassword();
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

}

int main() {
	//questionOne();
	RUN_QUESTION_2();
	//questionTree();
	//questionFour();
	//questionFive();
	//questionSix();
	//questionSeven();
	
	
}