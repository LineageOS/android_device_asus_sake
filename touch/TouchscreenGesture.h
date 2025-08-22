/*
 * Copyright (C) 2022, 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/vendor/lineage/touch/BnTouchscreenGesture.h>


namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

using ::aidl::vendor::lineage::touch::Gesture;

struct GestureInfo {
    int32_t keycode;
    const char* name;
    const char* type;
};

class TouchscreenGesture : public BnTouchscreenGesture {
  public:
    ndk::ScopedAStatus getSupportedGestures(std::vector<Gesture>* _aidl_return) override;
    ndk::ScopedAStatus setGestureEnabled(const Gesture& gesture, bool enabled) override;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
