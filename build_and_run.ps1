$ScriptDirectory = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent


.("$ScriptDirectory\build_binary.ps1")
echo "Running..."
.("$ScriptDirectory\build\main.exe")