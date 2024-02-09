#include "lib/cgi.h"
#include<iostream>
#include<string>
int main() { 
    CGI cgi;
    HtmlHeader("ja","UTF-8","テスト");
    v("<h1>GET Data</h1>");
    v(cgi.GET_("test"));
   // v(cgi.POST_("test"));
    v(cgi.REQUEST_("test"));
    v(cgi.SESSION_ID());
    v("<form action='./main-out.cgi' method='post'><input type='text' name='test' value='thello'></input><input type='submit' value='send'></input> </form>");
    HtmlFooter();
    return 0;
}