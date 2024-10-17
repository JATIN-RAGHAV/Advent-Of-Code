File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()

Values = {}
X = 1

for i in string.gmatch(Data, "[^\n]+") do
	local valueString = string.sub(i, 6)
	local valueN = #valueString == 0 and 0 or tonumber(valueString)
	local cycleCount = string.sub(i, 1, 1) == "a" and 2 or 1
	if cycleCount == 1 then
		table.insert(Values, X)
		X = X + valueN
	else
		table.insert(Values, X)
		table.insert(Values, X)
		X = X + valueN
	end
end
Screen = { {}, {}, {}, {}, {}, {} }

for i = 0, #Values - 1 do
	local row = math.floor((i - 1) / 40)
	if i - (row * 40) >= Values[i + 1] - 1 and i - (row * 40) <= Values[i + 1] + 1 then
		io.write("#")
	else
		io.write(".")
	end
	if i % 40 == 0 then
		io.write("\n")
	end
end
