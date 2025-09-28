#pragma once
#include <Print.h>
#include <AsyncTCP.h>
#include <queue>
#include <AsyncTCP.h>
#include <memory>

class AsyncBufferedTCPLogger: public Print {
public:
  static AsyncBufferedTCPLogger &instance();
  void setup(uint16_t port);
  void setBacklogLines(uint16_t backlog_lines) { this->backlog_lines = backlog_lines; };
  virtual size_t write(uint8_t c);
  void setOnDataReceived(const AcDataHandler &onDataReceived) { this->onDataReceived = onDataReceived; };
private:
  AsyncBufferedTCPLogger();
  AsyncClient *client = nullptr;
  void reset();
  void fillBacklog();
  std::array<char, 1024> buffer = {0};
  std::queue<String> backlog;
  uint16_t currentPosition = 0;
  std::unique_ptr<AsyncServer> loggerServer;
  uint16_t backlog_lines = 0;
  AcDataHandler onDataReceived;
};
