# Add driver as an executable target and pass optimization flags to compile with
add_executable(driver driver.cpp)
target_compile_options(driver PRIVATE -O3 -mavx2)

# Ensure HPX is there 
find_package(HPX REQUIRED)

# Link driver with HPX libs and matlib
target_link_libraries(driver PRIVATE HPX::hpx HPX::wrap_main matlib)