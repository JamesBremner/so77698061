#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"

class cEmail
{
    static std::vector<cEmail> theEmails;

public:
    std::string email;
    std::string company;
    std::string sender;
    std::string status;

    cEmail(
        const std::string &e,
        const std::string &c,
        const std::string &s,
        const std::string &sent = "")
        : email(e),
          company(c),
          sender(s),
          status(sent)
    {
    }
    static void add(const cEmail &e)
    {
        theEmails.push_back(e);
    }
    static std::vector<cEmail> &
    get()
    {
        return theEmails;
    }
};

std::vector<cEmail> cEmail::theEmails;

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Emails",
              {50, 50, 1000, 500})
    {
        generate();

        fm.events().draw(
            [&](PAINTSTRUCT &ps)
            {
                wex::shapes S(ps);
                draw(S);
            });

        show();
        run();
    }

private:
    void read();
    void generate();
    void draw(wex::shapes &S);
};

void cGUI::read()
{
}
void cGUI::generate()
{
    cEmail::add(cEmail("title1", "Amazon", "X"));
    cEmail::add(cEmail("title1", "Apple", "X", "sent"));
    cEmail::add(cEmail("title1", "Meta", "X", "sent"));
    cEmail::add(cEmail("title1", "Microsoft", "X", "sent"));
}

void cGUI::draw(wex::shapes &S)
{

    S.color(0x000000);
    S.text("email            company     sender",
        {10,10});
    int r = 70;
    for (cEmail &e : cEmail::get())
    {
        if( e.status == "sent")
            S.color(0x00AA00);
        else
            S.color(0x0000AA);
        int x = 10;
        S.text( e.email, {x,r});
        x += 100;
        S.text( e.company, {x,r});
        x += 100;
        S.text( e.sender, {x,r});
        r += 40;
    }
}

main()
{
    cGUI theGUI;
    return 0;
}
