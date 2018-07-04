#include <string>
#include <vector>
#include "..\Include\appInputParser.h"
#include "..\Include\appInputParserStrategy.h"
#include "..\Include\Parser.h"

using namespace std;

namespace aip {
	AbstractAppInputParserStrategy::AbstractAppInputParserStrategy() {}
	AbstractAppInputParserStrategy::~AbstractAppInputParserStrategy() {}

	InputFileNameAppInputParserStrategy::InputFileNameAppInputParserStrategy() {}
	InputFileNameAppInputParserStrategy::~InputFileNameAppInputParserStrategy() {}

	void InputFileNameAppInputParserStrategy::fillParameter(const string &parameter, Parameters &outParameters) const {
		outParameters._inputFileName = parameter;
	}

	OutputFileNameAppInputParserStrategy::OutputFileNameAppInputParserStrategy() {}
	OutputFileNameAppInputParserStrategy::~OutputFileNameAppInputParserStrategy() {}
	void OutputFileNameAppInputParserStrategy::fillParameter(const string &parameter, Parameters &outParameters) const {
		outParameters._outputFileName = parameter;
	}

	WidthAppInputParserStrategy::WidthAppInputParserStrategy() {}
	WidthAppInputParserStrategy::~WidthAppInputParserStrategy() {}
	void WidthAppInputParserStrategy::fillParameter(const string &parameter, Parameters &outParameters) const {
		using namespace prsr;
		Parser parser(vector<string>(1, parameter));
		try {
			outParameters._with = static_cast<int>(parser.parseNumber());
		}
		catch (ParserException &e) {
			throw AppInputParserExeption("Not a number for width.");
		}
	}
	HeightAppInputParserStrategy::HeightAppInputParserStrategy() {}
	HeightAppInputParserStrategy::~HeightAppInputParserStrategy() {}
	void HeightAppInputParserStrategy::fillParameter(const string &parameter, Parameters &outParameters) const {
		using namespace prsr;
		Parser parser(vector<string>(1, parameter));
		try {
			outParameters._height = static_cast<int>(parser.parseNumber());
		}
		catch (ParserException &e) {
			throw AppInputParserExeption("Not a number for height.");
		}
	}
}