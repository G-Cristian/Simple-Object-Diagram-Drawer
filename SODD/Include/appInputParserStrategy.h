#ifndef _APPINPUTPARSERSTRATEGY_H_
#define _APPINPUTPARSERSTRATEGY_H_

#include <string>
#include <vector>
#include "..\Include\appInputParser.h"
#include "..\Include\Parser.h"

using namespace std;

namespace aip {
	struct Parameters;
	class AbstractAppInputParserStrategy {
	public:
		AbstractAppInputParserStrategy();
		virtual ~AbstractAppInputParserStrategy();

		virtual void fillParameter(const string &parameter, Parameters &outParameters) const = 0;
	};

	class InputFileNameAppInputParserStrategy:public AbstractAppInputParserStrategy {
	public:
		InputFileNameAppInputParserStrategy();
		virtual ~InputFileNameAppInputParserStrategy();

		void fillParameter(const string &parameter, Parameters &outParameters) const override final;
	};

	class OutputFileNameAppInputParserStrategy :public AbstractAppInputParserStrategy {
	public:
		OutputFileNameAppInputParserStrategy();
		virtual ~OutputFileNameAppInputParserStrategy();

		void fillParameter(const string &parameter, Parameters &outParameters) const override final;
	};

	class WidthAppInputParserStrategy :public AbstractAppInputParserStrategy {
	public:
		WidthAppInputParserStrategy();
		virtual ~WidthAppInputParserStrategy();

		void fillParameter(const string &parameter, Parameters &outParameters) const override final;
	};

	class HeightAppInputParserStrategy :public AbstractAppInputParserStrategy {
	public:
		HeightAppInputParserStrategy();
		virtual ~HeightAppInputParserStrategy();

		void fillParameter(const string &parameter, Parameters &outParameters) const override final;
	};
}
#endif // !_APPINPUTPARSERSTRATEGY_H_
