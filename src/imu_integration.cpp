#include <fstream>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <string>

#include "imu.h"
#include "processor.h"

DEFINE_string(data_path, "./data/sensor_data.txt", "Data file path");
DEFINE_string(output_path, "./data/imu_integration.txt", "Output file path");

int main(int argc, char **argv) {
  FLAGS_log_dir = std::string("./logs");
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;

  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  std::ifstream ifs(FLAGS_data_path);
  std::ofstream ofs(FLAGS_output_path);

  IMUState init_state;
  init_state.bias_g = Eigen::Vector3d(00.000224886, -7.61038e-05, -0.000742259);
  init_state.bias_a = Eigen::Vector3d(-0.165205, 0.0926887, 0.0058049);
  IMUIntegrator integrator(init_state);

  Processor processor;
  auto imu_processor = [&integrator, &processor, &ofs](const IMU &imu_data) {
    integrator.integrate(imu_data);
    if (processor.write(ofs, integrator.state().timestamp) &&
        processor.write(ofs, integrator.state().pos) &&
        processor.write(ofs, integrator.state().rot.unit_quaternion()) &&
        processor.write(ofs, integrator.state().vel)) {
      ofs << std::endl;
    }
  };
  processor.setIMUProcessor(imu_processor);
  processor.process(ifs);

  return 0;
}