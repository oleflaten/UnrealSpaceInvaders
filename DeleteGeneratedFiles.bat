Echo deleting folders

@RD /S /Q "Binaries"
@RD /S /Q "Build"
@RD /S /Q "Saved"
@RD /S /Q "Intermediate"
@RD /S /Q "DerivedDataCache"
@RD /S /Q "Script"
@RD /S /Q ".vs"
@RD /S /Q ".idea"
DEL "*.code-workspace" /s /f /q
DEL "*.sln" /s /f /q
DEL "*.sln.DotSettings.user" /s /f /q

