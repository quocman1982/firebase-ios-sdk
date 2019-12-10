/*
 * Copyright 2019 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Firestore/core/src/firebase/firestore/local/index_free_query_engine.h"
#include "Firestore/core/src/firebase/firestore/local/memory_persistence.h"
#include "Firestore/core/src/firebase/firestore/local/query_engine.h"
#include "Firestore/core/src/firebase/firestore/local/reference_delegate.h"
#include "Firestore/core/src/firebase/firestore/local/simple_query_engine.h"
#include "Firestore/core/test/firebase/firestore/local/local_store_test.h"
#include "Firestore/core/test/firebase/firestore/local/persistence_testing.h"

namespace firebase {
namespace firestore {
namespace local {
namespace {

class TestHelper : public LocalStoreTestHelper {
 public:
  TestHelper(std::unique_ptr<QueryEngine> query_engine, bool index_free)
      : query_engine_(std::move(query_engine)), index_free_(index_free) {
  }

  std::unique_ptr<Persistence> MakePersistence() override {
    return MemoryPersistenceWithEagerGcForTesting();
  }

  QueryEngine* query_engine() override {
    return query_engine_.get();
  }

  /** Returns true if the garbage collector is eager, false if LRU. */
  bool IsGcEager() const override {
    return true;
  }

  bool IsIndexFree() const override {
    return index_free_;
  }

 private:
  std::unique_ptr<QueryEngine> query_engine_;
  bool index_free_;
};

std::unique_ptr<LocalStoreTestHelper> SimpleQueryEngineFactory() {
  return absl::make_unique<TestHelper>(absl::make_unique<SimpleQueryEngine>(),
                                       /* index_free= */ false);
}

std::unique_ptr<LocalStoreTestHelper> IndexFreeQueryEngineFactory() {
  return absl::make_unique<TestHelper>(
      absl::make_unique<IndexFreeQueryEngine>(), /* index_free= */ true);
}

}  // namespace

INSTANTIATE_TEST_SUITE_P(MemoryLocalStoreTest,
                         LocalStoreTest,
                         ::testing::Values(SimpleQueryEngineFactory,
                                           IndexFreeQueryEngineFactory));

}  // namespace local
}  // namespace firestore
}  // namespace firebase
