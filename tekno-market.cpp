/****************************************************************************
**                  SAKARYA ÜNİVERSİTESİ                                   **
**                   BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ             **
**                  BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ                         **
**                        PROGRAMLAMAYA GİRİŞİ DERSİ                       **
**                                                                         **
**              ÖDEV NUMARASI…...:1                                        **
**              ÖĞRENCİ ADI......:Burak Kahveci                            **
**              ÖĞRENCİ NUMARASI.:b241210084                               **
**              DERS GRUBU.......:A                                        **
*****************************************************************************/
#include <iostream> // Standart giriş/çıkış işlemleri için gerekli
#include <string>   // Yazı formatındaki veriler için gerekli
#include <cstdlib>  // Rastgele sayı üretimi için gerekli
#include <iomanip>  // setprecision için gerekli
#include <ctime>    // Rastgele sayılar için gerekli
using namespace std;

// Ürünleri temsil eden yapı (struct)
struct Urun {
    string isim;               // Ürün adı
    float maliyet;             // Ürün maliyeti
    float satisFiyati;         // Ürün satış fiyatı
    float satisMiktarlari[12]; // 12 ay için satış miktarları
};

int main() {
    setlocale(LC_ALL, "Turkish"); // Türkçe harf kullanımını etkinleştirme için gerekli
    srand(time(0)); // Rastgele sayı üretimini başlatmak için seed değeri belirler

    // Ay isimlerini içeren dizi
    string aylar[] = { "Ocak", "Şubat", "Mart", "Nisan", "Mayıs", "Haziran", "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık" };

    // Ürünlerin isimlerini ve maliyetlerini içeren diziler
    Urun urunler[20] = {
        {"mouse", 18.0F, 0}, {"mikrofon", 28.0F, 0}, {"cep telefonu", 35.0F, 0}, {"masaustu bilgisayar", 50.0F, 0},
        {"laptop", 35.0F, 0}, {"kulaklik", 24.5F, 0}, {"hoparlor", 24.0F, 0}, {"televizyon", 70.0F, 0},
        {"tablet", 20.0F, 0}, {"oyun konsolu", 40.0F, 0}, {"akıllı saat", 28.0F, 0}, {"kamera", 50.0F, 0},
        {"klavye", 15.0F, 0}, {"yazıcı", 60.0F, 0}, {"drone", 70.0F, 0}, {"router", 20.0F, 0},
        {"güvenlik kamerası", 45.0F, 0}, {"projeksiyon", 55.0F, 0}, {"monitör", 32.0F, 0}, {"dizüstü standı", 10.0F, 0}
    };

    // Sabit maliyetler (aylık)
    float elektrikMaliyeti = 500.0F; // Elektrik maliyeti
    float suMaliyeti = 300.0F;       // Su maliyeti
    float dogalGazMaliyeti = 600.0F; // Doğal gaz maliyeti
    float personelMaliyeti = 8000.0F;// Personel maliyeti

    // Kullanıcıdan zam oranlarını ve sıklığını al
    float zamOraniMaliyet;
    int zamSiklik;
    cout << "Ürün maliyetlerine yapılacak zam oranını giriniz (%): ";
    cin >> zamOraniMaliyet;
    zamOraniMaliyet = 1 + zamOraniMaliyet / 100; // Yüzdelik oranı çarpan olarak hesapla

    cout << "Zamların kaç ayda bir yapılacağını giriniz: ";
    cin >> zamSiklik;

    // Satış fiyatlarını belirle
    for (int urun = 0; urun < 20; urun++) {
        float minZam = urunler[urun].maliyet * 0.30F; // Minimum %30 zam
        float maxZam = urunler[urun].maliyet * 0.50F; // Maksimum %50 zam
        urunler[urun].satisFiyati = urunler[urun].maliyet + (minZam + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxZam - minZam)))); // Rastgele bir zam ekle
    }

    // Rastgele satış miktarlarını doldur
    for (int ay = 0; ay < 12; ay++) { // 12 ay için döngü
        for (int urun = 0; urun < 20; urun++) { // 20 ürün için döngü
            // Satış miktarını belirle 2000 ile 3000 arası rastgele sayı
            urunler[urun].satisMiktarlari[ay] = (rand() % 1000 + 2000);

            // Belirtilen aylarda zam yap
            if (ay != 0 && ay % zamSiklik == 0) {
                urunler[urun].maliyet *= zamOraniMaliyet; // Kullanıcı belirlediği zam oranını uygula
            }
        }
    }

    // Her ay için satış ve maliyetleri göster
    cout << fixed << setprecision(2); // Ondalık basamakları ayarlamak için fixed ve setprecision kullanılır
    for (int ay = 0; ay < 12; ay++) { // 12 ay için döngü
        cout << aylar[ay] << " Ayı Satış ve Maliyetleri: " << endl;
        float toplamSatis = 0;    // Toplam satış miktarını tutan değişken
        float toplamMaliyet = 0;  // Toplam maliyeti tutan değişken

        // Her ürün için satış ve maliyet bilgilerini yazdır
        for (int urun = 0; urun < 20; urun++) { // 20 ürün için döngü
            cout << urunler[urun].isim << ": Satış = " << urunler[urun].satisMiktarlari[ay] * urunler[urun].satisFiyati << " TL, Maliyet = " << urunler[urun].maliyet << " TL" << endl;
            toplamSatis += urunler[urun].satisMiktarlari[ay] * urunler[urun].satisFiyati; // Toplam satış hesapla
            toplamMaliyet += urunler[urun].maliyet * urunler[urun].satisMiktarlari[ay];   // Toplam maliyet hesapla
        }
        // Sabit maliyetleri toplam maliyete ekle
        toplamMaliyet += (elektrikMaliyeti + suMaliyeti + dogalGazMaliyeti + personelMaliyeti);

        // Kar veya zararı hesapla
        float karZarar = toplamSatis - toplamMaliyet;
        cout << "Toplam Satış: " << toplamSatis << " TL" << endl;
        cout << "Toplam Maliyet: " << toplamMaliyet << " TL" << endl;
        cout << "Net Kar: " << karZarar << " TL" << endl;
        cout << "------------------------------" << endl;
    }

    return 0; // Programın başarılı şekilde sona erdiğini belirtir
}
