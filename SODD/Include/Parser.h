#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <exception>
#include <functional>
#include <memory>

#include "ConnectivityMatrix.h"
#include "graphdrawer.h"

using namespace std;
using namespace gd;

namespace prsr {
	class AbstractParserNodeProperty;
	class ParserNodeDescriptionProperty;
	class ParserNodeRadiusProperty;
	class AbstractParserNodeConnectivity;
	class ParserNodeNormalConnectivity;
	class ParserNodeDashedConnectivity;

	class ParserException : public exception {
	public:
		ParserException(int line, int position, const string &msg);
		~ParserException();

		virtual const char* what() const throw();
	private:
		int _line;
		int _position;
		string _msg;

		string _finalMsg;
	};

	struct NodeProperties {
		string description;
		double radius;
	};

	class Parser {
	public:
		const static string UnexpectedEndOfFileError;
		const static string DoubleQuotesExpectedError;
		const static string EndOfStringExpectedError;
		const static string ColonExpectedError;
		const static string SemicolonExpectedError;
		const static string ObjectTokenExpectedError;
		const static string DescriptionTokenExpectedError;
		const static string RadiusTokenExpectedError;
		const static string NumberExpectedError;
		const static string OpeningBraceExpectedError;
		const static string ClosingBraceExpectedError;
		const static string HyphenSymbolExpectedError;
		const static string EqualSymbolExpectedError;
		const static string GreaterThanSymbolExpectedError;
		const static string ConnectivitySymbolExpectedError;
		const static string ObjectNameAlreadyExistError;
		const static string ObjectNameDoesNotExistError;

		Parser(const vector<string> &text);
		Parser(const vector<string> &text, int line, int position);
		~Parser();

		//Graph parseGraph();
		vector<gd::Node> parseObjects();
		pair<string, gd::Node> parseObject();
		NodeProperties parseProperties();
		shared_ptr<AbstractParserNodeProperty> parseProperty();
		shared_ptr<ParserNodeDescriptionProperty> parseDescriptionProperty();
		shared_ptr<ParserNodeRadiusProperty> parseRadiusProperty();
		unique_ptr<ConnectivityMatrix> parseConnectivities();
		void parseConnectivity(ConnectivityMatrix &outConnectivityMatrix);
		unique_ptr<AbstractParserNodeConnectivity> parseConnectivitySymbol();
		unique_ptr<ParserNodeNormalConnectivity> parseNormalConnectivitySymbol();
		bool isNormalConnectivitySymbol();
		unique_ptr<ParserNodeDashedConnectivity> parseDashedConnectivitySymbol();
		bool isDashedConnectivitySymbol();
		string readToken(const set<char> &delimiters, int &outTokenStartLine, int &outTokenStartPosition);
		void parseToken(const string &expectedToken, const set<char> &delimiters, const string &errorMessageIfNotExpectedToken);
		bool isToken(function<void()> tokenParsingFunction);
		void parseObjectToken();
		bool isObjectToken();
		void parseDescriptionToken();
		bool isDescriptionToken();
		void parseRadiusToken();
		bool isRadiusToken();
		string parseObjectName();
		string parseString();
		double parseNumber();
		void parseSingleCharToken(char expectedChar, bool shouldSkipSpacesAndNewLine, const string &errorMessageIfNotExpectedChar);
		bool isSingleCharToken(char expectedChar, bool shouldSkipSpacesAndNewLine);
		void parseColon();
		bool isColon();
		void parseSemicolon();
		bool isSemicolon();
		void parseOpeningBrace();
		void parseClosingBrace();
		bool isClosingBrace();
		void parseHyphen();
		bool isHyphen();
		void parseEqual();
		bool isEqual();
		void parseGreaterThan();
		bool isGreaterThan();
	private:
		//returns 'true' if end of text.
		bool skipSpacesAndNewLine();
		int parseIntegerPart();
		double parseDecimalPart();
		inline bool isNumeric(char c) const;
		inline int charNumberToInt(char c) const;
		void insertNodeIntoOutList(string name, gd::Node node, int currentNodeIndex, list<gd::Node> &outList);

		vector<string> _text;
		int _currentLine;
		int _currentPosition;

		map<string, int> _nodeIndexPerObjectName;
	};
}

#endif // !_PARSER_H_
