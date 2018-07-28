#ifndef _APPINPUTPARSER_H_
#define _APPINPUTPARSER_H_

#include <exception>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include "../Include/appInputParserStrategy.h"

using namespace std;

namespace aip {
	class AbstractAppInputParserStrategy;
	class gd::AbstractBoundingRectangleGetter;
	class gd::Graph;

	struct Parameters {
		string _appName;
		string _inputFileName;
		string _outputFileName;
		int _width;
		int _height;

		shared_ptr<gd::AbstractBoundingRectangleGetter> getBoundingRectangleGetter(const gd::Graph& graph) const;
	};

	class AppInputParserExeption :public exception {
	public:
		const static string DefaultMessage;
		AppInputParserExeption(const string &msg);
		~AppInputParserExeption();

		virtual const char* what() const throw();
	private:
		string _finalMsg;
	};

	class AppInputParser {
	public:
		const static string NotEnoughParametersError;

		AppInputParser(int parametersCount, char *parameters[]);
		~AppInputParser();

		const Parameters &getParameters()const;
		Parameters &getParameters();
	private:
		void fillPropertyParserStrategies();
		pair<string,string> splitParameter(string parameter)const;
		Parameters _parameters;
		map<string, unique_ptr<AbstractAppInputParserStrategy> > _propertyParserStrategies;
	};
}
#endif // !_APPINPUTPARSER_H_
