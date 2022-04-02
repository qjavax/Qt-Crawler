# QT documentation crawler

# Usage
The application built by default is located in `<root_dir>/build/bin/qt_crawler_cli`

## Example of usage
```
./bin/qt_crawler_cli --url https://doc.qt.io/qt-5/classes.html --out ./outDir
```
Where `https://doc.qt.io/qt-5/classes.html` is starting point for crawler, `./outDir` is path to existing directory that application will write HTML code of visited web pages.

# Building and Installation
## Dependencies
* conan
* cmake

## Building
```
cd <root_dir>/build
cmake .. <optional argument list>
cmake --build . <optional argument list> 
```
## Known issues on Apple Silicon
With default XCode SDK on Debug build, compilation might fail with error stating that stdarg.h is missing in XCode Framework
To fix it run:
```
rm -rf <root_dir>/build/*
```
And retry building with forcing clang compiler
```
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_BUILD_TYPE=Debug
```