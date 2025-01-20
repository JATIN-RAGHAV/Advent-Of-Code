f = open('./text.txt','r')

instructions = [int(x) for x in f.read().strip().split(',')]

def computer(instructions):
    i = 0;
    size = len(instructions)
    while instructions[i] != 99 :
        if(i==size-4):
            break;
        if instructions[i] == 1:
            instructions[instructions[i+3]] = instructions[instructions[i+1]] + instructions[instructions[i+2]]
        elif instructions[i] == 2:
            instructions[instructions[i+3]] = instructions[instructions[i+1]] * instructions[instructions[i+2]]
        i += 4
    return instructions

print(computer(instructions))
