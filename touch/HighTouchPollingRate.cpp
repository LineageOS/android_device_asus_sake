/*
 * Copyright (C) 2021-2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "HighTouchPollingRateService"

#include "HighTouchPollingRate.h"

#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::string kHighTouchPollingRatePath =
    "/sys/devices/platform/soc/990000.i2c/i2c-1/1-0038/fts_high_report_rate";

Return<bool> HighTouchPollingRate::isEnabled() {
    std::ifstream file(kHighTouchPollingRatePath);
    bool enabled;

    file >> enabled;

    return enabled;
}

Return<bool> HighTouchPollingRate::setEnabled(bool enabled) {
    std::ofstream file(kHighTouchPollingRatePath);

    file << enabled << std::flush;

    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
