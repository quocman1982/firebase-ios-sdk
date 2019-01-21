/*
 * Copyright 2017 Google
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

#import <XCTest/XCTest.h>

#import "Firestore/Source/Model/FSTDocument.h"

#import "Firestore/Example/Tests/Util/FSTHelpers.h"

#include "Firestore/core/src/firebase/firestore/remote/existence_filter.h"
#include "Firestore/core/src/firebase/firestore/remote/watch_change.h"

using firebase::firestore::remote::ExistenceFilter;

NS_ASSUME_NONNULL_BEGIN

@interface FSTWatchChangeTests : XCTestCase
@end

@implementation FSTWatchChangeTests

- (void)testDocumentChange {
  FSTMaybeDocument *doc = FSTTestDoc("a/b", 1, @{}, FSTDocumentStateSynced);
  FSTDocumentWatchChange *change =
      [[FSTDocumentWatchChange alloc] initWithUpdatedTargetIDs:@[ @1, @2, @3 ]
                                              removedTargetIDs:@[ @4, @5 ]
                                                   documentKey:doc.key
                                                      document:doc];
  XCTAssertEqual(change.updatedTargetIDs.count, 3);
  XCTAssertEqual(change.removedTargetIDs.count, 2);
  // Testing object identity here is fine.
  XCTAssertEqual(change.document, doc);
}

- (void)testExistenceFilterChange {
  ExistenceFilter filter{7};
  FSTExistenceFilterWatchChange *change = [FSTExistenceFilterWatchChange changeWithFilter:filter
                                                                                 targetID:5];
  XCTAssertEqual(change.filter.count(), 7);
  XCTAssertEqual(change.targetID, 5);
}

- (void)testWatchTargetChange {
  FSTWatchTargetChange *change =
      [FSTWatchTargetChange changeWithState:FSTWatchTargetChangeStateReset
                                  targetIDs:@[ @1, @2 ]
                                      cause:nil];
  XCTAssertEqual(change.state, FSTWatchTargetChangeStateReset);
  XCTAssertEqual(change.targetIDs.count, 2);
}

@end

NS_ASSUME_NONNULL_END
