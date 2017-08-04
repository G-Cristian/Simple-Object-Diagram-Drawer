#include "../Include/renderer.h"
#include <algorithm>

using namespace std;

Renderer::Renderer(Window &window) {
	_window = Window();
	_window.name = window.name;
	_window.width = window.width;
	_window.height = window.height;

	_img = Mat::zeros(window.height, window.width, CV_8UC3);
}

Renderer::~Renderer() {

}

void Renderer::resizeWindow(int width, int height) {
	_window.width = width;
	_window.height = height;

	resize(_img, _img, Size(width, height));
}

void Renderer::drawCircle(Geometry::Point2D center, int radius) {
	circle(_img, Point(center.x, center.y), radius, Scalar(255, 255, 255));
}

void Renderer::drawLine(Geometry::Point2D p1, Geometry::Point2D p2) {
	line(_img, Point(p1.x, p1.y), Point(p2.x, p2.y), Scalar(255,255,255));
}

void Renderer::drawDashedLine(Geometry::Point2D p1, Geometry::Point2D p2, int linesLength) {
	Geometry::Point2D pointsDiff = p2 - p1;
	int length = static_cast<int>(sqrt((pointsDiff.x)*(pointsDiff.x) + (pointsDiff.y)*(pointsDiff.y)));

	Vec2d lineVector = Vec2d(pointsDiff.x, pointsDiff.y);
	lineVector = normalize(lineVector);
	Geometry::Point2D lineNormalized = Geometry::Point2D(lineVector[0], lineVector[1]);
	int i = 0;
	for (; i <= length - linesLength; i += linesLength * 2) {
		drawLine(p1 + lineNormalized*i, p1 + lineNormalized*(i + linesLength));
	}

	if (i < length) {
		drawLine(p1 + lineNormalized*i, p2);
	}
}

void Renderer::drawArrow(Geometry::Point2D p1, Geometry::Point2D p2) {
	drawLine(p1, p2);
	drawArrowTip(p2, Geometry::Point2D(p2.x - p1.x, p2.y - p1.y));
}

void Renderer::drawDashedArrow(Geometry::Point2D p1, Geometry::Point2D p2, int linesLength) {
	drawDashedLine(p1, p2, linesLength);
	drawArrowTip(p2, Geometry::Point2D(p2.x - p1.x, p2.y - p1.y));
}

void Renderer::drawDoubleArrow(Geometry::Point2D p1, Geometry::Point2D p2) {
	drawLine(p1, p2);
	drawArrowTip(p2, Geometry::Point2D(p2.x - p1.x, p2.y - p1.y));
	drawArrowTip(p1, Geometry::Point2D(p1.x - p2.x, p1.y - p2.y));
}

void Renderer::drawDashedDoubleArrow(Geometry::Point2D p1, Geometry::Point2D p2, int linesLength) {
	drawDashedLine(p1, p2, linesLength);
	drawArrowTip(p2, Geometry::Point2D(p2.x - p1.x, p2.y - p1.y));
	drawArrowTip(p1, Geometry::Point2D(p1.x - p2.x, p1.y - p2.y));
}

void Renderer::drawArrowTip(Geometry::Point2D p1, Geometry::Point2D directionVector) {
	Vec2d localDirection = normalize(Vec2d(directionVector.x, directionVector.y));

	Vec2d l1 = getRotated(localDirection, 50) * 25;
	Vec2d l2 = getRotated(localDirection, -50) * 25;
	
	drawLine(p1, p1 + Geometry::Point2D(-l1[0], -l1[1]));
	drawLine(p1, p1 + Geometry::Point2D(-l2[0], -l2[1]));
}
//'boundingOffsetPerLineOfText' will be scaled.
void Renderer::drawTextCenteredInBoundingCircle(const string &text, const Geometry::Circle &circle, double boundingOffsetPerLineOfText) {
	//TODO: Remove debug code
	vector<string> linesInText = splitStringByDelimiter(text, "\n");
	Geometry::Rectangle boundingRectangle = getBoundingRectangle(linesInText, boundingOffsetPerLineOfText);
	
	/*
	boundingRectangle.centerInCircle(circle);
	rectangle(_img, Point(boundingRectangle.getLeft(), boundingRectangle.getTop()),
		Point(boundingRectangle.getRight(), boundingRectangle.getBottom()),
		Scalar(0, 0, 255));
	*/


	boundingRectangle.scaleToBoundingCircle(circle);
	boundingRectangle.centerInCircle(circle);

	/*
	rectangle(_img, Point(boundingRectangle.getLeft(), boundingRectangle.getTop()),
		Point(boundingRectangle.getRight(), boundingRectangle.getBottom()),
		Scalar(0, 0, 255));
	*/

	drawTextToRectangle(linesInText, boundingRectangle, boundingOffsetPerLineOfText);
	/*
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1;
	int thickness = 1;

	//Mat img(600, 800, CV_8UC3, Scalar::all(0));

	Mat &img = _img;

	int baseline = 0;
	Size textSize = getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	// center the text
	Point textOrg((img.cols - textSize.width) / 2,
		(img.rows + textSize.height) / 2);

	// draw the box
	rectangle(img, textOrg + Point(0, baseline),
		textOrg + Point(textSize.width, -textSize.height),
		Scalar(0, 0, 255));
	// ... and the baseline first
	line(img, textOrg + Point(0, thickness),
		textOrg + Point(textSize.width, thickness),
		Scalar(0, 0, 255));

	// then put the text itself
	putText(img, text, textOrg, fontFace, fontScale,
		Scalar::all(255), thickness, 8);
	*/
}

Vec2d Renderer::getRotated(const Vec2d &vector, float angle) const {
	Vec2d res = Vec2d();
	res[0] = vector[0] * cosf(angle) - vector[1] * sinf(angle);
	res[1] = vector[0] * sinf(angle) + vector[1] * cosf(angle);

	return res;
}

vector<string> Renderer::splitStringByDelimiter(const string &stringToSplit, const string &delimiter) const {
	vector<string> strings = vector<string>();

	std::size_t currentPos = 0;
	std::size_t previousPos = 0;

	while ((currentPos = stringToSplit.find(delimiter, previousPos)) != std::string::npos) {
		strings.push_back(stringToSplit.substr(previousPos, currentPos - previousPos));
		previousPos = currentPos + delimiter.size();
	}

	strings.push_back(stringToSplit.substr(previousPos));

	return strings;
}

//'boundingOffsetPerLine' will be scaled.
Geometry::Rectangle Renderer::getBoundingRectangle(const vector<string> &lines, double boundingOffsetPerLine) const {
	int n = lines.size();
	double totalHeight = 0;
	double maxWidth = 0;

	for (int i = 0; i < n; i++) {
		Geometry::Rectangle aux = getBoundingRectangleUntilBaseOfWords(lines[i], boundingOffsetPerLine, 1);
		//TODO: Remove commented.
		//Geometry::Rectangle aux = getBoundingRectangleIncludingDescender(lines[i], boundingOffsetPerLine, 1);
		totalHeight += aux.getHeight();
		maxWidth = max(maxWidth, aux.getWidth());
	}
	return Geometry::Rectangle(0, 0, maxWidth, totalHeight);
}

//'boundingOffset' will be scaled by 'scale'.
Geometry::Rectangle Renderer::getBoundingRectangleUntilBaseOfWords(const string &singleLine, double boundingOffset, double scale) const {
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = scale;
	int thickness = 1;

	int baseline = 0;
	Size textSize = getTextSize(singleLine, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;
	
	return Geometry::Rectangle(0, 0, textSize.width + 2 * boundingOffset*scale, textSize.height + 2 * boundingOffset*scale);
}
//TODO: Remove if not used.
/*
//'boundingOffset' will be scaled by 'scale'.
Geometry::Rectangle Renderer::getBoundingRectangleIncludingDescender(const string &singleLine, double boundingOffset, double scale) const {
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = scale;
	int thickness = 1;

	int baseline = 0;
	Size textSize = getTextSize(singleLine, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	return Geometry::Rectangle(0, 0, textSize.width + 2 * boundingOffset * scale, textSize.height + baseline + 2 * boundingOffset * scale);
}
*/

//'boundingOffsetPerLine' will be scaled.
void Renderer::drawTextToRectangle(const vector<string> &lines, const Geometry::Rectangle &rect, double boundingOffsetPerLine) {
	int n = lines.size();
	if (n > 0) {
		Geometry::Rectangle boundingRectangle = getBoundingRectangle(lines, boundingOffsetPerLine);
		double widthScaleFactor = rect.getWidth() / boundingRectangle.getWidth();
		double heightScaleFactor = rect.getHeight() / boundingRectangle.getHeight();
		double scaleFactor = (rect.getHeight() > rect.getWidth()) ? heightScaleFactor : widthScaleFactor;
		double centeredX = rect.getLeft() + rect.getWidth() * 0.5;

		double step = 0;
		double currentY = rect.getTop();
		for (int i = 0; i < n; ++i) {
			step = getBoundingRectangleUntilBaseOfWords(lines[i], boundingOffsetPerLine, scaleFactor).getHeight();
			//TODO: Removed commented.
			//step = getBoundingRectangleIncludingDescender(lines[i], boundingOffsetPerLine, scaleFactor).getHeight();
			drawTextCentered(lines[i], boundingOffsetPerLine, scaleFactor, Geometry::Point2D(centeredX, currentY + step * 0.5));
			currentY += step;
		}
	}
}

//'boundingOffset' will be scaled by 'scale'.
void Renderer::drawTextCentered(const string &text, double boundingOffset, double scale, const Geometry::Point2D &center) {
	//TODO: Remove debug code
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = scale;
	int thickness = 1;
	Geometry::Rectangle boundingRectangleUntilBaseOfWords = getBoundingRectangleUntilBaseOfWords(text, 0, scale);
	Geometry::Point2D position = center - Geometry::Point2D(boundingRectangleUntilBaseOfWords.getWidth()* 0.5, -boundingRectangleUntilBaseOfWords.getHeight() * 0.5);
	//TODO: Removed commented
	/*
	Geometry::Rectangle boundingRectangle = getBoundingRectangleIncludingDescender(text, 0, scale);

	//c.y+(boundingRectangle.h/2 - (boundingRectangle.h - boundingRectangleUntilBaseOfWords.h)) = c.y + (-boundingRectangle.h/2 + boundingRectangleUntilBaseOfWords.h)
	Geometry::Point2D position = center - Geometry::Point2D(boundingRectangle.getWidth()* 0.5, -(-boundingRectangle.getHeight()*0.5 + boundingRectangleUntilBaseOfWords.getHeight()));
	*/
	/*
	rectangle(_img, Point(position.x, position.y - boundingRectangleUntilBaseOfWords.getHeight()),
		Point(position.x + boundingRectangleUntilBaseOfWords.getWidth(), position.y),
		Scalar(0, 0, 255));
	*/

	putText(_img, text, Point(position.x, position.y), fontFace, fontScale,
		Scalar::all(255), thickness, 8);
}

void Renderer::show(int x, int y)  const{
	imshow(_window.name, _img);
	moveWindow(_window.name, x, y);
}