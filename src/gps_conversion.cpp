#include <fstream>
#include <gflags/gflags.h>
#include <glog/logging.h>

#include "processor.h"

DEFINE_string(data_path, "./data/sensor_data.txt", "Data file path");
DEFINE_string(output_path, "./data/gps_conversion.txt", "Output file path");
DEFINE_double(antenna_x, -0.17, "Antenna pos x to IMU");
DEFINE_double(antenna_y, -0.20, "Antenna pos y to IMU");
DEFINE_double(antenna_angle, 12.06, "Antenna angle (deg) to IMU"); // deg

int main(int argc, char **argv) {
  // FLAGS_log_dir = std::string("./logs");
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;

  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  std::ifstream ifs(FLAGS_data_path);
  std::ofstream ofs(FLAGS_output_path);
  Processor processor;

  bool set_origin = false;
  Sophus::SE3d origin; // Two
  auto gnns_processor = [&](GNSS &gps) {
    if (!gps.convert_utm()) {
      LOG(ERROR) << "Failed to convert gps data to utm.";
      return;
    }
    Sophus::SE3d Tob = gps.body_pose(FLAGS_antenna_x, FLAGS_antenna_y,
                                     FLAGS_antenna_angle, origin);
    if (!set_origin) {
      origin = Sophus::SE3d(Sophus::SO3d(), Tob.translation());
      Tob.translation() = Eigen::Vector3d::Zero();
      set_origin = true;
    }
    // processor.write(ofs, gps.timestamp(), Tob);
    if (processor.write(ofs, gps.timestamp()) &&
        processor.write(ofs, Tob.translation()) &&
        processor.write(ofs, Tob.unit_quaternion())) {
      ofs << std::endl;
    }
  };
  processor.setGNSSProcessor(gnns_processor);

  processor.process(ifs);

  return 0;
}