```txt
@echo off

echo开始清理系统垃圾文件，不要急......

rd /s /q C:\360SANDBOX\

rd /s /q C:\Config.Msi\

rd /s /q C:\MAXREPORT\

rd /s /q C:\MFG\

rd /s /q C:\Intel\

rd /s /q C:\MSOCache\

rd /s /q C:\Perflogs\

rd /s /q C:\swshare\

rd /s /q C:\SWTOOLS\

rd /s /q C:\FavoriteVideo\

rd /s /q C:\KanKan\

rd /s /q C:\MediaServer\

rd /s /q C:\MyDrivers\

rd /s /q C:\迅雷下载\

rd /s /q C:\Users\你的系统用户名文件夹\Documents\Tencent Files\你的QQ号码\FileRecv\

rd /s /q C:\Users\你的系统用户名文件夹\Documents\Tencent Files\你的QQ号码\Image\

del C:\p2pdown_30.log

del C:\setup.log

pushd "C:\Windows\SoftwareDistribution\Download\"

del * /q

for /d %%F in (*) do rd /s /q "%%F"

popd

pushd "%USERPROFILE%\AppData\Local\Temp\"

del * /q

for /d %%F in (*) do rd /s /q "%%F"

popd

pushd "C:\Windows\Temp\"

del * /q

for /d %%F in (*) do rd /s /q "%%F"

popd

pushd "%USERPROFILE%\AppData\Local\Google\Chrome\User Data\Default\Media Cache"

del * /q

for /d %%F in (*) do rd /s /q "%%F"

popd

pushd "%USERPROFILE%\AppData\Local\Google\Chrome\User Data\Default\Cache"

del * /q

for /d %%F in (*) do rd /s /q "%%F"

popd

del /f /s /q %systemdrive%\*.tmp

del /f /s /q %systemdrive%\*._mp

del /f /s /q %systemdrive%\*.log

del /f /s /q %systemdrive%\*.gid

del /f /s /q %systemdrive%\*.chk

del /f /s /q %systemdrive%\*.old

del /f /s /q %systemdrive%\recycled\*.*

del /f /s /q %windir%\*.bak

del /f /s /q %windir%\prefetch\*.*

echo 该删的都删了，满意了吗？

echo. & pause
```
* 选择“保存类型”为“所有文件”，文件名自己随便写一个，但是后缀要写成“.bat”。
* 然后用管理员权限运行即可
