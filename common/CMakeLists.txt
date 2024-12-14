# Ajout des sous-répertoires s'ils ont un fichier CMakeLists.txt
add_subdirectory(ecs)
add_subdirectory(files_selector)
add_subdirectory(protocol)
add_subdirectory(graphics_primitives)

# Créer une interface pour inclure les fichiers headers
add_library(common_interface INTERFACE)

target_include_directories(common_interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
