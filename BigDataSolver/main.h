#pragma once
#ifndef _MAIN_H__
#define _MAIN_H__
#include<iostream>
#include<string>
#include <Windows.h>
#include<fstream>	//提供文件操作函数
#include <chrono>	//提供计时函数
#include <random>	//提供随机数函数
#include <functional>	//提供string hash计算函数
#define MAXXX 1230000

using namespace std;

struct user {
	int user_id;
	string password;
};

struct counter {
	string password;
	int count;
}user[MAXXX];

struct counter counter[MAXXX];
struct counter temp;
struct counter temp_counter[MAXXX];
struct user *us = new struct user[MAXXX];
struct counter *co = new struct counter[MAXXX];
struct counter *users = new struct counter[MAXXX];

struct counter_temp {
	string password;
	int count;
};

struct user_list {
	string user_id;
	string password;
	struct user_list* next;
};

struct user_two_bit_node {
	int user_id;
	string password;
	struct user_two_bit_node *lchind;
	struct user_two_bit_node *rchind;
	struct user_two_bit_node *parent;
};

struct password_for_hash {
	string password_key;
	int data;
};
struct password_for_hash pfh[200000];
int user_sorted_int[1230000];



void questionOne();
int openPassword(string FILE_READS);
int questionTwo();
void questionFour();
void questionFive();
void insertTwoBitNode(user_two_bit_node **root, int id, string user_password);
user_two_bit_node* binaryTreeSearch(user_two_bit_node *root, int id);
int binarySearch(int id,int i,int j);
void insertSort(int number);
void mergeSort(int low ,int high);
void mergeAlgorithm(int low, int mid, int high);
void shellSort(struct counter c[],int number);
void heapSort(int number);
int std_hash_string(string password);


//RUN SORT FUNCTION
void RUN_BUBBLE();
void RUN_SELECTION();
void RUN_INSERT();
void RUN_SHELL();
void RUN_HEAP();
void RUN_QUICK();

void RUN_BUBBLE_REVERSE();
void RUN_SELECTION_REVERSE();
void RUN_INSERT_REVERSE();
void RUN_SHELL_REVERSE();
void RUN_HEAP_REVERSE();
void RUN_QUICK_REVERSE();
#endif // !_MAIN_H__
