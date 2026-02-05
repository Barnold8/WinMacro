$ScriptDirectory = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent


.("$ScriptDirectory\build_binary.ps1")
.("$ScriptDirectory\build\main.exe")