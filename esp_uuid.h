#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <array>

namespace esp_uuid {

/**
 * Holds a UUID and allows it to be used as a key in STL containers. It can be
 * constructed from a string or creates a new UUID. Allows printing the UUID
 * through the Printable interface (Serial and co.). See isValid for the
 * currently supported UUID types.
 */
class UUID : public Printable {
 public:
  /**
   * Create a new UUID
   */
  UUID();

  /**
   * Construct the UUID from the given string
   */
  UUID(const char* uuid);

  /**
   * Construct the UUID from the given string
   */
  UUID(const String& uuid);

  /**
   * Construct the UUID from the given JsonVariantConst as a string
   */
  UUID(const JsonVariantConst& uuid);

  virtual ~UUID() = default;

  bool operator<(const UUID& rhs) const;
  bool operator>(const UUID& rhs) const;
  bool operator<=(const UUID& rhs) const;
  bool operator>=(const UUID& rhs) const;

  bool operator==(const UUID& rhs) const;
  bool operator!=(const UUID& rhs) const;

  /**
   * Prints the UUID with the printable interface
   *
   * \param p Object to print the UUID to
   * \return The number of bytes printed
   */
  size_t printTo(Print& p) const final;

  /**
   * Creates a string representation of the UUID
   */
  String toString() const;

  /**
   * Tries to change to the UUID string provided
   *
   * \see isValid() for the validity constraints
   *
   * \param uuid The UUID in string form (Hex 8-4-4-4-12)
   * \return True if it is a valid UUID string
   */
  bool fromString(const char* uuid);

  /**
   * Tries to change to the UUID string provided
   *
   * \see fromString(const char*)
   *
   * \param uuid The UUID in string form (Hex 8-4-4-4-12)
   * \return True if it is a valid UUID string
   */
  bool fromString(const String& uuid);

  /**
   * Clears the UUID and makes it invalid
   */
  void clear();

  /**
   * Checks if the UUID is valid (currently only V4)
   *
   * \return True if it is valid
   */
  bool isValid() const;

 private:
  /// The internal binary buffer holding the UUID
  std::array<uint8_t, 16> buffer_;
};

}  // namespace utils
