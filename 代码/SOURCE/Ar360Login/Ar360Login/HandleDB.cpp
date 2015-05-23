#include "HandleDB.h"


HandleDB::HandleDB(void)
	: isFound(false)
	, isExist(true)
{
}

HandleDB::~HandleDB(void)
{
}

// �����������������Ƿ���Ϲ淶
int HandleDB::inputNumCheck(int min, int max)
{
	int num;

	while (true)
	{
		cout << "�����루���֣���";
		cin >> num;

		if (cin.fail()||cin.bad())
		{
			cout << "������Ĳ������֣��������������" << endl;
			cin.clear();
			char ch;
			cin>>ch;
			cin.ignore(256, '\n');
			continue;
		}
		if (num >= min && num <= max)
			break;
		cout << "���볬����Χ������������" << endl;
		cout << "����" << min << "-" << max << "�ķ�Χ����������" << endl;
	}

	cin.ignore(256, '\n');

	return num;
}

string HandleDB::inputStringCheck(int length,string inputType)
{

	string temp = "";

	while (true)
	{
		cout << inputType << ":" << endl;
		cin >> temp;

		if (temp.length() > length)
		{
			cout << "�������" << inputType << "����" << endl;
			cout << inputType << "����ӦС��" << length << endl;
			continue;
		}
		else if (temp.empty())
		{
			cout << "���벻��Ϊ��" << endl;
		}
		else{
			break;
		}

	}

	return temp;
}

bool HandleDB::checkIDFromDB(string Id,sqlite3 *db,bool &isJudged,int checkType)
{
	string strSQL = "";
	strSQL += "select * from UserLogin where ID ='";
	strSQL += Id;
	strSQL += "';";


	char **azResult;
	int	nCol,nRow;
	int res = sqlite3_get_table(db,strSQL.c_str(),&azResult,&nRow,&nCol,0);

	if (res == SQLITE_OK)
	{
		switch (checkType)
		{
		case 1:
			if (nRow == 0)
			{
				cout << "δ�ҵ����˻�,����������" << endl;
				isJudged = false;
			}
			else if (nRow == 1)
			{
				userPwd = azResult[3];
				isJudged = true;		
			}
			else
			{
				cout << "���ݿ����...��������ͬ�˻�" << endl;
				isJudged = false;
			}
			break;

		case 2:
			if (nRow == 0)
			{
				isJudged = false;
			}
			else if (nRow == 1)
			{
				cout << "�Ѵ��ڴ��˻�,����������" << endl;
				isJudged = true;
			}
			else
			{
				cout << "���ݿ����...��������ͬ�˻�" << endl;
				isJudged = true;
			}
			break;
		}
		sqlite3_free_table(azResult);

		return true;
	}else {
		return false;
	}
}

// ʵ�ֵ�½
void HandleDB::loginAR360(sqlite3 *db)
{
	string ID;
	string password;

	while (!isFound)
	{

		ID = inputStringCheck(10,"�˺�");
		userID = ID;
		if (checkIDFromDB(ID,db,isFound,1))
		{
			if (isFound == false)
			{
				cout << "�Ƿ����������˺ţ�" << endl;
				cout << "1.��" << endl;
				cout << "2.�񣬽�����������" << endl;
				int numCheck = inputNumCheck(1,2);
				if (numCheck == 1)
				{
					continue;
				}else{
					break;
				}
			}
		}else{
			cout << "���ݿ��ʧ��" << endl;
		}
	}

	while(isFound){

		password = inputStringCheck(20,"����");

		if (password == userPwd)
		{
			cout << "��½�ɹ���" << endl;
			exit(0);
		}
		else{
			cout << "�Ƿ������������룿" << endl;
			cout << "1.��" << endl;
			cout << "2.�񣬽�����������" << endl;
			int numCheck = inputNumCheck(1,2);
			if (numCheck == 1)
			{
				continue;
			}else{
				isFound = false;
				break;
			}
		}
	}
	                        

	return;
}

void HandleDB::registerAR360(sqlite3 *db)
{
	string ID;
	string password;

	while (isExist)
	{

		ID = inputStringCheck(10,"�˺�");
		userID = ID;
		if (checkIDFromDB(ID,db,isExist,2))
		{
			if (isExist == true)
			{
				cout << "�Ƿ����������˺ţ�" << endl;
				cout << "1.��" << endl;
				cout << "2.�񣬽�����������" << endl;
				int numCheck = inputNumCheck(1,2);
				if (numCheck == 1)
				{
					continue;
				}else{
					break;
				}
			}
		}else{
			cout << "���ݿ��ʧ��" << endl;
		}
	}

	if (!isExist)
	{
		password = inputStringCheck(20,"����");

		string strSQL;
		strSQL += "insert into UserLogin(ID,password)values('";
		strSQL += ID;
		strSQL += "','";
		strSQL += password;
		strSQL += "');";

		char* cErrMsg;  
		int nRes = sqlite3_exec(db,strSQL.c_str(),0,0,&cErrMsg);
		if (nRes != SQLITE_OK)    
		{  
			cout<< "ע��ʧ�ܣ�" << cErrMsg << endl;
			userID = "";
		}  
		else  
		{  
			cout<< "�˺�" << ID << "ע��ɹ�" << endl; 
			userPwd = password;
		}  
	}
}
