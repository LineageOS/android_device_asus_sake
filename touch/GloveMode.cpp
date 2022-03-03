/*
 * Copyright (C) 2021-2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "GloveModeService"

#include "GloveMode.h"

#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::string kGloveModePath =
    "/sys/devices/platform/soc/990000.i2c/i2c-1/1-0038/fts_glove_mode";

Return<bool> GloveMode::isEnabled() {
    std::ifstream file(kGloveModePath);
    std::string line;
    while (getline(file, line)) {
        if (line == "Glove Mode: On") return true;
    }
    return false;
}

Return<bool> GloveMode::setEnabled(bool enabled) {
    std::ofstream file(kGloveModePath);
    file << (enabled ? "1" : "0");
    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
