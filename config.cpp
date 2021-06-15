#include "config.h"

const std::string Config::url = "http://localhost:8080";
const std::string Config::loginUrl = url + "/login";
const std::string Config::homeUrl = url + "/home";
const std::string Config::registerUrl = url + "/register";
const std::string Config::enableAllUrl = url + "/home/activate";
const std::string Config::shutdownAllUrl = url + "/home/shutdown";
const std::string Config::changeDevicesStatusUrl = url + "/home/changeDevicesStatus";
const std::string Config::setDeviceConfigUrl = url + "/home/changeDeviceConfig";
const std::string Config::deviceUrl = url + "/home/device?username=";
const std::string Config::logoutUrl = url + "/logout";
const std::string Config::removeUrl = url + "/home/remove";

int Config::width = 1920;
int Config::height = 1080;

int Config::updateInterval = 60;

int Config::popupWidth = 400;
int Config::popupHeight = 600;
QPoint Config::popupDeviation = QPoint(0, 120);
