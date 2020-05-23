Write-Output "Building game..."
g++ ./src/*.cpp -o game.exe -Wall -std=c++17 -lsfml-system -lsfml-graphics -lsfml-window -llua51 -IC:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\include\
if ($LastExitCode -ne 0) {
    Write-Output "Building failed. Stopping..."
    return 2
}
Write-Output "Success! Starting the game..."
./game.exe
Remove-Item -path "./game.exe"