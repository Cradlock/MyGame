message(STATUS "=== Configuration: Windows x32/x86 (MinGW Toolchain) ===")

# 1. Глобальные макросы для C++ кода
add_compile_definitions(
    SF_PLATFORM_WINDOWS=1
    SF_ARCH_X86=1
    WIN32_LEAN_AND_MEAN
)

# 2. Флаги компилятора под 32 бита
add_compile_options(
    -m32                    # Жестко контролируем 32-битную сборку
    -O3                     # Максимальная оптимизация
    -msse2                  # Базовые векторные инструкции
    -mfpmath=sse            # Математика через SSE, обгоняя стандартный x87
    -Wall
)


# Определяем пути к системным DLL MinGW в Arch Linux (i686 архитектура)
if(NOT DEFINED MINGW_BIN_DIR)
    set(MINGW_BIN_DIR "/usr/i686-w64-mingw32/bin")
endif()

set(GCC_DLL "libgcc_s_dw2-1.dll")
set(REQUIRED_DLLS
    "${MINGW_BIN_DIR}/${GCC_DLL}"
    "${MINGW_BIN_DIR}/libstdc++-6.dll"
    "${MINGW_BIN_DIR}/libwinpthread-1.dll"
)

# 4. ЕДИНАЯ команда деплоя всех DLL (и системных x32, и vcpkg)
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${REQUIRED_DLLS} $<TARGET_FILE_DIR:app>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:core> $<TARGET_FILE_DIR:app>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:logic> $<TARGET_FILE_DIR:app>
    COMMAND_EXPAND_LISTS
    COMMENT "Deploying all 32-bit Windows runtime and target DLLs..."
)

# 5. Дебаг-вывод зависимостей в консоль
add_custom_target(print_dlls ALL
    COMMAND ${CMAKE_COMMAND} -E echo "--- DLLS FOR APP (x32): ---"
    COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_RUNTIME_DLLS:app>"
    COMMAND ${CMAKE_COMMAND} -E echo "---------------------------------------"
    COMMAND_EXPAND_LISTS
)
add_dependencies(print_dlls app)

# 6. Правила инсталляции для 32-битного дистрибутива
install(FILES ${REQUIRED_DLLS} DESTINATION "bin")

install(TARGETS core logic 
    RUNTIME DESTINATION "bin"
    LIBRARY DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
)
