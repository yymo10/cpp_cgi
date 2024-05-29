/**********************************************************
 * CGI Library for C++
 * License : MIT
 * Author : @yymo10 (YoheiYamamoto)
 * Remote Repository : https://github.com/yymo10/cpp_cgi
 * WebSite : https://www.sb-i.jp/cpplib/
 **********************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <sstream>
#include <ctime>
#include <vector>
/**
 * HtmlHead 関数
 * @param {string} charset : 文書で使用される文字セットを指定します。例えば、"UTF-8"。
 * @return {void}
 */
void HtmlHeader(std::string charset="utf-8"){
       std::cout << "Content-type: text/html;charset="<<charset<<"\n\n";
}
/**
 * JsonHeader 関数
 * @param {string} charset : 文字セットを設定する（初期値はutf-8）
 * @return {void}
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
/**
 * v 関数
 * テキストを挿入する関数
 * @return {void}
*/
template<typename T>
void v(T view){
        std::cout << view << "\n";
}
/**
 * vln 関数
 * テキストと改行を挿入する関数
 * @return {void}
*/
template<typename T>
void vln(T view){
        std::cout << view << "<br />" << "\n";
}
/**
 * system_info 関数
 * 環境変数を一覧表示する関数
 * @return {void}
*/
void system_info(){
    const char* env_vars[] = {
        "CONTENT_LENGTH",
        "CONTENT_TYPE",
        "DOCUMENT_ROOT",
        "GATEWAY_INTERFACE",
        "HTTP_ACCEPT",
        "HTTP_COOKIE",
        "HTTP_HOST",
        "HTTP_REFERER",
        "HTTP_USER_AGENT",
        "PATH",
        "QUERY_STRING",
        "REMOTE_ADDR",
        "REMOTE_PORT",
        "REQUEST_METHOD",
        "REQUEST_URI",
        "SCRIPT_FILENAME",
        "SCRIPT_NAME",
        "SERVER_ADDR",
        "SERVER_ADMIN",
        "SERVER_NAME",
        "SERVER_PORT",
        "SERVER_PROTOCOL",
        "SERVER_SIGNATURE",
        "SERVER_SOFTWARE",
        nullptr
    };
    std::cout <<"<table>" << std::endl;
    for (int i = 0; env_vars[i] != nullptr; ++i) {
        const char* value = std::getenv(env_vars[i]);
        std::cout <<"<tr>" <<std::endl;
        if (value != nullptr) {
               std::cout <<"<th style='text-align: left;'>" << env_vars[i] << "</th>" << std::endl;
               std::cout <<"<td>"<< value << "</td>";
        } else {
                std::cout <<"<th  style='text-align: left;'>" << env_vars[i] << "</th>" << std::endl;
               std::cout <<"<td>"<< "Not Set;" << "</td>";
        }
        std::cout <<"</tr>" <<std::endl;
    }
    std::cout <<"</table>";
}

class CGI{
            std::string sessionId_;

         /**
         * GenerateSessionId メゾット
         * sessionId_にセッションIDの乱数を生成代入（CGIクラスのインスタンスで初期化実行）
        */
        void GenerateSessionId() {
            srand(time(0));
            sessionId_ = std::to_string(rand());
            try{
                if(sessionId_==""){
                        throw std::runtime_error("Error: Session ID is not initialized.");
                }
                this->status=200;
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg.push_back(e.what());
                this->status=500;
            }
        }
        protected:
            std::vector<std::string> emsg;
        public:
            int status;
        CGI(){
            this->GenerateSessionId();
        }
        /**
         * error_msg　メゾット
         * エラーメッセージをテキストで返すメゾット
         * @return { string } : エラーメッセージを連結して文字列として返します。
        */
        std::string error_msg(){
            std::string view;
            std::vector<std::string> msg;
            try{
                msg = this->emsg;
            }catch(const std::runtime_error& e){
                std::cerr << e.what() << std::endl;
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg.push_back(e.what());
                this->status=500;
            }
            if(msg.size()==1){
                view = msg[0];
            }else{
                for(int i=0;i <= msg.size()-1;i++){
                    view += msg[i];
                }
            }
           return view;
        }
        std::map<std::string, std::string> parseQueryString() {
            std::map<std::string, std::string> data;
            std::string query_string = getenv("QUERY_STRING");

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
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg.push_back(e.what());
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
            std::cin >> post_data;

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
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                this->emsg.push_back(e.what());
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
                this->emsg.push_back(e.what());
                this->status=500;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                this->emsg.push_back(e.what());
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
                this->emsg.push_back(e.what());
            }catch(const std::exception& e){
                this->emsg.push_back(e.what());
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
            if (method != nullptr) {
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
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e)
            {
                this->emsg.push_back(e.what());
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
                const char* referer = std::getenv("HTTP_USER_AGENT");
                if (referer == nullptr) {
                    throw std::runtime_error("Error:Error:UserAgent is not set.");
                    return "";
                } else {
                    useragent = std::string(referer);
                }
            }catch(const std::runtime_error& e){
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                this->emsg.push_back(e.what());
                this->status=500;
                std::cerr << e.what() << '\n';
            }
            return useragent;
        }
        /**
         * REMOTE_IP_ADDR　メゾット
         * @return {string} : 取得したアクセス元のIPアドレスを返すメゾット
        */
        std::string REMOTE_IP_ADDR(){
            std::string ipaddress;
            try
            {
                const char* ip = std::getenv("REMOTE_ADDR");
                if (ip == nullptr) {
                    throw std::runtime_error("Error: Remote IP address is not set.");
                    return "";
                } else {
                    ipaddress = std::string(ip);
                }
            }catch(const std::runtime_error& e){
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                this->emsg.push_back(e.what());
                this->status=500;
                std::cerr << e.what() << '\n';
            }
            return ipaddress;
        }
        /**
         * DOCUMENT_ROOT　メゾット
         * @return {string} : ドキュメントのルートディレクトリ（絶対パス）を返すメゾット
        */
        std::string DOCUMENT_ROOT(){
            std::string document_root;
            try
            {
                const char* referer = std::getenv("DOCUMENT_ROOT");
                if (referer == nullptr) {
                    throw std::runtime_error("Error: DOCUMENT_ROOT is not set.");
                    return "";
                } else {
                    document_root = std::string(referer);
                }
            }catch(const std::runtime_error& e){
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                this->emsg.push_back(e.what());
                this->status=500;
                std::cerr << e.what() << '\n';
            }
            return document_root;
        }
        
        /**
         * SCRIPT_FILENAME　メゾット
         * @return {string} : 実行しているCGIスクリプトのファイル名を絶対パスと一緒に返すメゾット
        */
        std::string SCRIPT_FILENAME(){
            std::string script_filename;
            try
            {
                const char* referer = std::getenv("SCRIPT_FILENAME");
                if (referer == nullptr) {
                    throw std::runtime_error("Error: Script File Name is not set.");
                    return "";
                } else {
                    script_filename = std::string(referer);
                }
            }catch(const std::runtime_error& e){
                this->emsg.push_back(e.what());
                this->status=500;
            }catch(const std::exception& e){
                this->emsg.push_back(e.what());
                this->status=500;
                std::cerr << e.what() << '\n';
            }
            return script_filename;
        }
        /**
         * error_msg_map　メゾット
         * @return {vector<string>} : エラーメッセージを取得 
        */
        std::vector<std::string> error_msg_map(){
            if(this->emsg.size()<=1){
                return this->emsg;
            }else{
                return;
            }
        }
};
class Auth : CGI{
private:
    std::string token;
public:
    bool status_;
    Auth(std::string token_):token(token_){
        try{
            const char* auth = std::getenv("HTTP_AUTHORIZATION");
            if (auth) {
                if(auth==this->token){
                    this->status_=true;
                }else{
                    this->status_ = false;
                    throw std::runtime_error("Authotization Token Error: Authentication token does not match.");
                }
            } else {
                this->status = false;
                throw std::runtime_error("Authotization Token Error: Cannot find authentication token.");
            }
        }catch(const std::runtime_error& e){
                this->emsg.push_back(e.what());
                this->status=401;
        }catch(const std::exception& e){
                this->emsg.push_back(e.what());
                this->status=401;
                std::cerr << e.what() << '\n';
        }
    }
    bool check(){
        if(this->status_!=NULL){
            return this->status_;
        }
    }
};
