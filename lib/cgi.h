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
void HtmlHeader(std::string lang,std::string charset,std::string title,std::string head=""){
       std::cout << "Content-type: text/html\n\n";
       std::cout << "<!DOCTYPE html><html lang='"+lang+"'><head><meta charset='"+charset+"'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>"+title+"</title>"+head+"</head>";
}
/**
 * HtmlFooter 関数
 * </body>と</html>を挿入する関数
 * @param {string} footer: </body>と</html>の間に挿入するテキスト初期値は""
*/
void HtmlFooter(std::string footer=""){
    std::cout <<"</body>"+footer+"</html>" << std::endl;
}
/**
 * v 関数
 * @param {string} view: 挿入したいテキスト
 * std::coutを省略した関数
*/
void v(std::string view){
    if(view!=""){
        std::cout << view << std::endl;
    }
}

class CGI{
        std::string sessionId_;
        public:
        CGI(){
            GenerateSessionId();
        }

        std::map<std::string, std::string> parseQueryString() {
            std::map<std::string, std::string> data;
            std::string query_string = getenv("QUERY_STRING");
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
        /**
         * parse_　メゾット
         * @param {String} param: GETのパラメータを設定
         * @return { string　or int } : 第一引数に設定されたGETの値を取得 
        */
        std::map<std::string, std::string> parse_post_data() {
            std::string post_data;
            std::cin >> post_data;

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
         * POST_　メゾット
         * @param {String} param: GETのパラメータを設定
         * @return { string　or int } : 第一引数に設定されたGETの値を取得 
        */
        std::string POST_(std::string param){
            auto data_map = parse_post_data();
            auto it = data_map.find(param);
            return it->second; // パラメータに該当する値を返す   
        }
        /**
         * GET_　メゾット
         * @param {String} param: GETのパラメータを設定
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
         * REQUEST_　メゾット
         * @param {String} param: GETまたはPOSTのパラメータを設定
         * @return { string　or int } : 第一引数に設定されたGETまたはPOSTの値を取得 
        */
        std::string REQUEST_(std::string param){
            const char* method = std::getenv("REQUEST_METHOD");
            std::string value;
            if (method != nullptr) { // 環境変数が設定されているか確認
                std::string requestMethod(method);

                if (requestMethod == "GET") {
                value = this->GET_(param);
                } else if (requestMethod == "POST") {
                value = this->POST_(param);
                }
            }
            return value;
        }
        /**
         * GenerateSessionId メゾット
         * sessionId_にセッションIDの乱数を生成代入（CGIクラスのインスタンスで初期化実行）
        */
        void GenerateSessionId() {
            srand(time(0));
            sessionId_ = std::to_string(rand());
        }
        /**
         * SESSION_ID　メゾット
         * @return { string } id: セッションIDを発行
        */
        std::string SESSION_ID(){
            std::string id;
            if(sessionId_!=""){
                id = sessionId_;
            }else{
                id = "";
            }
            return id;
        }
};