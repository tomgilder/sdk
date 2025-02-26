// Copyright (c) 2022, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

// @dart = 2.9

// SharedOptions=--enable-experiment=records

main() {
  var r1 = const (42);
  //             ^
  // [analyzer] SYNTACTIC_ERROR.EXPERIMENT_NOT_ENABLED
  // [cfe] This requires the experimental 'records' language feature to be enabled.
  //                ^
  // [analyzer] SYNTACTIC_ERROR.RECORD_LITERAL_ONE_POSITIONAL_NO_TRAILING_COMMA
  // [cfe] Record literal with one field requires a trailing comma.

  var r2 = const ();
  //             ^
  // [analyzer] SYNTACTIC_ERROR.EXPERIMENT_NOT_ENABLED
  // [cfe] This requires the experimental 'records' language feature to be enabled.
  //              ^
  // [analyzer] SYNTACTIC_ERROR.RECORD_LITERAL_EMPTY
  // [cfe] Record literal can't be empty.
}
