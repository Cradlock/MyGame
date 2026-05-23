message(STATUS "=== Конфигурация: Windows x32/x86 (Кросс-компиляция MinGW) ===")

# 1. Глобальные макросы для C++ кода
add_compile_definitions(
    SF_PLATFORM_WINDOWS=1
    SF_ARCH_X86=1
    WIN32_LEAN_AND_MEAN
)

# 2. Флаги компилятора под 32 бита
add_compile_options(
    -m32                    # Жестко контролируем 32-битную сборку
    -O3
    -msse2                  # Базовые векторные инструкции (есть на всех x86 процах с 2004 года)
    -mfpmath=sse            # Считать математику через SSE, а не старый медленный сопроцессор 80387
    -Wall
)

# 3. Флаги линковщика


# Разрешаем динамическую линковку + флаг большой памяти для x32
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -shared-libgcc")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared-libgcc")

# Определяем пути к системным DLL MinGW в Arch Linux
set(MINGW_BIN_DIR "/usr/i686-w64-mingw32/bin")
set(GCC_DLL "libgcc_s_dw2-1.dll")

# Список всех DLL, которые должны лежать с аппкой
set(REQUIRED_DLLS
        "${MINGW_BIN_DIR}/${GCC_DLL}"
        "${MINGW_BIN_DIR}/libstdc++-6.dll"
        "${MINGW_BIN_DIR}/libwinpthread-1.dll"
    )

    # Добавляем кастомную команду после сборки app
add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${REQUIRED_DLLS}
            $<TARGET_FILE_DIR:app> # Это автоматически подставит папку, где лежит app.exe
        COMMENT "Копирование системных Windows DLL в папку сборки..."
)

install(FILES 
  "${MINGW_BIN_DIR}/${GCC_DLL}"
  "${MINGW_BIN_DIR}/libstdc++-6.dll"
  "${MINGW_BIN_DIR}/libwinpthread-1.dll"
  DESTINATION "bin" 
)

install(TARGETS 
  core logic 
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
)


