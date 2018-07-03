#include <iostream>
#include <vector>
#include <string>
//#include <utility>
//#include <memory>

#include "../SODD/Include/ConnectivityMatrix.h"
#include "../SODD/Include/Parser.h"
#include "../SODD/Include/ParserNodeProperty.h"
#include "../SODD/Include/ParserNodeConnectivity.h"
//#include "../SODD/Include/graphdrawer.h"


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

//Description property test
bool testParseDescriptionProperty();
bool testFailParseDescriptionPropertyUnexpectedEndOfFile();
bool testFailParseDescriptionPropertyMissingSemicolon();
bool testFailParseDescriptionPropertyMissingColon();
bool testFailParseDescriptionPropertyMissingOpeningDoubleQuotes();
bool testFailParseDescriptionPropertyMissingEndingDoubleQuotes();

//Radius property test
bool testParseRadiusProperty();
bool testFailParseRadiusPropertyUnexpectedEndOfFile();
bool testFailParseRadiusPropertyMissingSemicolon1();
bool testFailParseRadiusPropertyMissingSemicolon2();
bool testFailParseRadiusPropertyMissingColon();
bool testFailParseRadiusPropertyNumberExpected();

//Object test
bool testParseObjectOk();

//Objects test
bool testParseObjectsOk();
bool testParseObjectsRepetedObjectName();
bool testParseObjectsExpectedClosingBraceError();
bool testParseObjectsUnexpectedEndOfFileError1();
bool testParseObjectsUnexpectedEndOfFileError2();

//Connectivity symbol test
bool testParseNormalConnectivityOk();
bool testParseDashedConnectivityOk();
bool testParseNormalConnectivityExpectedGreaterSimbolError();
bool testParseDashedConnectivityExpectedGreaterSimbolError();
bool testParseNormalConnectivityButFoundDashedConnectivityError();
bool testParseDashedConnectivityButFoundNormalConnectivityError();
bool testIsNormalConnectivityOk();
bool testIsDashedConnectivityOk();
bool testIsNotNormalConnectivity();
bool testIsNotDashedConnectivity();

//Connectivity test
bool testParseConnectivityOk();
bool testParseConnectivityNameDoesNotExistError();

//Connectivities test
bool testParseConnectivitiesOk();

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

	//Description property tests
	message += CHECK_TESTING_FUNCTION(testParseDescriptionProperty, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseDescriptionPropertyUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseDescriptionPropertyMissingSemicolon, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseDescriptionPropertyMissingColon, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseDescriptionPropertyMissingOpeningDoubleQuotes, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseDescriptionPropertyMissingEndingDoubleQuotes, correctTests, incorrectTests);

	//Radius property tests
	message += CHECK_TESTING_FUNCTION(testParseRadiusProperty, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseRadiusPropertyUnexpectedEndOfFile, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseRadiusPropertyMissingSemicolon1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseRadiusPropertyMissingSemicolon2, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseRadiusPropertyMissingColon, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testFailParseRadiusPropertyNumberExpected, correctTests, incorrectTests);

	//Object test
	message += CHECK_TESTING_FUNCTION(testParseObjectOk, correctTests, incorrectTests);

	//Objects test
	message += CHECK_TESTING_FUNCTION(testParseObjectsOk, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseObjectsRepetedObjectName, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseObjectsExpectedClosingBraceError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseObjectsUnexpectedEndOfFileError1, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseObjectsUnexpectedEndOfFileError2, correctTests, incorrectTests);

	//Connectivity symbol test
	message += CHECK_TESTING_FUNCTION(testParseNormalConnectivityOk, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseDashedConnectivityOk, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseNormalConnectivityExpectedGreaterSimbolError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseDashedConnectivityExpectedGreaterSimbolError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseNormalConnectivityButFoundDashedConnectivityError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseDashedConnectivityButFoundNormalConnectivityError, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsNormalConnectivityOk, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsDashedConnectivityOk, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsNotNormalConnectivity, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testIsNotDashedConnectivity, correctTests, incorrectTests);

	//Connectivity test
	message += CHECK_TESTING_FUNCTION(testParseConnectivityOk, correctTests, incorrectTests);
	message += CHECK_TESTING_FUNCTION(testParseConnectivityNameDoesNotExistError, correctTests, incorrectTests);

	//Connectivities test
	message += CHECK_TESTING_FUNCTION(testParseConnectivitiesOk, correctTests, incorrectTests);

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
		expectedError << Parser::EndOfStringExpectedError << " Line: " << 2 << ", Position: " << 10 << ".";

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
/**************************/
//Description property test
/**************************/
bool testParseDescriptionProperty() {
	vector<string> strings = vector<string>();
	string result = "";
	strings.push_back("  ");
	strings.push_back("  desCription  ");
	strings.push_back("  :     \"  Hola que tal \"  ");
	strings.push_back("  ;  ");
	Parser parser = Parser(strings);
	try {
		ParserNodeDescriptionProperty property = *(parser.parseDescriptionProperty());
		NodeProperties nodeProperties;
		property.setThisPropertyToNodeProperty(nodeProperties);
		result = nodeProperties.description;
	}
	catch (ParserException &e) {
		return false;
	}

	return result == "  Hola que tal ";
}

bool testFailParseDescriptionPropertyUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back(" Description : ");
	Parser parser = Parser(strings);
	try {
		ParserNodeDescriptionProperty property = *(parser.parseDescriptionProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 15<< ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseDescriptionPropertyMissingSemicolon() {
	vector<string> strings = vector<string>();
	strings.push_back(" Description : \" hola\",");
	Parser parser = Parser(strings);
	try {
		ParserNodeDescriptionProperty property = *(parser.parseDescriptionProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::SemicolonExpectedError << " Line: " << 1 << ", Position: " << 23 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseDescriptionPropertyMissingColon() {
	vector<string> strings = vector<string>();
	strings.push_back(" Description  ;");
	Parser parser = Parser(strings);
	try {
		ParserNodeDescriptionProperty property = *(parser.parseDescriptionProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ColonExpectedError << " Line: " << 1 << ", Position: " << 15 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseDescriptionPropertyMissingOpeningDoubleQuotes() {
	vector<string> strings = vector<string>();
	strings.push_back("Description:  h");
	Parser parser = Parser(strings);
	try {
		ParserNodeDescriptionProperty property = *(parser.parseDescriptionProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::DoubleQuotesExpectedError << " Line: " << 1 << ", Position: " << 15 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseDescriptionPropertyMissingEndingDoubleQuotes() {
	vector<string> strings = vector<string>();
	strings.push_back("Description:\"h  ");
	Parser parser = Parser(strings);
	try {
		ParserNodeDescriptionProperty property = *(parser.parseDescriptionProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::EndOfStringExpectedError << " Line: " << 1 << ", Position: " << 17 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

/**************************/
//Radius property test
/**************************/
bool testParseRadiusProperty() {
	vector<string> strings = vector<string>();
	double result = 0;
	strings.push_back("  ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	Parser parser = Parser(strings);
	try {
		ParserNodeRadiusProperty property = *(parser.parseRadiusProperty());
		NodeProperties nodeProperties;
		property.setThisPropertyToNodeProperty(nodeProperties);
		result = nodeProperties.radius;
	}
	catch (ParserException &e) {
		return false;
	}

	return result == 120.0102;
}

bool testFailParseRadiusPropertyUnexpectedEndOfFile() {
	vector<string> strings = vector<string>();
	strings.push_back(" Radius : ");
	Parser parser = Parser(strings);
	try {
		ParserNodeRadiusProperty property = *(parser.parseRadiusProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 1 << ", Position: " << 10 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseRadiusPropertyMissingSemicolon1() {
	vector<string> strings = vector<string>();
	strings.push_back(" Radius : 12.3  9");
	Parser parser = Parser(strings);
	try {
		ParserNodeRadiusProperty property = *(parser.parseRadiusProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::SemicolonExpectedError << " Line: " << 1 << ", Position: " << 17 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseRadiusPropertyMissingSemicolon2() {
	vector<string> strings = vector<string>();
	strings.push_back(" Radius : 12.3G  ");
	Parser parser = Parser(strings);
	try {
		ParserNodeRadiusProperty property = *(parser.parseRadiusProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::SemicolonExpectedError << " Line: " << 1 << ", Position: " << 15 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseRadiusPropertyMissingColon() {
	vector<string> strings = vector<string>();
	strings.push_back(" Radius  9");
	Parser parser = Parser(strings);
	try {
		ParserNodeRadiusProperty property = *(parser.parseRadiusProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ColonExpectedError << " Line: " << 1 << ", Position: " << 10 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

bool testFailParseRadiusPropertyNumberExpected() {
	vector<string> strings = vector<string>();
	strings.push_back("Radius:A");
	Parser parser = Parser(strings);
	try {
		ParserNodeRadiusProperty property = *(parser.parseRadiusProperty());
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::NumberExpectedError << " Line: " << 1 << ", Position: " << 8 << ".";

		return errorMsg == expectedError.str();
	}
	return false;
}

//Object test
bool testParseObjectOk() {
	vector<string> strings = vector<string>();
	shared_ptr< pair<string, gd::Node> > result = nullptr;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } ");

	Parser parser = Parser(strings);
	try {
		result = make_shared< pair<string, gd::Node> >(parser.parseObject());
	}
	catch (ParserException &e) {
		return false;
	}

	return *result == pair<string, gd::Node>("ANOBJECT", gd::Node(120.0102, "desc 1"));
}

//Objects test
bool testParseObjectsOk() {
	vector<string> strings = vector<string>();
	vector<gd::Node> result;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } object otherObject{");
	strings.push_back("");
	strings.push_back(" ");
	strings.push_back("}");

	Parser parser = Parser(strings);
	try {
		result = parser.parseObjects();
	}
	catch (ParserException &e) {
		return false;
	}

	return result.size() == 2 && result[0] == gd::Node(0120.01020f,"desc 1") && result[1] == gd::Node(0, "");
}

bool testParseObjectsRepetedObjectName() {
	vector<string> strings = vector<string>();
	vector<gd::Node> result;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } ");
	strings.push_back(" object ANobJect ");
	strings.push_back("");
	strings.push_back(" { ");
	strings.push_back("}");

	Parser parser = Parser(strings);
	try {
		result = parser.parseObjects();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ObjectNameAlreadyExistError << "(ANOBJECT)" << " Line: " << 13 << ", Position: " << 2 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testParseObjectsExpectedClosingBraceError() {
	vector<string> strings = vector<string>();
	vector<gd::Node> result;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } object otherObject{");
	strings.push_back("");
	strings.push_back(" ;");
	strings.push_back("}");

	Parser parser = Parser(strings);
	try {
		result = parser.parseObjects();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ClosingBraceExpectedError << " Line: " << 11 << ", Position: " << 2 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testParseObjectsUnexpectedEndOfFileError1() {
	vector<string> strings = vector<string>();
	vector<gd::Node> result;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } object otherObject{");
	strings.push_back("Radius:1.2;");
	strings.push_back(" ");
	strings.push_back("");

	Parser parser = Parser(strings);
	try {
		result = parser.parseObjects();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 10 << ", Position: " << 12 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testParseObjectsUnexpectedEndOfFileError2() {
	vector<string> strings = vector<string>();
	vector<gd::Node> result;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } object otherObject{");
	strings.push_back("");
	strings.push_back(" ");
	strings.push_back("");

	Parser parser = Parser(strings);
	try {
		result = parser.parseObjects();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::UnexpectedEndOfFileError << " Line: " << 9 << ", Position: " << 23 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

//Connectivity symbol test
bool testParseNormalConnectivityOk() {
	vector<string> strings = vector<string>();
	unique_ptr<AbstractParserNodeConnectivity> result;
	strings.push_back("  ");
	strings.push_back(" -> ");
	strings.push_back("  ");

	Parser parser = Parser(strings);
	try {
		result = parser.parseConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return dynamic_cast<ParserNodeNormalConnectivity *>(result.get()) != nullptr;
}

bool testParseDashedConnectivityOk() {
	vector<string> strings = vector<string>();
	unique_ptr<AbstractParserNodeConnectivity> result;
	strings.push_back("  ");
	strings.push_back(" => ");
	strings.push_back("  ");

	Parser parser = Parser(strings);
	try {
		result = parser.parseConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return dynamic_cast<ParserNodeDashedConnectivity *>(result.get()) != nullptr;
}
bool testParseNormalConnectivityExpectedGreaterSimbolError() {
	vector<string> strings = vector<string>();
	unique_ptr<AbstractParserNodeConnectivity> result;
	strings.push_back("  ");
	strings.push_back(" - > ");
	strings.push_back("  ");

	Parser parser = Parser(strings);
	try {
		result = parser.parseConnectivitySymbol();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ConnectivitySymbolExpectedError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testParseDashedConnectivityExpectedGreaterSimbolError() {
	vector<string> strings = vector<string>();
	unique_ptr<AbstractParserNodeConnectivity> result;
	strings.push_back("  ");
	strings.push_back(" =");

	Parser parser = Parser(strings);
	try {
		result = parser.parseConnectivitySymbol();
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ConnectivitySymbolExpectedError << " Line: " << 1 << ", Position: " << 1 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

bool testParseNormalConnectivityButFoundDashedConnectivityError() {
	vector<string> strings = vector<string>();
	unique_ptr<AbstractParserNodeConnectivity> result;
	strings.push_back("  ");
	strings.push_back(" => ");
	strings.push_back("  ");

	Parser parser = Parser(strings);
	try {
		result = parser.parseConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return dynamic_cast<ParserNodeNormalConnectivity *>(result.get()) == nullptr;
}

bool testParseDashedConnectivityButFoundNormalConnectivityError() {
	vector<string> strings = vector<string>();
	unique_ptr<AbstractParserNodeConnectivity> result;
	strings.push_back("  ");
	strings.push_back(" -> ");
	strings.push_back("  ");

	Parser parser = Parser(strings);
	try {
		result = parser.parseConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return dynamic_cast<ParserNodeDashedConnectivity *>(result.get()) == nullptr;
}

bool testIsNormalConnectivityOk() {
	vector<string> strings = vector<string>();
	bool result = false;
	strings.push_back("  ");
	strings.push_back(" -> ");
	strings.push_back("  ");

	Parser parser = Parser(strings);
	try {
		result = parser.isNormalConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return result;
}

bool testIsDashedConnectivityOk() {
	vector<string> strings = vector<string>();
	bool result = false;
	strings.push_back("  ");
	strings.push_back(" => ");
	strings.push_back("  ");

	Parser parser = Parser(strings);
	try {
		result = parser.isDashedConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return result;
}

bool testIsNotNormalConnectivity() {
	vector<string> strings = vector<string>();
	bool result = false;
	strings.push_back("  ");
	strings.push_back(" -");

	Parser parser = Parser(strings);
	try {
		result = parser.isNormalConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return !result;
}

bool testIsNotDashedConnectivity() {
	vector<string> strings = vector<string>();
	bool result = false;
	strings.push_back("  ");
	strings.push_back(" ->");

	Parser parser = Parser(strings);
	try {
		result = parser.isDashedConnectivitySymbol();
	}
	catch (ParserException &e) {
		return false;
	}

	return !result;
}

//Connectivity test
bool testParseConnectivityOk() {
	vector<string> strings = vector<string>();
	vector<gd::Node> objects;
	unique_ptr<ConnectivityMatrix> connectivityMatrix;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } object otherObject{");
	strings.push_back("");
	strings.push_back(" ");
	strings.push_back("}");
	strings.push_back("  ");
	strings.push_back("  ");
	strings.push_back("  AnObJect->   ");
	strings.push_back("  ");
	strings.push_back("  OTHERObJect;");

	Parser parser = Parser(strings);
	try {
		objects = parser.parseObjects();
		connectivityMatrix = unique_ptr<ConnectivityMatrix>(new ConnectivityMatrix(objects.size()));
		parser.parseConnectivity(*connectivityMatrix);
	}
	catch (ParserException &e) {
		return false;
	}

	//should check that all other positions of the matrix are false for has connection and all are false for has dashed connection.
	return connectivityMatrix->hasArrow(0, 1) && !connectivityMatrix->hasArrow(1, 0);
}

bool testParseConnectivityNameDoesNotExistError() {
	vector<string> strings = vector<string>();
	vector<gd::Node> objects;
	unique_ptr<ConnectivityMatrix> connectivityMatrix;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } object otherObject{");
	strings.push_back("");
	strings.push_back(" ");
	strings.push_back("}");
	strings.push_back("  ");
	strings.push_back("  ");
	strings.push_back("  AnObJect->   ");
	strings.push_back("  ");
	strings.push_back("  aaaa;");

	Parser parser = Parser(strings);
	try {
		objects = parser.parseObjects();
		connectivityMatrix = unique_ptr<ConnectivityMatrix>(new ConnectivityMatrix(objects.size()));
		parser.parseConnectivity(*connectivityMatrix);
	}
	catch (ParserException &e) {
		string errorMsg = string(e.what());
		ostringstream expectedError;
		expectedError << Parser::ObjectNameDoesNotExistError << " Line: " << 17 << ", Position: " << 3 << ".";

		return errorMsg == expectedError.str();
	}

	return false;
}

//Connectivities test
bool testParseConnectivitiesOk() {
	vector<string> strings = vector<string>();
	vector<gd::Node> objects;
	unique_ptr<ConnectivityMatrix> connectivityMatrix;
	strings.push_back("  ");
	strings.push_back(" obJect ");
	strings.push_back(" anObject ");
	strings.push_back(" { ");
	strings.push_back("  Radius  ");
	strings.push_back("  :  0120.01020; ");
	strings.push_back(" descripTion :  \"desc 1\" ");
	strings.push_back(" ; ");
	strings.push_back(" } object otherObject{");
	strings.push_back("");
	strings.push_back(" ");
	strings.push_back("}");
	strings.push_back("  ");
	strings.push_back("  ");
	strings.push_back("  AnObJect->   ");
	strings.push_back("  ");
	strings.push_back("  OTHERObJect;  otherobject");
	strings.push_back("  =>  ");
	strings.push_back("  AnObJect  ");
	strings.push_back("  ");
	strings.push_back(" ; ");

	Parser parser = Parser(strings);
	try {
		objects = parser.parseObjects();
		connectivityMatrix = parser.parseConnectivities();
	}
	catch (ParserException &e) {
		return false;
	}

	//should check that all other positions of the matrix are false for has connection and all are false for has dashed connection.
	return	connectivityMatrix->hasArrow(0, 1)			&& !connectivityMatrix->hasArrow(1, 0) &&
			!connectivityMatrix->hasDashedArrow(0, 1)	&& connectivityMatrix->hasDashedArrow(1, 0);
}