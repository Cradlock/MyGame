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
    "${RES_SOURCE_DIR}/.config.ini"
)
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/resources.stamp"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${RES_SOURCE_DIR}/assets" "${RES_TARGET_DIR}/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${RES_SOURCE_DIR}/configs" "${RES_TARGET_DIR}/configs"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RES_SOURCE_DIR}/.plugins.json" "${RES_TARGET_DIR}/.plugins.json"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RES_SOURCE_DIR}/.config.ini" "${RES_TARGET_DIR}/.config.ini"
    # Создаем маркер-файл, чтобы Ninja понимал, что копирование завершено успешно
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_BINARY_DIR}/resources.stamp"
    COMMENT "Copy resources (assets, configs, json) in bin folder..."
)

add_custom_target(copy_engine_resources DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources.stamp")

add_dependencies(app copy_engine_resources)


