File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()

function PrintCurrentDirectory()
	for i = 1, #CurrentDirectory do
		if CurrentDirectory[i] == "/" then
			io.write("~" .. "/")
		else
			io.write(CurrentDirectory[i] .. "/")
		end
	end
	io.write("\n")
end

function GetCurrentLocation()
	local currentLocation = DirectoryTree
	for j = 1, #CurrentDirectory do
		currentLocation = currentLocation[CurrentDirectory[j]]
	end
	return currentLocation
end

CurrentDirectory = {}
DirectoryTree = {}
for i in string.gmatch(Data, "[^\n]+") do
	if string.sub(i, 1, 4) == "$ cd" then
		--print(i)
		--		PrintCurrentDirectory()
		if string.sub(i, 6) == ".." then
			CurrentDirectory[#CurrentDirectory] = nil
		else
			local newDirectory = string.sub(i, 6)
			local currentLocation = GetCurrentLocation()
			currentLocation[newDirectory] = {}
			table.insert(CurrentDirectory, newDirectory)
		end
	elseif tonumber(string.sub(i, 1, 1)) ~= nil then
		local size
		for j in string.gmatch(i, "[^ ]+") do
			size = tonumber(j)
			break
		end
		local currentLocation = GetCurrentLocation()
		if currentLocation["size"] == nil then
			currentLocation["size"] = size
		else
			currentLocation["size"] = currentLocation["size"] + size
		end
	end
end
function IsEmpty(table)
	for key, _ in pairs(table) do
		return false
	end
	return true
end
Spaces = 0
function PrintTree(tree)
	if IsEmpty(tree) then
		Spaces = Spaces - 1
	else
		Spaces = Spaces + 1
		for key, value in pairs(tree) do
			io.write(string.rep("    |", Spaces))
			io.write(key .. "/")
			io.write("\n")
			PrintTree(value)
		end
	end
end

RequiredSizes = {}
function FindRequiredDirectories(tbl)
	local currentSize = 0
	for key, value in pairs(tbl) do
		if key == "size" then
			currentSize = currentSize + value
		else
			currentSize = currentSize + FindRequiredDirectories(value)
		end
	end
	table.insert(RequiredSizes, currentSize)
	return currentSize
end

FindRequiredDirectories(DirectoryTree)
FinalAns = 0
TotalUsedSpace = 0
for i = 1, #RequiredSizes do
	if RequiredSizes[i] > TotalUsedSpace then
		TotalUsedSpace = RequiredSizes[i]
	end
end
SizeFree = 70000000 - TotalUsedSpace
SizeToFree = 30000000 - SizeFree

SizeOfDirectoryToFree = TotalUsedSpace
for i = 1, #RequiredSizes do
	local currentSize = RequiredSizes[i]
	if currentSize > SizeToFree and currentSize < SizeOfDirectoryToFree then
		SizeOfDirectoryToFree = currentSize
	end
end

print(SizeOfDirectoryToFree)
