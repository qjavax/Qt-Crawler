# QT documentation crawler

## How to build
### Prerequesites
* conan
* cmake

### Steps
* cd build
* cmake .. <optional argument list>
* cmake --build . <optional argument list> 


### Issues on M1 Mac
Force using clang as a compiler in debug mode (missing stdarg.h in xcode framework)
* cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_BUILD_TYPE=Debug