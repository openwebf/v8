// Copyright 2017 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_OBJECTS_REGEXP_MATCH_INFO_H_
#define V8_OBJECTS_REGEXP_MATCH_INFO_H_

#include "src/base/compiler-specific.h"
#include "src/objects/fixed-array.h"
#include "src/objects/objects.h"

// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"

namespace v8 {
namespace internal {

class Object;
class String;

// TODO(jgruber): These should no longer be included here; instead, all
// TorqueGeneratedFooAsserts should be emitted into a global .cc file.
#include "torque-generated/src/objects/regexp-match-info-tq.inc"

// The property RegExpMatchInfo includes the matchIndices
// array of the last successful regexp match (an array of start/end index
// pairs for the match and all the captured substrings), the invariant is
// that there are at least two capture indices.  The array also contains
// the subject string for the last successful match.
// After creation the result must be treated as a FixedArray in all regards.
class RegExpMatchInfo : public FixedArray {
 public:
  // Returns the number of captures, which is defined as the length of the
  // matchIndices objects of the last match. matchIndices contains two indices
  // for each capture (including the match itself), i.e. 2 * #captures + 2.
  inline int NumberOfCaptureRegisters();
  inline void SetNumberOfCaptureRegisters(int value);

  // Returns the subject string of the last match.
  inline Tagged<String> LastSubject();
  inline void SetLastSubject(Tagged<String> value,
                             WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  // Like LastSubject, but modifiable by the user.
  inline Tagged<Object> LastInput();
  inline void SetLastInput(Tagged<Object> value,
                           WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  // Returns the i'th capture index, 0 <= i < NumberOfCaptures(). Capture(0) and
  // Capture(1) determine the start- and endpoint of the match itself.
  inline int Capture(int i);
  inline void SetCapture(int i, int value);

  // Creates a new RegExpMatchInfo with space for capture_count captures.
  static Handle<RegExpMatchInfo> New(Isolate* isolate, int capture_count);

  // Reserves space for captures.
  static Handle<RegExpMatchInfo> ReserveCaptures(
      Isolate* isolate, Handle<RegExpMatchInfo> match_info, int capture_count);

  static const int kNumberOfCapturesIndex = 0;
  static const int kLastSubjectIndex = 1;
  static const int kLastInputIndex = 2;
  static const int kFirstCaptureIndex = 3;
  static const int kLastMatchOverhead = kFirstCaptureIndex;

  // Every match info is guaranteed to have enough space to store two captures.
  static const int kInitialCaptureIndices = 2;

  DECL_CAST(RegExpMatchInfo)

  OBJECT_CONSTRUCTORS(RegExpMatchInfo, FixedArray);
};

}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"

#endif  // V8_OBJECTS_REGEXP_MATCH_INFO_H_
