f = open('text.txt','r')

text = f.read().strip().split('\n')

def fuleFinder(num):
    ans = (num//3)-2
    return ans

def finalFuleFinder(string):
    num = int(string)
    fuel = 0;
    x = fuleFinder(num)
    while(x > 0):
        fuel += x
        x = fuleFinder(x)
    return fuel

convertedAns = [finalFuleFinder(x) for x in text]

finalAns = sum(convertedAns)

print(finalAns)
