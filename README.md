# 42_So_Long  🦖
Simple 2D game using the MinilibX library  
Contains instructions on how to install the required program and dependancies.
1. [Installing and Running X server](#install&runXsrv)
   - [Install an X server](#installXsrv)
   - [Starting up X server](#startXsrv)
   - [Test X server](#testXsrv)
2. [Running the program](#runProgram)
 
<a name="install&runXsrv"></a>
## Installing and Running X server
<a name="installXsrv"></a>
### Install an X server (VcXsrv)
There are various X servers. VcXsrv is for **Windows**.  
[Download here](https://sourceforge.net/projects/vcxsrv/)

<div>
  <img src="https://user-images.githubusercontent.com/75291303/125171009-7532f900-e1e4-11eb-9ad4-ede60287d477.png" height="200"/>
  <p>Download and start the installer</p>
</div>
 <div>
  <img src="https://user-images.githubusercontent.com/75291303/125171057-bb885800-e1e4-11eb-87f4-dff1a2de1eac.png" height="200"/>
  <p>Leave as default and hit <i>Next</i></p>
</div>
<div>
  <img src="https://user-images.githubusercontent.com/75291303/125171089-df4b9e00-e1e4-11eb-8e75-9a512daa3b0c.png" height="200"/>
  <p>Leave as default and hit <i>Install</i></p>
</div>
<div>
  <img src="https://user-images.githubusercontent.com/75291303/125171126-1752e100-e1e5-11eb-8717-ce5ffb60aa78.png" height="200"/>
  <p>Allow installation to complete</p>
</div>

<a name="startXsrv"></a>
### Starting up VcXsrv
<div>
  <img src="https://user-images.githubusercontent.com/75291303/125172663-7ddbfd00-e1ed-11eb-932c-0f9bb86c2a21.png" height="200"/>
  <p>Run <i>XLaunch</i></p>
</div>
<div>
  <img src="https://user-images.githubusercontent.com/75291303/125171617-ba0c5f00-e1e7-11eb-9ca1-2a6e97c8594a.jpg" height="200"/>
  <p>Leave as default and hit <i>Next</i></p>
</div>
<div>
  <img src="https://user-images.githubusercontent.com/75291303/125171673-f3dd6580-e1e7-11eb-907a-c81d62f11073.png" height="200"/>
  <p>Leave as default and hit <i>Next</i></p>
</div>
<div>
  <img src="https://user-images.githubusercontent.com/75291303/125171752-68180900-e1e8-11eb-9c40-b9d6a16b6042.png" height="200"/>
  <p>Check <i>Disable access control</i> then hit <i>Next</i></p>
</div>
<div>
  <img src="https://user-images.githubusercontent.com/75291303/125171780-90a00300-e1e8-11eb-8ad8-f1950ab4c637.png" height="200"/>
  <p>Hit <i>Finish</i></p>
</div>

![Screenshot 2021-07-11 012648](https://user-images.githubusercontent.com/75291303/125171516-3a7e9000-e1e7-11eb-8353-099ecfa6fc13.png)  
No window will be displayed but you'll find the VcXsrv icon in your taskbar

<a name="testXsrv"></a>
### Test that X server running accordingly 
1. Set display enviroment variable  
  - for WSL2  
> export DISPLAY=$(grep -oP "(?<=nameserver ).+" /etc/resolv.conf):0
   - for WSL1  
> export DISPLAY=:0
2. Install and run X applications
> sudo apt install x11-apps -y  
> xeyes  
> xclock

*An appication should pop out in a separate window*

<a name="runProgram"></a>
## To run program in terminal
1. Install required dependencies into system (Ubuntu/Debian)
> sudo apt-get update && sudo apt-get install gcc make xorg libxext-dev libbsd-dev
2. Set display environment variable(if haven't done so).
3. I think that's it. Continue project following [this guide](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)
