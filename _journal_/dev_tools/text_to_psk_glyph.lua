local file = io.open("glyphs.txt", "r")
if not file then
    print("File not found")
    return
end

-- Could write these directly to font.c to make things simpler.
-- Just match default: and write the output above
for line in file:lines() do
    local char = line:match("%[(.+)%]")
    if char then
        print(string.format("case '%s':", char))
        print(string.format("  return (PSK_Glyph){{"))
    end

    if line:match("[.#]") then
        local bin = line:gsub("%.", "0"):gsub("#", "1")
        local byte = tonumber(bin, 2)
        if byte then
            print(string.format("      0x%02X,", byte))
        end
    end
end

print("}};")
file:close()
