/*
 *  Copyright 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <jni.h>
#undef JNIEXPORT
#define JNIEXPORT __attribute__((visibility("default")))

#include "webrtc/examples/unityplugin/classreferenceholder.h"
#include "webrtc/rtc_base/ssladapter.h"
#include "webrtc/sdk/android/src/jni/classreferenceholder.h"
#include "webrtc/sdk/android/src/jni/jni_helpers.h"

namespace webrtc_jni {

extern "C" jint JNIEXPORT JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved) {
  jint ret = InitGlobalJniVariables(jvm);
  RTC_DCHECK_GE(ret, 0);
  if (ret < 0)
    return -1;

  RTC_CHECK(rtc::InitializeSSL()) << "Failed to InitializeSSL()";
  LoadGlobalClassReferenceHolder();
  unity_plugin::LoadGlobalClassReferenceHolder();

  return ret;
}

extern "C" void JNIEXPORT JNICALL JNI_OnUnLoad(JavaVM* jvm, void* reserved) {
  FreeGlobalClassReferenceHolder();
  unity_plugin::FreeGlobalClassReferenceHolder();
  RTC_CHECK(rtc::CleanupSSL()) << "Failed to CleanupSSL()";
}

}  // namespace webrtc_jni