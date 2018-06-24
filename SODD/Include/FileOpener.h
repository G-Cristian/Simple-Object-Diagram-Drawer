#ifndef _FILEOPENER_H_
#define _FILEOPENER_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class FileOpener {
public:
	FileOpener();
	~FileOpener();

	vector<string> openFile(string fileName);

private:
	void setTextFromFile();
	ifstream _file;
	vector<string> _text;
};

#endif // !_FILEOPENER_H_

