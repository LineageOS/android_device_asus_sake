#
# Copyright (C) 2021-2023 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from the device configuration.
$(call inherit-product, device/asus/sake/device.mk)

# Inherit from the Lineage configuration.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

PRODUCT_BRAND := asus
PRODUCT_DEVICE := sake
PRODUCT_MANUFACTURER := asus
PRODUCT_MODEL := ASUS_I006D
PRODUCT_NAME := lineage_sake

PRODUCT_GMS_CLIENTID_BASE := android-asus

PRODUCT_BUILD_PROP_OVERRIDES += \
    TARGET_DEVICE=ASUS_I006D \
    TARGET_PRODUCT=WW_I006D

BUILD_FINGERPRINT := asus/WW_I006D/ASUS_I006D:13/TKQ1.220807.001/33.0210.0210.210:user/release-keys
