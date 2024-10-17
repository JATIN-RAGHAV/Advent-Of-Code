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

HEAD = { 0, 0 }
TAIL = { 0, 0 }

function AreTouching()
	local XDist = HEAD[1] - TAIL[1]
	local touchingInX = XDist <= 1 and XDist >= -1
	local YDist = HEAD[2] - TAIL[2]
	local touchingInY = YDist <= 1 and YDist >= -1
	return touchingInX and touchingInY
end

function Move(move)
	for _ = 1, move[2] do
		if move[1] == "R" then
			HEAD[1] = HEAD[1] + 1
		elseif move[1] == "L" then
			HEAD[1] = HEAD[1] - 1
		elseif move[1] == "U" then
			HEAD[2] = HEAD[2] + 1
		else
			HEAD[2] = HEAD[2] - 1
		end
		if not AreTouching() then
			local sameX = HEAD[1] == TAIL[1]
			local sameY = HEAD[2] == TAIL[2]
			if sameX or sameY then
				if sameX then
					TAIL[2] = TAIL[2] + math.floor((HEAD[2] - TAIL[2]) / 2)
				else
					TAIL[1] = TAIL[1] + math.floor((HEAD[1] - TAIL[1]) / 2)
				end
			else
				TAIL[1] = TAIL[1] + (((HEAD[1] - TAIL[1]) > 0) and 1 or -1)
				TAIL[2] = TAIL[2] + (((HEAD[2] - TAIL[2]) > 0) and 1 or -1)
			end
			if not Visited[TAIL[1] .. "," .. TAIL[2]] then
				Count = Count + 1
				Visited[TAIL[1] .. "," .. TAIL[2]] = true
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

-- 6495
-- 6494
