aux_source_directory(. SRCS)
list(APPEND SRCS ${CMAKE_CURRENT_SOURCE_DIR}/MyDemo.rc)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../output/bin/${Configuration})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Duilib)

add_executable(MyDemo ${SRCS})

target_link_libraries(MyDemo duilib)