#include<bits/stdc++.h>

using namespace std;


stack<string> to_prepare_start;
stack<string> to_prepare_end;
set<string> done_file_start;
set<string> done_file_end;

ofstream outcpp;

string prefix_file = "/usr/local/include/";

void print_rest(ifstream &in){
	string s;
	while(in.good()){
		getline(in,s);
		outcpp << s << '\n';
	}
}

bool has_prefix(string line, string match){
	if(match.size() > line.size())return false;
	for(int i = 0; i < (int)match.size(); ++i)if(match[i] != line[i])return false;
	return true;
}

bool has_suffix(string line, string match){
	if(match.size() > line.size())return false;
	for(int i = 0; i < (int)match.size(); ++i)if(match[(int)match.size() - i - 1] != line[(int)line.size() - i - 1])return false;
	return true;
}

string remove_include(string s){
	string ret;
	bool st = false;
	for(char c : s){
		if(c == '>')break;
		if(c == '<')st = true;
		else if(st)ret+=c;
	}
	return ret;
}

void prepare_start(string file){
	string s;
	if(!has_suffix(file, ".cpp"))file = prefix_file + file;
	cerr << file << " start" << endl;
	ifstream in_file(file, ifstream::in);
	while(in_file.good()){
		getline(in_file, s);
		if(s == "// :-)")return;
		if(has_prefix(s,"#include")){
			if(has_suffix(file, ".cpp") && (has_prefix(remove_include(s),"bits") || has_prefix(remove_include(s), "ext"))){
				outcpp << s << '\n';
				continue;
			}
			if(has_prefix(remove_include(s),"bits") || has_prefix(remove_include(s), "ext")){
				continue;
			}
			to_prepare_start.push(remove_include(s));
		}
		else if(has_suffix(file, ".cpp"))outcpp << s << '\n';
	}
}

void prepare_end(string file){
	string s;
	if(!has_suffix(file, ".cpp"))file = prefix_file + file;
	cerr << file << " end" << endl;
	ifstream in_file(file, ifstream::in);
	while(in_file.good()){
		getline(in_file, s);
		if(s == "// :-)")break;
	}
	print_rest(in_file);
}

void prepare_file(string in_file){
	to_prepare_start.push(in_file);
	while(to_prepare_start.size()){
		string current_file = to_prepare_start.top();
		to_prepare_start.pop();
		to_prepare_end.push(current_file);
		if(done_file_start.count(current_file))continue;
		prepare_start(current_file);
		done_file_start.insert(current_file);
	}
	while(to_prepare_end.size()){
		string current_file = to_prepare_end.top();
		to_prepare_end.pop();
		if(done_file_end.count(current_file))continue;
		prepare_end(current_file);
		done_file_end.insert(current_file);
	}
}

int main(int argc, char** argv){
	outcpp.open("out.cpp", ofstream::out | ofstream::trunc);
	prepare_file((string)argv[1]);
}

