f = open('text.txt','r')

text = f.read().strip().split('\n')

def converter(string):
    num = int(string)
    ans = (num//3)-2
    return ans

convertedAns = [converter(x) for x in text]

finalAns = sum(convertedAns)

print(finalAns)
