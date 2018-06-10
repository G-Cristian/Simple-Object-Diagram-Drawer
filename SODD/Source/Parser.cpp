#include "../Include/Parser.h"
#include <string>
#include <cctype>
#include <memory>
#include <utility>
#include "../Include/ParserNodeProperty.h"
#include "../Include/graphdrawer.h"

using namespace std;
using namespace gd;

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
	const string Parser::DescriptionTokenExpectedError = "'Description' expected.";
	const string Parser::RadiusTokenExpectedError = "'Radius' expected.";
	const string Parser::NumberExpectedError = "Number expected.";
	const string Parser::OpeningBraceExpectedError = "'{' expected.";
	const string Parser::ClosingBraceExpectedError = "'}' expected.";

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

	pair<string, gd::Node> Parser::parseObject() {
		parseObjectToken();
		string name = parseObjectName();
		parseOpeningBrace();
		NodeProperties properties = parseProperties();
		parseClosingBrace();

		return pair<string, gd::Node>(name, gd::Node(properties.radius, properties.description));
	}

	NodeProperties Parser::parseProperties() {
		NodeProperties properties = { "", 0.0 };
		bool isValidProperty = true;
		while (isValidProperty) {
			shared_ptr<AbstractParserNodeProperty> property = parseProperty();
			property->setThisPropertyToNodeProperty(properties);
			isValidProperty = property->isValidProperty();
		}

		return properties;
	}

	shared_ptr<AbstractParserNodeProperty> Parser::parseProperty()
	{
		shared_ptr<AbstractParserNodeProperty> property = make_shared<ParserNodeInvalidProperty>(ParserNodeInvalidProperty());

		if (isDescriptionToken()) {
			property = parseDescriptionProperty();
		}
		else if (isRadiusToken()) {
			property = parseRadiusProperty();
		}

		return property;
	}
	
	shared_ptr<ParserNodeDescriptionProperty> Parser::parseDescriptionProperty() {
		parseDescriptionToken();
		parseColon();
		string description = parseString();
		parseSemicolon();
		return make_shared<ParserNodeDescriptionProperty>(description);
	}

	shared_ptr<ParserNodeRadiusProperty> Parser::parseRadiusProperty() {
		parseRadiusToken();
		parseColon();
		double radius = parseNumber();
		parseSemicolon();
		return make_shared<ParserNodeRadiusProperty>(radius);
	}

	//The returned string is in uppercase.
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

	bool Parser::isToken(function<void()> tokenParsingFunction) {
		int previousLine = _currentLine;
		int previousPosition = _currentPosition;
		bool result = true;

		try {
			tokenParsingFunction();
		}
		catch (ParserException &e) {
			result = false;
		}

		_currentLine = previousLine;
		_currentPosition = previousPosition;

		return result;
	}

	void Parser::parseObjectToken() {
		char delimiters[] = { ' ' };
		parseToken("OBJECT", set<char>(delimiters, delimiters + 1),ObjectTokenExpectedError);
	}

	bool Parser::isObjectToken() {
		function<void()> p = [this]() {this->parseObjectToken();};
		return (isToken(p));
	}

	void Parser::parseDescriptionToken() {
		char delimiters[] = { ' ', ':' };
		parseToken("DESCRIPTION", set<char>(delimiters, delimiters + 2), DescriptionTokenExpectedError);
	}

	bool Parser::isDescriptionToken() {
		function<void()> p = [this]() {this->parseDescriptionToken();};
		return (isToken(p));
	}

	void Parser::parseRadiusToken()
	{
		char delimiters[] = { ' ', ':' };
		parseToken("RADIUS", set<char>(delimiters, delimiters + 2), RadiusTokenExpectedError);
	}

	bool Parser::isRadiusToken()
	{
		function<void()> p = [this]() {this->parseRadiusToken();};
		return (isToken(p));
	}

	string Parser::parseObjectName() {
		char delimiters[] = { ' ', '{' };
		int tokenStartLine = _currentLine;
		int tokenStartPosition = _currentPosition;

		return readToken(set<char>(delimiters, delimiters + 2), tokenStartLine, tokenStartPosition);
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
			throw ParserException(_currentLine + 1, _currentPosition + 1, EndOfStringExpectedError);

		_currentPosition++;
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

	void Parser::parseOpeningBrace() {
		parseSingleCharToken('{', OpeningBraceExpectedError);
	}

	void Parser::parseClosingBrace() {
		parseSingleCharToken('}', ClosingBraceExpectedError);
	}

	bool Parser::isClosingBrace() {
		return isSingleCharToken('}');
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