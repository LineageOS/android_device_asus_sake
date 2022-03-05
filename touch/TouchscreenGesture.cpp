/*
 * Copyright (C) 2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"

#include <android-base/file.h>
#include <android-base/logging.h>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

using ::android::hardware::Void;

Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(const Gesture& gesture, bool enabled) {
    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
