cmake_minimum_required  (VERSION 3.1)
project                 (Revert CXX)

add_library (Revert INTERFACE)
add_library (Revert::Revert ALIAS Revert)

target_compile_features (Revert
    INTERFACE cxx_std_11
)

target_include_directories (Revert
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)


add_subdirectory (test)
