// history.h

#ifndef HISTORY_H
#define HISTORY_H

#define MAX_COMMAND_LENGTH 100
#define MAX_HISTORY_SIZE 10

typedef struct {
    char commands[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH];
    int count;
} CommandHistory;

void addToHistory(CommandHistory *history, const char *command, const char *initialPath);
void loadHistoryFromFile(CommandHistory *history, const char *initialPath);
void printHistory(const CommandHistory *history);

#endif  // HISTORY_H