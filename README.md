This UUID test code uses the reference code in rfc4122 with minimal changes.
It uses mbedtls as a submodule for sha1 and md5.
It uses cmake as a cross-platform Makefile generation tool.
```
git clone https://github.com/cfogelklou/rfc4122.git --recursive
```

To build in linux / osx, do

```
mkdir build
cd build
cmake ..
make
./uuid
```

To build in Visual Studio
```
cmake -G "Visual Studio 15 2017"
```

To build in Xcode
```
cmake -G Xcode
```

You get the gist.