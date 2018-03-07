#pragma once
#ifndef _MAIN_H__
#define _MAIN_H__
#include<iostream>
#include<string>
#include<Windows.h>
#include<iomanip>
#include<fstream>
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


void questionOne();
int questionTwo();
void insertSort(int number);
void realMergeSort(int a, int b);
void mergeSort(int a, int b);
#endif // !_MAIN_H__
