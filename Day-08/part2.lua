File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()

FormattedData = {}

for i in string.gmatch(Data, "[^\n]+") do
	local row = {}
	for j = 1, #i do
		table.insert(row, tonumber(string.sub(i, j, j)))
	end
	table.insert(FormattedData, row)
end

function FindTreeScore(i, j)
	local height = FormattedData[i][j]
	local left = 0
	for column = j - 1, 1, -1 do
		if FormattedData[i][column] < height then
			left = left + 1
		elseif FormattedData[i][column] >= height then
			left = left + 1
			break
		end
	end
	local right = 0
	for column = j + 1, #FormattedData[1] do
		if FormattedData[i][column] < height then
			right = right + 1
		elseif FormattedData[i][column] >= height then
			right = right + 1
			break
		end
	end

	local top = 0
	for row = i - 1, 1, -1 do
		if FormattedData[row][j] < height then
			top = top + 1
		elseif FormattedData[row][j] >= height then
			top = top + 1
			break
		end
	end

	local bottom = 0
	for row = i + 1, #FormattedData do
		if FormattedData[row][j] < height then
			bottom = bottom + 1
		elseif FormattedData[row][j] >= height then
			bottom = bottom + 1
			break
		end
	end
	return left * right * top * bottom
end

MaxScore = 0

for i = 2, #FormattedData - 1 do
	for j = 2, #FormattedData[1] - 1 do
		local score = FindTreeScore(i, j)
		if score > MaxScore then
			MaxScore = score
		end
	end
end

print(MaxScore)
