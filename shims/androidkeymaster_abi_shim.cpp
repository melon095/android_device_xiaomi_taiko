#include <cstdint>
#include <new>

namespace keymaster {
class KeymasterContext;
}  // namespace keymaster

#include <keymaster/android_keymaster.h>

extern "C" void _ZN9keymaster16AndroidKeymasterC1EPNS_16KeymasterContextEmj(
    keymaster::AndroidKeymaster* self, keymaster::KeymasterContext* context,
    unsigned long operation_table_size, unsigned int message_version) {
    new (self) keymaster::AndroidKeymaster(
        context, operation_table_size, static_cast<int32_t>(message_version));
}
