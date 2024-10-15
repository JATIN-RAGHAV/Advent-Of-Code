File = io.open("text.txt", "r")
Data = File:read("*a")
WinScore = { ["X"] = 0, ["Y"] = 3, ["Z"] = 6 }

IfWin = { ["A"] = 2, ["B"] = 3, ["C"] = 1 }
IfLoose = { ["A"] = 3, ["B"] = 1, ["C"] = 2 }
IfTie = { ["A"] = 1, ["B"] = 2, ["C"] = 3 }

FindValue = function(line)
	local score = 0
	local first = string.sub(line, 1, 1)
	local second = string.sub(line, 3, 3)
	score = WinScore[second]
	if second == "X" then
		score = score + IfLoose[first]
	elseif second == "Y" then
		score = score + IfTie[first]
	else
		score = score + IfWin[first]
	end
	return score
end

Total = 0

for line in string.gmatch(Data, "[^\n]+") do
	Total = Total + FindValue(line)
end

print(Total)
io.close(File)
