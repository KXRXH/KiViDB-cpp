# KiViDB C++

Simple non-SQL database. Was written with [Golang](https://github.com/BigCubeCat/KiViDB), but now with C++

## Usage

### Create an environment variables

```bash
$ export KIVIDB_HOME=/any/folder/you/like
$ export KIVIDB_PORT=8080
```

### Build

```bash
$ mkdir include
$ cd include
$ curl -LO https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow_all.h
$ cd ..
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```
<div style="text-align: center;"><h3>or</h3></div>

```bash
$ ./build.sh
```

### Run

```bash
$ ./kividb
```
