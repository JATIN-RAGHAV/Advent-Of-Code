require 'set'
data = File.read("./text.txt")
data = data.strip
data = data.split("\n")
splitters = []
for i in 0...data.length
  splitters.push(Set.new([]))
  for j in 0...data[i].length
    if data[i][j] == "^"
      splitters[i] << j
    end
  end
end
beams = {}
for i in 0...data[0].length
  if data[0][i] == "S"
    beams[i] = 1
    break
  end
end

res = 1
for i in 0...splitters.length
  if splitters[i].size > 0 
    del = {}
    beams.each do |key,value| 
      if splitters[i].include?(key)
        res += value
        del[key] = value
      end
    end
    del.each do |key,value|
      beams.delete(key)
      if beams.key?(key+1)
        beams[key+1]+=value
      else
        beams[key+1] = value
      end
      if beams.key?(key-1)
        beams[key-1]+=value
      else
        beams[key-1] = value
      end
    end
  end
end

puts "Answer is #{res}"
