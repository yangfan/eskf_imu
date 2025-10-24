#pragma once

#include <Eigen/Core>
#include <sophus/so3.hpp>

struct IMU {
  IMU() = default;
  IMU(const double time, const Eigen::Vector3d &omega, const Eigen::Vector3d &a)
      : timestamp(time), gyr(omega), acc(a) {}
  double timestamp{0.0};
  Eigen::Vector3d gyr{};
  Eigen::Vector3d acc{};
};

struct IMUState {
  IMUState() = default;
  IMUState(const Eigen::Matrix<double, 18, 1> &vec)
      : pos(vec.head<3>()), vel(vec.segment<3>(3)),
        rot(Sophus::SO3d::exp(vec.segment<3>(6))), bias_g(vec.segment<3>(9)),
        bias_a(vec.segment<3>(12)), gravity(vec.tail<3>()) {}

  Eigen::Matrix<double, 18, 1> vec() const {
    Eigen::Matrix<double, 18, 1> res;
    res << pos, vel, rot.log(), bias_g, bias_a, gravity;
    return res;
  }
  double timestamp{0.0};
  Eigen::Vector3d pos = Eigen::Vector3d::Zero();
  Eigen::Vector3d vel = Eigen::Vector3d::Zero();
  Sophus::SO3d rot{};
  Eigen::Vector3d bias_g = Eigen::Vector3d::Zero();
  Eigen::Vector3d bias_a = Eigen::Vector3d::Zero();
  Eigen::Vector3d gravity{0, 0, -9.8};
  // Eigen::Vector3d bias_g =
  //     Eigen::Vector3d(00.000224886, -7.61038e-05, -0.000742259);
  // Eigen::Vector3d bias_a = Eigen::Vector3d(-0.165205, 0.0926887, 0.0058049);
};

class IMUIntegrator {
public:
  IMUIntegrator(const IMUState &init_state) : state_(init_state) {}
  bool integrate(const IMU &data);
  IMUState state() const { return state_; }

private:
  IMUState state_;
};
