Get-ChildItem "dll_src/" -Filter *.c | 
Foreach-Object {
    $file_path     = $_.FullName
    
    $file_name     = $file_path.split("\")[-1]  
    $dll_name      = $file_name.split(".")[0]+".dll"

    $dll_full_path = "modules/"+$dll_name

    echo $dll_full_path

    gcc -shared -o $dll_full_path $file_path

}