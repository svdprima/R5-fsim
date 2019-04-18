# R5-fsim
A simple RISC-V functional simulator which currently supports RV32IM instruction set and virtual memory simulation.

## Usage
Only linux is supported.  
To run available tests (for example, queens) compile the simulator
```console
make build_src
```
and launch  
```console
./build/src/simulator ./build/tests/<test_name>/<test_name>.elf
```
There is also a python script which runs the simulator n times and calculates the mean MIPS and standard deviation
```console
python run.py <n>
```
or 
```console
python run.py <n> -v
```
to print MIPS metric for every run.  
RISC-V GNU toolchain is required to compile new tests. After setting the toolchain, place the source code to 
```console
tests/<your_test_name>.c  
```
and set the PATH variable
```console
. set_env.sh
```
To compile the test, the source code and launch the simulator, type
```console
make TEST=<your_test_name> 
```
To compile and run the test, launch
```console
make TEST=<your_test_name> build_test 
```
