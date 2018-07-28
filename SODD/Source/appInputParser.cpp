#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include "../Include/appInputParser.h"
#include "../Include/BoundingRectangleGetters.h"
#include "../Include/graphdrawer.h"

using namespace std;

namespace aip {

	/*********************Parameters******************/
	/*******methods*******/
	shared_ptr<gd::AbstractBoundingRectangleGetter> Parameters::getBoundingRectangleGetter(const gd::Graph& graph) const {
		if (_height <= 0 && _width <= 0) {
			return shared_ptr<gd::AbstractBoundingRectangleGetter>(new gd::AutomaticWidthAndHeightBoundingRectangleGetter(graph));
		}
		else if (_width <= 0) {
			return shared_ptr<gd::AbstractBoundingRectangleGetter>(new gd::AutomaticWidthManualHeightBoundingRectangleGetter(graph, _height));
		}
		else if (_height <= 0) {
			return shared_ptr<gd::AbstractBoundingRectangleGetter>(new gd::ManualWidthAutomaticHeightBoundingRectangleGetter(graph, _width));
		}
		else {
			return shared_ptr<gd::AbstractBoundingRectangleGetter>(new gd::ManualWidthAndHeightBoundingRectangleGetter(_width, _height));
		}
	}

	/*********************AppInputParserExeption******************/
	/************consts*********/
	const string AppInputParserExeption::DefaultMessage = "Usage: inputFileName:string.txt outputFileName:string.jpg <width:int> <height:int>";
	/*******methods*******/
	AppInputParserExeption::AppInputParserExeption(const string &msg) {
		ostringstream tempMsg;
		tempMsg << msg << endl << DefaultMessage << endl;
		_finalMsg = tempMsg.str();
	}

	AppInputParserExeption::~AppInputParserExeption(){
	}

	const char * AppInputParserExeption::what() const throw(){
		return _finalMsg.c_str();
	}

	/*********************AppInputParser******************/
	/************consts*********/
	const string AppInputParser::NotEnoughParametersError = "Not enough parameters.";
	/*******methods*******/
	AppInputParser::AppInputParser(int parametersCount, char * parameters[]) {
		fillPropertyParserStrategies();
		_parameters = { "", "", "", -1, -1 };
		if (parametersCount < 3) {
			throw AppInputParserExeption(NotEnoughParametersError);
		}
		_parameters._appName = string(parameters[0]);
		for (int i = 1; i < parametersCount; ++i) {
			string parameter = string(parameters[i]);
			pair<string, string> words = splitParameter(parameter);
			auto strategy = _propertyParserStrategies.find(words.first);
			
			if (strategy == _propertyParserStrategies.end()) {
				throw AppInputParserExeption("Invalid parameter (" + words.first + ").");
			}
			
			strategy->second->fillParameter(words.second, _parameters);
		}
	}

	AppInputParser::~AppInputParser()
	{
	}

	const Parameters & AppInputParser::getParameters() const{
		return _parameters;
	}

	Parameters & AppInputParser::getParameters(){
		return _parameters;
	}
	
	void AppInputParser::fillPropertyParserStrategies(){
		_propertyParserStrategies = map<string, unique_ptr<AbstractAppInputParserStrategy> >();
		_propertyParserStrategies["inputFileName"] = unique_ptr<InputFileNameAppInputParserStrategy>(new InputFileNameAppInputParserStrategy());
		_propertyParserStrategies["outputFileName"] = unique_ptr<OutputFileNameAppInputParserStrategy>(new OutputFileNameAppInputParserStrategy());
		_propertyParserStrategies["width"] = unique_ptr<WidthAppInputParserStrategy>(new WidthAppInputParserStrategy());
		_propertyParserStrategies["height"] = unique_ptr<HeightAppInputParserStrategy>(new HeightAppInputParserStrategy());
	}

	pair<string,string> AppInputParser::splitParameter(string parameter) const {
		pair<string,string> words;
		size_t collonPosition = parameter.find(':');
		if (collonPosition == string::npos) {
			words.first = parameter;
			words.second = "";
		}
		else {
			words.first = parameter.substr(0, collonPosition);
			words.second = parameter.substr(collonPosition+1);
		}
		
		return words;
	}
}
