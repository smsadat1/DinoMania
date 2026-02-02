# DinoMania
A clone of Chrome dinosaur game made with C++ SFML

## Setup (Ubuntu 22.04+)
` $ git clone <repo> `
` $ sudo apt-get install libsfml-dev `
` $ cd <repo-name> `

## Setup (Windows 10/11)
Open powershell or cmd
` git clone <repo> `
` cd <repo-name> `


## Build and Installation (Ubuntu 22.04+)
```
$ mkdir build 
$ cd build
$ cmake ..
$ make -j $(nproc)
$ ./DinoMania
```

## Build and Installation (Windows 10/11)
```
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
make -j $(nproc)
DinoMania.exe
```
If you use static library
` cmake .. -G "Visual Studio 17 2022" -A x64 -DSFML_STATIC=ON `