// url - https://adventofcode.com/[year]/day/[date]/input
#include "string"
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <fstream>

size_t write_call_back(void* contents, size_t size, size_t nmemb, std::string* output) {
	size_t total_size = size * nmemb;
	output->append((char*)contents, total_size);
	return total_size;
}

std::string get_input(int year, int date){
	std::stringstream url_stream;
	url_stream << "https://adventofcode.com/" << year << "/day/" << date << "/input";

	CURL* curl = curl_easy_init();

	struct curl_slist* header = nullptr;
	std::ifstream cookie(".cookie",std::ios::in);
	if(!cookie){
		std::cerr << "Couln't get cookie";
	}
	std::stringstream cookie_stream;
	std::string cookie_str;
	cookie >> cookie_str;
	cookie_stream << "cookie:session=" << cookie_str;
	header = curl_slist_append(header, cookie_stream.str().c_str());
	cookie.close();

	std::string response;
	response.reserve(4 * 1024 * 1024);

	curl_easy_setopt(curl, CURLOPT_URL, url_stream.str().c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_call_back);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

	CURLcode res = curl_easy_perform(curl);
	if(res == CURLE_OK){
		return response;
	}
	else{
		std::cout << response;
		std::cerr << "Couln't get input";
		exit(1);
	}
}
