#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 256

// Basit log yapısı
typedef struct LogEntry {
    time_t timestamp;
    char severity[MAX_LENGTH];
    char message[MAX_LENGTH];
    struct LogEntry* next;
} LogEntry;

// Log listesi yapısı
typedef struct {
    LogEntry* head;
    int count;
} LogList;

// Liste başlatma
void initLogList(LogList* list) {
    list->head = NULL;
    list->count = 0;
}

// Yeni log ekleme
void addLog(LogList* list, const char* severity, const char* message) {
    LogEntry* newEntry = (LogEntry*)malloc(sizeof(LogEntry));
    if (newEntry == NULL) {
        printf("Bellek hatasi!\n");
        return;
    }

    newEntry->timestamp = time(NULL);
    strncpy(newEntry->severity, severity, MAX_LENGTH - 1);
    strncpy(newEntry->message, message, MAX_LENGTH - 1);
    newEntry->severity[MAX_LENGTH - 1] = '\0';
    newEntry->message[MAX_LENGTH - 1] = '\0';
    
    newEntry->next = list->head;
    list->head = newEntry;
    list->count++;
}

// Logları yazdırma
void printLogs(LogList* list) {
    LogEntry* current = list->head;
    char timeStr[26];

    while (current != NULL) {
        struct tm* timeinfo = localtime(&current->timestamp);
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);
        printf("[%s] %s: %s\n", timeStr, current->severity, current->message);
        current = current->next;
    }
}

// Listeyi temizleme
void clearList(LogList* list) {
    LogEntry* current = list->head;
    while (current != NULL) {
        LogEntry* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}

int main() {
    LogList logs;
    initLogList(&logs);

    // Örnek loglar ekleme
    addLog(&logs, "ERROR", "Sistem hatasi olustu");
    addLog(&logs, "INFO", "Uygulama baslatildi");
    addLog(&logs, "WARNING", "Disk alani azaliyor");

    // Logları yazdır
    printf("Tum Loglar:\n");
    printf("------------------------\n");
    printLogs(&logs);

    // Temizle
    clearList(&logs);
    return 0;
}
