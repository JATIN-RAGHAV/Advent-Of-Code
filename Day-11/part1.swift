import Foundation
var data = ""
let path = URL(fileURLWithPath:"./text.txt")
do {
    data = try String(contentsOf:path,encoding: .utf8)
}

data = data.trimmingCharacters(in: .whitespacesAndNewlines)
let lines = data.split(separator: "\n")

var adj:[String:[String]] = [:]
var values:[String:Int] = [:]

for line in lines{
    let conn = line.split(separator: ":")
    let key = String(conn[0])
    var outs = String(conn[1])
    outs = outs.trimmingCharacters(in: .whitespacesAndNewlines)
    let outsl = outs.split(separator: " ")
    for s in outsl{
        adj[key,default:[]].append(String(s))
    }
}

func dfs(s: String) -> Int{
    if values.keys.contains(s) {
        return values[s,default: 0]
    }
    if s == "out" {
        return 1
    }
    var res = 0
    for ss in adj[s,default: []]{
        res += dfs(s: ss)
    }
    values[s] = res
    return res
}

var res = dfs(s: "you")
print(res)
