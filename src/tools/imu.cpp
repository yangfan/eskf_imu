#include "imu.h"
#include <glog/logging.h>

bool IMUIntegrator::integrate(const IMU &imu_data) {
  const double dt = imu_data.timestamp - state_.timestamp;
  if (dt > 0 && dt < 0.1) {
    const Eigen::Vector3d acc =
        state_.rot * (imu_data.acc - state_.bias_a) + state_.gravity;
    state_.pos += state_.vel * dt + 0.5 * acc * dt * dt;
    state_.vel += acc * dt;
    state_.rot *= Sophus::SO3d::exp((imu_data.gyr - state_.bias_g) * dt);
  }

  state_.timestamp = imu_data.timestamp;
  // assumming bias and gravity remain the same
  return true;
}