#include "lib/cgi.h"
#include<iostream>
#include<string>
int main() {
    // コンテンツタイプのヘッダを出力
    std::cout << "Content-type: text/html\n\n";

    // GETデータを取得してパース
    auto get_data = parseQueryString();

    // 取得したデータをHTML形式で出力
    std::cout << "<html><body>";
    std::cout << "<h1>GET Data</h1>";
    for (auto& pair : get_data) {
        std::cout << "<p>" << pair.first << " = " << pair.second << "</p>";
    }
    std::cout << "</body></html>";

    return 0;
}