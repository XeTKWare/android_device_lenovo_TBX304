/*
   Copyright (c) 2016, The CyanogenMod Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/sysinfo.h>
#include <stdlib.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

#define PROP_BOOT_BASEBAND "ro.boot.baseband"
using android::base::GetProperty;

void property_override(char const prop[], char const value[])
{
	prop_info *pi;

	pi = (prop_info*) __system_property_find(prop);
	if (pi)
		__system_property_update(pi, value, strlen(value));
	else
		__system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], const char value[])
{
	property_override(system_prop, value);
	property_override(vendor_prop, value);
}


static void set_fingerprint()
{
	std::string baseband = GetProperty(PROP_BOOT_BASEBAND, "");
	if (baseband == "apq") {
		property_override("ro.build.description", "hq_msm8917_64-user 8.1.1 NMF26F 1581 release-keys");
		property_override("ro.build.product", "TB-X304F");
		property_override_dual("ro.product.device", "ro.vendor.product.device", "X304F");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "Lenovo/LenovoTB-X304F/X304F:8.1.1/NMF26F/TB-X304F_S000056_191115_ROW:user/release-keys");
		property_override_dual("ro.product.model", "ro.vendor.product.model", "Lenovo TB-X304F");
		//for installing stock OTA with TWRP
		property_override("ro.product.ota.model", "LenovoTB-X304F_ROW");
		property_override_dual("persist.multisim.config", "persist.radio.multisim.config", "");
		property_override("ro.radio.noril", "yes");
	} else if (baseband == "msm") {
		struct sysinfo sys;
		sysinfo(&sys);
		property_override("ro.build.description", "hq_msm8917_64-user 8.1.1 NMF26F 1580 release-keys");
		property_override("ro.build.product", "TB-X304L");
		property_override_dual("ro.product.device", "ro.vendor.product.device", "X304L");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "Lenovo/LenovoTB-X304L/X304L:8.1.1/NMF26F/TB-X304L_S000056_191115_ROW:user/release-keys");
		property_override_dual("ro.product.model", "ro.vendor.product.model", "Lenovo TB-X304L");
		//for installing stock OTA with TWRP
		property_override("ro.product.ota.model", "LenovoTB-X304L_ROW");
		property_override("ro.telephony.default_network", "22,20");
		property_override("ro.telephony.lteOnCdmaDevice", "1");
		property_override_dual("persist.multisim.config", "persist.radio.multisim.config", "ssss");
		property_override("ro.radio.noril", "");
	}
}

void vendor_load_properties()
{
	set_fingerprint();
}