#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Array>


using namespace std;
using namespace Wt;

class Light {
    
public:
    Light(WString lightNum, Json::Object lightData);
    
    virtual ~Light();
    
    //GETTERS
    WString getLightnum() {return lightnum_;}
    WString getName() {return name_;}
    WString getType() {return type_;}
    WString getModelid() {return modelid_;}
    WString getAlert() {return alert_;}
    int getBri() {return bri_;}
    WString getColormode() {return colormode_;}
    int getCt() {return ct_;}
    WString getEffect() {return effect_;}
    int getHue() {return hue_;}
    bool getOn() {return on_;}
    bool getReachable() {return reachable_;}
    int getSat() {return sat_;}
    double getX() {return xy_[0];}
    double getY() {return xy_[1];}
    
    //SETTERS
    void setLightnum(WString lightnum) {lightnum_ = lightnum;}
    void setName(WString name) {name_ = name;}
    void setType(WString type) {type_ = type;}
    void setModelid(WString modelid) {modelid_ = modelid;}
    void setAlert(WString alert) {alert_ = alert;}
    void setBri(int bri) {bri_ = bri;}
    void setColormode(WString colormode) {colormode_ = colormode;}
    void setCt(int ct) {ct_ = ct;}
    void setEffect(WString effect) {effect_ = effect;}
    void setHue(int hue) {hue_ = hue;}
    void setOn(bool on) {on_ = on;}
    void setReachable(bool reachable) {reachable_ = reachable;}
    void setSat(int sat) {sat_ = sat;}
    void setX(double x) {xy_[0] = x;}
    void setY(double y) {xy_[1] = y;}
    
    void toggleOnOff() {on_ = !on_;}
    
private:
    WString lightnum_;
    WString name_;
    WString type_;
    WString modelid_;
    WString alert_;
    int bri_;
    WString colormode_;
    int ct_;
    WString effect_;
    int hue_;
    bool on_;
    bool reachable_;
    int sat_;
    double xy_[2];
};

#endif //LIGHT_H
