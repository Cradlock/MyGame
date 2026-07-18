message(STATUS "=== Configuration: Windows x64 (MinGW Toolchain) ===")

# 1. Глобальные макросы для C++ кода
add_compile_definitions(
    SF_PLATFORM_WINDOWS=1
    SF_ARCH_X64=1
    WIN32_LEAN_AND_MEAN
)

# 2. Флаги оптимизации компилятора под x64
add_compile_options(
    -m64
    -O3
    -march=x86-64-v2
    -Wall
)

# Поиск системных DLL MinGW (для Linux хоста)
if(NOT DEFINED MINGW_BIN_DIR)
    set(MINGW_BIN_DIR "/usr/x86_64-w64-mingw32/bin")
endif()

set(GCC_DLL "libgcc_s_seh-1.dll")
set(REQUIRED_DLLS
    "${MINGW_BIN_DIR}/${GCC_DLL}"
    "${MINGW_BIN_DIR}/libstdc++-6.dll"
    "${MINGW_BIN_DIR}/libwinpthread-1.dll"
)

# 4. ЕДИНАЯ команда деплоя всех DLL (и системных, и vcpkg)
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${REQUIRED_DLLS} $<TARGET_FILE_DIR:app>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:core> $<TARGET_FILE_DIR:app>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:logic> $<TARGET_FILE_DIR:app>
    COMMAND_EXPAND_LISTS
    COMMENT "Deploying all Windows runtime and target DLLs..."
)


# 5. Дебаг-вывод зависимостей в консоль
add_custom_target(print_dlls ALL
    COMMAND ${CMAKE_COMMAND} -E echo "--- DLLS FOR APP: ---"
    COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_RUNTIME_DLLS:app>"
    COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_RUNTIME_DLLS:core>"
    COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_RUNTIME_DLLS:logic>"
    COMMAND ${CMAKE_COMMAND} -E echo "---------------------------------------"
    COMMAND_EXPAND_LISTS
)
add_dependencies(print_dlls app)

# 6. Правила инсталляции для дистрибутива
install(FILES ${REQUIRED_DLLS} DESTINATION "bin")

install(TARGETS core logic 
    RUNTIME DESTINATION "bin"
    LIBRARY DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
)
