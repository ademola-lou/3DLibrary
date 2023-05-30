if [ "$1" == "gener" ]; then
    # echo "setting up emsdk..."
    # cd emsdk
    # ./emsdk activate latest
    # # Activate PATH and other environment variables in the current terminal
    # source ./emsdk_env.sh
    # cd ..
    # pwd
    echo "Generating makefile..."
    rm -rf build
    mkdir build && cd build
    emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
    emmake make
elif [ "$1" == "emsdk" ]; then
    echo "setting up emsdk..."
    cd emsdk
    ./emsdk activate latest
    # Activate PATH and other environment variables in the current terminal
    source ./emsdk_env.sh
    cd ..
    clear
else
    echo "building..."
    cd build
    emmake make
    
fi
