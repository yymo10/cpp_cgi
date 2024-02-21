#include "lib/cgi.h"
#include<iostream>
#include<string>
int main() { 
    CGI cgi;
    HtmlHeader("ja","UTF-8","テスト");
        v("<h1>GET Data</h1>");
        v(cgi.GET_("test"));
        v(cgi.REQUEST_("test"));
        v(cgi.SESSION_ID());
        v(cgi.REFERER_());
        v(cgi.error_msg());
        v(cgi.status);

        v("<a href='http://localhost:8888/cgi-bin/main-out.cgi'>Ref</a>");
        v("<form action='./main-out.cgi' method='post'><input type='text' name='test' value='thello'></input><input type='submit' value='send'></input> </form>");
    HtmlFooter();
    return 0;
}