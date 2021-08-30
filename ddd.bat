@echo off

set opts=-FC -GR- -EHa- -nologo -Zi
set code=%cd%
pushd dfd
cl %opts% %code%\ddds -Fedfd
popd
