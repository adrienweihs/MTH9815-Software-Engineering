# MTH9815_tradingSystem


## Run steps:
#### 1. Change current directory to clone path
#### 2. To compile the project:
```Bash
g++  -c  "./main.cpp" -g -O0 -std=c++17 -Wall  -o ./Debug/main.cpp.o -I. -I.
```
```Bash
g++ -o ./Debug/tradingsystem @"tradingsystem.txt" -L.   
```
#### 3. Run the executable file:
```Bash
./Debug/tradingsystem
```

## Instructions:
#### 0. All steps include generating data and building trading system are done in single cpp project
#### 1. All .txt files will be output to ./Debug folder, as well as excutable file 
#### 2. BondStreamingService and BondExecutionService's output will be printed by cout
#### 3. All other's output will be printed to .txt files
#### 4. Generated data's size can be modified in main.cpp, the very first part in main function. Comments can be found there.
#### 5. Native compiler is Codelite and there is a TradingSystem.workspace file which can be imported by compiler

