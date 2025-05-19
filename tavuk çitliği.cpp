
#include <iostream> // Giriş çıkış işlemleri için gerekli kütüphane
#include <vector>   // Vektör veri yapısı için gerekli kütüphane
#include <locale.h> // Dil ayarları için gerekli kütüphane
#include <cstdlib>  // Rastgele sayı üretimi için gerekli kütüphane
#include <ctime>    // Zamanı almak için gerekli kütüphane

// TavukCiftligi isim uzayı
namespace TavukCiftligi {

    // Tavuk sınıfı tanımı
    class Tavuk {
    private:
        int yumurtaSayisi; // Tavuk başına üretilen yumurta sayısı
        int gunlukYumurtaSayisi; // Her gün üretilen yumurta sayısı
        int yumurtlamamaSayisi; // Üst üste yumurtlamama sayısı
    public:
        Tavuk() : yumurtaSayisi(0), gunlukYumurtaSayisi(0), yumurtlamamaSayisi(0) {} // Yapıcı fonksiyon, başlangıçta değerleri 0 olarak ayarlar
        void yumurtaUret(int gun) {
            if (gun > 3) { // İlk üç gün yumurta üretimi yok
                int ihtimal = rand() % 3;
                if (ihtimal == 0) {
                    gunlukYumurtaSayisi = 1; // Üçte bir ihtimalle 1 yumurta
                }
                else if (ihtimal == 1) {
                    gunlukYumurtaSayisi = 2; // Üçte bir ihtimalle 2 yumurta
                }
                else {
                    gunlukYumurtaSayisi = 0; // Üçte bir ihtimalle 0 yumurta
                }
                yumurtaSayisi += gunlukYumurtaSayisi; // Toplam yumurta sayısını günceller
            }
            else {
                gunlukYumurtaSayisi = 0; // İlk üç gün yumurta üretimi yok
            }
            if (gunlukYumurtaSayisi == 0 && gun > 3) {
                yumurtlamamaSayisi++; // Yumurtlamadığı gün sayısını artırır
            }
            else {
                yumurtlamamaSayisi = 0; // Yumurtladığında sıfırlar
            }
        }
        int getGunlukYumurtaSayisi() const {
            return gunlukYumurtaSayisi; // Günlük yumurta sayısını döndüren fonksiyon
        }
        int getYumurtaSayisi() const {
            return yumurtaSayisi; // Toplam yumurta sayısını döndüren fonksiyon
        }
        int getYumurtlamamaSayisi() const {
            return yumurtlamamaSayisi; // Yumurtlamama sayısını döndüren fonksiyon
        }
        void reset() {
            yumurtaSayisi = 0; // Tavuk sıfırlanıyor
            yumurtlamamaSayisi = 0;
        }
    };

    // Çiftlik sınıfı tanımı
    class Ciftlik {
    private:
        std::vector<Tavuk> tavuklar; // Çiftlikteki tavukların listesi
    public:
        Ciftlik(int tavukSayisi) { // Yapıcı fonksiyon, başlangıçta belirtilen sayıda tavuk ekler
            for (int i = 0; i < tavukSayisi; ++i) {
                tavuklar.push_back(Tavuk());
            }
        }

        // Simülasyon fonksiyonu
        void simulasyonYap(int gunSayisi, double yemFiyati, double yumurtaFiyati, double tavukAlisFiyati, int& sermaye) {
            srand(static_cast<unsigned>(time(0))); // Rastgele sayı üretimi için tohumlama
            int toplamYumurtaSayisi = 0; // Toplam yumurta sayısını izlemek için değişken
            for (int gun = 1; gun <= gunSayisi; ++gun) {
                int gunlukYumurtaSayisi = 0; // Günlük üretilen yumurta sayısı
                for (auto& tavuk : tavuklar) {
                    tavuk.yumurtaUret(gun);
                    gunlukYumurtaSayisi += tavuk.getGunlukYumurtaSayisi();
                }
                toplamYumurtaSayisi += gunlukYumurtaSayisi; // Toplam yumurta sayısını günceller
                int gunlukYemMaliyeti = static_cast<int>(yemFiyati * tavuklar.size()); // Günlük yem maliyeti hesaplanır
                int gunlukYumurtaGeliri = static_cast<int>(yumurtaFiyati * gunlukYumurtaSayisi); // Günlük yumurta geliri hesaplanır

                sermaye -= gunlukYemMaliyeti; // Sermayeden günlük yem maliyeti düşülür
                sermaye += gunlukYumurtaGeliri; // Sermayeye günlük yumurta geliri eklenir

                // Üç gün üst üste yumurtlamayan tavukları kesip yenileriyle değiştir
                for (auto& tavuk : tavuklar) {
                    if (tavuk.getYumurtlamamaSayisi() >= 3) {
                        sermaye += static_cast<int>(tavukAlisFiyati / 2); // Yarı fiyatına satılıyor
                        tavuk.reset(); // Yeni tavuk yerine ekleniyor
                    }
                }

                // Günlük finansal durum ve toplam yumurta sayısı ekrana yazdırılır
                std::cout << "Gün " << gun << " - Harcanan Para: " << gunlukYemMaliyeti << " - Kazanılan Para: " << gunlukYumurtaGeliri << " - Kalan Sermaye: " << sermaye << " - Günlük Yumurta: " << gunlukYumurtaSayisi << " - Toplam Yumurta: " << toplamYumurtaSayisi << std::endl;
            }
        }

        int getTotalYumurtaSayisi() const {
            int toplam = 0; // Toplam yumurta sayısı
            for (const auto& tavuk : tavuklar) {
                toplam += tavuk.getYumurtaSayisi();
            }
            return toplam; // Toplam yumurta sayısını döndüren fonksiyon
        }
    };

} // namespace TavukCiftligi

using namespace TavukCiftligi;
using namespace std;

int main() {
    setlocale(LC_ALL, "turkish"); // Türkçe karakterleri etkinleştirir
    int sermaye = 100000; // Başlangıç sermayesi
    int tavukSayisi; // Kullanıcıdan alınacak tavuk sayısı
    double yemFiyati = 1.5; // Birim yem fiyatı
    double yumurtaFiyati = 2.0; // Birim yumurta fiyatı
    double tavukAlisFiyati = 10.0; // Tavuk alış fiyatı
    int gunSayisi; // Simülasyon gün sayısı

    cout << "Simulasyon gün sayisini girin: "; // Kullanıcıdan simülasyon gün sayısını isteme
    cin >> gunSayisi;

    cout << "Tavuk sayisini girin: "; // Kullanıcıdan tavuk sayısını isteme
    cin >> tavukSayisi;

    Ciftlik ciftlik(tavukSayisi); // Çiftlik nesnesi oluşturma
    ciftlik.simulasyonYap(gunSayisi, yemFiyati, yumurtaFiyati, tavukAlisFiyati, sermaye); // Simülasyonu gerçekleştirme

    cout << "Simulasyon tamamlandi!" << endl; // Simülasyonun tamamlandığını bildiren mesaj
    cout << "Toplam sermaye: " << sermaye << endl; // Simülasyon sonunda kalan sermaye
    cout << "Toplam yumurta sayisi: " << ciftlik.getTotalYumurtaSayisi() << endl; // Simülasyon sonunda üretilen toplam yumurta sayısı

    return 0; // Programın sonlanması
}
