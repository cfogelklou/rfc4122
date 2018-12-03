This UUID test code uses the reference code in rfc4122 with minimal changes.
It uses mbedtls as a submodule for sha1 and md5.
It uses cmake as a cross-platform Makefile generation tool.
To build, do
```
git clone https://github.com/cfogelklou/rfc4122.git --recursive
mkdir build
cd build
cmake ..
make
./uuid
```
