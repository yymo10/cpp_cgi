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
       std::cout << "<!DOCTYPE html><html lang="+lang+"><head><meta charset="+charset+"><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>"+title+"</title>"+head+"</head>";
}
/**
 * JsonHeader 関数
 * @param {string} charset : 文字セットを設定する（初期値はutf-8）
*/
void JsonHeader(std::string charset="utf-8"){
    std::cout << "Content-type: application/json;charset="<< charset <<"\n\n";
}

/**
 * HtmlFooter 関数
 * @return {void} :</body>と</html>を挿入する関数
*/
void HtmlFooter(){
    std::cout <<"</body></html>" << std::endl;
}
template<typename T>
void v(T view){
        std::cout << view << std::endl;
}

class CGI{
            std::string sessionId_;
            std::string emsg;
        public:
        int status;
        CGI(){
            try{
                GenerateSessionId();
                if(sessionId_==""){
                    throw std::runtime_error("Error: Session ID is not initialized.");
                }
                this->status=200;
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg = e.what();
                this->status=500;
            }
        }
        ~CGI(){
            try{
                GenerateSessionId();
                if(sessionId_==""){
                    throw std::runtime_error("Error: Session ID is not initialized.");
                }
                this->status=200;
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg = e.what();
                this->status=500;
            }
        }
        std::string error_msg(){
            std::string msg;
            try{
                msg = this->emsg;
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg = e.what();
                this->status=500;
            }
            return msg;
        }
        std::map<std::string, std::string> parseQueryString() {
            std::map<std::string, std::string> data;
            std::string query_string = getenv("QUERY_STRING"); // 環境変数からQUERY_STRINGを取得

            std::string key, value;
            try{
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
                this->status=200;
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg = e.what();
                this->status=500;
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
            std::cin >> post_data; // POSTデータを標準入力から読み取る

            std::map<std::string, std::string> data_map;
            try{
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
                this->status=200;
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg = e.what();
                this->status=500;
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
            std::string _value;
            try{
                auto get_data = parseQueryString();
                for (auto& pair : get_data) {
                    if(param == pair.first){
                        _value=pair.second;
                    }else{
                        _value="";
                    }
                }
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg = e.what();
                this->status=500;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                this->emsg = e.what();
                this->status=500;
                std::cerr << e.what() << '\n';
            }
            return _value;
        }
        /**
         * REFERER_　メゾット
         * @return {string} : 取得したリファラを返す
        */
        std::string REFERER_(){
            std::string ref;
            try
            {
                char* referer = std::getenv("HTTP_REFERER");
                if (referer == nullptr) {
                    throw std::runtime_error("Error: Referer is not set.");
                    return "";
                } else {
                    ref = std::string(referer);
                }
            }catch(const std::runtime_error& e){
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e){
                this->emsg = e.what();
                this->status=500;
                std::cerr << e.what() << '\n';
            }
            return ref;
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
                    // GETリクエストの場合の処理
                value = this->GET_(param);
                } else if (requestMethod == "POST") {
                    // POSTリクエストの場合の処理
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
            try{
                if(sessionId_!=""){
                    id = sessionId_;
                }else{
                    id = "";
                    throw std::runtime_error("Error:Session ID is not initialized.");
                }
                this->status=200;
            }catch(const std::runtime_error& e){
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e)
            {
                this->emsg = e.what();
                this->status=500;
                std::cerr << e.what() << '\n';
            }
            return id;
        }
        /**
         * USERAGENT_　メゾット
         * @return {string} : 取得したUserAgentを返すメゾット
        */
        std::string USERAGENT_(){
            std::string useragent;
            try
            {
                const char* referer = getenv("HTTP_USER_AGENT");
                if (referer == nullptr) {
                    throw std::runtime_error("Error:Error:UserAgent is not set.");
                    return "";
                } else {
                    useragent = std::string(referer);
                }
            }catch(const std::runtime_error& e){
                this->emsg = e.what();
                this->status=500;
            }catch(const std::exception& e){
                this->emsg = e.what();
                this->status=500;
                std::cerr << e.what() << '\n';
            }
        }
};