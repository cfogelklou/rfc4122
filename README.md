# Quick and dirty implementation of RFC1422 using mbedTLS

[![Build and Test](https://github.com/cfogelklou/rfc4122/actions/workflows/actions.yml/badge.svg)](https://github.com/cfogelklou/rfc4122/actions/workflows/actions.yml)

This UUID test code uses the reference code in rfc4122 with minimal changes.
It uses mbedtls as a submodule for sha1 and md5.
It uses cmake as a cross-platform Makefile generation tool.

```sh
git clone https://github.com/cfogelklou/rfc4122.git --recursive
```

To build in linux / osx, do

```sh
mkdir build
cd build
cmake ..
make
./uuid
```

To build in Visual Studio

```sh
cmake -G "Visual Studio 15 2017"
```

To build in Xcode

```sh
cmake -G Xcode
```

Then run with ./uuid
