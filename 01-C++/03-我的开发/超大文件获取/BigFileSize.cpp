#include<iostream>
using namespace::std;
int main()
{
    __int64 num = 0;
	num = 9223372036854775806;
	cout << num / 1024 << "KB" << endl;
	cout << num / 1024/1024 << "MB" << endl;
	cout << num / 1024/1024/1024 << "GB" << endl;
	cout << num / 1024 / 1024 / 1024 /1024<< "TB" << endl;
	char tp;
	cin >> tp;
	return 0;
}
