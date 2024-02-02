#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

std::map<std::string, std::string> parseQueryString() {
    std::map<std::string, std::string> data;
    std::string query_string = getenv("QUERY_STRING"); // 環境変数からQUERY_STRINGを取得

    std::string key, value;
    size_t pos = 0;
    while ((pos = query_string.find('=')) != std::string::npos) {
        key = query_string.substr(0, pos);
        query_string.erase(0, pos + 1);
        pos = query_string.find('&');
        if (pos == std::string::npos) {
            value = query_string;
            query_string = "";
        } else {
            value = query_string.substr(0, pos);
            query_string.erase(0, pos + 1);
        }
        data[key] = value;
    }

    return data;
}