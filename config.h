#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <QPoint>

class Config
{
public:
    const static std::string loginUrl;
    const static std::string homeUrl;
    const static std::string registerUrl;
    const static std::string enableAllUrl;
    const static std::string shutdownAllUrl;
    const static std::string changeDevicesStatusUrl;
    const static std::string setDeviceConfigUrl;
    const static std::string deviceUrl;
    const static std::string logoutUrl;
    const static std::string removeUrl;
    static int width;
    static int height;
    static int updateInterval;
    static int popupWidth;
    static int popupHeight;
    static QPoint popupDeviation;
private:
    Config() = delete;
    ~Config() = delete;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    const static std::string url;
};

#endif // CONFIG_H
