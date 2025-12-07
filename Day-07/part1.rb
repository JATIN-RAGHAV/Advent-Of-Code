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
beams = Set.new([])
for i in 0...data[0].length
  if data[0][i] == "S"
    beams << i
    break
  end
end

res = 0

for i in 0...splitters.length
  if splitters[i].size > 0 
    del = Set.new([])
    beams.each do |beam|
      if splitters[i].include?(beam)
        del << beam
        res += 1
      end
    end
    del.each do |d|
      beams.delete(d)
    end
    del.each do |d|
      beams << d+1
      beams << d-1
    end
  end
end

puts "Answer is #{res}"
