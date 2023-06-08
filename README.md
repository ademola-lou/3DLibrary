# How to build
## Linux

### install libraries
```cd wasm-library && ./install_libraries.sh ```

### install emsdk (https://emscripten.org/docs/getting_started/downloads.html)

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

### building wasm library (make sure you are in /wasm-library directory)

compiling cmake file and build
```
./build.sh gener
```
after editing the main.cpp, recurrent build will be
```
./build.sh
```

check build folder for index.js and index.wasm file
