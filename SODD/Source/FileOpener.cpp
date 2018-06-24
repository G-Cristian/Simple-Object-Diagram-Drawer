#include "../Include/FileOpener.h"

FileOpener::FileOpener() {

}
FileOpener::~FileOpener() {

}

vector<string> FileOpener::openFile(string fileName) {
	_file = ifstream(fileName, ios::in);
	if (_file.is_open()) {
		setTextFromFile();
		_file.close();
	}
	else {
		//TODO: throw exception
	}

	return _text;
}

void FileOpener::setTextFromFile() {
	_text = vector<string>();
	string line;

	while (getline(_file, line)) {
		_text.push_back(line);
	}
}