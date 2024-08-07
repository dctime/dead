#include <cppconn/connection.h>
#include <mysql_driver.h>

class DEAD_DataBaseConnector {
public:
  DEAD_DataBaseConnector();
  void sendDataToDataBase(std::string name, int time);
private:
  sql::mysql::MySQL_Driver *driver;
  sql::Connection *conn;
  sql::ConnectOptionsMap connectionProperties;
  bool hasSend;
};
