/*
 * Copyright (C) 2021-2022, 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "HighTouchPollingRateService"

#include "HighTouchPollingRate.h"

#include <fstream>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

const std::string kHighTouchPollingRatePath =
    "/sys/devices/platform/soc/990000.i2c/i2c-1/1-0038/fts_high_report_rate";

ndk::ScopedAStatus HighTouchPollingRate::getEnabled(bool* _aidl_return) {
    std::ifstream file(kHighTouchPollingRatePath);

    if (file.fail()) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    bool enabled;

    file >> enabled;

    *_aidl_return = enabled;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus HighTouchPollingRate::setEnabled(bool enabled) {
    std::ofstream file(kHighTouchPollingRatePath);

    if (file.fail()) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    file << enabled << std::flush;

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
