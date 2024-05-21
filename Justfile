BIN := "build/Norden"

build: prep
    cmake --build build

prep:
    cmake -DCMAKE_BUILD_TYPE=Debug -G "Ninja" -B build -S .

run: build
    ./{{BIN}}

valgrind: build
    valgrind --leak-check=full {{BIN}}

lldb: build
    lldb {{BIN}}

gdb: build
    gdb {{BIN}}

release:
    cmake -DCMAKE_BUILD_TYPE=Release -G "Ninja" -B build -S .
    cmake --build build
    strip {{BIN}}
    upx {{BIN}}