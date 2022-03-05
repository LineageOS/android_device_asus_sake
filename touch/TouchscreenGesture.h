/*
 * Copyright (C) 2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <vendor/lineage/touch/1.0/ITouchscreenGesture.h>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

using ::android::hardware::Return;
using ::vendor::lineage::touch::V1_0::Gesture;

class TouchscreenGesture : public ITouchscreenGesture {
  public:
    // Methods from ::vendor::lineage::touch::V1_0::ITouchscreenGesture follow.
    Return<void> getSupportedGestures(getSupportedGestures_cb resultCb) override;
    Return<bool> setGestureEnabled(const Gesture& gesture, bool enabled) override;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
