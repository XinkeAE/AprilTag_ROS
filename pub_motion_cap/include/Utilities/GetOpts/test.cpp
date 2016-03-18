#include <iostream>
#include "GetOpts.hpp"
#include <vector>

using namespace std;

void display(){
	cout << "got here" << endl;
}

void display2(){
	cout << "got here as well" << endl;
}

int main(int argc, char **argv){
	GetOpts ops;
	bool b = false;
	int i = 9;
	char c = 'a';
	double d = .5;
	float f = 3.14;
	string s = "ops";
	
	vector<int*> v;
	int x = 5;
	int y = 90;
	int z = -30;
	v.push_back(&x);
	v.push_back(&y);
	v.push_back(&z);
	
	vector<void (*)()> callback;
	callback.push_back(&display);
	callback.push_back(&display2);
	
	ops.Add_Option("--display", "-dis", "will display got here", &display);
	ops.Add_Option("--say", "-say", "will display got here as well", &display2);
	
	ops.Add_Option_Set("--bool", "-b", "will set b to be given bool", &b);
	ops.Add_Option_Set("--int", "-i", "will set i to be given integer", &i);
	ops.Add_Option_Set("--char", "-c", "will set c to be given char", &c);
	ops.Add_Option_Set("--double", "-d", "will set d to be given double", &d);
	ops.Add_Option_Set("--float", "-f", "will set f to be given float", &f);
	ops.Add_Option_Set("--string", "-s", "will set s to be given string", &s);
	ops.Add_Option_Set_Group("--vector", "-v", "will set group of ints in v to given values", v);
	ops.Add_Option_Group("--callback", "-cb", "will execute all functions in the callback vector", callback);
	ops.Parse(argc, argv);
	
	cout << "b = " << b << endl;
	cout << "i = " << i << endl;
	cout << "c = " << c << endl;
	cout << "d = " << d << endl;
	cout << "f = " << f << endl;
	cout << "s = " << s << endl;
	
	cout << "v = " << endl;
	for(int i = 0; i < 3; i++)
		cout << (*v[i]) << endl;
}
