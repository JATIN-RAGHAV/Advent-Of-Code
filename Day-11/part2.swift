import Foundation
var data = ""
let path = URL(fileURLWithPath:"./text.txt")
do {
    data = try String(contentsOf:path,encoding: .utf8)
}
// data = """
// svr: aaa bbb
// aaa: fft
// fft: ccc
// bbb: tty
// tty: ccc
// ccc: ddd eee
// ddd: hub
// hub: fff
// eee: dac
// dac: fff
// fff: ggg hhh
// ggg: out
// hhh: out
// """

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

func dfs(s: String,dac: Bool,fft: Bool) -> Int{
    if dac && fft && values.keys.contains(s){
        return values[s, default:0]
    }
    if s == "out"{
        if dac && fft{
            return 1
        }
        else{
            return 0
        }
    }
    var ldac = dac
    var lfft = fft
    if s == "dac"{
        ldac = true
    }
    if s == "fft"{
        lfft = true
    }
    var res = 0
    for ss in adj[s,default: []]{
        res += dfs(s: ss,dac : ldac, fft : lfft)
    }
    if ldac && lfft {
        values[s] = res
    }
    if ldac{
        print(1)
    }
    if lfft{
        print(2)
    }
    return res
}
var res = dfs(s: "svr",dac: false, fft: false)
print(values)
print(res)
