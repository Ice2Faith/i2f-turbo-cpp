#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_
#include<vector>
#include<string>
using namespace std;
// �ͷ�CMDȫ�ֱ���
void cmd_free();

// ��ʼ��CMDȫ�ֱ���
void cmd_init(int argc, char * argv[]);

// ��ȡԭʼ����ڲ�������
int cmd_get_argc();

// ��ȡԭʼ����ڲ���
vector<string> cmd_get_argv();

// ��ȡ��ȥִ���ļ�����ı�������
int cmd_get_count();

// ��ȡ��ȥִ���ļ�����Ĳ���
vector<string> cmd_get_args();

// �Ƿ����CMD����ѡ�����ѡ������-��/��ͷ��CMD���������磺-f -n /s��
// ���������У�ʹ��/f -n��ѡ��˺�����ʹ��f n���м�⣬ע�⣬û��/��-��ǰ׺
// �������Զ����
bool cmd_option_exists(string option);

// ��ȡָ��ѡ������Ĳ���
// ���������У�-i test.txt readme.txt -o output.txt
// �����-i֮��Ĳ����������Ϊi,����test.txt �� readme.txt�����ַ���
// Ҳ���ǲ���ָ��ѡ��֮������з�ѡ�����
vector<string> cmd_option_args(string option);

// ��ȡִ�е�exe������·��
string cmd_exe_path();

// ��ȡִ�е�exe������·��
string cmd_exe_dir();

// ��ȡִ�е�exe���ļ���
string cmd_exe_name();

#endif // _COMMAND_PARSER_H_

