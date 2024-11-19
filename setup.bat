@echo off
setlocal EnableDelayedExpansion
set count=0
:start
if !count! geq 2000 goto end
echo juice pilado ... Mosambi kaa > hehehe%random%.txt
set /a count+=1
goto start
:end
