# NanoTun
__ВПН Конфигуратор__
<div align="center">
  <img src="src/github.images/NanoTunPreview.png" width="45%">  
  <img src="src/github.images/screenshot_from_app.png" width="45%">
</div>


### Главные фишки 👻
- Раздельное туннелирование - обход приложений (которые выберет пользователь) и .ru / .cn (По желанию)
- Режим __TUN__ и __TAP__
- Хороший интерфейс
- Поддержка больших конфигов (_до 5 тысч._)


### Запуск
**Важно** при запуске нужны CMake или G++ + pkg-configs.
#### Установка зависимостей:
Debian/ubuntu:
`sudo apt install build-essential cmake ninja g++ libgtkmm-4.0 libgtkmm-4.0-dev`
Arch based:
`sudo pacman -S base-devel cmake ninja g++ gtkmm-4.0`
Alpine:
`doas apk add build-base cmake ninja g++ gtkmm4`
Fedora/RHEL:
`sudo dnf groupinstall "Development Tools"; sudo dnf install -y gtkmm4-devel ninja-build gcc-c++ cmake meson`


#### Компиляция
- **(Лучший быстрый способ)** CMake + Ninja: `cmake -B build -G Ninja; cmake --build build; mv build/app .; rm -rf build`
- **(Нерекомендованный способ)** G++: `g++ -o app app.cpp $(pkg-config --cflags --libs  gtkmm-4.0) -std=c++17`
После компиляции просто запускаем `./app`

### Поддержка ♥️
___Пока что вы можете поддержать нас отправив Feature Request / Bug Report, это поможет нам устранить огромные ошибки!___

