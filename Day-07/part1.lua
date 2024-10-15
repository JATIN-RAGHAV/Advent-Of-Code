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

-- Function to print the table in a tree-like structure
local function printTable(tbl, indent)
	indent = indent or "" -- Default indent to an empty string if not provided
	for key, value in pairs(tbl) do
		-- Print the current key
		print(indent .. tostring(key) .. ":")
		if type(value) == "table" and next(value) then
			-- If the value is a non-empty table, call the function recursively
			printTable(value, indent .. "    |") -- Increase the indentation
		elseif type(value) == "table" then
			-- If the value is an empty table, indicate that it's empty
			print(indent .. "  (empty)")
		else
			-- Otherwise, print the value
			print(indent .. "  " .. tostring(value))
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
	if currentSize <= 100000 then
		table.insert(RequiredSizes, currentSize)
	end
	return currentSize
end

FindRequiredDirectories(DirectoryTree)
FinalAns = 0
for i = 1, #RequiredSizes do
	print(RequiredSizes[i])
	FinalAns = FinalAns + RequiredSizes[i]
end

print("The ans is: " .. FinalAns)
