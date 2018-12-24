
Özet

Programımız, basit devre elemanlarından oluşan mantıksal bir devreyi kapıların yayılım gecikmeleri de dikkate alarak simule etmektedir. Metin belgesi içerisinde bulunan devre bilgileri giriş, çıkış ve gecikme süreleri dikkate alınarak programa yüklenir. Sonrasında kullanıcıdan alınan komutlara göre devre içinde işlemler yapılır ve devre değişimlere göre simule edilir. Programın çalışması esnasında yapılan her işlem bir log dosyasına yazılır. Lojik devre benzetimi programı, projede istenilen tüm işlemleri doğru bir şekilde yapmaktadır.  


1.  Giriş

Lojik devre benzetimi programı, metin belgesinde bulunan «giriş uçları», «giriş sayısı», «giriş değerleri», «çıkış uçları», «çıkış sayısı», «çıkış değerleri», «kapı isimleri», «kapı girişleri ve çıkışı» ve «gecikme süreleri» bilgilerini alarak devrenin tasarımını yapar. Sonrasında değerlerin yazılı olduğu bir metin belgesini kullarak devredeki uçlarının değerlerini atar. Devrenin bilgilerinin alındığı metin dosyası başka bir devre dosyasını  dahil ediyor ise iki dosya birlikte alınarak devre tasarlanır.

Devre oluşturulduktan sonra devrenin kapıları gecikme sürelerine göre sıralanır. Kullanıcının girdiği komuta göre devre simule edilir. Devrede hangi saniyede hangi değişimin olduğu bir stringe kaydedilir. Kullanıcı ister ise bu değişimleri ekranda listeleyebilir. Kullanıcı listeleme yaptıktan sonra string temizlenir. Girilen her komut ve bu komutların çıktıları bir log dosyasına kaydedilir. Kullanıcı çıkış komutu girene kadar program çalışmaya devam eder.

2.  Temel Bilgiler
Program​ ​ C ​ ​ programlama​ ​ dilinde​ ​ geliştirilmiş​ ​ olup,
tümleşik​ ​ geliştirme​ ​ ortamı​ ​ olarak​ ​ “Clion”
kullanılmıştır. 

                          3.  Tasarım
3.1  Algoritma
Kullanıcıdan tüm komutlar, main içersinde  bir while döngüsü içerisinde alınır. Kullanıcı ‹C› komutu girine kadar döngü çalışmaya devam eder.Devrenin tasarlanması ve değerlerin alınması için metin belgesi gerekir. Bunun için devrenin bilgelerini içerisinde doğru formatta tutan bir metin belgesinin programa yüklenmesi gerekir. Kullanıcı ilk olarak ‹Y› komutunu girmelidir aksi halde girdiği diğer komutlar çalışmayacaktır. Devre yüklendikten sonra değerlerin de ‹I›  komutu ile bir metin dosyasından alınması gerekir. Kullanıcıdan bu komutları sıra ile girmesi beklenir devre oluşturulduktan sonra kullanıcı sırası ile istediği komutu girebilir. 

Kullanıcı herhangi bir giriş ucunda değişim yaptı ise bu uca bağlı tüm kapılar açık duruma getirilir. Ve kapılar gecikme sürelerine göre sıralanır. Sonrasında açık olan kapılar sırası ile çalıştırılır, bir kapı çalıştığında devrede geçen süre çalışan  kapının gecikme süresi kadar arttırılır ve diğer açık kapıların gecikme süreleri bu süre kadar azaltılır. Çalışan kapının çıkış ucunun, giriş olduğu kapılar açık hale getirirlir ve çalışan kapı kapatılır. Bundan sonra kapılar tekrar gecikme sürelerine göre sıralanır ve tüm kapılar kapalı olana kadar kapılar çalıştırılmaya devam edilir.

Yapılan tüm değişimler kapıların çalışması esnasında geçen süre ile birlikte bir string içerisinde tutulur. Kullanıcının bu değişimleri görmek istemesi halinde bu string ekrana bastırılır. Sonrasında geçen süre sıfırlanır ve string temizlenir.
3.2 Kapıların İşlemleri


AND Kapısı

Bir çıkış, iki veya daha fazla giriş hattı bulunur.  Tüm girişlerin değeri "1" olmadan, elde edilen çıkış "1" olmaz. 
"Y = A . B" ile gösterilir


OR Kapısı

Bir çıkış, iki veya daha fazla giriş hattı bulunur. Çıkıştan "1" elde etmek için herhangi bir giriş değerinin "1" olması yeterlidir. Tüm girişlerin "1" olmasının sonucu da yine "1" olarak kabul edilir.
"Y = A + B" ile gösterilir.


NOT Kapısı

Bir çıkış, bir giriş hattı bulunur. Çıkış işareti, giriş işaretinin
tam tersi (devriği) olur. "0" girişli bir devrenin çıkışı "1"
olurken, "1" girişli bir devrenin çıkışı "0" olur. 
" Y = A' " ile  gösterilir.


NAND Kapısı

Bir çıkış, iki veya daha fazla giriş hattı bulunur. "VE" fonksiyonunun "DEĞİL" ile birleşimi olarak düşünebiliriz. Bu doğrultuda "VE" fonksiyonundan elde edilen çıkışların tam tersi elde edilir. Girişlerin hepsi "1" olursa çıkış "0" olur ancak bunun dışındaki tüm durumlarda "1" çıkışı elde edilir.  
" Y = (A . B)' " ile gösterilir. 


NOR Kapısı

Bir çıkış, iki veya daha fazla giriş hattı bulunur. "VEYA" fonksiyonunun "DEĞİL" ile birleşimi olarak düşünebiliriz. Bu yüzden "VEYA" fonksiyonundan elde edilen çıkışların tam tersi elde edilir. Girişlerin hepsi "0" olursa çıkış "1" olur ancak bunun dışındaki tüm durumlarda "0" çıkışı elde edilir.
 " Y = (A + B)' " ile gösterilir.


XOR Kapısı

Bir çıkış, iki veya daha fazla giriş hattı bulunur. Tek bir özellik dışında "VEYA" kapısı ile birebir aynıdır. Bu özellik de; girişlerin hepsi "1" olursa çıkış değeri "1" yerine "0" olur. " Y= A' . B + A . B' " ile ifade edilebilir.











3.3 Kullanılan Fonksiyonlar

int komutcalistir(const char *komut);
//Girilen komutları çalıştırır.

void kapilarisirala();
//Kapıları gecikme sürelerine göre sıralar.

void kapilarisirala2();
//Kapılar çalıştıktan sonra geçen zamanın, gecikme süresinden çıkarılaması sonucu oluşan sürelere göre sıralama yapar.

int giris_var_mi(char giris);
//Devrede giris adında bir giriş olup olmadığını kontrol eder. 

int uc_var_mi(char giris);
//Devrede giris adında bir uc olup olmadığını kontrol eder.

int birdenfazlakontrolu(char *uclar);
//uclar dizisinde birden fazla aynı elemen var mı kontrol eder.

void arabulyaz(char *uclar);
//uclar dizindeki uçların devredeki anlık değerlerini listeler.

void devresimulasyonu(char *degisecekuclar,int durum);
//Yapılan değişiklerden sonra devreyi çalıştırır ve bir string içine yapılan işlemleri kaydeder.

void saniyeayarlama(struct KAPI *kapi);
//Tüm açık durumda olan kapıların gecikme sürelerinden, çalıştırılan kapının gecikme süresi çıkartılır ve devrede geçen zamana çalıştırılan kapının gecikme süresi eklenir.

void OnOff(char isim,int onoff);
//isim değişkeninde tutulan kapı açık veya kapalı duruma getirilir.

int kapiyicalistir(struct KAPI *kapi);
//Degisen giriş değerlerine göre kapının çalışması sonucunda oluşan yeni çıktı belirlenir.

int indexbul(char *dizi,char a);
//dizi dizisinde a karakterinin buluduğu yerin indeksi döndürülür.

void degerdegistir(char isim,int yenideger);
//isim değişkenindeki uçların değerini değiştirir.

void kapisayisibul(FILE *devredosyasi);
//Devre dosyasindaki kapıların sayısını bulur ve kapıları struct KAPI tipindeki kapi değişkene atar.

void includer(char *satir,char dosyaadi[25]);
//Baska dosyanin adını devre dosyasindan alır.

void Ykomutu_satirislem(const char * satir);
//satir stringindeki giris ise giris saysini ve uçlarını, çıkış ise çıkış sayısını ve çıkıs uçlarını Struct DEVRE tipindeki devre değişkenine atar.

void includeYkomutu_satirislem(const char*satir);
//Baska dosya girilmesi halinde realloc kullanarak, Ykomutu _satirislem() fonksiyonundaki atamaları gerçekleştirir.

void includekapisayisibul(FILE *devredosyasi);
//Baska dosya girilmesi halinde realloc kullanarak
kapisayisibul() fonksiyonundaki atamaları gerçekleştirir.
3.3​ ​Akış​ ​Diyagramı
