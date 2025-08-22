/*
 * Copyright (C) 2021-2022, 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "GloveModeService"

#include "GloveMode.h"

#include <fstream>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

const std::string kGloveModePath =
    "/sys/devices/platform/soc/990000.i2c/i2c-1/1-0038/fts_glove_mode";

ndk::ScopedAStatus GloveMode::getEnabled(bool* _aidl_return) {
    std::ifstream file(kGloveModePath);

    if (file.fail()) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    bool enabled;

    file >> enabled;

    *_aidl_return = enabled;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus GloveMode::setEnabled(bool enable) {
    std::ofstream file(kGloveModePath);

    if (file.fail()) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    file << enable << std::flush;

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
