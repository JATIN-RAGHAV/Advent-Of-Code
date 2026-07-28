file = open("./text.txt",'r')
strig = file.read()
data = strig.strip().split('\n')
final_data:list[list] = []
"""

record-> [
    string: final light pattern,
    list[list[numbers]]: buttons,
    list[nums]: joltage
]

"""
for row in data:
    parts = row.split(' ')
    curr:list = []
    curr.append(parts[0][1:-1])
    buttons:list[list]=[]
    for i in range(1,len(parts)-1):
        button = list(map(lambda s: int(s),parts[i][1:-1].split(',')))
        buttons.append(button)
    curr.append(buttons)
    joltage = list(map(lambda s: int(s),parts[-1][1:-1].split(',')))
    curr.append(joltage)
    final_data.append(curr)

# Finding answer
res = 0

for record in final_data:
    mx = (1<<(len(record[1])))
    cbest = len(record[1])
    i = 0
    while i < mx:
        cnt = 0
        light = ['.']*len(record[0])
        for b in range(0,len(record[1])):
            if ((1<<b)&i):
                cnt+=1
                for x in record[1][b]:
                    if light[x] == '.':
                        light[x] = '#'
                    else:
                        light[x] = '.'
        if (''.join(light) == record[0]) and cnt<cbest:
            cbest = cnt
        i+=1
    res+=cbest

print("final answer is",res)
