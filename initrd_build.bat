xcopy /y initrd_bootstrap\initrd_bootstrap.bin .\initrd_filesystem\terminal
xcopy /y SHELL\SHELL.bin .\initrd_filesystem\txtio
xcopy /y stnacs\stnacs.bin .\initrd_filesystem\stnacs
xcopy /y nic\nic.bin .\initrd_filesystem\nic
darkOsRsfs.exe rsfs initrd .\initrd_filesystem