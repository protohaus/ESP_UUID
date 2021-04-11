[![MIT Licence](https://img.shields.io/github/license/protohaus/ESPRandom?style=flat-square "MIT Licence")](https://en.wikipedia.org/wiki/MIT_License)

# ESP UUID

A library to work with UUIDs.

It supports:
 - generating them
 - parsing them from
   - Strings
   - char arrays
   - ArduinoJson documents. 
 - being a key in std::map

Library is extracted from the [sdg-controller](https://github.com/protohaus/sdg-controller) firmware.

## Limitations

Currently only v4 is supported.