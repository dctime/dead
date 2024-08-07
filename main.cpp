// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <DEAD_game_builder.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <gtk/gtk.h>
#include <iostream>
#include <memory>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <string>
#include <unistd.h>

namespace dead {
  sql::mysql::MySQL_Driver *driver;
  sql::Connection *conn;
  sql::ConnectOptionsMap connectionProperties;
  bool pressedPlay = false;
  GtkWidget *window;
  GtkListStore *liststoreLongest;
  GtkTreeViewColumn *columnLongestName;
  GtkTreeViewColumn *columnLongestTime;
  GtkCellRenderer *cellRendererLongestName;
  GtkCellRenderer *cellRendererLongestTime;
  GtkButton *playButton;
  GtkEntry *enterYourNameEntry;
  GtkBuilder *builder;
  void playButtonPressed();
  void onMainWindowDestory(GtkWidget * window);
  void onPlayButtonClicked(GtkButton * window);
  bool stringHasText(std::string text);
}

int main(int argc, char **argv) {
  

  dead::driver = sql::mysql::get_mysql_driver_instance();
  dead::conn = dead::driver->connect("sql12.freemysqlhosting.net", "sql12724310",
                         "xffMZcQICr");
  dead::conn->setSchema("sql12724310");

  GError *err = NULL;
  
  gtk_init(&argc, &argv);

  dead::builder = gtk_builder_new();
  gtk_builder_add_from_file(dead::builder, "assets/glade/Test.glade", &err);
  if (err != NULL) {
    std::cout << "Error: " << err->message << std::endl;
  }

  dead::window = GTK_WIDGET(gtk_builder_get_object(dead::builder, "mainWindow"));
  dead::playButton = GTK_BUTTON(gtk_builder_get_object(dead::builder, "playButton"));
  dead::enterYourNameEntry = GTK_ENTRY(gtk_builder_get_object(dead::builder, "enterYourNameEntry"));

  g_signal_connect(dead::window, "destroy", G_CALLBACK(dead::onMainWindowDestory), NULL);
  g_signal_connect(dead::playButton, "clicked", G_CALLBACK(dead::onPlayButtonClicked),
                   NULL);

  gtk_builder_connect_signals(dead::builder, NULL);

  dead::liststoreLongest =
      GTK_LIST_STORE(gtk_builder_get_object(dead::builder, "liststoreLongest"));
  dead::columnLongestName = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(dead::builder, "columnLongestName"));
  dead::columnLongestTime = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(dead::builder, "columnLongestTime"));
  dead::cellRendererLongestName = GTK_CELL_RENDERER(
      gtk_builder_get_object(dead::builder, "cellRendererLongestName"));
  dead::cellRendererLongestTime = GTK_CELL_RENDERER(
      gtk_builder_get_object(dead::builder, "cellRendererLongestTime"));
  gtk_tree_view_column_add_attribute(dead::columnLongestName, dead::cellRendererLongestName,
                                     "text", 0);
  gtk_tree_view_column_add_attribute(dead::columnLongestTime, dead::cellRendererLongestTime,
                                     "text", 1);

  std::cout << "TIME FOR SQL" << std::endl;

  std::unique_ptr<sql::Statement> statement(dead::conn->createStatement());
  std::unique_ptr<sql::ResultSet> resultSet(statement->executeQuery(
      "SELECT * FROM LongestSurvivalTime ORDER BY TimeInSeconds DESC LIMIT 10"));
  std::string name;
  int timeInSeconds;

  try {
    GtkTreeIter iterLongest;
    while (resultSet->next()) {
      name = resultSet->getString("Name");
      timeInSeconds = resultSet->getInt("TimeInSeconds");
      const char *nameChars = name.c_str();
      std::string timeFormatted = std::to_string(timeInSeconds);
      const char *timeFormattedChars = timeFormatted.c_str();
      std::cout << "Name: " << nameChars << ", TimeInSeconds: " << timeInSeconds
                << std::endl;
      gtk_list_store_append(dead::liststoreLongest, &iterLongest);
      gtk_list_store_set(dead::liststoreLongest, &iterLongest, 0, nameChars, -1);
      gtk_list_store_set(dead::liststoreLongest, &iterLongest, 1, timeFormattedChars,
                         -1);
      std::cout << "added a row" << std::endl;
    }
  } catch (sql::SQLException &e) {
    std::cout << "# Err: " << e.what();
    std::cout << " (My SQL Error Code: " << e.getErrorCode();
    std::cout << ", SQL_STATE: " << e.getSQLState() << " )" << std::endl;
  }

  gtk_widget_show_all(dead::window);
  gtk_main();

 std::shared_ptr<DEAD_Game> game;
  if (dead::pressedPlay == true) {
    std::shared_ptr<DEAD_GameBuilder> gameBuilder =
        std::make_shared<DEAD_GameBuilder>();
    game = gameBuilder->build();

  }

  delete dead::conn;

  game->run();  
   
}

void dead::onMainWindowDestory(GtkWidget *window) {
  std::cout << "Hello!" << std::endl;
  gtk_main_quit();
}

void dead::onPlayButtonClicked(GtkButton *button) {
  std::string nameText (gtk_entry_get_text(dead::enterYourNameEntry));
  std::cout << "Entry Text: " << nameText << std::endl;
  if (dead::stringHasText(nameText)) {
    dead::playButtonPressed();
    gtk_main_quit();
  }
}  

void dead::playButtonPressed() {
  dead::pressedPlay = true;
}

bool dead::stringHasText(std::string text) {
  for (const char c : text) {
    if (c != ' ') return true; 
  } 
  return false;
}
