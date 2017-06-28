xcopy /y initrd_bootstrap\initrd_bootstrap.bin initrd_filesystem\terminal
xcopy /y SHELL\SHELL.bin initrd_filesystem\txtio
xcopy /y stnacs\stnacs.bin initrd_filesystem\stnacs
darkOsRsfs.exe rsfs initrd .\initrd_filesystem