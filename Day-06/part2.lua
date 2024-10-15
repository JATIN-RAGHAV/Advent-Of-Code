File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()
function IsSimilar(s)
	local length = #s
	for i = 1, length - 1 do
		local isRepeated = string.find(string.sub(s, i + 1), string.sub(s, i, i))
		if isRepeated then
			return true
		end
	end
	return false
end

local testData1 = "mjqjpqmgbljsphdztnvjfqwrcgsmlb"
local testData2 = "bvwbjplbgvbhsrlpgdmjqwftvncz"

for i = 1, #Data - 13 do
	if not IsSimilar(string.sub(Data, i, i + 13)) then
		print(i + 13)
		break
	end
end
