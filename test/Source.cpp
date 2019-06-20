#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream file;
	file.open("test.txt", ios::in);

	char c;
	file >> c;
	cout << c << endl;

	int pos = file.tellg();
	file >> c;
	file >> c;
	cout << c << endl;

	file.seekg(pos);
	file >> c;
	cout << c << endl;
}