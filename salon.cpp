#include <iostream>
#include <string>

using namespace std;

// Array global untuk menyimpan daftar layanan dan harganya
string layanan[5] = {
    "Haircut",
    "Hairstyling (catok/curl/perm)",
    "Haircolor (any color)",
    "Hair treatment (creambath/smoothing/masking)",
    "Shampoo-blow-dry-style"
};

double harga[5] = {50000, 100000, 200000, 150000, 75000};

// Function Overloading untuk menghitung total tagihan
// 1. Tarif reguler (tanpa diskon member)
double hitungPayment(double hargaLayanan) {
    return hargaLayanan;
}

// 2. Tarif berdiskon member (dengan tambahan persentase diskon)
double hitungPayment(double hargaLayanan, double diskon) {
    return hargaLayanan - (hargaLayanan * diskon);
}

// Function b: Tampilkan Treatment & Pricelist
void tampilkanPricelist() {
    cout << "\n=== DAFTAR TREATMENT & PRICELIST ===" << endl;
    // For Loop untuk menampilkan isi array
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << layanan[i] << " - Rp" << harga[i] << endl;
    }
}

int main() {
    // Deklarasi variabel
    int pilihanMenu, pilihanLayanan;
    string namaPelanggan = "", jadwalReservasi = "";
    bool isMember = false;
    bool adaReservasi = false;
    double hargaLayananTerpilih = 0;
    
    // While Loop agar menu utama terus berulang sampai pengguna keluar
    while (true) {
        // Function a: Menu Utama
        cout << "\n====================================" << endl;
        cout << "      SISTEM RESERVASI SALON       " << endl;
        cout << "====================================" << endl;
        cout << "1. Treatment & Pricelist" << endl;
        cout << "2. Reservasi" << endl;
        cout << "3. Member Discount" << endl;
        cout << "4. Payment & Kembalian" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu (1-5): ";
        
        // Input pilihan pengguna
        if (!(cin >> pilihanMenu)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pilihan tidak valid!" << endl;
            continue; // Continue untuk melompati input yang salah
        }

        // Switch Case untuk navigasi menu utama
        switch (pilihanMenu) {
            case 1:
                tampilkanPricelist();
                break; // Break untuk menghentikan cabang switch-case

            case 2: {
                // Function c: Reservasi
                tampilkanPricelist();
                cout << "\nPilih nomor layanan (1-5): ";
                cin >> pilihanLayanan;

                // Checking range array
                if (pilihanLayanan < 1 || pilihanLayanan > 5) {
                    cout << "Pilihan layanan tidak valid!" << endl;
                    continue;
                }

                cin.ignore(); // Membersihkan buffer input
                cout << "Masukkan Nama Pelanggan: ";
                getline(cin, namaPelanggan);

                cout << "Masukkan Tanggal & Jam (contoh: 30 Okt, 14:00): ";
                getline(cin, jadwalReservasi);

                // Bool untuk ketersediaan slot / status reservasi
                bool slotTersedia = true; 

                // If-Else untuk pengecekan slot reservasi
                if (slotTersedia) {
                    hargaLayananTerpilih = harga[pilihanLayanan - 1];
                    adaReservasi = true;
                    cout << "\n[Sukses] Reservasi berhasil dicatat!" << endl;
                    cout << "Layanan: " << layanan[pilihanLayanan - 1] << endl;
                } else {
                    cout << "Jadwal tidak tersedia." << endl;
                }
                break;
            }

            case 3: {
                // Function d: Member Discount
                if (!adaReservasi) {
                    cout << "\n[!] Silakan lakukan reservasi terlebih dahulu." << endl;
                    break;
                }

                char statusMember;
                cout << "\nApakah pelanggan memiliki Kartu Member? (y/n): ";
                cin >> statusMember;

                // If-Else menentukan status keanggotaan (bool)
                if (statusMember == 'y' || statusMember == 'Y') {
                    isMember = true;
                    cout << "Status Member Aktif! Anda mendapatkan diskon 10%." << endl;
                } else {
                    isMember = false;
                    cout << "Lanjut ke perhitungan harga normal." << endl;
                }
                break;
            }

            case 4: {
                // Function e: Payment dan kembalian
                if (!adaReservasi) {
                    cout << "\n[!] Belum ada transaksi / reservasi yang diproses." << endl;
                    break;
                }

                double totalTagihan;
                // Penerapan Function Overloading berdasarkan status member
                if (isMember) {
                    totalTagihan = hitungPayment(hargaLayananTerpilih, 0.10); // Diskon 10%
                } else {
                    totalTagihan = hitungPayment(hargaLayananTerpilih); // Tanpa diskon
                }

                cout << "\n========== RINCIAN PAYMENT ==========" << endl;
                cout << "Nama Pelanggan : " << namaPelanggan << endl;
                cout << "Jadwal         : " << jadwalReservasi << endl;
                cout << "Total Tagihan  : Rp" << totalTagihan << endl;
                cout << "=====================================" << endl;

                double bayar;
                cout << "Masukkan nominal pembayaran: Rp";
                cin >> bayar;

                // While Loop & If-Else untuk cek kecukupan pembayaran
                while (bayar < totalTagihan) {
                    cout << "Pembayaran kurang! Silakan masukkan nominal yang cukup: Rp";
                    cin >> bayar;
                }

                double kembalian = bayar - totalTagihan;
                cout << "\n------- STRUK PEMBAYARAN -------" << endl;
                cout << "Total Tagihan : Rp" << totalTagihan << endl;
                cout << "Uang Dibayar  : Rp" << bayar << endl;
                cout << "Kembalian     : Rp" << kembalian << endl;
                cout << "--------------------------------" << endl;
                cout << "   Terima Kasih Atas Kunjungan Anda!   " << endl;

                // Reset status setelah pembayaran selesai
                adaReservasi = false;
                isMember = false;
                break;
            }

            case 5:
                cout << "\nProgram selesai. Terima kasih!" << endl;
                return 0; // Menghentikan program

            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    }

}