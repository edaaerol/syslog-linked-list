# Syslog Log Yönetim Sistemi

## Proje Açıklaması
Bu proje, Linux işletim sisteminde sistem günlüklerini (syslog) yönetmek ve işlemek amacıyla geliştirilmiştir. Log kayıtlarını verimli bir şekilde saklamak, filtrelemek ve yönetmek için çift yönlü bağlı liste (doubly linked list) veri yapısı kullanılmaktadır. Uygulama, belirli kriterlere göre logları listeleyebilir, eski kayıtları silebilir ve tüm logları temizleyebilir.

## Özellikler

- **Dinamik Bellek Yönetimi:** Log girişleri dinamik olarak tahsis edilir ve bellek sızıntılarını önlemek için serbest bırakılır.
- **Çift Yönlü Bağlı Liste Kullanımı:** Loglar, çift yönlü bağlı liste yapısı kullanılarak saklanır.
- **Zaman Damgası Desteği:** Her log girişine otomatik olarak bir zaman damgası eklenir.
- **Farklı Log Seviyeleri:** "INFO", "WARNING", "ERROR" gibi log seviyeleri ile giriş yapılabilir.
- **Kolay Kullanım:** Yeni log ekleme, logları yazdırma ve temizleme işlemleri için fonksiyonlar sağlanmıştır.
- **Log Filtreleme:** Belirli kriterlere göre logları filtreleme özelliği.
- **Eski Kayıtları Silme:** Belirli bir zamandan önce oluşturulmuş logları temizleme.

## Kullanım

### Derleme ve Çalıştırma

Bu kodu çalıştırmak için bir C derleyicisine ihtiyacınız vardır. GCC kullanarak şu şekilde derleyebilirsiniz:

```sh
gcc syslog_linked_list.c -o syslog_linked_list
./syslog_linked_list
```

### Örnek Çıktı

Kod çalıştırıldığında aşağıdaki gibi bir çıktı üretilecektir:

```
Tüm Loglar:
------------------------
[2025-02-19 12:30:45] WARNING: Disk alanı azalıyor
[2025-02-19 12:30:45] INFO: Uygulama başlatıldı
[2025-02-19 12:30:45] ERROR: Sistem hatası oluştu
```

## Fonksiyonlar

`void initLogList(LogList* list)`: Log listesini başlatır.

`void addLog(LogList* list, const char* severity, const char* message)`: Yeni bir log girişini listeye ekler.

`void printLogs(LogList* list)`: Tüm log girişlerini ekrana yazdırır.

`void filterLogs(LogList* list, const char* severity)`: Belirtilen şiddet seviyesine göre logları filtreler ve listeler.

`void deleteOldLogs(LogList* list, time_t threshold)`: Belirtilen zamandan eski olan logları siler.

`void clearList(LogList* list)`: Bellekteki log girişlerini temizler.

## Lisans

Bu proje MIT Lisansı ile lisanslanmıştır. Daha fazla bilgi için `LICENSE` dosyasına bakabilirsiniz.

