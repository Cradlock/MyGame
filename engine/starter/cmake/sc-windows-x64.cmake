message(STATUS "=== Конфигурация: Windows x64 (Кросс-компиляция MinGW) ===")

# 1. Глобальные макросы для C++ кода
add_compile_definitions(
    SF_PLATFORM_WINDOWS=1
    SF_ARCH_X64=1
    WIN32_LEAN_AND_MEAN     # Ускоряет компиляцию Windows.h, отсекая старый хлам
)

# 2. Флаги оптимизации компилятора под x64
add_compile_options(
    -m64                    # Жестко контролируем 64-битную сборку
    -O3                     # Максимальная оптимизация скорости
    -march=x86-64-v2        # Оптимизация под современные процессоры (SSE4.2, Popcnt)
    -Wall                   # Включаем предупреждения
)

# 3. Важнейшие флаги линковщика для кросс-компиляции
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -shared-libgcc")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared-libgcc")


set(MINGW_BIN_DIR "/usr/x86_64-w64-mingw32/bin")
set(GCC_DLL "libgcc_s_seh-1.dll")

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
