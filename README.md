# Simple-Object-Diagram-Drawer
A simple object diagram drawer usefull for the course "Software Engineering" at "Facultad de Ciencias Exactas y Naturales".

The app makes use of OpenCV.

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

In Source foulder open terminal and run: <br />
g++ -std=c++11 *.cpp -o 'output name' `pkg-config --cflags --libs opencv`

Example <br />
g++ -std=c++11 *.cpp -o main `pkg-config --cflags --libs opencv`

If when running the program it throws an error similar to the following

'./main: error while loading shared libraries: libopencv_imgcodecs.so.3.3: cannot open shared object file: No such file or directory'

run the following on the terminal

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib <br />
sudo ldconfig <br />

and try building again.

## Running the program

In order to run the program you have write the following in the terminal

'program name' inputFileName:'name of txt file' outputFileName:'name of output image with extention' [width:'width as integer'] [height:'height as integer']

The width and height are optionals and their order can be interchanged.

Example (on windows) <br />
SODD.exe inputFileName:Tests\test1.txt outputFileName:Tests\test1.jpg <br />