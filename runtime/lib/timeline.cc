// Copyright (c) 2015, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

#include "vm/bootstrap_natives.h"

#include "include/dart_api.h"

#include "vm/native_entry.h"
#include "vm/object.h"
#include "vm/os.h"
#include "vm/timeline.h"

namespace dart {

// Native implementations for the dart:developer library.

DEFINE_NATIVE_ENTRY(Timeline_isDartStreamEnabled, 0, 0) {
#if defined(SUPPORT_TIMELINE)
  if (Timeline::GetDartStream()->enabled()) {
    return Bool::True().ptr();
  }
#endif
  return Bool::False().ptr();
}

DEFINE_NATIVE_ENTRY(Timeline_getNextTaskId, 0, 0) {
#if !defined(SUPPORT_TIMELINE)
  return Integer::New(0);
#else
  return Integer::New(thread->GetNextTaskId());
#endif
}

DEFINE_NATIVE_ENTRY(Timeline_getTraceClock, 0, 0) {
  return Integer::New(OS::GetCurrentMonotonicMicros(), Heap::kNew);
}

DEFINE_NATIVE_ENTRY(Timeline_reportTaskEvent, 0, 5) {
#if defined(SUPPORT_TIMELINE)
  GET_NON_NULL_NATIVE_ARGUMENT(Integer, id, arguments->NativeArgAt(0));
  GET_NON_NULL_NATIVE_ARGUMENT(String, phase, arguments->NativeArgAt(1));
  GET_NON_NULL_NATIVE_ARGUMENT(String, category, arguments->NativeArgAt(2));
  GET_NON_NULL_NATIVE_ARGUMENT(String, name, arguments->NativeArgAt(3));
  GET_NON_NULL_NATIVE_ARGUMENT(String, args, arguments->NativeArgAt(4));

  TimelineEventRecorder* recorder = Timeline::recorder();
  if (recorder == NULL) {
    return Object::null();
  }

  TimelineEvent* event = Timeline::GetDartStream()->StartEvent();
  if (event == NULL) {
    // Stream was turned off.
    return Object::null();
  }

  DartTimelineEventHelpers::ReportTaskEvent(
      thread, event, id.AsInt64Value(), phase.ToCString(), category.ToCString(),
      name.ToMallocCString(), args.ToMallocCString());
#endif  // SUPPORT_TIMELINE
  return Object::null();
}

DEFINE_NATIVE_ENTRY(Timeline_reportFlowEvent, 0, 5) {
#if defined(SUPPORT_TIMELINE)
  GET_NON_NULL_NATIVE_ARGUMENT(String, category, arguments->NativeArgAt(0));
  GET_NON_NULL_NATIVE_ARGUMENT(String, name, arguments->NativeArgAt(1));
  GET_NON_NULL_NATIVE_ARGUMENT(Integer, type, arguments->NativeArgAt(2));
  GET_NON_NULL_NATIVE_ARGUMENT(Integer, flow_id, arguments->NativeArgAt(3));
  GET_NON_NULL_NATIVE_ARGUMENT(String, args, arguments->NativeArgAt(4));

  TimelineEventRecorder* recorder = Timeline::recorder();
  if (recorder == NULL) {
    return Object::null();
  }

  TimelineEvent* event = Timeline::GetDartStream()->StartEvent();
  if (event == NULL) {
    // Stream was turned off.
    return Object::null();
  }

  DartTimelineEventHelpers::ReportFlowEvent(
      thread, event, category.ToCString(), name.ToMallocCString(),
      type.AsInt64Value(), flow_id.AsInt64Value(), args.ToMallocCString());
#endif  // SUPPORT_TIMELINE
  return Object::null();
}

DEFINE_NATIVE_ENTRY(Timeline_reportInstantEvent, 0, 3) {
#if defined(SUPPORT_TIMELINE)
  GET_NON_NULL_NATIVE_ARGUMENT(String, category, arguments->NativeArgAt(0));
  GET_NON_NULL_NATIVE_ARGUMENT(String, name, arguments->NativeArgAt(1));
  GET_NON_NULL_NATIVE_ARGUMENT(String, args, arguments->NativeArgAt(2));

  TimelineEventRecorder* recorder = Timeline::recorder();
  if (recorder == NULL) {
    return Object::null();
  }

  TimelineEvent* event = Timeline::GetDartStream()->StartEvent();
  if (event == NULL) {
    // Stream was turned off.
    return Object::null();
  }

  DartTimelineEventHelpers::ReportInstantEvent(
      thread, event, category.ToCString(), name.ToMallocCString(),
      args.ToMallocCString());
#endif  // SUPPORT_TIMELINE
  return Object::null();
}

}  // namespace dart
