/**
 *  @file       WelcomeScreen.cpp
 *  @author     CS 3307 - Team 13
 *  @date       10/7/2017
 *  @version    1.0
 *
 *  @brief      CS 3307, Hue Light Application main screen which controls the user's view
 *
 *  @section    DESCRIPTION
 *
 *              This class represents the main screen of the application. All internal path changes
 *              as well as any persistent widgets will be handled here.
 */

#include "WelcomeScreen.h"
#include <string>
#include <stdio.h>
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <regex>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WMenu>
#include <Wt/WTableCell>
#include <Wt/WServer>
#include <Wt/WStackedWidget>
#include "CreateAccountWidget.h"
#include "LoginWidget.h"
#include "BridgeScreenWidget.h"
#include "ProfileWidget.h"
#include "LightManagementWidget.h"

using namespace Wt;
using namespace std;

/**
 *   @brief  Main Screen constructor
 *
 *   @param  *parent is a pointer the the containerwidget that stores this widget
 */
WelcomeScreen::WelcomeScreen(WContainerWidget *parent):
WContainerWidget(parent),
createScreen_(0),
loginScreen_(0),
bridgeScreen_(0),
profileScreen_(0),
account_("","","","") {
    //Logged Out Navigation Bar - Login, Create Account
    navBar_ = new WNavigationBar(this);
    navBar_->setTitle("Ambience");
    navBar_->setResponsive(true);

    //Left Menu for Login/Create/Profile/Bridges depending on login status
    WMenu *leftMenu = new WMenu();
    navBar_->addMenu(leftMenu);
    
    loginMenuItem_ = new WMenuItem("Login");
    loginMenuItem_->setLink(WLink(WLink::InternalPath, "/login"));
    leftMenu->addItem(loginMenuItem_);
    
    createMenuItem_ = new WMenuItem("Create Account");
    createMenuItem_->setLink(WLink(WLink::InternalPath, "/create"));
    leftMenu->addItem(createMenuItem_);
    
    profileMenuItem_ = new WMenuItem("Profile");
    profileMenuItem_->setLink(WLink(WLink::InternalPath, "/profile"));
    leftMenu->addItem(profileMenuItem_);
    
    bridgesMenuItem_ = new WMenuItem("Bridges");
    bridgesMenuItem_->setLink(WLink(WLink::InternalPath, "/bridges"));
    leftMenu->addItem(bridgesMenuItem_);
    
    //Right Menu contains Logout button
    WMenu *rightMenu = new WMenu();
    navBar_->addMenu(rightMenu, AlignmentFlag::AlignRight);
    
    logoutMenuItem_ = new WMenuItem("Logout");
    logoutMenuItem_->setLink(WLink(WLink::InternalPath, "/logout"));
    rightMenu->addItem(logoutMenuItem_);
    
    //Initially not logged in - hide logged in pages
    profileMenuItem_->setHidden(true);
    bridgesMenuItem_->setHidden(true);
    logoutMenuItem_->setHidden(true);
    
    serverMessage_ = new WText("You are connected to the Team 13 Production Server", this);
    new WBreak(this);
    
    welcome_image_ = new WImage(WLink("images/login_lights.jpeg"));
    addWidget(welcome_image_);
    
    mainStack_ = new WStackedWidget();
    addWidget(mainStack_);
    
    // detects any changes to the internal path and sends to the handle internal path function
    WApplication::instance()->internalPathChanged().connect(this, &WelcomeScreen::handleInternalPath);
}

/**
 *   @brief  Handle Internal Path function, checks for any changes to the internal
 *           path and redirects the page according to internalPath
 *   @param  internalPath is the page name to be re-directed to
 *   @return  void
 */
void WelcomeScreen::handleInternalPath(const string &internalPath) {
    if (account_.isAuth()) {
        welcome_image_->setHidden(true);
        serverMessage_->setHidden(true);
        profileMenuItem_->setHidden(false);
        bridgesMenuItem_->setHidden(false);
        logoutMenuItem_->setHidden(false);
        loginMenuItem_->setHidden(true);
        createMenuItem_->setHidden(true);
        
        updateProfileName(); //set name of logged in user
        
        regex re("/bridges/(\\d{1,3})");
        
        if (internalPath == "/bridges") { // opens bridge page
            bridgeScreen();
        }
        else if (regex_match(internalPath, re)) {
            smatch match;
            regex_match(internalPath, match, re);
            string result = match.str(1);
            lightManagementScreen(stoi(result));
        }
        else if (internalPath == "/profile") {
            profileScreen();
        }
        else if (internalPath == "/logout") {
            //refreshing page to logout
            //account_->logout();
            loginMenuItem_->select();
        }
    }
    else {
        welcome_image_->setHidden(true);
        serverMessage_->setHidden(false);
        profileMenuItem_->setHidden(true);
        bridgesMenuItem_->setHidden(true);
        logoutMenuItem_->setHidden(true);
        loginMenuItem_->setHidden(false);
        createMenuItem_->setHidden(false);
        
        if (internalPath == "/create") {// opens create page
            createAccountScreen();
        }
        else if (internalPath == "/login") { // opens login page
            loginScreen();
        }
    }
}

void WelcomeScreen::lightManagementScreen(int index) {
    Bridge *bridge = account_.getBridgeAt(index);
    
    //create new LMW on view because bridge data may have changed since last view
    lightManage_[index] = new LightManagementWidget(mainStack_, bridge, this);
    mainStack_->setCurrentWidget(lightManage_[index]);
    lightManage_[index]->update();
}

/**
 *   @brief  Create Account function, updates the page to the
 *           creation screen
 *   @return void
 */
void WelcomeScreen::createAccountScreen() {
    if (!createScreen_) {
        createScreen_ = new CreateAccountWidget(mainStack_, &account_, this);
    }
    mainStack_->setCurrentWidget(createScreen_);
    createScreen_->update();
}

/**
 *   @brief  profile screen function, updates the page to the
 *           profile management screen
 *   @return void
 */
void WelcomeScreen::profileScreen() {
    if (!profileScreen_) {
        profileScreen_ = new ProfileWidget(mainStack_, &account_, this);
    }
    mainStack_->setCurrentWidget(profileScreen_);
    profileScreen_->update();
}

/**
 *   @brief  Validates user account to logged in after successful login.
 *   @return void
 */
void WelcomeScreen::loginSuccess() {
    account_.setAuth(true); //set account to authorized (logged in status)
    bridgesMenuItem_->select(); //click bridge menu item
    WApplication::instance()->setInternalPath("/bridges", true);
}

/**
 *   @brief  Login screen function, updates the page to the
 *           login screen
 *   @return void
 */
void WelcomeScreen::loginScreen() {
    if (!loginScreen_) {
        loginScreen_ = new LoginWidget(mainStack_, &account_, this);
    }
    mainStack_->setCurrentWidget(loginScreen_);
    loginScreen_->update();
}

/**
 *   @brief  Bridge function, updates the page to the
 *           bridge control screen
 *   @return void
 */
void WelcomeScreen::bridgeScreen() {
    if (!bridgeScreen_) {
        bridgeScreen_ = new BridgeScreenWidget(mainStack_, &account_, this);
    }
    mainStack_->setCurrentWidget(bridgeScreen_);
    bridgeScreen_->update();
}

/**
 *   @brief  Updates name of logged in user on the top menu bar
 *
 *   @return void
 */
void WelcomeScreen::updateProfileName() {
    profileMenuItem_->setText("Profile (" + account_.getFirstName() + " " + account_.getLastName() + ")");
}


