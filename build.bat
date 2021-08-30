echo hello

set opts=-FC -GR- -EHa- -nologo -Zi
set code=%cd%
pushd .\debug

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"  "..\Run Hajta.vcxproj" /p:configuration=debug
popd

