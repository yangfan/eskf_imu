#pragma once

#include <Eigen/Core>
#include <sophus/se3.hpp>

class GNSS {
public:
  struct UTM {
    long zone = 0;
    bool north_hemi = true;
    Eigen::Vector2d xy;
  };
  GNSS(const double time, const double lat, const double lon, const double alt,
       const double head, const bool hvalid)
      : timestamp_(time), geodetic_(lat, lon, alt), heading_(head),
        heading_valid_(hvalid) {}

  bool convert_utm();
  Sophus::SE3d body_pose(const double antenna_x, const double antenna_y,
                         const double antenna_theta,
                         const Sophus::SE3d &origin);
  double timestamp() const { return timestamp_; }
  bool valid_heading() const { return heading_valid_; }

private:
  double timestamp_ = 0;
  Eigen::Vector3d geodetic_; // lat, lon (deg), alt
  double heading_ = 0;       // deg, orientation: north-east-down
  bool heading_valid_ = false;
  UTM utm_;
};