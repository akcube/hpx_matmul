# Creates the library and sets compiler flags
add_library(matlib matrix.hpp)
set_target_properties(matlib PROPERTIES LINKER_LANGUAGE CXX) 
target_compile_options(matlib PRIVATE -O3 -mavx2)

# Find HPX
find_package(HPX REQUIRED)

# Users of our library will need this include
target_include_directories(matlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add HPX include dirs and link our library to HPX privately
target_include_directories(matlib PRIVATE ${HPX_INCLUDE_DIR})
target_link_libraries(matlib PRIVATE HPX::hpx)