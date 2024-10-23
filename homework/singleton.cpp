#include <iostream>
#include <mutex>

std::mutex mutex;

class ConfigurationManager {
private:
    static ConfigurationManager* instance;
    std::string appName{"DefaultApp"};
    std::string version{"1.0"};
    
    ConfigurationManager() {
        std::lock_guard<std::mutex> myLock(mutex);
    }

public:
    ConfigurationManager(const ConfigurationManager &) = delete;
    void operator=(const ConfigurationManager &) = delete;

    static ConfigurationManager* getInstance() {
        std::lock_guard<std::mutex> myLock(mutex);
        if (instance == nullptr) {
            instance = new ConfigurationManager();
        }
        return instance;
    }

    void setAppName(const std::string& name) {
        appName = name;
    }

    std::string getAppName() const {
        return appName;
    }

    void setVersion(const std::string& ver) {
        version = ver;
    }

    std::string getVersion() const {
        return version;
    }
};

ConfigurationManager* ConfigurationManager::instance = nullptr;

int main() {
    ConfigurationManager* config = ConfigurationManager::getInstance();
    std::cout << "App Name: " << config->getAppName() << "\n";
    std::cout << "Version: " << config->getVersion() << "\n";

    config->setAppName("BruhApp");
    config->setVersion("2.0");

    std::cout << "Updated App Name: " << config->getAppName() << "\n";
    std::cout << "Updated Version: " << config->getVersion() << "\n";

    return 0;
}
