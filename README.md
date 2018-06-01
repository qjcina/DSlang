# DSlang
## Usage 
### Compiling
For compiling you will need cmake, on linux simply write (switch apt for your package manager):
```sh
$ sudo apt install cmake
```
For compiling use CMakeLists:
```
$ cmake CMakeLists.txt
$ make
```
Then just run compiled vm with your input file (ex. "in.asm"):
```
$ ./VM -fin.asm -C
```
You can always check your version with:
```
$ ./VM -v
```
Which is written as `MAJOR_VERSION.MINOR_VERSION.COMMIT`, for ex. `0.1.da5fd1b`. <br />
If you need further help just use `-h`
## Compiler
At this moment compiler only works with DS-asm, also generates simple byte-code as placeholder.
## Virtual Machine
DS VM is stack-based virtual machine for interpretation of DS-asm, which is sepecified [here](ASM.md).
VMs input can come from any type of `std::istream`.
### Memory
VM has 3 types of memory:
1. Map-based unlimited memory for variables.
2. Array-based 128-element memory for quick operation registers.
3. Main operations stack.
Additionaly vm stores jump positions in "seek map", which speeds up jumps in loops.
## Links
[Assembly specification](ASM.md)
