// Copyright 2015 The Crashpad Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "snapshot/test/test_memory_map_region_snapshot.h"

namespace crashpad {
namespace test {

TestMemoryMapRegionSnapshot::TestMemoryMapRegionSnapshot() : memory_info_() {
}

TestMemoryMapRegionSnapshot::~TestMemoryMapRegionSnapshot() {
}

void TestMemoryMapRegionSnapshot::SetMindumpMemoryInfo(
    const MINIDUMP_MEMORY_INFO& mmi) {
  memory_info_ = mmi;
}

const MINIDUMP_MEMORY_INFO& TestMemoryMapRegionSnapshot::AsMinidumpMemoryInfo()
    const {
  return memory_info_;
}

}  // namespace test
}  // namespace crashpad
