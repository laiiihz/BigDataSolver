#pragma once
#ifndef _MAIN_H__
#define _MAIN_H__
#include<iostream>
#include<string>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include <chrono>
#include <ratio>
#include <random>
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
	int my_count;
	struct user_list* next;
};


void questionOne();
int questionTwo();
void insertSort(int number);
void mergeSort(int number);
void MergeSort(int s, int e);
void Merge(int s, int m, int e);
void shellSort(int number);
void radixSort(int number);
int countMaxBit(int number);
void heapSort(int number);
#endif // !_MAIN_H__
