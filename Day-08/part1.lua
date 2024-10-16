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
function PrintData()
	for i = 1, #FormattedData do
		for j = 1, #FormattedData[i] do
			io.write(FormattedData[i][j] .. ",")
		end
		io.write("\n")
	end
end

VisibleTrees = (#FormattedData * 2) + (#FormattedData[1] * 2) - 4
print(VisibleTrees)
TreesAdded = {}
-- Checking rows from left to right
for i = 2, #FormattedData - 1 do
	local currentMax = FormattedData[i][1]
	for j = 2, #FormattedData[i] - 1 do
		if FormattedData[i][j] > currentMax then
			currentMax = FormattedData[i][j]
			VisibleTrees = VisibleTrees + 1
			TreesAdded[i .. "," .. j] = true
		end
		if currentMax == 9 then
			break
		end
	end
end
-- Check the rows from right to left
for i = 2, #FormattedData - 1 do
	local currentMax = FormattedData[i][#FormattedData[i]]
	for j = #FormattedData[i] - 1, 2, -1 do
		if FormattedData[i][j] > currentMax then
			currentMax = FormattedData[i][j]
			if not TreesAdded[i .. "," .. j] then
				VisibleTrees = VisibleTrees + 1
				TreesAdded[i .. "," .. j] = true
			end
		end
		if currentMax == 9 then
			break
		end
	end
end
-- Checking the columns from top to bottom
for i = 2, #FormattedData[1] - 1 do
	local currentMax = FormattedData[1][i]
	for j = 2, #FormattedData - 1 do
		if FormattedData[j][i] > currentMax then
			currentMax = FormattedData[j][i]
			if not TreesAdded[j .. "," .. i] then
				VisibleTrees = VisibleTrees + 1
				TreesAdded[j .. "," .. i] = true
			end
		end
		if currentMax == 9 then
			break
		end
	end
end

-- Checking the columns from bottom to top
for i = 2, #FormattedData[1] - 1 do
	local currentMax = FormattedData[#FormattedData][i]
	for j = #FormattedData - 1, 2, -1 do
		if FormattedData[j][i] > currentMax then
			currentMax = FormattedData[j][i]
			if not TreesAdded[j .. "," .. i] then
				VisibleTrees = VisibleTrees + 1
				TreesAdded[j .. "," .. i] = true
			end
		end
		if currentMax == 9 then
			break
		end
	end
end
local treeLength = 0
for _, values in pairs(TreesAdded) do
	treeLength = treeLength + 1
end
print(treeLength)
print(VisibleTrees)
