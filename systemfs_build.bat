del filesystem.vhd
del filesystem.img
copy template.vhd .\filesystem.vhd
((echo select vdisk file=C:\Users\Jeremy\Desktop\DCPUOS-master\filesystem.vhd) & (echo attach vdisk)) | diskpart

for /f %%D in ('wmic volume get DriveLetter^, Label ^| find "DCPUOSFS"') do set myDrive=%%D

xcopy /s C:\Users\Jeremy\Desktop\DCPUOS-master\system_filesystem\*.* %myDrive%\

((echo select vdisk file=C:\Users\Jeremy\Desktop\DCPUOS-master\filesystem.vhd) & (echo detach vdisk))|diskpart
.\qemu\qemu-img convert -f vpc filesystem.vhd -O raw filesystem.img
del filesystem.vhd
