# Настройки проекта
cmake_minimum_required(VERSION 3.15)
set(VCPKG_APPLOCAL_DEPS OFF CACHE BOOL "Disable vcpkg applocal deployment" FORCE)

project(sandform_starter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


add_executable(app app.cpp)

add_library(engine_sdk INTERFACE)
target_include_directories(engine_sdk INTERFACE "${CMAKE_SOURCE_DIR}/sdk")

# Активация модулей 
add_subdirectory(static/plugin_manager)

add_subdirectory(dynamic/logic)
add_subdirectory(dynamic/core)


# Подключение core и plugin_manager
target_link_libraries(app PRIVATE 
  core 
  plugin_manager
  logic
)


# ОС зависимость
if(CROSS_SETTINGS)
    message(STATUS "Загружаются кастомные настройки платформы из: ${CROSS_SETTINGS}")
    
    # Подключаем файл. CMake сам найдет его относительно CMAKE_SOURCE_DIR
    include(${CROSS_SETTINGS})
else()
    message(WARNING "CROSS_SETTINGS_FILE не задан в пресете! Используются дефолтные настройки.")
endif()

# Подключение nvim
if(CMAKE_EXPORT_COMPILE_COMMANDS)
set(SOURCE_FILE "${CMAKE_BINARY_DIR}/compile_commands.json")
set(DESTINATION_FILE "${CMAKE_SOURCE_DIR}/compile_commands.json")

if(NOT EXISTS ${DESTINATION_FILE})
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_FILE} ${DESTINATION_FILE})
endif()

endif()


# Копирование ресурсов
set(RES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

if(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(RES_TARGET_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
    set(RES_TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}")
endif()

set(RESOURCES_TO_COPY
    "${RES_SOURCE_DIR}/assets"
    "${RES_SOURCE_DIR}/configs"
    "${RES_SOURCE_DIR}/.plugins.json"
)
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/resources.stamp"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${RES_SOURCE_DIR}/assets" "${RES_TARGET_DIR}/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${RES_SOURCE_DIR}/configs" "${RES_TARGET_DIR}/configs"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RES_SOURCE_DIR}/.plugins.json" "${RES_TARGET_DIR}/.plugins.json"
    # Создаем маркер-файл, чтобы Ninja понимал, что копирование завершено успешно
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_BINARY_DIR}/resources.stamp"
    COMMENT "Копирование ресурсов (assets, configs, json) в папку сборки..."
)

add_custom_target(copy_engine_resources DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources.stamp")

add_dependencies(app copy_engine_resources)


install(TARGETS app
    RUNTIME DESTINATION "bin" 
    LIBRARY DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
)


