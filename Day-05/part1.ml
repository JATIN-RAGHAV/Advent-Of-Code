let data = In_channel.with_open_text "./text.txt" In_channel.input_all;;

let data = String.trim data in
let splitted = String.split_on_char '\n' data in
