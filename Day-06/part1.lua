
local file = io.open("./text.txt","r")
local data = {}
if file then
        for line in file:lines() do
                table.insert(data,line)
        end
else
        print("Can't read file")
end

local final_data = {}
for l = 1, #data  do
        table.insert(final_data,{})
        if l < #data then
                for num in string.gmatch(data[l],"(%d*)") do
                        table.insert(final_data[#final_data],tonumber(num))
                end
        else
                for sym in string.gmatch(data[l],"([+*])") do
                        table.insert(final_data[#final_data],sym)
                end
        end
end
local res = 0
for col = 1, #final_data[1] do
        local curr = final_data[1][col]
        for i = 2,#final_data -1 do
                if final_data[#final_data][col] == "+" then
                        curr = curr + final_data[i][col]
                else
                        curr = curr * final_data[i][col]
                end
        end
        res = res + curr
end

print("answer",res)
