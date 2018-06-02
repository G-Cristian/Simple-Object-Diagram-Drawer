#include <iostream>
#include <vector>
#include <string>

#include "../SODD/Include/Parser.h"

using namespace std;
using namespace prsr;

#define CHECK_TESTING_FUNCTION(functionToTest, inOutCorrectTests, inOutIncorrectTests) checkTestingFunction(functionToTest, inOutCorrectTests, inOutIncorrectTests, #functionToTest)

string checkTestingFunction(bool(*functionToTest)(), int &inOutCorrectTests, int &inOutincorrectTests, const string errorMsgToReturn);

bool testParseStringCorrect();
bool testFailParseStringUnexpectedEndOfFile();
bool testFailMissingOpeningDoubleQuotes();
bool testFailMissingEndingDoubleQuotes();

bool testParseColon();
bool testFailParseColonUnexpectedEndOfFile();
bool testExpectedColonError();
bool testIsColonTrue();
bool testIsColonFalse1();
bool testIsColonFalse2();

bool testParseSemicolon();
bool testFailParseSemicolonUnexpectedEndOfFile();
bool testExpectedSemicolonError();
bool testIsSemicolonTrue();
bool testIsSemicolonFalse1();
bool testIsSemicolonFalse2();

bool testExpectedOpeningBraceError();
bool testExpectedClosingBraceError();

bool testParseObjectToken1();
bool testParseObjectToken2();
bool testFailParseObjectTokenUnexpectedEndOfFile();
bool testFailObjectToken1();
bool testFailObjectToken2();
bool testIsObjectTokenTrue();
bool testIsObjectTokenFalse();

//Description token tests
bool testParseDescriptionToken1();
bool testParseDescriptionToken2();
bool testParseDescriptionToken3();
bool testFailParseDescriptionTokenUnexpectedEndOfFile();
bool testFailDescriptionToken1();
bool testFailDescriptionToken2();
bool testIsDescriptionTokenTrue();
bool testIsDescriptionTokenFalse();

//Radius token tests
bool testParseRadiusToken1();
bool testParseRadiusToken2();
bool testParseRadiusToken3();
bool testFailParseRadiusTokenUnexpectedEndOfFile();
bool testFailRadiusToken1();
bool testFailRadiusToken2();
bool testIsRadiusTokenTrue();
bool testIsRadiusTokenFalse();

bool testParseObjectName1();
bool testParseObjectName2();
bool testFailParseObjectNameUnexpectedEndOfFile();

bool testParseNumberInteger1();
bool testParseNumberInteger2();
bool testParseNumberDecimal1();
bool testParseNumberDecimal2();
bool testParseNumberIntegerAndDecimal1();
bool testParseNumberIntegerAndDecimal2();
bool testFailParseNumberUnexpectedEndOfFile();
bool testFailNumberIntegerPart();
bool testFailNumberDecimalPartUnexpectedEndOfLine();
bool testFailNumberDecimalPartUnexpectedCharacter();

int main() {
	int correctTests = 0;
	int incorrectTests = 0;
	string message = "";
	
	message += CHECK_TESTING_FUNCTION(testParseStringCorrect, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseStringUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailMissingOpeningDoubleQuotes, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailMissingEndingDoubleQuotes, correctTests, incorrectTests);
	
	message += CHECK_TESTING_FUNCTION(testParseColon, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseColonUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testExpectedColonError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsColonTrue, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsColonFalse1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsColonFalse2, correctTests, incorrectTests);

	message += CHECK_TESTING_FUNCTION(testParseSemicolon, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseSemicolonUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testExpectedSemicolonError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsSemicolonTrue, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsSemicolonFalse1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsSemicolonFalse2, correctTests, incorrectTests);

	message += CHECK_TESTING_FUNCTION(testExpectedOpeningBraceError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testExpectedClosingBraceError, correctTests, incorrectTests);

	message += CHECK_TESTING_FUNCTION(testParseObjectToken1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseObjectToken2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseObjectTokenUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailObjectToken1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailObjectToken2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsObjectTokenTrue, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsObjectTokenFalse, correctTests, incorrectTests);

	//Description token tests
	message += CHECK_TESTING_FUNCTION(testParseDescriptionToken1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseDescriptionToken2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseDescriptionToken3, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseDescriptionTokenUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailDescriptionToken1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailDescriptionToken2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsDescriptionTokenTrue, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsDescriptionTokenFalse, correctTests, incorrectTests);
	
	//Radius token tests
	message += CHECK_TESTING_FUNCTION(testParseRadiusToken1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseRadiusToken2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseRadiusToken3, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseRadiusTokenUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailRadiusToken1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailRadiusToken2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsRadiusTokenTrue, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsRadiusTokenFalse, correctTests, incorrectTests);

	//Object name tests
	message += CHECK_TESTING_FUNCTION(testParseObjectName1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseObjectName2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseObjectNameUnexpectedEndOfFile, correctTests, incorrectTests);

	message += CHECK_TESTING_FUNCTION(testParseNumberInteger1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseNumberInteger2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseNumberDecimal1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseNumberDecimal2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseNumberIntegerAndDecimal1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseNumberIntegerAndDecimal2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseNumberUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailNumberIntegerPart, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailNumberDecimalPartUnexpectedEndOfLine, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailNumberDecimalPartUnexpectedCharacter, correctTests, incorrectTests);

	cout << "Correct tests: " << correctTests << endl;
	cout << "Incorrect tests: " << incorrectTests << endl;
	cout << "The tests that failed were: " << message << endl;

	//_getwch();

	return 0;
}

string checkTestingFunction(bool(*functionToTest)(), int &inOutCorrectTests, int &inOutIncorrectTests, const string errorMsgToReturn) {
	string error = "";
	if (functionToTest())
		inOutCorrectTests++;
	else {
		inOutIncorrectTests++;
		error = "Failed test \"" + errorMsgToReturn + "\". ";
	}

	return error;
}

bool testParseStringCorrect() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   \"Casa \nloca\"  ");
	Parser parser = Parser(strings);
	string result = parser.parseString();

	if (result == "Casa \nloca") {
		return true;
	}
	else {
		return false;
	}
}

bool testFailParseStringUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	try {
		string result = parser.parseString();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";
		
		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailMissingOpeningDoubleQuotes() {
	vector<string> strings = vector<string>();
	strings.push_back("    ");
	strings.push_back("  Casa");
	Parser parser = Parser(strings);
	try {
		string result = parser.parseString();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::DoubleQuotesExpectedError << " Line: " << 2 << ", Position: " << 3 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailMissingEndingDoubleQuotes() {
	vector<string> strings = vector<string>();
	strings.push_back("      ");
	strings.push_back("  \"Casa  ");
	Parser parser = Parser(strings);
	try {
		string result = parser.parseString();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::EndOfStringExpectedError << " Line: " << 2 << ", Position: " << 9 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testParseColon() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   :");
	Parser parser = Parser(strings);
	try {
		parser.parseColon();
	}
	catch (ParserException &e) {
		return false;
	}

	return true;
}

bool testFailParseColonUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	try {
		parser.parseColon();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testExpectedColonError() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   a");
	Parser parser = Parser(strings);
	try {
		parser.parseColon();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ColonExpectedError << " Line: " << 2 << ", Position: " << 4 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testIsColonTrue() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   :");
	Parser parser = Parser(strings);

	return parser.isColon();
}

bool testIsColonFalse1() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("    ");
	Parser parser = Parser(strings);

	return !parser.isColon();
}

bool testIsColonFalse2() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("    a");
	Parser parser = Parser(strings);

	return !parser.isColon();
}

bool testParseSemicolon() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   ;");
	Parser parser = Parser(strings);
	try {
		parser.parseSemicolon();
	}
	catch (ParserException &e) {
		return false;
	}

	return true;
}

bool testFailParseSemicolonUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	try {
		parser.parseSemicolon();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testExpectedSemicolonError() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   a");
	Parser parser = Parser(strings);
	try {
		parser.parseSemicolon();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::SemicolonExpectedError << " Line: " << 2 << ", Position: " << 4 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testIsSemicolonTrue() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   ;");
	Parser parser = Parser(strings);

	return parser.isSemicolon();
}

bool testIsSemicolonFalse1() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("    ");
	Parser parser = Parser(strings);

	return !parser.isSemicolon();
}

bool testIsSemicolonFalse2() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("    a");
	Parser parser = Parser(strings);

	return !parser.isSemicolon();
}

bool testExpectedOpeningBraceError() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   a");
	Parser parser = Parser(strings);
	try {
		parser.parseOpeningBrace();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::OpeningBraceExpectedError << " Line: " << 2 << ", Position: " << 4 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testExpectedClosingBraceError() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   a");
	Parser parser = Parser(strings);
	try {
		parser.parseClosingBrace();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ClosingBraceExpectedError << " Line: " << 2 << ", Position: " << 4 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testParseObjectToken1() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    object");
	Parser parser = Parser(strings);
	try {
		parser.parseObjectToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testParseObjectToken2() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    object ");
	Parser parser = Parser(strings);
	try {
		parser.parseObjectToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testFailParseObjectTokenUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	try {
		parser.parseObjectToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailObjectToken1() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    obj");
	Parser parser = Parser(strings);
	try {
		parser.parseObjectToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ObjectTokenExpectedError << " Line: " << 2 << ", Position: " << 5 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}
bool testFailObjectToken2() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    objectA");
	Parser parser = Parser(strings);
	try {
		parser.parseObjectToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ObjectTokenExpectedError << " Line: " << 2 << ", Position: " << 5 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testIsObjectTokenTrue() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   oBject ");
	Parser parser = Parser(strings);

	return parser.isObjectToken();
}

bool testIsObjectTokenFalse() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   ob ");
	Parser parser = Parser(strings);

	return !parser.isObjectToken();
}
/******************************/
//Description token tests
/******************************/
bool testParseDescriptionToken1() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    description");
	Parser parser = Parser(strings);
	try {
		parser.parseDescriptionToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testParseDescriptionToken2() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    Description:");
	Parser parser = Parser(strings);
	try {
		parser.parseDescriptionToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testParseDescriptionToken3() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    Description  ");
	Parser parser = Parser(strings);
	try {
		parser.parseDescriptionToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testFailParseDescriptionTokenUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	try {
		parser.parseDescriptionToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailDescriptionToken1() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    desc");
	Parser parser = Parser(strings);
	try {
		parser.parseDescriptionToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::DescriptionTokenExpectedError << " Line: " << 2 << ", Position: " << 5 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}
bool testFailDescriptionToken2() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    DescriptionA");
	Parser parser = Parser(strings);
	try {
		parser.parseDescriptionToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::DescriptionTokenExpectedError << " Line: " << 2 << ", Position: " << 5 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testIsDescriptionTokenTrue() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   deScriPtion :");
	Parser parser = Parser(strings);

	return parser.isDescriptionToken();
}

bool testIsDescriptionTokenFalse() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   des ");
	Parser parser = Parser(strings);

	return !parser.isDescriptionToken();
}
/******************************/
//Radius token tests
/******************************/
bool testParseRadiusToken1() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    Radius");
	Parser parser = Parser(strings);
	try {
		parser.parseRadiusToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testParseRadiusToken2() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    Radius:");
	Parser parser = Parser(strings);
	try {
		parser.parseRadiusToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testParseRadiusToken3() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    Radius  ");
	Parser parser = Parser(strings);
	try {
		parser.parseRadiusToken();
	}
	catch (ParserException &e) {
		return false;
	}
	return true;
}

bool testFailParseRadiusTokenUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	try {
		parser.parseRadiusToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailRadiusToken1() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    rad");
	Parser parser = Parser(strings);
	try {
		parser.parseRadiusToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::RadiusTokenExpectedError << " Line: " << 2 << ", Position: " << 5 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}
bool testFailRadiusToken2() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    Radis");
	Parser parser = Parser(strings);
	try {
		parser.parseRadiusToken();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::RadiusTokenExpectedError << " Line: " << 2 << ", Position: " << 5 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testIsRadiusTokenTrue() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   RadiUs :");
	Parser parser = Parser(strings);

	return parser.isRadiusToken();
}

bool testIsRadiusTokenFalse() {
	vector<string> strings = vector<string>();
	strings.push_back("     ");
	strings.push_back("   rad ");
	Parser parser = Parser(strings);

	return !parser.isRadiusToken();
}
/***********************/
//Object name tests
/***********************/
bool testParseObjectName1() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    hOlA chau{");
	Parser parser = Parser(strings);
	string name = "";
	const string expectedName = "HOLA";
	try {
		name = parser.parseObjectName();
	}
	catch (ParserException &e) {
		return false;
	}
	return name == expectedName;
}

bool testParseObjectName2() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    hOlA{chau ");
	Parser parser = Parser(strings);
	string name = "";
	const string expectedName = "HOLA";
	try {
		name = parser.parseObjectName();
	}
	catch (ParserException &e) {
		return false;
	}
	return name == expectedName;
}

bool testFailParseObjectNameUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	string name = "";
	try {
		name = parser.parseObjectName();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testParseNumberInteger1() {
	vector<string> strings = vector<string>();
	double result = 0;
	strings.push_back("  ");
	strings.push_back("    01020");
	Parser parser = Parser(strings);
	try {
		result = parser.parseNumber();
	}
	catch (ParserException &e) {
		return false;
	}

	return result == 1020;
}

bool testParseNumberInteger2() {
	vector<string> strings = vector<string>();
	double result = 0;
	strings.push_back("  ");
	strings.push_back("    01020G12.3");
	Parser parser = Parser(strings);
	try {
		result = parser.parseNumber();
	}
	catch (ParserException &e) {
		return false;
	}

	return result == 1020;
}

bool testParseNumberDecimal1() {
	vector<string> strings = vector<string>();
	double result = 0;
	strings.push_back("  ");
	strings.push_back("    00.01020");
	Parser parser = Parser(strings);
	try {
		result = parser.parseNumber();
	}
	catch (ParserException &e) {
		return false;
	}

	return result == 0.0102;
}

bool testParseNumberDecimal2() {
	vector<string> strings = vector<string>();
	double result = 0;
	strings.push_back("  ");
	strings.push_back("    .01020G12.3");
	Parser parser = Parser(strings);
	try {
		result = parser.parseNumber();
	}
	catch (ParserException &e) {
		return false;
	}

	return result == 0.0102;
}

bool testParseNumberIntegerAndDecimal1() {
	vector<string> strings = vector<string>();
	double result = 0;
	strings.push_back("  ");
	strings.push_back("    0120.01020");
	Parser parser = Parser(strings);
	try {
		result = parser.parseNumber();
	}
	catch (ParserException &e) {
		return false;
	}

	return result == 120.0102;
}

bool testParseNumberIntegerAndDecimal2() {
	vector<string> strings = vector<string>();
	double result = 0;
	strings.push_back("  ");
	strings.push_back("    0120.01020G12.3");
	Parser parser = Parser(strings);
	try {
		result = parser.parseNumber();
	}
	catch (ParserException &e) {
		return false;
	}

	return result == 120.0102;
}

bool testFailParseNumberUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    ");
	Parser parser = Parser(strings);
	try {
		parser.parseNumber();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailNumberIntegerPart() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    a120.01");
	Parser parser = Parser(strings);
	try {
		parser.parseNumber();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::NumberExpectedError << " Line: " << 2 << ", Position: " << 5 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailNumberDecimalPartUnexpectedEndOfLine() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    120.");
	Parser parser = Parser(strings);
	try {
		parser.parseNumber();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::NumberExpectedError << " Line: " << 2 << ", Position: " << 9 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailNumberDecimalPartUnexpectedCharacter() {
	vector<string> strings = vector<string>();
	strings.push_back("  ");
	strings.push_back("    120. ");
	Parser parser = Parser(strings);
	try {
		parser.parseNumber();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::NumberExpectedError << " Line: " << 2 << ", Position: " << 9 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}
