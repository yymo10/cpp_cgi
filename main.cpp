#include "lib/cgi.h"
#include<iostream>
#include<string>
int main() { 
    CGI cgi;
    Auth auth("100002a");
    if(auth.check()==true){
        v("success");
    }
    cgi.SESSION_ID();
    HtmlHeader();
        v("<a href='http://localhost:8888/cgi-bin/main-out.cgi'>Ref</a>");
        v("<form action='./main-out.cgi' method='post'><input type='text' name='test' value='thello'></input><input type='submit' value='send'></input> </form>");
    system_info();
    HtmlFooter();
    return 0;
}