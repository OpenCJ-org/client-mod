Rem IMPORTANT: this makeMod.bat needs to be in the Mods/opencj/cod4 folder for the paths to work

@Rem Some variables that are used multiple times or need to be remembered
@echo off
SET OPENCJ_COD4_DIR=%cd%
SET OPENCJ_DIR=%OPENCJ_COD4_DIR%\..
SET ROOT_DIR=%OPENCJ_COD4_DIR%\..\..\..
SET RAW_DIR=%ROOT_DIR%\raw
SET BIN_DIR=%ROOT_DIR%\bin
SET ZONE_SOURCE_DIR=%ROOT_DIR%\zone_source
SET ZONE_DIR=%ROOT_DIR%\zone
SET OPENCJ_IWD=z_opencj.iwd
SET OPENCJ_FF=mod.ff
@echo on

@Rem we are in subdir cod4, and while we need files from here, the output needs to be in the parent directory for the fs_game to be working
cd %OPENCJ_DIR%

@if ERRORLEVEL 1 echo "Failed to cd to parent dir" & cd %OPENCJ_COD4_DIR% & goto:eof

@Rem remove any existing output files
@if exist %OPENCJ_IWD% (
    del %OPENCJ_IWD%
)
@if exist %OPENCJ_FF% (
    del %OPENCJ_FF%
)

@if ERRORLEVEL 1 echo "Failed to remove output files (perhaps the game is using them?)" & cd %OPENCJ_COD4_DIR% & goto:eof

cd %OPENCJ_COD4_DIR%

@Rem ..and copy over all files to raw for the mod tools to do their job
@set /A nr_folders=0
@setlocal enabledelayedexpansion
@for %%x in (opencj animtrees english fx images maps material_properties materials info mp soundaliases sound ui ui_mp weapons vision xanim xmodel xmodelparts xmodelsurfs) do (
    @if exist %%x\ (
        @set /A nr_folders+=1
        echo d | xcopy %%x "%RAW_DIR%\%%x" /SY
    ) else (
        @echo No %%x folder
    )
)
@endlocal

@if ERRORLEVEL 1 echo "One or more xcopy failed" & cd %OPENCJ_COD4_DIR% & goto:eof

@Rem if no folders were copied, then we are probably in wrong directory
@if nr_folders equ 0 (
    @echo No folders to copy were found..
    GOTO:FAIL
)

@Rem make sure to copy the mod.csv too so it is known what files are used for our mod
copy /Y mod.csv "%ZONE_SOURCE_DIR%"

@if ERRORLEVEL 1 echo "Failed to copy mod.csv" & cd %OPENCJ_COD4_DIR% & goto:eof

@Rem go to the ModTools bin folder and start working
cd %BIN_DIR%
start /W linker_pc.exe -language english -compress -cleanup mod

@if ERRORLEVEL 1 echo "Failed to build mod" & cd %OPENCJ_COD4_DIR% & goto:eof

@Rem go back to the mods/opencj/cod4 folder
cd %OPENCJ_COD4_DIR%

@Rem and now we can copy over the output files
copy "%ZONE_DIR%\english\mod.ff" "%OPENCJ_DIR%\"

@if ERRORLEVEL 1 echo "Failed to copy back mod.ff file" & cd %OPENCJ_COD4_DIR% & goto:eof

@Rem ..and zip all folders to the iwd
@set /A nr_folders_zip=0
@setlocal enabledelayedexpansion
@for %%x in (images weapons) do (
    @if exist %%x\ (
        @set /A nr_folders_zip+=1
        start /W 7za a -r -tzip "%OPENCJ_DIR%\%OPENCJ_IWD%" %%x
    ) else (
        @echo No %%x folder to add to zip
    )
)
@endlocal

@echo =========== Mod created successfully! ===========
pause
@exit /B 0

