@echo off
echo cleartrash

md .\temp_dir

move .\Obj\Listings .\temp_dir
move .\Obj\Objects .\temp_dir
move .\Obj\Template.hex .\temp_dir

del /f /s /q  .\Obj\*.*

move .\temp_dir\Listings .\Obj\ 
move .\temp_dir\Objects .\Obj\ 
move .\temp_dir\Template.hex .\Obj\ 

rd .\temp_dir