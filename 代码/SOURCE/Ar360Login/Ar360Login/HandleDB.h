#pragma once
#include "sqlite3.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
class HandleDB
{
public:
	HandleDB(void);
	~HandleDB(void);
	// �����������������Ƿ���Ϲ淶
	static int inputNumCheck(int min, int max);
	// ʵ�ֵ�½
	void loginAR360(sqlite3 *db);
	string inputStringCheck(int length,string inputType);
	bool checkIDFromDB(string Id,sqlite3 *db,bool &isJudged,int checkType);
	// ʵ��ע��
	void registerAR360(sqlite3 *db);
//	static int userResult(void * notUsed, int nCol, char ** azValues, char ** azColName);
private:
	// �洢��ǰ��½����ע����˺�
	string userID;
	// �洢��Ӧ��ǰ�˺ŵ�����
	string userPwd;
	// �����ݿ����Ƿ��ҵ�����ĵ�½�˺�
	bool isFound;	
	// �ж�Ҫע����˺��Ƿ��Ѿ�����
	bool isExist;
};

