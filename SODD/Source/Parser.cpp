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
	const string Parser::ColonExpectedError = "':' expected.";
	const string Parser::SemicolonExpectedError = "';' expected.";
	const string Parser::ObjectTokenExpectedError = "'Object' expected.";
	const string Parser::NumberExpectedError = "Number expected.";

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

	string Parser::readToken(const set<char> &delimiters, int &outTokenStartLine, int &outTokenStartPosition) {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		if (skipSpacesAndNewLine())
			throw ParserException(previousLine + 1, previousPosition + 1, UnexpectedEndOfFileError);

		outTokenStartLine = _currentLine;
		outTokenStartPosition = _currentPosition;

		string line = _text[_currentLine];
		size_t lineLength = line.length();
		string parsedText = "";
		while (_currentPosition < lineLength && delimiters.find(line[_currentPosition]) == delimiters.end()) {
			parsedText += toupper(line[_currentPosition]);
			_currentPosition++;
		}

		return parsedText;
	}

	//expectedToken must be uppercase.
	void Parser::parseToken(const string &expectedToken, const set<char> &delimiters, const string &errorMessageIfNotExpectedToken) {
		int tokenStartLine = _currentLine;
		int tokenStartPosition = _currentPosition;

		string parsedText = readToken(delimiters, tokenStartLine, tokenStartPosition);
		
		if (parsedText != expectedToken)
			throw ParserException(tokenStartLine + 1, tokenStartPosition + 1, errorMessageIfNotExpectedToken);
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

	double Parser::parseNumber() {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		double result = 0.0;

		if (skipSpacesAndNewLine())
			throw ParserException(previousLine + 1, previousPosition + 1, UnexpectedEndOfFileError);

		string line = _text[_currentLine];
		size_t lineLength = line.length();
		
		if (!isNumeric(line[_currentPosition]) && line[_currentPosition] != '.') {
			throw ParserException(_currentLine + 1, _currentPosition + 1, NumberExpectedError);
		}

		result = parseIntegerPart();

		if (_currentPosition < lineLength && line[_currentPosition] == '.') {
			_currentPosition++;

			if (_currentPosition >= lineLength || !isNumeric(line[_currentPosition])) {
				throw ParserException(_currentLine + 1, _currentPosition + 1, NumberExpectedError);
			}

			result += parseDecimalPart();
		}

		return result;
	}

	int Parser::parseIntegerPart() {
		int result = 0;

		string line = _text[_currentLine];
		size_t lineLength = line.length();

		while (_currentPosition < lineLength && isNumeric(line[_currentPosition])) {
			result *= 10;
			result += charNumberToInt(line[_currentPosition]);

			_currentPosition++;
		}

		return result;
	}

	double Parser::parseDecimalPart() {
		double result = 0.0;

		string line = _text[_currentLine];
		size_t lineLength = line.length();
		double divider = 10;
		while (_currentPosition < lineLength && isNumeric(line[_currentPosition])) {
			result += charNumberToInt(line[_currentPosition]) / divider;
			divider *= 10;

			_currentPosition++;
		}

		return result;
	}

	inline bool Parser::isNumeric(char c) const {
		return c >= '0' && c <= '9';
	}
	//'c' should be a number.
	inline int Parser::charNumberToInt(char c) const {
		return c - '0';
	}

	void Parser::parseSingleCharToken(char expectedChar, const string &errorMessageIfNotExpectedChar) {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		if (skipSpacesAndNewLine())
			throw ParserException(previousLine + 1, previousPosition + 1, UnexpectedEndOfFileError);

		string line = _text[_currentLine];
		size_t lineLength = line.length();
		if (line[_currentPosition] != expectedChar)
			throw ParserException(_currentLine + 1, _currentPosition + 1, errorMessageIfNotExpectedChar);

		_currentPosition++;
	}

	bool Parser::isSingleCharToken(char expectedChar) {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		bool result = true;

		try {
			parseSingleCharToken(expectedChar, "");
		}
		catch (ParserException &e) {
			result = false;
		}

		_currentLine = previousLine;
		_currentPosition = previousPosition;

		return result;
	}

	void Parser::parseColon() {
		parseSingleCharToken(':', ColonExpectedError);
	}

	bool Parser::isColon() {
		return isSingleCharToken(':');
	}

	void Parser::parseSemicolon() {
		parseSingleCharToken(';', SemicolonExpectedError);
	}

	bool Parser::isSemicolon() {
		return isSingleCharToken(';');
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