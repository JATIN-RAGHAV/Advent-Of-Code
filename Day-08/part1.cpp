#include "../get_input.cpp"
#include <string>
#include <vector>

std::string test{"2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2"};

int* get_metadata_sum(std::vector<int> vec);

int main(){
	std::string input = get_input(2018, 8);
	std::stringstream lines{input};
	std::string line;
	std::vector<int> nums;
	while(lines >> line)
		nums.push_back(std::stoi(line));

	int* result = get_metadata_sum(nums);
	printf("Meta data sum: %d\n",result[0]);
}

int* get_metadata_sum(std::vector<int> vec){
	int childnodes = vec[0];
	int metadata_count = vec[1];

	if(childnodes == 0){
		int* result= new int[2];
		int metadata = 0;
		for(int i = 0;i<metadata_count; i++)
			metadata += vec[2+i];
		result[1] = 2+metadata_count;
		result[0] = metadata;
		return result;
	}

	int node_offset = 2;
	int metadata = 0;
	for(int i = 0;i<childnodes;i++){
		std::vector<int> passed_down(vec.begin()+node_offset, vec.end());
		int* result = get_metadata_sum(passed_down);
		metadata += result[0];
		node_offset += result[1];
	delete[] result;
	}

	for(int i = 0; i<metadata_count;i++){
		metadata += vec[node_offset+i];
	}
	int* result = new int[2];
	result[0] = metadata;
	result[1] = node_offset + metadata_count;
	return result;
}
