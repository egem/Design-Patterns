#include <iostream>
#include <mutex>

class Logger {
  private:
    static std::unique_ptr<Logger> mInstance;
    static std::mutex mInstanceMutex;

    Logger() = default;

    Logger(const Logger& rhs) = delete;
    Logger& operator=(const Logger& rhs) = delete;

  public:
    static Logger& getInstance1() {
      static Logger instance;
      return instance;
    }

    static Logger* getInstance2() {
      std::lock_guard<std::mutex> lockGuard(mInstanceMutex);

      if (!mInstance) {
        mInstance = std::unique_ptr<Logger>(new Logger());
      }

      return mInstance.get();
    }

    void log(std::string message) {
      std::cout << message << std::endl;
    }
};

std::unique_ptr<Logger> Logger::mInstance = nullptr;
std::mutex Logger::mInstanceMutex;

int main() {
  Logger::getInstance1().log("Hello");
  Logger::getInstance2()->log("Hello2");

  return 0;
}


