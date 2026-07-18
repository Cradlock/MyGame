# Настройки проекта

# Версия cmake 
cmake_minimum_required(VERSION 3.21)


# Флаги проекта
set(VCPKG_APPLOCAL_DEPS ON CACHE BOOL "Disable vcpkg applocal deployment" FORCE)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Force shared libraries" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Проект - инстанс
project(sandform_starter VERSION 1.0.0 LANGUAGES CXX)

# Настройка компиляции
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Настройка путей бинарника
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


# Создание главного исполняемого файла 
add_executable(app app.cpp)

# Настройка SDK 
add_library(engine_sdk INTERFACE)
target_include_directories(engine_sdk INTERFACE "${CMAKE_SOURCE_DIR}/sdk")

# Список cmake файлов в папке /cmake 
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


# Активация модулей 
add_subdirectory(static/plugin_manager)

add_subdirectory(dynamic/logic)
add_subdirectory(dynamic/core)

add_subdirectory(resources)


# Подключение core,plugin_manager,logic К app 
target_link_libraries(app PRIVATE 
  core 
  plugin_manager
  logic
)

# Подключаем ресуры (resources/CMakeLists.txt)
add_dependencies(app copy_engine_resources)


# ОС зависимость
if(CROSS_SETTINGS)
  message(STATUS "LOAD os custom cmake settings: ${CROSS_SETTINGS}")
    
    # Подключаем файл. CMake сам найдет его относительно CMAKE_SOURCE_DIR
    include(${CROSS_SETTINGS})
else()
    message(WARNING "CROSS_SETTINGS_FILE not used in preset. used default!!!")
endif()



# nvim настройка
include(cmake/nvim.cmake)

# лицензии
file(COPY "${CMAKE_SOURCE_DIR}/../../licenses" 
     DESTINATION "${CMAKE_BINARY_DIR}"
)


install(TARGETS app
    RUNTIME DESTINATION "bin" 
    LIBRARY DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
)


