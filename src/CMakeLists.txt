include_directories(commands)

file(GLOB_RECURSE FILENAMES *.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(phyLS phyLS.cpp ${FILENAMES})
target_link_libraries(phyLS alice mockturtle libabc-pic)

# include_directories(commands)

# # 手动设置其他的源文件（排除 phyLS.cpp 和 test.cpp）
# file(GLOB_RECURSE OTHER_FILENAMES "src/*.cpp")
# list(REMOVE_ITEM OTHER_FILENAMES ${CMAKE_SOURCE_DIR}/src/phyLS.cpp ${CMAKE_SOURCE_DIR}/src/test.cpp)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# # 如果需要生成 phyLS 可执行文件，取消注释以下内容
# # add_executable(phyLS phyLS.cpp ${OTHER_FILENAMES})
# # target_link_libraries(phyLS alice mockturtle libabc-pic)

# # 生成 test 可执行文件
# add_executable(test test.cpp ${OTHER_FILENAMES})
# target_link_libraries(test alice mockturtle libabc-pic)

