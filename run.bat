:run.bat
cd debug
@echo Demonstrating Project #3
:start ServerExecutive.exe 9080
:start ClientExecutive.exe "Demonstrating Project 3" localhost 9080 localhost 9080
start ServerExecutive.exe 9080
start ClientExecutive.exe "../TestFolder/Test.txt" localhost 9080 localhost 9080
cd ..