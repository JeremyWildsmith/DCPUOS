xcopy /y initrd_bootstrap\initrd_bootstrap.bin initrd_filesystem\bootstrap
xcopy /y SHELL\SHELL.bin initrd_filesystem\shell
darkOsRsfs.exe rsfs initrd .\initrd_filesystem