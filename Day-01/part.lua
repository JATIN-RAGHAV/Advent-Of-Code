local file = io.open("text.txt", "r")
if file then
	First = 0
	Second = 0
	Third = 0
	Current = 0
	for line in file:lines() do
		if line == "" then
			if Current > First then
				Third = Second
				Second = First
				First = Current
			elseif Current > Second then
				Third = Second
				Second = Current
			elseif Current > Third then
				Third = Current
			end
			Current = 0
		else
			Current = Current + tonumber(line)
		end
	end
end

print(First + Second + Third)
