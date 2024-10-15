File = io.open("text.txt", "r")
local data = File:read("*a")

Equal = { ["A"] = "X", ["B"] = "Y", ["C"] = "Z" }
Beat = { ["X"] = "C", ["Y"] = "A", ["Z"] = "B" }

local findValues = function(line)
	local score = 0
	local first = string.sub(line, 1, 1)
	local second = string.sub(line, 3, 3)
	if second == "X" then
		score = 1
	elseif second == "Y" then
		score = 2
	else
		score = 3
	end
	if Equal[first] == second then
		score = score + 3
	elseif Beat[second] == first then
		score = score + 6
	end
	return score
end

Total = 0

for line in string.gmatch(data, "[^\n]+") do
	Total = Total + findValues(line)
end

print(Total)
io.close(File)
