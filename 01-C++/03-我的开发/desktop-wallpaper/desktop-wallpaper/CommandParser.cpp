#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<string>
#include<math.h>
#include "CommandParser.h"

using namespace std;

static int cmd_argc = 0;
static vector<string> cmd_argv;

void cmd_free(){
	cmd_argv.clear();
	cmd_argc = 0;
}

void cmd_init(int argc, char * argv[]){
	cmd_free();
	cmd_argc = argc;
	for (int i = 0; i < argc; i++){
		cmd_argv.push_back(argv[i]);
	}
}

int cmd_get_argc(){
	return cmd_argc;
}

vector<string> cmd_get_argv(){
	return cmd_argv;
}

int cmd_get_count(){
	return cmd_argc - 1;
}

vector<string> cmd_get_args(){
	vector<string> ret;
	for (int i = 1; i < cmd_argv.size(); i++){
		ret.push_back(cmd_argv[i]);
	}
	return ret;
}

bool cmd_option_exists(string option){
	bool ret = false;
	for (int i = 1; i < cmd_argc; i++){
		if (cmd_argv[i].compare("/" + option) == 0 || cmd_argv[i].compare("-" + option) == 0){
			ret = true;
			break;
		}
	}
	return ret;
}

vector<string> cmd_option_args(string option){
	vector<string> ret;
	bool begin = false;
	for (int i = 1; i < cmd_argc; i++){
		if (cmd_argv[i].compare("/" + option) == 0 || cmd_argv[i].compare("-" + option) == 0){
			begin = true;
			continue;
		}
		if (cmd_argv[i].length()>0){
			if (cmd_argv[i][0] == '/' || cmd_argv[i][0] == '-'){
				begin = false;
				break;
			}
		}
		if (begin){
			ret.push_back(cmd_argv[i]);
		}
	}
	return ret;
}

string cmd_exe_path(){
	if (cmd_argc == 0){
		return ".";
	}
	return cmd_argv[0];
}

string cmd_exe_dir(){
	if (cmd_argc == 0){
		return ".";
	}
	string ret = "";
	int idx = cmd_argv[0].find_last_of("/");
	int widx = cmd_argv[0].find_last_of("\\");
	idx = idx > widx ? idx : widx;
	if (idx >= 0){
		ret = cmd_argv[0].substr(0, idx);
	}
	return ret;
}

string cmd_exe_name(){
	if (cmd_argc == 0){
		return ".";
	}
	string ret = "";
	int idx = cmd_argv[0].find_last_of("/");
	int widx = cmd_argv[0].find_last_of("\\");
	idx = idx > widx ? idx : widx;
	if (idx >= 0){
		ret = cmd_argv[0].substr(idx+1);
	}
	return ret;
}
