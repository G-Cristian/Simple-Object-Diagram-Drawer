#include <iostream>
#include <vector>
#include <string>

#include "../SODD/Include/Parser.h"

using namespace std;
using namespace prsr;

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

bool testParseObjectToken1();
bool testParseObjectToken2();
bool testFailParseObjectTokenUnexpectedEndOfFile();
bool testFailObjectToken1();
bool testFailObjectToken2();
bool testIsObjectTokenTrue();
bool testIsObjectTokenFalse();

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
	
	message += checkTestingFunction(testParseStringCorrect, correctTests, incorrectTests, "testParseStringCorrect");
	message += checkTestingFunction(testFailParseStringUnexpectedEndOfFile, correctTests, incorrectTests, "testFaileParseStringUnexpectedEndOfFile");
	message += checkTestingFunction(testFailMissingOpeningDoubleQuotes, correctTests, incorrectTests, "testFaileMissingOpeningDoubleQuotes");
	message += checkTestingFunction(testFailMissingEndingDoubleQuotes, correctTests, incorrectTests, "testFailMissingEndingDoubleQuotes");
	
	message += checkTestingFunction(testParseColon, correctTests, incorrectTests, "testParseColon");
	message += checkTestingFunction(testFailParseColonUnexpectedEndOfFile, correctTests, incorrectTests, "testFailParseColonUnexpectedEndOfFile");
	message += checkTestingFunction(testExpectedColonError, correctTests, incorrectTests, "testExpectedColonError");
	message += checkTestingFunction(testIsColonTrue, correctTests, incorrectTests, "testIsColonTrue");
	message += checkTestingFunction(testIsColonFalse1, correctTests, incorrectTests, "testIsColonFalse1");
	message += checkTestingFunction(testIsColonFalse2, correctTests, incorrectTests, "testIsColonFalse2");

	message += checkTestingFunction(testParseSemicolon, correctTests, incorrectTests, "testParseSemicolon");
	message += checkTestingFunction(testFailParseSemicolonUnexpectedEndOfFile, correctTests, incorrectTests, "testFailParseSemicolonUnexpectedEndOfFile");
	message += checkTestingFunction(testExpectedSemicolonError, correctTests, incorrectTests, "testExpectedSemicolonError");
	message += checkTestingFunction(testIsSemicolonTrue, correctTests, incorrectTests, "testIsSemicolonTrue");
	message += checkTestingFunction(testIsSemicolonFalse1, correctTests, incorrectTests, "testIsSemicolonFalse1");
	message += checkTestingFunction(testIsSemicolonFalse2, correctTests, incorrectTests, "testIsSemicolonFalse2");

	message += checkTestingFunction(testParseObjectToken1, correctTests, incorrectTests, "testParseObjectToken1");
	message += checkTestingFunction(testParseObjectToken2, correctTests, incorrectTests, "testParseObjectToken2");
	message += checkTestingFunction(testFailParseObjectTokenUnexpectedEndOfFile, correctTests, incorrectTests, "testFailParseObjectTokenUnexpectedEndOfFile");
	message += checkTestingFunction(testFailObjectToken1, correctTests, incorrectTests, "testFailObjectToken1");
	message += checkTestingFunction(testFailObjectToken2, correctTests, incorrectTests, "testFailObjectToken2");
	message += checkTestingFunction(testIsObjectTokenTrue, correctTests, incorrectTests, "testIsObjectTokenTrue");
	message += checkTestingFunction(testIsObjectTokenFalse, correctTests, incorrectTests, "testIsObjectTokenFalse");
	
	message += checkTestingFunction(testParseNumberInteger1, correctTests, incorrectTests, "testParseNumberInteger1");
	message += checkTestingFunction(testParseNumberInteger2, correctTests, incorrectTests, "testParseNumberInteger2");
	message += checkTestingFunction(testParseNumberDecimal1, correctTests, incorrectTests, "testParseNumberDecimal1");
	message += checkTestingFunction(testParseNumberDecimal2, correctTests, incorrectTests, "testParseNumberDecimal2");
	message += checkTestingFunction(testParseNumberIntegerAndDecimal1, correctTests, incorrectTests, "testParseNumberIntegerAndDecimal1");
	message += checkTestingFunction(testParseNumberIntegerAndDecimal2, correctTests, incorrectTests, "testParseNumberIntegerAndDecimal2");
	message += checkTestingFunction(testFailParseNumberUnexpectedEndOfFile, correctTests, incorrectTests, "testFailParseNumberUnexpectedEndOfFile");
	message += checkTestingFunction(testFailNumberIntegerPart, correctTests, incorrectTests, "testFailNumberIntegerPart");
	message += checkTestingFunction(testFailNumberDecimalPartUnexpectedEndOfLine, correctTests, incorrectTests, "testFailNumberDecimalPartUnexpectedEndOfLine");
	message += checkTestingFunction(testFailNumberDecimalPartUnexpectedCharacter, correctTests, incorrectTests, "testFailNumberDecimalPartUnexpectedCharacter");

	cout << "Correct tests: " << correctTests << endl;
	cout << "Incorrect tests: " << incorrectTests << endl;
	cout << "The tests that failed were: " << message << endl;

	_getwch();

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
