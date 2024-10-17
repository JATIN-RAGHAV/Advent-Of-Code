File = io.open("text.txt", "r")

Data = File:read("*a")

File:close()

FormattedData = {}

for i in string.gmatch(Data, "[^\n]+") do
	local direction = string.sub(i, 1, 1)
	local count = tonumber(string.sub(i, 3))
	local move = { direction, count }
	table.insert(FormattedData, move)
end

Rope = {}
for _ = 1, 10 do
	table.insert(Rope, { 0, 0 })
end

function AreTouching(i, j)
	local XDist = Rope[i][1] - Rope[j][1]
	local touchingInX = XDist <= 1 and XDist >= -1
	local YDist = Rope[i][2] - Rope[j][2]
	local touchingInY = YDist <= 1 and YDist >= -1
	return touchingInX and touchingInY
end

function Move(move)
	for _ = 1, move[2] do
		if move[1] == "R" then
			Rope[1][1] = Rope[1][1] + 1
		elseif move[1] == "L" then
			Rope[1][1] = Rope[1][1] - 1
		elseif move[1] == "U" then
			Rope[1][2] = Rope[1][2] + 1
		else
			Rope[1][2] = Rope[1][2] - 1
		end
		for i = 2, 10 do
			if not AreTouching(i - 1, i) then
				local sameX = Rope[i - 1][1] == Rope[i][1]
				local sameY = Rope[i - 1][2] == Rope[i][2]
				if sameX or sameY then
					if sameX then
						Rope[i][2] = Rope[i][2] + math.floor((Rope[i - 1][2] - Rope[i][2]) / 2)
					else
						Rope[i][1] = Rope[i][1] + math.floor((Rope[i - 1][1] - Rope[i][1]) / 2)
					end
				else
					Rope[i][1] = Rope[i][1] + (((Rope[i - 1][1] - Rope[i][1]) > 0) and 1 or -1)
					Rope[i][2] = Rope[i][2] + (((Rope[i - 1][2] - Rope[i][2]) > 0) and 1 or -1)
				end
				if not Visited[Rope[10][1] .. "," .. Rope[10][2]] then
					Count = Count + 1
					Visited[Rope[10][1] .. "," .. Rope[10][2]] = true
				end
			end
		end
	end
end

Visited = { ["0,0"] = true }
Count = 1

for i = 1, #FormattedData do
	Move(FormattedData[i])
end

print(Count)
