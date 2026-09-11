# Device tree for the Xiaomi Redmi Pad 2 (taiko)

LineageOS 22.2 (Android 15) device tree for the Xiaomi Redmi Pad 2 (codename `taiko`, model 25040RP0AE), MediaTek Helio G100 Ultra (MT6789).

Structurally based on [device_xiaomi_yunluo](https://github.com/xiaomi-mt6789-devs/android_device_xiaomi_yunluo) (same MT6789 chipset family, officially supported).

Built against stock firmware `taiko_eea_global_images_OS2.0.201.0.VOVEUXM_20250620.0000.00_15.0_eea_d993468df3`.

## About this repository

Everything in this repository was written by an AI coding agent, not hand-authored by me. If you are interested in working on this device, please do not contact me about it. Please fork or copy the code and work on it yourself.

## Known issues

Everything following this was written by the AI agent, please do not trust what it is saying, everything here could be a complete lie!

- `vendor.xiaomi.hardware.mtdservice@1.0/1.1/1.2/1.3.so` and `vendor.mediatek.hardware.mtkpower@1.0.so` are not built in: their names collide with genuine AOSP-buildable modules of the same name that install to a different partition, and the normal `proprietary-files.txt` rename mechanism doesn't resolve it. Needs a hand-written `cc_prebuilt_library_shared` Soong module with a distinct `name:` and an explicit `stem:`. Not confirmed to break anything at runtime.
- `mtk_hal_c2` (Codec2 HAL) runs in a scoped `permissive` domain, not full SELinux enforcing — it's denied reading `custom_version_prop`, and granting that access hits a hard AOSP neverallow (HAL domains can't read that property type). No known fix.
- `hal_mtdservice_default` has one remaining property-write denial under enforcing (the real property name being set couldn't be identified from the binary; likely built via runtime string concatenation). The service itself works.
- `system_suspend` can't see one battery-related wakeup source (another neverallow wall, this one blocking vendor sepolicy from touching a platform-domain type). Suspend/resume itself works via other tracked sources.
- A kernel-level display DSC (stream compression) attach defect is present but currently invisible — a `disp_decompress=0` property workaround hides the visible symptom (purple/dither). The underlying kernel bug is unfixed since Xiaomi has never published taiko's kernel source.
- A handful of low-value AVC denials are left un-investigated by design: `dmesgd` (kmsg access — `adb shell dmesg` as root works fine without it), `vendor_init` (a broad property-scan denial), a one-off `secure_element` ART-cache category mismatch, and early-boot HAL processes writing startup logs to `/dev/kmsg` before `logd` is ready (cosmetic, several HAL domains do this).
