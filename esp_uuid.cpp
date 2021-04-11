#include "esp_uuid.h"

namespace esp_uuid {

UUID::UUID() {
  for (int i = 0; i < 16; i += 4) {
    uint32_t random = esp_random();
    memcpy(&buffer_[i], &random, 4);
  }

  // Format the UUID --> version number and control bits
  buffer_[6] = (buffer_[6] & 0x0F) | 0x40;
  buffer_[8] = (buffer_[8] & 0x3F) | 0x80;
}

UUID::UUID(String& uuid) : UUID(uuid.c_str()) {}

UUID::UUID(const char* uuid) { fromString(uuid); }

UUID::UUID(const JsonVariantConst& uuid) {
  if (uuid.isNull() || !uuid.is<char*>()) {
    clear();
    return;
  }

  fromString(uuid.as<char*>());
}

bool UUID::operator<(const UUID& rhs) const { return buffer_ < rhs.buffer_; }
bool UUID::operator>(const UUID& rhs) const { return rhs < *this; }
bool UUID::operator<=(const UUID& rhs) const { return !(*this > rhs); }
bool UUID::operator>=(const UUID& rhs) const { return !(*this < rhs); }

bool UUID::operator==(const UUID& rhs) const { return buffer_ == rhs.buffer_; }
bool UUID::operator!=(const UUID& rhs) const { return !(*this == rhs); }

size_t UUID::printTo(Print& p) const {
  size_t n = 0;

  // Convert to HEX and break up into blocks (8, 4, 4, 4, 12)
  for (int i = 0; i < 16; i++) {
    if (i == 4 || i == 6 || i == 8 || i == 10) {
      n += p.write("-");
    }
    n += p.print(buffer_[i] >> 4, HEX);
    n += p.print(buffer_[i] & 0x0F, HEX);
  }
  return n;
}

String UUID::toString() const {
  String uuid_str;
  uuid_str.reserve(36 + 1);  // Include NULL / terminator byte

  for (int i = 0; i < 16; i++) {
    if (i == 4 || i == 6 || i == 8 || i == 10) {
      uuid_str += "-";
    }
    uuid_str += String(buffer_[i] >> 4, HEX);
    uuid_str += String(buffer_[i] & 0x0F, HEX);
  }
  return uuid_str;
}

bool UUID::fromString(const char* uuid) {
  if (!uuid || strlen(uuid) != 36) {
    clear();
    return false;
  }

  char uuid_str[32];
  char* outc = uuid_str;
  for (int i = 0; i < 36; ++i) {
    char c = uuid[i];
    if (i == 8 || i == 13 || i == 18 || i == 23) {
      if (c != '-') {
        return false;
      }
    } else {
      if (!isxdigit(c)) {
        return false;
      }
      *outc = (char)tolower(c);
      ++outc;
    }
  }

#define UUID_HEXCHRTO_DEC(c)               \
  (unsigned char)((c) <= '9' ? ((c) - '0') \
                             : 10 + (c) - ((c) <= 'F' ? 'A' : 'a'))

  for (int byte = 0; byte < 16; ++byte) {
    unsigned char v1 = UUID_HEXCHRTO_DEC(uuid_str[byte * 2]);
    unsigned char v2 = UUID_HEXCHRTO_DEC(uuid_str[byte * 2 + 1]);
    buffer_[byte] = (unsigned char)((v1 << 4) | v2);
  }
#undef UUID_HEXCHRTO_DEC

  if (isValid()) {
    return true;
  } else {
    clear();
    return false;
  }
}

bool UUID::fromString(String& uuid) { return fromString(uuid.c_str()); }

void UUID::clear() {
  memset(buffer_.data(), 0,
         (sizeof(buffer_[0]) / sizeof(uint8_t)) * buffer_.size());
}

bool UUID::isValid() const {
  // The 13th hex has to be 4
  if (buffer_[6] >> 4 != 0x4) {
    return false;
  }

  // The 17th hex has to by 0x8, 0x9, 0xA or 0xB
  uint8_t hex17 = buffer_[8] >> 4;
  if (hex17 != 0x8 && hex17 != 0x9 && hex17 != 0xA && hex17 != 0xB) {
    return false;
  }

  return true;
}

}  // namespace esp_uuid
