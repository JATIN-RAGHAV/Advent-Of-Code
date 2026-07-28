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
local syms = {}
for sym in string.gmatch(data[#data],"([+*])") do
        table.insert(syms,sym)
end
local sizes = {}
for spaces in string.gmatch(data[#data],"([+*]%s*)") do
        table.insert(sizes,spaces:len()-1)
end
sizes[#sizes] = sizes[#sizes]+1

for l = 1, #data-1  do
        table.insert(final_data,{})
        local curr = 1
        local i = 1
        while curr <= #sizes do
                table.insert(final_data[#final_data],data[l]:sub(i,i+sizes[curr]))
                i = i + sizes[curr] + 1
                curr = curr + 1
        end
end

local res = 0
for i = 1,#syms do
        local curr
        if syms[i] == '+' then
                curr = 0
        else
                curr = 1
        end
        while sizes[i] > 0 do
                local num=0
                local present = false
                for j = 1,#final_data do
                        if final_data[j][i]:sub(1,1) ~= " " then
                                num = (num*10) + tonumber(final_data[j][i]:sub(1,1))
                                present = true
                        end
                        final_data[j][i] = final_data[j][i]:sub(2)
                end
                if syms[i] == '+' then
                        curr = curr + num
                elseif (num > 0) or present then
                        curr = curr * num
                end
                sizes[i] = sizes[i]-1
        end
        res = res + curr
end

print("Answer is",res)
