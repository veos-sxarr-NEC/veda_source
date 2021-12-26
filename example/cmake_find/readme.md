# CMake Injection Example

If you have an existing CPU application, you can use the ```InjectVE.cmake``` from VEDA to replace the host C/CXX/Fortran compiler with the NEC NCC compiler.

## How to build:
```bash
mkdir build
cd build
cmake -C /opt/nec/ve/share/veda/cmake/InjectVE.cmake ..
make
```
