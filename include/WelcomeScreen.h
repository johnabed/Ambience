#ifndef WELCOME_SCREEN_H
#define WELCOME_SCREEN_H

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WMenu>
#include <Wt/WImage>
#include <Wt/WMenuItem>
#include <Wt/WNavigationBar>
#include <Wt/WPushButton>
#include <string>
#include <vector>
#include "Account.h"

namespace Wt {
  class WStackedWidget;
  class WAnchor;
}

class LoginWidget;
class CreateAccountWidget;
class BridgeScreenWidget;
class ProfileWidget;
class LightManagementWidget;

class WelcomeScreen : public Wt::WContainerWidget
{
public:
    WelcomeScreen(Wt::WContainerWidget *parent = 0);
    void handleInternalPath(const std::string &internalPath);

    Account getAccount() {return account_;};
    void setAccount(Account account) {account_ = account;};

    void connectBridge();
    void handleHttpResponse(boost::system::error_code err, const Wt::Http::Message &response);
    
    void updateProfileName();

private:
    Wt::WImage *welcome_image_;
    Wt::WMenu *leftMenu_;
    Wt::WMenu *rightMenu_;
    Wt::WMenuItem *profileMenuItem_;
    Wt::WNavigationBar *loggedOutNavBar_;
    Wt::WNavigationBar *navBar_;
    Wt::WText *serverMessage_;
    Wt::WAnchor *profileAnchor_;
    Wt::WAnchor *homeAnchor_;
    Wt::WStackedWidget *mainStack_; // main stack of the application
    Wt::WContainerWidget *links_; // links container that stores anchors
    
    CreateAccountWidget *create_; // create widget
    LoginWidget *login_; // login widget
    BridgeScreenWidget *bridgeScreen_; // bridge widget
    ProfileWidget *profileScreen_;
    
    Wt::WAnchor *createAnchor_; // anchor for create link
    Wt::WAnchor *loginAnchor_; // anchor for login link
    Wt::WAnchor *logoutAnchor_; // anchor for logout link
    void login();
    void logout();
    void createAccount();
    void bridgeScreen();
    void profileScreen();
    void lightManagementScreen(int index);

    vector<LightManagementWidget*> lightManage_ = vector<LightManagementWidget*>(100, NULL); // max 100 bridges for now
    Account account_;
};

#endif //WELCOME_SCREEN_H
