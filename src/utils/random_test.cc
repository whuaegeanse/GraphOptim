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

#define TEST_NAME "util/random"
#include "utils/random.h"

#include <numeric>

#include "utils/math.h"
#include "utils/testing.h"

using namespace colmap;

BOOST_AUTO_TEST_CASE(TestPRNGSeed) {
  BOOST_CHECK(PRNG == nullptr);
  SetPRNGSeed();
  BOOST_CHECK(PRNG != nullptr);
  SetPRNGSeed(0);
  BOOST_CHECK(PRNG != nullptr);
}

BOOST_AUTO_TEST_CASE(TestRepeatability) {
  SetPRNGSeed(0);
  std::vector<int> numbers1;
  for (size_t i = 0; i < 100; ++i) {
    numbers1.push_back(RandomInteger(0, 10000));
  }
  SetPRNGSeed();
  std::vector<int> numbers2;
  for (size_t i = 0; i < 100; ++i) {
    numbers2.push_back(RandomInteger(0, 10000));
  }
  SetPRNGSeed(0);
  std::vector<int> numbers3;
  for (size_t i = 0; i < 100; ++i) {
    numbers3.push_back(RandomInteger(0, 10000));
  }
  BOOST_CHECK_EQUAL_COLLECTIONS(numbers1.begin(), numbers1.end(),
                                numbers3.begin(), numbers3.end());
  bool all_equal = true;
  for (size_t i = 0; i < numbers1.size(); ++i) {
    if (numbers1[i] != numbers2[i]) {
      all_equal = false;
    }
  }
  BOOST_CHECK(!all_equal);
}

BOOST_AUTO_TEST_CASE(TestRandomInteger) {
  SetPRNGSeed();
  for (size_t i = 0; i < 1000; ++i) {
    BOOST_CHECK_GE(RandomInteger(-100, 100), -100);
    BOOST_CHECK_LE(RandomInteger(-100, 100), 100);
  }
}

BOOST_AUTO_TEST_CASE(TestRandomReal) {
  SetPRNGSeed();
  for (size_t i = 0; i < 1000; ++i) {
    BOOST_CHECK_GE(RandomReal(-100.0, 100.0), -100.0);
    BOOST_CHECK_LE(RandomReal(-100.0, 100.0), 100.0);
  }
}

BOOST_AUTO_TEST_CASE(TestRandomGaussian) {
  SetPRNGSeed(0);
  const double kMean = 1.0;
  const double kSigma = 1.0;
  const size_t kNumValues = 100000;
  std::vector<double> values;
  for (size_t i = 0; i < kNumValues; ++i) {
    values.push_back(RandomGaussian(kMean, kSigma));
  }
  BOOST_CHECK_LE(std::abs(Mean(values) - kMean), 1e-2);
  BOOST_CHECK_LE(std::abs(StdDev(values) - kSigma), 1e-2);
}

BOOST_AUTO_TEST_CASE(TestShuffleNone) {
  SetPRNGSeed();
  std::vector<int> numbers(0);
  Shuffle(0, &numbers);
  numbers = {1, 2, 3, 4, 5};
  std::vector<int> shuffled_numbers = numbers;
  Shuffle(0, &shuffled_numbers);
  BOOST_CHECK_EQUAL_COLLECTIONS(numbers.begin(), numbers.end(),
                                shuffled_numbers.begin(),
                                shuffled_numbers.end());
}

BOOST_AUTO_TEST_CASE(TestShuffleAll) {
  SetPRNGSeed(0);
  std::vector<int> numbers(1000);
  std::iota(numbers.begin(), numbers.end(), 0);
  std::vector<int> shuffled_numbers = numbers;
  Shuffle(1000, &shuffled_numbers);
  size_t num_shuffled = 0;
  for (size_t i = 0; i < numbers.size(); ++i) {
    if (numbers[i] != shuffled_numbers[i]) {
      num_shuffled += 1;
    }
  }
  BOOST_CHECK_GT(num_shuffled, 0);
}
