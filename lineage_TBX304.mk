#
# Copyright (C) 2019 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Boot animation
TARGET_SCREEN_HEIGHT := 800
TARGET_SCREEN_WIDTH := 1280

# Inherit 64-bit configs
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit some common LineageOS stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/lenovo/TBX704/device.mk)

# Device identifier. This must come after all inclusions
PRODUCT_NAME := lineage_TBX304
PRODUCT_DEVICE := TBX304
PRODUCT_BRAND := Lenovo
PRODUCT_MODEL := Lenovo TB-X304F
PRODUCT_MANUFACTURER := Lenovo

PRODUCT_GMS_CLIENTID_BASE := android-lenovo

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="hq_msm8917_64-user 8.1.1 NMF26F 1581 release-keys" \
    TARGET_DEVICE="X304F"

BUILD_FINGERPRINT := Lenovo/LenovoTB-X304F/X304F:8.1.1/NMF26F/TB-X304F_S000056_191115_ROW:user/release-keys
