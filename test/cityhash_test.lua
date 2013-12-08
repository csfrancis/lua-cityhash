require("luarocks.loader")

describe("cityhash tests", function()
  local cityhash

  setup(function()
    cityhash = require("cityhash")
    data = "this is a test hash string"
  end)

  it("hash64 should return a hex string", function()
    str = cityhash.hash64(data, data:len(), true)
    assert.is_nil(str:find("[^0-9a-f]"))
    assert.are.equal(16, str:len())
  end)

  it("hash64 should return different values with seed", function()
    str = cityhash.hash64(data, data:len(), true)
    str2 = cityhash.hash64(data, data:len(), true, 123456)
    assert.are_not.equal(str, str2)
  end)

  it("hash64 should return a binary data", function()
    str = cityhash.hash64(data, data:len())
    assert(str:find("[^0-9a-f]"))
    assert.are.equal(8, str:len())
  end)

  it("hash128 should return a hex string", function()
    str = cityhash.hash128(data, data:len(), true)
    assert.is_nil(str:find("[^0-9a-f]"))
    assert.are.equal(32, str:len())
  end)

  it("hash128 should return different values with seed", function()
    str = cityhash.hash128(data, data:len(), true)
    str2 = cityhash.hash128(data, data:len(), true, 123456)
    assert.are_not.equal(str, str2)
    str3 = cityhash.hash128(data, data:len(), true, 123456, 78910)
    assert.are_not.equal(str2, str3)
  end)

  it("hash128 should return a binary data", function()
    str = cityhash.hash128(data, data:len())
    assert(str:find("[^0-9a-f]"))
    assert.are.equal(16, str:len())
  end)
end)
