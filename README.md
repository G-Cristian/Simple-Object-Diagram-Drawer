# Simple-Object-Diagram-Drawer
A simple object diagram drawer usefull for the course "Software Engineering" at "Facultad de Ciencias Exactas y Naturales".

The app makes use of OpenCV.

## Table of content
* Windows 10
  * Information for installation and configuration.
* Ubuntu
  * Information for installation and configuration
  * For building
* Running the program
* Syntax of the language
* Known issues

## Windows 10

Tested on Visual Studio 2015.

### Information for installation and configuration.

http://docs.opencv.org/3.0-beta/doc/tutorials/introduction/windows_install/windows_install.html

Set the OpenCV enviroment variable and add it to the systems path
http://docs.opencv.org/3.0-beta/doc/tutorials/introduction/windows_install/windows_install.html#windowssetpathandenviromentvariable

How to build applications with OpenCV inside the Microsoft Visual Studio
http://docs.opencv.org/3.0-beta/doc/tutorials/introduction/windows_visual_studio_Opencv/windows_visual_studio_Opencv.html#windows-visual-studio-how-to

Note that, because of the OpenCV version I have, when adding the additional dependencies I only added 'opencv_world320d.lib' (without quotes) for debug and 'opencv_world320.lib'(without quotes) for release.

## Ubuntu

### Information for installation and configuration

Guide from http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html

sudo apt-get install build-essential <br />
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev <br />
git clone https://github.com/opencv/opencv.git <br />
cd opencv <br />
mkdir release <br />
cd release <br />
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local .. <br />
make <br />
sudo make install <br />

Note: Use cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local .. , without spaces after -D if 'cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..' do not work.

### For building

In Source folder open terminal and run: <br />
g++ -std=c++11 *.cpp -o 'output name' \`pkg-config --cflags --libs opencv\`

Example <br />
g++ -std=c++11 *.cpp -o main \`pkg-config --cflags --libs opencv\`

If when running the program it throws an error similar to the following

'./main: error while loading shared libraries: libopencv_imgcodecs.so.3.3: cannot open shared object file: No such file or directory'

run the following on the terminal

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib <br />
sudo ldconfig <br />

and try building again.

## Running the program

In order to run the program you have to write the following in the terminal

'program name' inputFileName:'name of txt file' outputFileName:'name of output image with extention' \<width:'width as integer'\> \<height:'height as integer'\>

The width and height are optionals and their order can be interchanged. Note that these values are hints for the application and the actual size of the image may be smaller. These hints are usefull if your diagram has few objects. We will see an example when explaining the syntax of the language.

Example (on windows) <br />
SODD.exe inputFileName:Tests\test1.txt outputFileName:Tests\test1.jpg <br />

## Syntax of the language

First you must add the objects. These can have two properties: a description and a radius. Then you add the connections between them. There are two kinds of connections: arrows with dashed lines and arrows without solid lines.

Let's see an axample of a simple diagram.

```
object anObject{
 radius:10.5;
 description:"Hi\n there";
}

object anotherObject{
 radius:30.5;
 description:"bye\n here \n and there";
}

anObject->anotherObject;
anObject=>anotherObject;
anotherObject->anObject;
```

This is [test1.txt](Tests\test1.txt) and generated the image [test1AutoWidthAutoHeight.jpg](Tests\test1AutoWidthAutoHeight.jpg), if not setting the width nor height, and the image [test1ManualWidthManualHeight.jpg](Tests\test1ManualWidthManualHeight.jpg), when setting both width and height. Note how in this case you get better results by giving a hint for the desired size.

The 'object' word is a reserved word and mean the start of an object declaration. Then you must specify an object name, in this case 'anObject'. After that you must insert the properties between '{' and '}'. The allowed properties are 'radius' and 'description'. See that next to the property name you must write a ':' and then the property value, which is a numeric value, float or int, for radius and a string between '"' for the description. Note that at the end of eah property you must write a ';'. You can add as many object as you want. When you are finished you can add the connections between them. This is done by specifying the object name followed be '-\>' for a solid arrow or '=\>' for a dashed arrow and the name of the other object, ending with a ';'.

Some things to keep in mind are that everything, exept for the description, is not case sensitive, so OBJECT is the same as object, anObject is the same as ANOBJECT, etc.

Another thins is that the object names must be unique.

There are some examples in the [Tests](Tests) folder.

## Known issues
* Errors when parsing the file if using tabs instead of spaces.
* Can't use " character in object descriptions. (Should add support for escape characters like \\").
* Doesn't support connection to same object. Example, anObject->anObject.
