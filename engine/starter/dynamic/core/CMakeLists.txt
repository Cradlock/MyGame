set(CORE_SOURCES
  src/Engine.cpp 
  src/boot/BootConfig.cpp
  src/boot/BootLogger.cpp
  src/utils/root.cpp
  src/utils/time.cpp
  src/utils/str.cpp 
)


add_library(core SHARED ${CORE_SOURCES})

target_include_directories(core PUBLIC 
  include 
)

set(X_VCPKG_APPLOCAL_DEPS OFF)

find_package(RapidJSON CONFIG REQUIRED)

target_link_libraries(core PUBLIC engine_sdk)
target_link_libraries(core PUBLIC rapidjson)



install(TARGETS core
    RUNTIME DESTINATION "bin" 
    LIBRARY DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
)


