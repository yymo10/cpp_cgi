#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <sstream>
#include <ctime>
/**
 * HtmlHead 関数
 * @param {string} lang HTML文書の言語を指定する文字列です。例えば、"en"や"ja"など。
 * @param {string} charset 文書で使用される文字セットを指定します。例えば、"UTF-8"。
 * @param {string} title HTML文書のタイトルを指定する文字列です。
 * @param {string} head そのほか追加したいheadの内容を記載
 */
void HtmlHead(std::string lang,std::string charset,std::string title,std::string head=""){
       std::cout << "Content-type: text/html\n\n";
       std::cout << "<!DOCTYPE html><html lang="+lang+"><head><meta charset="+charset+"><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>"+title+"</title>"+head+"</head>";
}

void v(std::string view){
    if(view!=""){
        std::cout << view << std::endl;
    }
}

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
std::map<std::string, std::string> parse_post_data() {
    std::string post_data;
    std::cin >> post_data; // POSTデータを標準入力から読み取る

    std::map<std::string, std::string> data_map;
    std::istringstream data_stream(post_data);
    std::string pair;

    while (std::getline(data_stream, pair, '&')) {
        auto delimiter_pos = pair.find('=');
        if (delimiter_pos != std::string::npos) {
            std::string key = pair.substr(0, delimiter_pos);
            std::string value = pair.substr(delimiter_pos + 1);
            data_map[key] = value;
        }
    }

    return data_map;
}

/**
 * POST_　関数
 * @param {String} : GETのパラメータを設定
 * @return { string　or int } : 第一引数に設定されたGETの値を取得 
*/
std::string POST_(std::string param){
    auto data_map = parse_post_data();
    auto it = data_map.find(param);
    return it->second; // パラメータに該当する値を返す   
}
/**
 * GET_　関数
 * @param {String} : GETのパラメータを設定
 * @return { string　or int } : 第一引数に設定されたGETの値を取得 
*/
std::string GET_(std::string param){

    auto get_data = parseQueryString();
    std::string _value;
    for (auto& pair : get_data) {
        if(param == pair.first){
            _value=pair.second;
        }else{
            _value="";
        }
    }
    return _value;
}

/**
 * REQUEST_　関数
 * @param {String} : GETまたはPOSTのパラメータを設定
 * @return { string　or int } : 第一引数に設定されたGETまたはPOSTの値を取得 
*/
std::string REQUEST_(std::string param){
    const char* method = std::getenv("REQUEST_METHOD");
    std::string value;
    if (method != nullptr) { // 環境変数が設定されているか確認
        std::string requestMethod(method);

        if (requestMethod == "GET") {
            // GETリクエストの場合の処理
         value = GET_(param);
        } else if (requestMethod == "POST") {
            // POSTリクエストの場合の処理
         value = POST_(param);
        }
    }
    return value;
}

std::string GenerateSessionId() {
    // 乱数を使ってセッションIDを生成（例として簡単な実装）
    srand(time(0));
    std::string sessionId = std::to_string(rand());
    return sessionId;
}