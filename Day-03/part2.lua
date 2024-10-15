local File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()

local FindCommonChars = function(str1, str2)
	local common = ""
	for i = 1, #str1 do
		local charIndex = string.find(str2, string.sub(str1, i, i))
		if charIndex then
			common = common .. string.sub(str2, charIndex, charIndex)
		end
	end
	return common
end

local FindCommon = function(group)
	local first, second, third
	local count = 1
	for line in string.gmatch(group, "[^\n]+") do
		if count == 1 then
			first = line
		elseif count == 2 then
			second = line
		else
			third = line
		end
		count = count + 1
	end
	local common = FindCommonChars(first, second)
	local commonChar = FindCommonChars(common, third)

	return commonChar
end

Total = 0
for group in string.gmatch(Data, "[^\n]+\n[^\n]+\n[^\n]+") do
	local commonChar = FindCommon(group)
	local charCode = string.byte(commonChar)
	if charCode <= 90 then
		Total = Total + charCode - 38
	else
		Total = Total + charCode - 96
	end
end

print(Total)
