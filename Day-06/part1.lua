File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()
function IsSimilar(s)
	local isFirstRepeated = string.find(string.sub(s, 2), string.sub(s, 1, 1))
	if isFirstRepeated then
		return true
	end
	local isSecondRepeated = string.find(string.sub(s, 3), string.sub(s, 2, 2))
	if isSecondRepeated then
		return true
	end
	local isThirdRepeated = string.sub(s, 3, 3) == string.sub(s, 4, 4)
	if isThirdRepeated then
		return true
	end
	return false
end

local testData1 = "bvwbjplbgvbhsrlpgdmjqwftvncz"
local testData2 = "nppdvjthqldpwncqszvftbrmjlhg"

for i = 1, #Data - 3 do
	if not IsSimilar(string.sub(Data, i, i + 3)) then
		print(i + 3)
		break
	end
end
