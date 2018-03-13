#pragma once
#ifndef _MAIN_H__
#define _MAIN_H__
#include<iostream>
#include<string>
#include<Windows.h>	//提供暂停函数Sleep()
#include<iomanip>
#include<fstream>	//提供文件操作函数
#include <chrono>	//提供计时函数
#include <ratio>
#include <random>	//提供随机数函数
using namespace std;

struct user {
	string user_id;
	string password;
}user[1230000];

struct counter {
	string password;
	int count;
}counter[1230000],temp;

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

void questionOne();
int questionTwo();
void questionFour();
void questionFive();
void insertTwoBitNode(user_two_bit_node **root, int id, string user_password);
user_two_bit_node* binarySearch(user_two_bit_node *root, int id);
void insertSort(int number);
void mergeSort(int number);
void MergeSort(int s, int e);
void Merge(int s, int m, int e);
void shellSort(int number);
void radixSort(int number);
int countMaxBit(int number);
void heapSort(int number);
#endif // !_MAIN_H__
