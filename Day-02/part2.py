f = open('./text.txt','r')

target = 19690720

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

noun = 0
verb = 0

def goForIt(instructions):
    for i in range(0,100):
        for j in range(0,100):
            instructionsCopy = [x for x in instructions]
            instructionsCopy[1] = i
            instructionsCopy[2] = j
            outInstructions = computer(instructionsCopy)
            if outInstructions[0] == target:
                noun = outInstructions[1]
                verb = outInstructions[2]
                return noun*100 + verb


print(goForIt(instructions))
