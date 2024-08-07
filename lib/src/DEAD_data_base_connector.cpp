#include <DEAD_data_base_connector.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>

DEAD_DataBaseConnector::DEAD_DataBaseConnector() : hasSend(false) {
  try {
    this->driver = sql::mysql::get_mysql_driver_instance();
    this->conn = this->driver->connect("sql12.freemysqlhosting.net",
                                       "sql12724310", "xffMZcQICr");
    this->conn->setSchema("sql12724310");
  } catch (sql::SQLException &e) {
    std::cout << "# Err: " << e.what();
    std::cout << " (My SQL Error Code: " << e.getErrorCode();
    std::cout << ", SQL_STATE: " << e.getSQLState() << " )" << std::endl;
  }
}

void DEAD_DataBaseConnector::sendDataToDataBase(std::string name, int time) {
  if (!hasSend) {
    try {
      std::unique_ptr<sql::Statement> statement(this->conn->createStatement());
      statement->executeQuery("INSERT INTO LongestSurvivalTime VALUES (\"" +
                              name + "\"," + std::to_string(time) + ");");
      hasSend = true;
    } catch (sql::SQLException &e) {
      std::cout << "# Err: " << e.what();
      std::cout << " (My SQL Error Code: " << e.getErrorCode();
      std::cout << ", SQL_STATE: " << e.getSQLState() << " )" << std::endl;
    }
  }
}
