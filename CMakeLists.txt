# 1. Минимальная версия CMake
cmake_minimum_required(VERSION 3.20)

# 2. Имя проекта и язык
project(NanoTun LANGUAGES CXX)

# 3. Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Поиск библиотек через pkg-config (Alpine использует pkgconf)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

# 5. Исходники
add_executable(app
    app.cpp
)

# 6. Подключаем библиотеки
target_link_libraries(app PRIVATE PkgConfig::GTKMM)
