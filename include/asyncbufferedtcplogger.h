#pragma once
#include <Print.h>
#include <AsyncTCP.h>
#include <queue>
#include <AsyncTCP.h>
#include <memory>

#ifndef DEFAULT_ASYNC_BUFFERED_TCP_LOGGER_BACKLOG_LINES
#define DEFAULT_ASYNC_BUFFERED_TCP_LOGGER_BACKLOG_LINES 100
#endif

class AsyncBufferedTCPLogger: public Print {
public:
  static AsyncBufferedTCPLogger &instance();
  void setup(uint16_t port);
  void begin(uint16_t port) { setup(port); }; // Compatibility with Serial
  void setBacklogLines(uint16_t backlog_lines) { this->backlog_lines = backlog_lines; };
  virtual size_t write(uint8_t c);
  void setOnDataReceived(const AcDataHandler &onDataReceived) { this->onDataReceived = onDataReceived; };
private:
  AsyncBufferedTCPLogger();
  AsyncClient *client = nullptr;
  void reset();
  void fillBacklog();
  void flush();
  void client_write(const char *buf, size_t size);
  std::array<char, 1024> buffer = {0};
  std::queue<String> backlog;
  uint16_t currentPosition = 0;
  std::unique_ptr<AsyncServer> loggerServer;
  uint16_t backlog_lines = DEFAULT_ASYNC_BUFFERED_TCP_LOGGER_BACKLOG_LINES;
  AcDataHandler onDataReceived;
};
