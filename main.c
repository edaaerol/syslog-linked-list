#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LENGTH 1024
#define MAX_FACILITY_LENGTH 32
#define MAX_SEVERITY_LENGTH 32
#define TIME_STRING_LENGTH 26

// Syslog kay�t yap�s�
typedef struct SyslogNode {
    time_t timestamp;
    char facility[MAX_FACILITY_LENGTH];
    char severity[MAX_SEVERITY_LENGTH];
    char message[MAX_MSG_LENGTH];
    struct SyslogNode* next;
    struct SyslogNode* prev;
} SyslogNode;

// �ift y�nl� ba�l� liste yap�s�
typedef struct {
    SyslogNode* head;
    SyslogNode* tail;
    size_t count;
} SyslogList;

// Liste ba�latma
void initSyslogList(SyslogList* list) {
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->count = 0;
    }
}

// Yeni d���m olu�turma
SyslogNode* createNode(time_t timestamp, const char* facility, 
                      const char* severity, const char* message) {
    SyslogNode* newNode = (SyslogNode*)malloc(sizeof(SyslogNode));
    if (newNode == NULL) {
        fprintf(stderr, "Bellek ay�rma hatas�!\n");
        return NULL;
    }

    newNode->timestamp = timestamp;
    strncpy(newNode->facility, facility, MAX_FACILITY_LENGTH - 1);
    strncpy(newNode->severity, severity, MAX_SEVERITY_LENGTH - 1);
    strncpy(newNode->message, message, MAX_MSG_LENGTH - 1);
    
    // Null terminat�r ekleme
    newNode->facility[MAX_FACILITY_LENGTH - 1] = '\0';
    newNode->severity[MAX_SEVERITY_LENGTH - 1] = '\0';
    newNode->message[MAX_MSG_LENGTH - 1] = '\0';
    
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

// Listeye yeni log ekleme
int appendLog(SyslogList* list, time_t timestamp, const char* facility, 
              const char* severity, const char* message) {
    if (list == NULL || facility == NULL || severity == NULL || message == NULL) {
        return -1;
    }

    SyslogNode* newNode = createNode(timestamp, facility, severity, message);
    if (newNode == NULL) {
        return -1;
    }

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
    return 0;
}

// Belirli �nem seviyesindeki loglar� yazd�rma
void printLogsBySeverity(const SyslogList* list, const char* severity) {
    if (list == NULL || severity == NULL) {
        return;
    }

    SyslogNode* current = list->head;
    char timeStr[TIME_STRING_LENGTH];

    while (current != NULL) {
        if (strcmp(current->severity, severity) == 0) {
            struct tm* timeinfo = localtime(&current->timestamp);
            if (timeinfo != NULL) {
                strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);
                printf("[%s] %s.%s: %s\n", 
                       timeStr, current->facility, 
                       current->severity, current->message);
            }
        }
        current = current->next;
    }
}

// T�m loglar� yazd�rma
void printAllLogs(const SyslogList* list) {
    if (list == NULL) {
        return;
    }

    SyslogNode* current = list->head;
    char timeStr[TIME_STRING_LENGTH];

    while (current != NULL) {
        struct tm* timeinfo = localtime(&current->timestamp);
        if (timeinfo != NULL) {
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);
            printf("[%s] %s.%s: %s\n", 
                   timeStr, current->facility, 
                   current->severity, current->message);
        }
        current = current->next;
    }
}

// Belirli zaman aral���ndaki loglar� yazd�rma
void printLogsByTimeRange(const SyslogList* list, time_t start, time_t end) {
    if (list == NULL) {
        return;
    }

    SyslogNode* current = list->head;
    char timeStr[TIME_STRING_LENGTH];

    while (current != NULL) {
        if (current->timestamp >= start && current->timestamp <= end) {
            struct tm* timeinfo = localtime(&current->timestamp);
            if (timeinfo != NULL) {
                strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);
                printf("[%s] %s.%s: %s\n", 
                       timeStr, current->facility, 
                       current->severity, current->message);
            }
        }
        current = current->next;
    }
}

// Listeyi temizleme
void clearList(SyslogList* list) {
    if (list == NULL) {
        return;
    }

    SyslogNode* current = list->head;
    while (current != NULL) {
        SyslogNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

// Eski loglar� silme
void deleteOldLogs(SyslogList* list, time_t cutoff_time) {
    if (list == NULL) {
        return;
    }

    while (list->head != NULL && list->head->timestamp < cutoff_time) {
        SyslogNode* temp = list->head;
        list->head = list->head->next;
        
        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }
        
        free(temp);
        list->count--;
    }
}


int main() {
    SyslogList logList;
    initSyslogList(&logList);

    // �rnek log kay�tlar� ekleme
    time_t current_time = time(NULL);
    
    if (appendLog(&logList, current_time, "kernel", "ERROR", 
                  "Buffer overflow detected in module XYZ") < 0) {
        fprintf(stderr, "Log eklenemedi!\n");
        return 1;
    }
    
    if (appendLog(&logList, current_time + 60, "auth", "WARNING", 
                  "Failed login attempt from IP 192.168.1.100") < 0) {
        fprintf(stderr, "Log eklenemedi!\n");
        return 1;
    }
    
    if (appendLog(&logList, current_time + 120, "system", "INFO", 
                  "System update started") < 0) {
        fprintf(stderr, "Log eklenemedi!\n");
        return 1;
    }

    // T�m loglar� yazd�r
    printf("\nTum Loglar:\n");
    printf("------------------------\n");
    printAllLogs(&logList);

    // ERROR seviyesindeki loglar� yazd�r
    printf("\nERROR Seviyesindeki Loglar:\n");
    printf("------------------------\n");
    printLogsBySeverity(&logList, "ERROR");

    // Son 5 dakikal�k loglar� yazd�r
    printf("\nSon 5 Dakikalik Loglar:\n");
    printf("------------------------\n");
    printLogsByTimeRange(&logList, current_time - 300, current_time + 300);

    // Listeyi temizle
    clearList(&logList);

    return 0;
}
