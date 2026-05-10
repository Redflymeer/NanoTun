# NanoTun
__VPN configurator__
<div align="center">
  <img src="src/github.images/NanoTunPreview.png" width="45%">  
  <img src="src/github.images/screenshot_from_app.png" width="45%">
</div>


### Features 👻
- Double tunneling - app bypass (user chooses) and site bypass (.ru / .cn) (Optional)
- **TUN** and **TAP** (no VPN mode) mode
- Good interface
- Support big configs (up to 5k)


### Compiling
**Important** for compiling needs CMake or G++ + pkg-configs.
#### Downloading addictions:
Debian/ubuntu:
`sudo apt install build-essential cmake ninja g++ libgtkmm-4.0 libgtkmm-4.0-dev`

Arch based:
`sudo pacman -S base-devel cmake ninja g++ gtkmm-4.0`

Alpine:
`doas apk add build-base cmake ninja g++ gtkmm4`

Fedora/RHEL:
`sudo dnf groupinstall "Development Tools"; sudo dnf install -y gtkmm4-devel ninja-build gcc-c++ cmake meson`


#### Compiling
- **(Recommended)** CMake + Ninja: `cmake -B build -G Ninja; cmake --build build; mv build/app .; rm -rf build`

- **(No Recommended)** G++: `g++ -o app app.cpp $(pkg-config --cflags --libs  gtkmm-4.0) -std=c++17`

after compiling starting `./app`

### Supporting ♥️
**Now you can only send to us Feature Request / Bug Report, it's will help us!**

