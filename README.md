# syslog-linked-list
# Syslog Log Yönetim Sistemi

## Proje Açıklaması
Bu proje, Linux işletim sisteminde sistem günlüklerini (syslog) yönetmek ve işlemek amacıyla geliştirilmiştir. Log kayıtlarını verimli bir şekilde saklamak, filtrelemek ve yönetmek için çift yönlü bağlı liste (doubly linked list) veri yapısı kullanılmaktadır. Uygulama, belirli kriterlere göre logları listeleyebilir, eski kayıtları silebilir ve tüm logları temizleyebilir.

## Özellikler
- **Çift Yönlü Bağlı Liste Yapısı**: Log ekleme ve silme işlemleri verimli bir şekilde yapılır.
- **Log Ekleme**: Dinamik olarak yeni log ekleme desteği.
- **Önem Derecesine Göre Filtreleme**: ERROR, WARNING, INFO gibi önem seviyelerine göre logları listeleme.
- **Zaman Aralığına Göre Filtreleme**: Belirli bir zaman aralığındaki logları getirme.
- **Tüm Logları Temizleme**: Listedeki tüm logları temizleme.
- **Eski Logları Silme**: Belirtilen zamandan daha eski logları kaldırma.

## Veri Yapıları

### `SyslogNode`
Bir log kaydını temsil eden yapı:
```c
typedef struct SyslogNode {
    time_t timestamp;
    char facility[MAX_FACILITY_LENGTH];
    char severity[MAX_SEVERITY_LENGTH];
    char message[MAX_MSG_LENGTH];
    struct SyslogNode* next;
    struct SyslogNode* prev;
} SyslogNode;
```

### `SyslogList`
Bağlı listeyi temsil eden yapı:
```c
typedef struct {
    SyslogNode* head;
    SyslogNode* tail;
    size_t count;
} SyslogList;
```

## Fonksiyonlar

### Listeyi Başlatma
```c
void initSyslogList(SyslogList* list);
```
Boş bir `SyslogList` başlatır.

### Yeni Log Düğümü Oluşturma
```c
SyslogNode* createNode(time_t timestamp, const char* facility, 
                      const char* severity, const char* message);
```
Belirtilen parametrelerle yeni bir log düğümü oluşturur.

### Log Ekleme
```c
int appendLog(SyslogList* list, time_t timestamp, const char* facility, 
              const char* severity, const char* message);
```
Listeye yeni bir log kaydı ekler.

### Önem Derecesine Göre Logları Yazdırma
```c
void printLogsBySeverity(const SyslogList* list, const char* severity);
```
Belirtilen önem seviyesindeki tüm logları ekrana yazdırır.

### Tüm Logları Yazdırma
```c
void printAllLogs(const SyslogList* list);
```
Listedeki tüm logları ekrana yazdırır.

### Zaman Aralığına Göre Logları Yazdırma
```c
void printLogsByTimeRange(const SyslogList* list, time_t start, time_t end);
```
Belirtilen zaman aralığındaki logları ekrana yazdırır.

### Listeyi Temizleme
```c
void clearList(SyslogList* list);
```
Listedeki tüm logları siler ve belleği serbest bırakır.

### Eski Logları Silme
```c
void deleteOldLogs(SyslogList* list, time_t cutoff_time);
```
Belirtilen zamandan daha eski olan logları listeden kaldırır.

## Örnek Kullanım

```c
int main() {
    SyslogList logList;
    initSyslogList(&logList);

    time_t current_time = time(NULL);
    appendLog(&logList, current_time, "kernel", "ERROR", "Buffer overflow algılandı");
    appendLog(&logList, current_time + 60, "auth", "WARNING", "Başarısız giriş denemesi");
    appendLog(&logList, current_time + 120, "system", "INFO", "Sistem güncellemesi başlatıldı");

    printf("\nTüm Loglar:\n");
    printAllLogs(&logList);
    
    printf("\nERROR Logları:\n");
    printLogsBySeverity(&logList, "ERROR");
    
    clearList(&logList);
    return 0;
}
```

## Derleme ve Çalıştırma

1. **GCC** kullanarak kodu derleyin:
   ```sh
   gcc -o syslog syslog.c
   ```
2. Çalıştırın:
   ```sh
   ./syslog
   ```

## Lisans
Bu proje **MIT Lisansı** altında lisanslanmıştır.

## Yazar
**[Adınız]** tarafından oluşturulmuştur. Geri bildirim ve katkılarınızı bekliyoruz!

