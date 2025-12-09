const std = @import("std");
const allocator = std.heap.page_allocator;

const point = struct {
    x:i64,
    y:i64
};

pub fn main() !void {
    const file = try std.fs.cwd().openFile("./text.txt",.{});
    defer file.close();
    const stats =try  file.stat();

    const un_trimmed_data:[]u8 = try file.readToEndAlloc(allocator,stats.size);
    defer allocator.free(un_trimmed_data);
    const data_immutable = std.mem.trim(u8,un_trimmed_data," \t\n\r");
    const data = try allocator.alloc(u8, data_immutable.len);
    defer allocator.free(data);

    std.mem.copyForwards(u8,data,data_immutable);

    var points:[1000]point = undefined;
    var pcnt:usize = 0;

    var iterator = std.mem.splitScalar(u8,data,'\n');
    while (iterator.next()) |row|{
        var i_num = std.mem.splitScalar(u8,row,',');
        if (i_num.next()) |x|{
            points[pcnt].x =try std.fmt.parseInt(i32, x, 10);
        }
        if (i_num.next()) |y|{
            points[pcnt].y =try std.fmt.parseInt(i32, y, 10);
        }
        pcnt += 1;
    }

    var max:u64 = 0;
    for (0..pcnt) |i|{
        for (0..pcnt) |j|{
            const area = @abs(points[i].x - points[j].x + 1) * @abs(points[i].y - points[j].y + 1);
            if (area>max){
                max = area;
            }
        }
    }

    std.debug.print("Answer: {d}\n",.{max});
}
