#include <iostream>
#include <string>

// Base Handler class
class Logger {
    protected:
        Logger *nextLogger;

    public:
        Logger(Logger *next = nullptr) : nextLogger(next) {}

        virtual void LogMessage(int level, const std::string &message) {
            if (nextLogger) {
                nextLogger->LogMessage(level, message);
            }
        }

        virtual ~Logger() = default;
};

// Concrete Handler 1: Info Logger
class InfoLogger : public Logger {
    public:
        using Logger::Logger;

        void LogMessage(int level, const std::string &message) override {
            if (level == 1) {
                std::cout << "[INFO]: " << message << std::endl;
            } else if (nextLogger) {
                nextLogger->LogMessage(level, message);
            }
        }
};

// Concrete Handler 2: Warning Logger
class WarningLogger : public Logger {
    public:
        using Logger::Logger;

        void LogMessage(int level, const std::string &message) override {
            if (level == 2) {
                std::cout << "[WARNING]: " << message << std::endl;
            } else if (nextLogger) {
                nextLogger->LogMessage(level, message);
            }
        }
};

// Concrete Handler 3: Error Logger
class ErrorLogger : public Logger {
    public:
        using Logger::Logger;

        void LogMessage(int level, const std::string &message) override {
            if (level == 3) {
                std::cerr << "[ERROR]: " << message << std::endl;
            } else if (nextLogger) {
                nextLogger->LogMessage(level, message);
            }
        }
};

int main() {
    // Create the chain of responsibility
    Logger *loggerChain = new InfoLogger(new WarningLogger(new ErrorLogger()));

    std::cout << "Logging messages:" << std::endl;

    loggerChain->LogMessage(1, "Application started");
    loggerChain->LogMessage(2, "Potential issue detected");
    loggerChain->LogMessage(3, "System failure");

    // Clean up
    delete loggerChain;
    return 0;
}
