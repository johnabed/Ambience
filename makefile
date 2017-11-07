EXE = MainApp
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

OBJS = MainApplication.o Hash.o WelcomeScreen.o Account.o LoginWidget.o CreateAccountWidget.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 -Iinclude -L/usr/local/lib $(DEBUG)
LFLAGS = -Wall -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -lboost_date_time -lcrypto $(DEBUG)

MainApp : $(OBJS)
	$(CC) $(OBJS) -o MainApp $(LFLAGS)

MainApplication.o : $(INC_DIR)/WelcomeScreen.h $(SRC_DIR)/MainApplication.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/MainApplication.cpp

Hash.o : $(INC_DIR)/Hash.h $(SRC_DIR)/Hash.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/Hash.cpp

WelcomeScreen.o : $(INC_DIR)/Account.h $(SRC_DIR)/WelcomeScreen.cpp	
	$(CC) $(CFLAGS) $(SRC_DIR)/WelcomeScreen.cpp

Account.o : $(INC_DIR)/Account.h $(SRC_DIR)/Account.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/Account.cpp

LoginWidget.o : $(INC_DIR)/LoginWidget.h $(SRC_DIR)/LoginWidget.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/LoginWidget.cpp

CreateAccountWidget.o : $(INC_DIR)/CreateAccountWidget.h $(SRC_DIR)/CreateAccountWidget.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/CreateAccountWidget.cpp

clean:
	rm $(OBJS) MainApp