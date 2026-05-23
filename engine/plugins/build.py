#!/usr/bin/env python3
import os
import sys
import shutil
from pathlib import Path

def deploy_plugins(target_os: str, bit_depth: str):
    """
    Сканирует папки плагинов и копирует скомпилированные .dll/.so 
    в каталог дистрибутива движка.
    """
    # Текущая директория, где лежит скрипт (т.е. .../plugins)
    pwd = Path(__file__).parent.resolve()
    
    # Формируем целевое имя папки сборки CMake, например: build_windows_x64 или build_linux_x64
    build_dir_name = f"build_{target_os}_{bit_depth}"
    
    # Путь назначения, куда собираем плагины, например: .../builder/tools/windows/x64/plugins
    # pwd.parent — это шаг вверх из plugins/ в корень, где лежит папка builder
    target_plugins_dir = pwd.parent / "builder" / "tools" / target_os / bit_depth / "plugins"
    
    print(f"=== Запуск деплоя плагинов для {target_os} ({bit_depth}) ===")
    print(f"Ищем папки сборки: {build_dir_name}")
    print(f"Целевая папка назначения: {target_plugins_dir}\n")

    # Маска для поиска нужных бинарников в зависимости от ОС
    # На Windows ищем .dll, на Linux ищем .so
    extension_pattern = "*.dll" if target_os.lower() == "windows" else "*.so"

    copied_count = 0

    # Сканируем все элементы внутри папки plugins/
    for item in pwd.iterdir():
        # Нас интересуют только подпапки (audio, graphics, и т.д.), пропускаем сам build.py
        if item.is_dir() and not item.name.startswith('.'):
            # Проверяем, есть ли внутри этой папки нужная директория сборки CMake
            cmake_build_path = item / build_dir_name
            
            if cmake_build_path.exists() and cmake_build_path.is_dir():
                print(f"-> Найдена сборка в плагине [{item.name}]")
                
                # Ищем файлы .dll или .so внутри этой папки сборки
                # rglob найдет их, даже если CMake положил их в подпапку (например, build_.../bin/)
                for binary_file in cmake_build_path.rglob(extension_pattern):
                    
                    # Жесткий фильтр: полностью игнорируем файлы импорта .dll.a
                    if binary_file.name.endswith(".dll.a"):
                        continue
                        
                    # Создаем целевую папку plugins/ (включая все поддиректории), если её ещё нет
                    target_plugins_dir.mkdir(parents=True, exist_ok=True)
                    
                    destination = target_plugins_dir / binary_file.name
                    
                    # Копируем файл (copy2 сохраняет метаданные и время изменения файла)
                    shutil.copy2(binary_file, destination)
                    print(f"   [Скопирован] {binary_file.name} -> tools/.../plugins/")
                    copied_count += 1
            else:
                # Если папка плагина есть, но для этой ОС он ещё не собирался — просто пропускаем
                pass

    print(f"\n=== Деплой завершен. Всего скопировано плагинов: {copied_count} ===")

if __name__ == "__main__":
    # Скрипт ожидает два аргумента: операционную систему и разрядность
    # Пример вызова: python build.py windows x64
    if len(sys.argv) < 3:
        print("Ошибка: Недостаточно аргументов!")
        print("Использование: python build.py {windows|linux} {x64|x32}")
        sys.exit(1)
        
    os_arg = sys.argv[1].lower()
    arch_arg = sys.argv[2].lower()
    
    # Быстрая валидация параметров
    if os_arg not in ["windows", "linux"] or arch_arg not in ["x64", "x32"]:
        print(f"Ошибка: Неверные параметры сборки: {os_arg} {arch_arg}")
        sys.exit(1)
        
    deploy_plugins(os_arg, arch_arg)
