#include "../Include/Parser.h"
#include <cctype>

using namespace std;

namespace prsr {

	ParserException::ParserException(int line, int position, string msg) {
		_line = line;
		_position = position;
		_msg = msg;

		ostringstream tempMsg;
		tempMsg << _msg << " Line: " << _line << ", Position: " << _position << ".";

		_finalMsg = tempMsg.str();

	}

	ParserException::~ParserException() {

	}

	const char* ParserException::what() const throw() {		
		return _finalMsg.c_str();
	}

	const string Parser::UnexpectedEndOfFileError = "Unexpected end of file.";
	const string Parser::DoubleQuotesExpectedError = "Double quotes expected.";
	const string Parser::EndOfStringExpectedError = "End of string (\") expected.";
	const string Parser::ColonExpectedError = "';' expected.";
	const string Parser::ObjectTokenExpectedError = "'Object' expected.";

	Parser::Parser(const vector<string> &text):Parser(text, 0, 0){
	}

	Parser::Parser(const vector<string> &text, int line, int position) {
		_text = text;
		_currentLine = line;
		_currentPosition = position;

		_nodeIndexPerObjectName = map<string, int>();
	}

	Parser::~Parser() {

	}

	//expectedToken must be uppercase.
	void Parser::parseToken(const string &expectedToken, const set<char> &delimiters, const string &errorMessageIfNotExpectedToken) {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		if (skipSpacesAndNewLine())
			throw ParserException(previousLine + 1, previousPosition + 1, UnexpectedEndOfFileError);

		previousLine = _currentLine;
		previousPosition = _currentPosition;

		string line = _text[_currentLine];
		size_t lineLength = line.length();
		string parsedText = "";
		while (_currentPosition < lineLength && delimiters.find(line[_currentPosition]) == delimiters.end()) {
			parsedText += toupper(line[_currentPosition]);
			_currentPosition++;
		}

		if (parsedText != expectedToken)
			throw ParserException(previousLine + 1, previousPosition + 1, errorMessageIfNotExpectedToken);
	}

	void Parser::parseObjectToken() {
		char delimiters[] = { ' ' };
		parseToken("OBJECT", set<char>(delimiters, delimiters + 1),ObjectTokenExpectedError);
	}

	bool Parser::isObjectToken() {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		bool result = true;

		try {
			parseObjectToken();
		}
		catch (ParserException &e) {
			result = false;
		}

		_currentLine = previousLine;
		_currentPosition = previousPosition;

		return result;
	}

	string Parser::parseString() {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		if (skipSpacesAndNewLine())
			throw ParserException(previousLine+1, previousPosition+1, UnexpectedEndOfFileError);

		string line = _text[_currentLine];
		size_t lineLength = line.length();
		if (line[_currentPosition] != '"')
			throw ParserException(_currentLine + 1, _currentPosition + 1, DoubleQuotesExpectedError);

		_currentPosition++;
		string result = "";
		while (_currentPosition < lineLength && (line[_currentPosition] != '"')) {
			result += line[_currentPosition];
			_currentPosition++;
		}

		if (_currentPosition >= lineLength)
			throw ParserException(_currentLine + 1, _currentPosition, EndOfStringExpectedError);

		return result;
	}

	void Parser::parseColon() {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		if (skipSpacesAndNewLine())
			throw ParserException(previousLine + 1, previousPosition + 1, UnexpectedEndOfFileError);

		string line = _text[_currentLine];
		size_t lineLength = line.length();
		if (line[_currentPosition] != ';')
			throw ParserException(_currentLine + 1, _currentPosition + 1, ColonExpectedError);

		_currentPosition++;
	}

	bool Parser::isColon() {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		bool result = true;

		try {
			parseColon();
		}
		catch (ParserException &e) {
			result = false;
		}

		_currentLine = previousLine;
		_currentPosition = previousPosition;

		return result;
	}

	//returns 'true' if end of text.
	bool Parser::skipSpacesAndNewLine() {
		bool finishSkiping = false;
		size_t numberOfLines = _text.size();

		string line;
		size_t lineLength;
		while (!finishSkiping && _currentLine < numberOfLines) {
			finishSkiping = true;
			line = _text[_currentLine];
			lineLength = line.length();

			while (_currentPosition < lineLength && line[_currentPosition] == ' ') {
				_currentPosition++;
			}

			if (_currentPosition >= lineLength) {
				finishSkiping = false;
				_currentPosition = 0;
				_currentLine++;
			}
		}

		if (_currentLine >= numberOfLines) {
			return true;
		}
		else {
			return false;
		}
	}
}