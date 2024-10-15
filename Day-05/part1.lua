File = io.open("text.txt", "r")
Data = File:read("*a")
File:close()
StackString = {}
MovesString = {}
local isStep = false
StackCount = 0
MoveCount = 0
for i in string.gmatch(Data, "[^\n\n]+") do
	if isStep then
		MoveCount = MoveCount + 1
		table.insert(MovesString, i)
	else
		table.insert(StackString, i)
	end
	if string.sub(i, 2, 2) == "1" then
		isStep = true
		StackCount = tonumber(string.sub(i, -2, -2))
	end
end

Stack = {}
for _ = 1, StackCount do
	table.insert(Stack, {})
end
Moves = {}
for _ = 1, MoveCount do
	table.insert(Moves, {})
end
for i = 1, #StackString - 1 do
	for j = 0, StackCount - 1 do
		local element = string.sub(StackString[i], (j * 4) + 2, (j * 4) + 2)
		if element ~= " " then
			table.insert(Stack[j + 1], 1, element)
		end
	end
end
for i = 1, #MovesString do
	for j in string.gmatch(MovesString[i], "[^ ]+") do
		if tonumber(j) ~= nil then
			table.insert(Moves[i], tonumber(j))
		end
	end
end
function PrintStack()
	for i = 1, StackCount do
		for j = 1, #Stack[i] do
			io.write(Stack[i][j])
		end
		io.write("\n")
		print("New Stack")
	end
end

--for i = 1, MoveCount do
--	io.write(Moves[i][1] .. " ")
--	io.write(Moves[i][2] .. " ")
--	io.write(Moves[i][3] .. " ")
--	io.write("\n")
--end
function MoveElement(from, to)
	local Element = Stack[from][#Stack[from]]
	Stack[from][#Stack[from]] = nil
	table.insert(Stack[to], Element)
end

function MakeAMove(moveIndex)
	local count = Moves[moveIndex][1]
	local from = Moves[moveIndex][2]
	local to = Moves[moveIndex][3]
	for _ = 1, count do
		MoveElement(from, to)
	end
end

for i = 1, MoveCount do
	MakeAMove(i)
end

FinalAns = ""
for i = 1, StackCount do
	FinalAns = FinalAns .. Stack[i][#Stack[i]]
end

print(FinalAns)
