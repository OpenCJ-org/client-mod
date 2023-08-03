Rem IMPORTANT: this makeMod.bat needs to be in the Mods/opencj/cod4 folder for the paths to work

@echo off
@Rem Some variables that are used multiple times or need to be remembered
SET OPENCJ_COD4_DIR=%cd%
SET OPENCJ_DIR=%OPENCJ_COD4_DIR%\..
SET ROOT_DIR=%OPENCJ_COD4_DIR%\..\..\..
SET RAW_DIR=%ROOT_DIR%\raw
SET BIN_DIR=%ROOT_DIR%\bin
SET ZONE_SOURCE_DIR=%ROOT_DIR%\zone_source
SET ZONE_DIR=%ROOT_DIR%\zone
SET OPENCJ_IWD=z_opencj.iwd
@echo on

@Rem we are in subdir cod4, and while we need files from here, the output needs to be in the parent directory for the fs_game to be working
cd %OPENCJ_DIR%

@CALL :CHECK_ERROR "Failed to cd to parent dir"

@Rem remove any existing output files
del z_opencj.iwd 2>NUL
del mod.ff 2>NUL

cd %OPENCJ_COD4_DIR%

@Rem ..and copy over all files to raw for the mod tools to do their job
@set /A nr_folders=0
@setlocal enabledelayedexpansion
@for %%x in (animtrees english fx images maps material_properties materials info mp soundaliases sound ui ui_mp weapons vision xanim xmodel xmodelparts xmodelsurfs) do (
    @if exist %%x\ (
        @set /A nr_folders+=1
        echo d | xcopy %%x "%RAW_DIR%\%%x" /SY
    ) else (
        @echo No %%x folder
    )
)
@endlocal

@CALL :CHECK_ERROR "One or more xcopy failed"

@Rem if no folders were copied, then we are probably in wrong directory
@if nr_folders equ 0 (
    @echo No folders to copy were found..
    pause
    exit /b 1
)

@Rem make sure to copy the mod.csv too so it is known what files are used for our mod
copy /Y mod.csv "%ZONE_SOURCE_DIR%"

@CALL :CHECK_ERROR "Failed to copy mod.csv"

@Rem go to the ModTools bin folder and start working
cd %BIN_DIR%
start /W linker_pc.exe -language english -compress -cleanup mod

@CALL :CHECK_ERROR "Failed to build mod"

@Rem go back to the mods/opencj/cod4 folder
cd %OPENCJ_COD4_DIR%

@Rem and now we can copy over the output files
copy "%ZONE_DIR%\english\mod.ff" "%OPENCJ_DIR%\"

@CALL :CHECK_ERROR "Failed to copy back mod.ff file"

7za a -r -tzip "%OPENCJ_DIR%\%OPENCJ_IWD%" images
7za a -r -tzip "%OPENCJ_DIR%\%OPENCJ_IWD%" materials
7za a -r -tzip "%OPENCJ_DIR%\%OPENCJ_IWD%" material_properties
7za a -r -tzip "%OPENCJ_DIR%\%OPENCJ_IWD%" weapons


:WAIT_FOR_INPUT
pause
@exit /B 0


:CHECK_ERROR
@if %errorlevel% neq 0 (
    @echo Error occurred: %~1
    cd %OPENCJ_COD4_DIR%
    pause
    Rem won't find this label but that's intended, otherwise we can't cause an exit return code from a called procedure
    GOTO END_NOK
    @exit /B %errorlevel%
)
