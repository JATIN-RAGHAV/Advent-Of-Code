local File = io.open("text.txt", "r")
Data = File:read("*a")

local FindCommon = function(line)
	for i = (#line / 2) + 1, #line do
		local charIndex = string.find(string.sub(line, 1, #line / 2), string.sub(line, i, i))
		if charIndex then
			return string.sub(line, charIndex, charIndex)
		end
	end
end

Total = 0
for line in string.gmatch(Data, "[^\n]+") do
	local commonChar = FindCommon(line)
	local charCode = string.byte(commonChar)
	if charCode <= 90 then
		Total = Total + charCode - 38
	else
		Total = Total + charCode - 96
	end
end

print(Total)
