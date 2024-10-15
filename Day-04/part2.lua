File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()

local isOverlap = function(line)
	local initialTable = {}
	for range in string.gmatch(line, "[^,]+") do
		table.insert(initialTable, range)
	end
	local firstRange = {}
	local secondRange = {}
	for range in string.gmatch(initialTable[1], "[^-]+") do
		table.insert(firstRange, tonumber(range))
	end
	for range in string.gmatch(initialTable[2], "[^-]+") do
		table.insert(secondRange, tonumber(range))
	end
	local isFirstInSecond = (firstRange[1] >= secondRange[1] and firstRange[1] <= secondRange[2])
		or (firstRange[2] <= secondRange[2] and firstRange[2] >= secondRange[1])
	local isSecondInFirst = (secondRange[1] >= firstRange[1] and secondRange[1] <= firstRange[2])
		or (secondRange[2] <= firstRange[2] and secondRange[2] >= firstRange[1])
	if isFirstInSecond or isSecondInFirst then
		return true
	end
	return false
end

Total = 0

for line in string.gmatch(Data, "[^\n]+") do
	if isOverlap(line) then
		Total = Total + 1
	end
end

print(Total)
