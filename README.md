*This project has been created as part of the 42 curriculum by iekmen.*

# Minitalk

## Description

**Minitalk**, UNIX sinyallerini kullanarak iki süreç arasında iletişim kurulmasını sağlayan küçük bir **client-server** uygulamasıdır. Bu proje, süreçler arası iletişimi (Interprocess Communication - IPC) düşük seviyede anlamayı amaçlar.

Projede iki ayrı program bulunmaktadır:

- **Server**: Gelen sinyalleri dinler ve gönderilen mesajı yeniden oluşturur.
- **Client**: Server’a bir mesaj gönderir.

Client programı, gönderilecek mesajı **bit bit** parçalara ayırır ve her biti bir UNIX sinyali ile server’a iletir.

Kullanılan sinyaller:

- `SIGUSR1` → **1 bitini temsil eder**
- `SIGUSR2` → **0 bitini temsil eder**

Server bu sinyalleri alarak bitleri tekrar birleştirir ve karakterleri oluşturup ekrana yazdırır.

Bu proje sayesinde aşağıdaki konular öğrenilir:

- UNIX sinyalleri
- Süreçler arası iletişim (IPC)
- Bit işlemleri (bitwise operations)
- Sistem çağrıları (`kill`, `signal`, `pause`)
- Client-server mimarisi

---

## Instructions

### Compilation

Projeyi klonladıktan sonra aşağıdaki komut ile derleyebilirsiniz:

```bash
git clone <repo-url>
cd minitalk
make
```
## RESOURCES

- [UNIX Sinyal Yönetimi (man sigaction) ](https://man7.org/linux/man-pages/man2/sigaction.2.html): Güvenilir sinyal yönetimi için resmi dokümantasyon.
- [C Dilinde Bitwise Operatörleri](https://www.geeksforgeeks.org/c/bitwise-operators-in-c-cpp/) : Veri göndermek için bitlerin nasıl manipüle edileceğine dair bir rehber.
- [Süreçler Arası İletişim (IPC)](https://en.wikipedia.org/wiki/Inter-process_communication) : Farklı süreçlerin nasıl veri alışverişinde bulunduğuna dair genel bakış.


## AI USAGE

Bu projede Yapay Zeka (Gemini/ChatGPT), aşağıdaki görevler için kullanılmıştır:

- Mimari Tasarım: Karakterlerin iletim için 8 bitlik dizilere bölünmesi mantığının kurulmasına yardımcı olunması.

- Dokümantasyon: Bu README.md dosyasının teknik dilinin müfredat standartlarını karşılayacak şekilde yapılandırılması ve geliştirilmesi.

- Hata Giderme: Sinyal kaybıyla ilgili potansiyel sorunların belirlenmesi ve daha iyi güvenilirlik için ``` sigaction ``` bayraklarının (örneğin SA_SIGINFO) kullanımı konusunda öneriler alınması.
