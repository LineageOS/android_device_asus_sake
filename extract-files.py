#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: 2024 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.file import File
from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)
from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

blob_fixups: blob_fixups_user_type = {
    ('vendor/lib64/libwvhidl.so', 'vendor/lib64/mediadrm/libwvdrmengine.so'): blob_fixup()
        .add_needed('libcrypto_shim.so'),
    ('vendor/etc/media_codecs.xml', 'vendor/etc/media_codecs_lahaina.xml', 'vendor/etc/media_codecs_lahaina_vendor.xml', 'vendor/etc/media_codecs_yupik_v1.xml'): blob_fixup()
        .regex_replace('.*media_codecs_(google_audio|google_c2|google_telephony|vendor_audio).*\n', ''),
    'vendor/etc/msm_irqbalance.conf': blob_fixup()
        .regex_replace('IGNORED_IRQ=27,23,38$', 'IGNORED_IRQ=27,23,38,115,332'),
}  # fmt: skip

module = ExtractUtilsModule(
    'sake',
    'asus',
    blob_fixups=blob_fixups,
)

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
