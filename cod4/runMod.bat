set WORKING_DIR=%cd%
set COD4_ROOT_DIR=%WORKING_DIR%\..\..\..

cd %COD4_ROOT_DIR%
start iw3mp.exe +set fs_game "mods\opencj" +set g_gametype cj +set dedicated 0 +set sv_punkbuster 0 +set developer 1 +set logfile 1 +set sv_hostname "OpenCJ testing" +devmap mp_crash