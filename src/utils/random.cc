// Copyright (C) 2014 The Regents of the University of California (Regents).
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//
//     * Neither the name of The Regents or University of California nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Please contact the author of this library if you have any questions.
// Author: Chris Sweeney (cmsweeney@cs.ucsb.edu)

// BSD 3-Clause License

// Copyright (c) 2021, Chenyu
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "utils/random.h"

#include <algorithm>

namespace gopt {

#ifdef GOPT_HAS_THREAD_LOCAL_KEYWORD
thread_local std::mt19937 util_generator;
#else
static std::mt19937 util_generator;
#endif  // GOPT_HAS_THREAD_LOCAL_KEYWORD

RandomNumberGenerator::RandomNumberGenerator() {
  const unsigned seed =
      std::chrono::system_clock::now().time_since_epoch().count();
  util_generator.seed(seed);
}

RandomNumberGenerator::RandomNumberGenerator(const unsigned seed) {
  util_generator.seed(seed);
}

void RandomNumberGenerator::Seed(const unsigned seed) {
  util_generator.seed(seed);
}

// Get a random double between lower and upper (inclusive).
double RandomNumberGenerator::RandDouble(const double lower,
                                         const double upper) {
  std::uniform_real_distribution<double> distribution(lower, upper);
  return distribution(util_generator);
}

float RandomNumberGenerator::RandFloat(const float lower, const float upper) {
  std::uniform_real_distribution<float> distribution(lower, upper);
  return distribution(util_generator);
}

// Get a random int between lower and upper (inclusive).
int RandomNumberGenerator::RandInt(const int lower, const int upper) {
  std::uniform_int_distribution<int> distribution(lower, upper);
  return distribution(util_generator);
}

// Gaussian Distribution with the corresponding mean and std dev.
double RandomNumberGenerator::RandGaussian(const double mean,
                                           const double std_dev) {
  std::normal_distribution<double> distribution(mean, std_dev);
  return distribution(util_generator);
}

// Gaussian Distribution with the zero mean and one dev.
double RandomNumberGenerator::RandStdGaussian() {
  std::normal_distribution<double> distribution(0, 1);
  return distribution(util_generator);
}

Eigen::Vector2d RandomNumberGenerator::RandVector2d(const double min,
                                                    const double max) {
  return Eigen::Vector2d(RandDouble(min, max), RandDouble(min, max));
}

Eigen::Vector2d RandomNumberGenerator::RandVector2d() {
  return RandVector2d(-1.0, 1.0);
}

Eigen::Vector3d RandomNumberGenerator::RandVector3d(const double min,
                                                    const double max) {
  return Eigen::Vector3d(RandDouble(min, max), RandDouble(min, max),
                         RandDouble(min, max));
}

Eigen::Vector3d RandomNumberGenerator::RandVector3d() {
  return RandVector3d(-1.0, 1.0);
}

Eigen::Vector4d RandomNumberGenerator::RandVector4d(const double min,
                                                    const double max) {
  return Eigen::Vector4d(RandDouble(min, max), RandDouble(min, max),
                         RandDouble(min, max), RandDouble(min, max));
}

Eigen::Vector4d RandomNumberGenerator::RandVector4d() {
  return RandVector4d(-1.0, 1.0);
}

Eigen::Vector2d RandomNumberGenerator::RandnVector2d() {
  return Eigen::Vector2d(RandStdGaussian(), RandStdGaussian());
}

Eigen::Vector3d RandomNumberGenerator::RandnVector3d() {
  return Eigen::Vector3d(RandStdGaussian(), RandStdGaussian(), RandStdGaussian());
}

Eigen::Vector4d RandomNumberGenerator::RandnVector4d() {
  return Eigen::Vector4d(RandStdGaussian(),
                         RandStdGaussian(),
                         RandStdGaussian(),
                         RandStdGaussian());
}

}  // namespace gopt
