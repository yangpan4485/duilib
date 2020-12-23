@echo off
setlocal enabledelayedexpansion

set local_path=%~dp0
set src_path=%local_path%..\resources
set dest_path=%local_path%..\output\bin\Debug\

echo "copy file"
rd /s /Q %dest_path%resources
md %dest_path%resources

xcopy %src_path% %dest_path%resources /s /e 