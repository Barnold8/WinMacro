echo "building dlls..."

$ScriptDirectory = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent

echo "building main binary..."
.("$ScriptDirectory\build_dlls.ps1")

gcc .\src\main.c -o .\build\main.exe