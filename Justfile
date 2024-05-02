BIN := "bin/norden"
SOURCEFILES := "src/Gui.cpp src/View.cpp src/RectangleView.cpp src/ButtonView.cpp src/CompositeView.cpp src/TextView.cpp src/main.cpp"
LIBS := `pkg-config cairo cairomm-1.0 pango pangomm-1.4 --libs --cflags` + " -lSDL2 -lGL -lGLEW"
CFLAGS := "--std=c++23 -Wall -Wextra -Wpedantic"
INCLUDES := "-Iinclude"

build: prep
    clang++ {{INCLUDES}} {{CFLAGS}} {{LIBS}} {{SOURCEFILES}} -o {{BIN}} -g -DDEBUG  

prep:
    mkdir -p bin

run: build
    {{BIN}}

valgrind: build
    valgrind --leak-check=full {{BIN}}

lldb: build
    lldb {{BIN}}

gdb: build
    gdb {{BIN}}

release: prep
    clang++ {{INCLUDES}} {{CFLAGS}} {{LIBS}} {{SOURCEFILES}} -o {{BIN}} -O3 -DNDEBUG
    strip {{BIN}}
    upx {{BIN}}