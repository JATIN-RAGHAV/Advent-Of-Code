// url - https://adventofcode.com/[year]/day/[date]/input
#include "string"
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <fstream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
	size_t total_size = size * nmemb;
	output->append((char*)contents, total_size);
	return output->size();
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

	std::string response;

	curl_easy_setopt(curl, CURLOPT_URL, url_stream.str().c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

	std::cout << url_stream.str() << '\n';
	CURLcode res = curl_easy_perform(curl);
	if(res == CURLE_OK){
		std::cout << response;
	}
	else{
		std::cerr << "Couln't get input";
	}
	return response;
}
