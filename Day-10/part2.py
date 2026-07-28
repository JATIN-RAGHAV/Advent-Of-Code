file = open("./text.txt",'r')
strig = file.read()
strig = '''[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}'''
strig = '''[.#.] (0) (2) (1,0) {100,2,3}'''
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
    buttons.sort(key = lambda button: len(button),reverse=True)
    curr.append(buttons)
    joltage = list(map(lambda s: int(s),parts[-1][1:-1].split(',')))
    curr.append(joltage)
    final_data.append(curr)

# Finding answer

def is_pressable(button:list[int], target:list[int], joltage:list[int])->bool:
    for b in button:
        if joltage[b] + 1 > target[b]:
            return False
    return True

def press(button:list[int], joltage:list[int]):
    for b in button:
        joltage[b] += 1

def unpress(button:list[int], joltage:list[int]):
    for b in button:
        joltage[b] -= 1
best = int(1e9)
def back_track(joltage:list[int], buttons:list[list[int]],target:list[int], depth:int):
    global best
    if joltage == target:
        best = min(best,depth)
    for button in buttons:
        if depth+1 < best:
            if is_pressable(button,target,joltage):
                press(button,joltage)
                back_track(joltage,buttons,target,depth+1)
                unpress(button,joltage)

res = 0
i = 1
for record in final_data:
    print("Record no.:",i)
    joltage = [0]*len(record[0])
    cur = back_track(joltage,record[1],record[2],0)
    i+=1
    res += cur
print("answer is:",res)
