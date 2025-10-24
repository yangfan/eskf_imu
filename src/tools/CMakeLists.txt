add_library(utils gnss.cpp processor.cpp imu.cpp initializer.cpp odom.cpp eskf.cpp
    ${PROJECT_SOURCE_DIR}/3rdparty/GeoConvert/tranmerc.cc
    ${PROJECT_SOURCE_DIR}/3rdparty/GeoConvert/utm.cc
)
target_include_directories(utils PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/3rdparty/GeoConvert/
)
target_link_libraries(utils Eigen3::Eigen Sophus::Sophus glog::glog)