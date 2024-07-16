#
# Copyright (C) 2021-2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := $(call my-dir)

ifneq ($(filter sake,$(TARGET_DEVICE)),)

# A/B builds require us to create the mount points at compile time.
# Just creating it for all cases since it does not hurt.
FIRMWARE_MOUNT_POINT := $(TARGET_OUT_VENDOR)/firmware_mnt
$(FIRMWARE_MOUNT_POINT): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating $(FIRMWARE_MOUNT_POINT)"
	@mkdir -p $(TARGET_OUT_VENDOR)/firmware_mnt

BT_FIRMWARE_MOUNT_POINT := $(TARGET_OUT_VENDOR)/bt_firmware
$(BT_FIRMWARE_MOUNT_POINT): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating $(BT_FIRMWARE_MOUNT_POINT)"
	@mkdir -p $(TARGET_OUT_VENDOR)/bt_firmware

DSP_MOUNT_POINT := $(TARGET_OUT_VENDOR)/dsp
$(DSP_MOUNT_POINT): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating $(DSP_MOUNT_POINT)"
	@mkdir -p $(TARGET_OUT_VENDOR)/dsp

ALL_DEFAULT_INSTALLED_MODULES += $(FIRMWARE_MOUNT_POINT) $(BT_FIRMWARE_MOUNT_POINT) $(DSP_MOUNT_POINT)

ASUSFW_MOUNT_POINT := $(TARGET_OUT_VENDOR)/asusfw
$(ASUSFW_MOUNT_POINT): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating $(ASUSFW_MOUNT_POINT)"
	@mkdir -p $(TARGET_OUT_VENDOR)/asusfw

FACTORY_MOUNT_POINT_SYMLINK := $(TARGET_OUT_VENDOR)/factory
$(FACTORY_MOUNT_POINT_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating $@ link"
	@rm -rf $@
	$(hide) ln -sf /mnt/vendor/persist $@

ALL_DEFAULT_INSTALLED_MODULES += $(ASUSFW_MOUNT_POINT) $(FACTORY_MOUNT_POINT_SYMLINK)

WIFI_FIRMWARE_SYMLINKS := $(TARGET_OUT_VENDOR)/firmware/wlan/qca_cld
$(WIFI_FIRMWARE_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating WiFi firmware symlinks: $@"
	@mkdir -p $@
	$(hide) ln -sf /vendor/factory/wlan_mac.bin $@/wlan_mac.bin
	$(hide) ln -sf /vendor/firmware/wlan/qca_cld/wlan/WCNSS_qcom_cfg.ini $@/WCNSS_qcom_cfg.ini

ALL_DEFAULT_INSTALLED_MODULES += \
    $(WIFI_FIRMWARE_SYMLINKS)

endif
