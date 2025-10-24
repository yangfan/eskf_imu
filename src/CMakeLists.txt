add_executable(conversion gps_conversion.cpp)
target_include_directories(conversion PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(conversion utils glog::glog ${GFLAGS_LIBRARIES})

add_executable(imu_integration imu_integration.cpp)
target_include_directories(imu_integration PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(imu_integration utils glog::glog ${GFLAGS_LIBRARIES})

add_executable(eskf estimate_eskf.cpp)
target_include_directories(eskf PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(eskf utils glog::glog ${GFLAGS_LIBRARIES})

add_subdirectory(tools)