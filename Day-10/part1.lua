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
	if X > 39 then
		print(X)
		print("X is bigger than screen")
	end
end

FinalAns = 0

for i = 20, 220, 40 do
	local currentValue = i * Values[i]
	FinalAns = FinalAns + currentValue
end

print(FinalAns)
