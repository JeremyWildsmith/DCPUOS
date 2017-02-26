xcopy /y initrd_bootstrap\initrd_bootstrap.bin initrd_filesystem\terminal
xcopy /y SHELL\SHELL.bin initrd_filesystem\shell
darkOsRsfs.exe rsfs initrd .\initrd_filesystem