#include "lib/cgi.h"
#include<iostream>
#include<string>
int main() { 
    CGI cgi;
    cgi.SESSION_ID();
    HtmlHeader("ja","UTF-8","テスト");
    //     v("<h1>GET Data</h1>");
    //     v(cgi.GET_("test"));
    //     v(cgi.REQUEST_("test"));
    //     v(cgi.SESSION_ID());
    //     v(cgi.error_msg());
    //     v(cgi.status);
    //v("<form action='./main-out.cgi' method='post'><input type='text' name='test' value='"<< name <<"'></input><input type='submit' value='send'></input> </form>");
    // HtmlFooter();
    return 0;
}