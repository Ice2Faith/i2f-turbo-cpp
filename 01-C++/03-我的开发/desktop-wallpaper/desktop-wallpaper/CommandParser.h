#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_
#include<vector>
#include<string>
using namespace std;
// 释放CMD全局变量
void cmd_free();

// 初始化CMD全局变量
void cmd_init(int argc, char * argv[]);

// 获取原始的入口参数个数
int cmd_get_argc();

// 获取原始的入口参数
vector<string> cmd_get_argv();

// 获取除去执行文件本身的变量个数
int cmd_get_count();

// 获取除去执行文件本身的参数
vector<string> cmd_get_args();

// 是否存在CMD开关选项，开关选项是以-或/开头的CMD参数，例如：-f -n /s等
// 在命令行中，使用/f -n的选项，此函数则使用f n进行检测，注意，没有/或-的前缀
// 函数会自动添加
bool cmd_option_exists(string option);

// 获取指定选项后跟随的参数
// 例如命令行：-i test.txt readme.txt -o output.txt
// 则查找-i之后的参数，则入参为i,返回test.txt 和 readme.txt两个字符串
// 也就是查找指定选项之后的所有非选项参数
vector<string> cmd_option_args(string option);

// 获取执行的exe的完整路径
string cmd_exe_path();

// 获取执行的exe的所在路径
string cmd_exe_dir();

// 获取执行的exe的文件名
string cmd_exe_name();

#endif // _COMMAND_PARSER_H_

