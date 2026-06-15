#include <vector>
#include <filesystem>
#include <stdexcept> // ОБЯЗАТЕЛЬНО: для std::runtime_error

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

std::filesystem::path get_executable_path() {
#if defined(_WIN32)
    std::vector<wchar_t> pathBuffer(MAX_PATH);
    while (true) {
        DWORD size = GetModuleFileNameW(NULL, pathBuffer.data(), static_cast<DWORD>(pathBuffer.size()));
        if (size == 0) break; 
        
        if (size == pathBuffer.size()) {
            pathBuffer.resize(pathBuffer.size() * 2);
        } else {
            return std::filesystem::path(pathBuffer.data());
        }
    }
#elif defined(__linux__)
    char buffer[4096];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        return std::filesystem::path(buffer);
    }
#endif

    throw std::runtime_error("FATAL: Operating System blocked access to executable path detection!");
}


