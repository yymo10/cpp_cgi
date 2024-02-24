#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>

class Log{
    std::vector<std::string> emsg;
    int status;
    public:
    Log(std::vector<std::string> err,int status_){
            this->emsg = err;
            this->status = status_;
    }
    /**
     * error_log　メゾット
     * エラーメッセージをログとして出力します。
     * @param {string} : ログファイル格納のパス
     * @param {string} : ログファイル名を指定
     * @param {date_format} : エラーログに出力する日付、時間のフォーマットを指定（例：　"%Y-%m-%d %H:%M:%S"）
     * @return { void }
    */
    void error_log(std::string path,std::string fname,std::string date_format,std::string ipaddr){
        std::ofstream logfile(path + fname,std::ios::app);
        std::vector<std::string> msg;
        try{
            msg = this->emsg;
            if(!logfile){
                std::cerr << "ファイルを開けませんでした。" << std::endl;
                std::runtime_error("Error: File is missing or cannot be opened.");
            }
            for(int i=0;i < msg.size();i++){
                auto now = std::chrono::system_clock::now();
                time_t tt = std::chrono::system_clock::to_time_t(now);
                struct tm *ptm = localtime(&tt);
                logfile << std::put_time(ptm, date_format.c_str()) <<" [error code: "<< this->status <<"; IP Address: "<< ipaddr << "]"<< this->emsg[i]<< std::endl;
            }
        }catch(const std::runtime_error& e){
            std::cerr << e.what() << std::endl;
            this->emsg.push_back(e.what());
        }catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            this->emsg.push_back(e.what());
            this->status=500;
        }
        logfile.close();
    }
};