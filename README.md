##lua-cityhash##

[![Build Status](https://travis-ci.org/csfrancis/lua-cityhash.png?branch=master)](https://travis-ci.org/csfrancis/lua-cityhash)

A [cityhash](https://code.google.com/p/cityhash/) module for Lua.

### Installation ###

```
luarocks install lua-cityhash
```

### Dependencies ###

- Lua >= 5.1 | Luajit >= 2.0.0

### Usage ###

The module exposes the 64-bit and 128-bit cityhash APIs.

```lua
cityhash = require("cityhash")

data = "this is data to hash"
hash = cityhash.hash128(data, data:len())
```

### Methods ###

#### hash64 ####
`syntax: cityhash.hash64(data, data_len, hex?, seed?)`

Calls `CityHash64WithSeed` on the provided data. It takes the following arguments:

- `data` Data to hash
- `data_len` Length of data
- `hex` Optional boolean value that determines if the output string should be converted to hex (default: false)
- `seed` Optional seed value (default: 0)

#### hash128 ####
`syntax: cityhash.hash128(data, data_len, hex?, seed_low?, seed_high?)`

Calls `CityHash128WithSeed` on the provided data. It takes the following arguments:

- `data` Data to hash
- `data_len` Length of data
- `hex` Optional boolean value that determines if the output string should be converted to hex (default: false)
- `seed_low` Optional 64-bit low seed (default: 0)
- `seed_high` Optional 64-bit high seed (default: 0)

### Development ###

Tests can be run using [busted](http://olivinelabs.com/busted):

```
sudo luarocks install busted
busted test/city_hash_test.lua
```
