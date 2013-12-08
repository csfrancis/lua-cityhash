package = "lua-cityhash"
version = "1.0-1"
source = {
  url = "https://github.com/csfrancis/lua-cityhash/archive/1.0.tar.gz"
}
description = {
  summary = "Lua cityhash module",
  homepage = "https://github.com/csfrancis/lua-cityhash",
  license = "MIT/X11",
  maintainer = "Scott Francis <scott.francis@shopify.com>"
}
dependencies = {
  "lua >= 5.1"
}

build = {
  type = "builtin",

  modules = {
    cityhash = {
      sources = { "src/city.cc", "src/cityhash.cc" },
      incdirs = { "src" }
    }
  }
}
