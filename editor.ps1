Write-Output "Building editor..."
g++ ./editor-src/*.cpp ./third-party/*.cpp -o editor.exe -Wall -std=c++17 -lsfml-system -lsfml-graphics -lsfml-window -llua51 -lglu32 -lopengl32 -IC:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\include\
if ($LastExitCode -ne 0) {
    Write-Output "Building failed. Stopping..."
    return 2
}
Write-Output "Success! Starting the editor..."
./editor.exe
Remove-Item -path "./editor.exe"