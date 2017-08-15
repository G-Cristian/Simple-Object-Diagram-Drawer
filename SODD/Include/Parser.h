#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include <string>
#include <map>
#include <set>
#include <exception>

#include "graphdrawer.h"

using namespace std;
using namespace gd;

namespace prsr {

	class ParserException : public exception {
	public:
		ParserException(int line, int position, string msg);
		~ParserException();

		virtual const char* what() const throw();
	private:
		int _line;
		int _position;
		string _msg;

		string _finalMsg;
	};

	class Parser {
	public:
		const static string UnexpectedEndOfFileError;
		const static string DoubleQuotesExpectedError;
		const static string EndOfStringExpectedError;
		const static string ColonExpectedError;
		const static string SemicolonExpectedError;
		const static string ObjectTokenExpectedError;
		const static string NumberExpectedError;

		Parser(const vector<string> &text);
		Parser(const vector<string> &text, int line, int position);
		~Parser();

		//Graph parseGraph();
		//gd::Node parseObject();
		string readToken(const set<char> &delimiters, int &outTokenStartLine, int &outTokenStartPosition);
		void parseToken(const string &expectedToken, const set<char> &delimiters, const string &errorMessageIfNotExpectedToken);
		void parseObjectToken();
		bool isObjectToken();
		string parseString();
		double parseNumber();
		void parseSingleCharToken(char expectedChar, const string &errorMessageIfNotExpectedChar);
		bool isSingleCharToken(char expectedChar);
		void parseColon();
		bool isColon();
		void parseSemicolon();
		bool isSemicolon();
	private:
		//returns 'true' if end of text.
		bool skipSpacesAndNewLine();
		int parseIntegerPart();
		double parseDecimalPart();
		inline bool isNumeric(char c) const;
		inline int charNumberToInt(char c) const;

		vector<string> _text;
		int _currentLine;
		int _currentPosition;

		map<string, int> _nodeIndexPerObjectName;
	};
}

#endif // !_PARSER_H_
