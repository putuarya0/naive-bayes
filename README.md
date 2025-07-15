📌 Deskripsi
Program ini adalah implementasi sederhana dari algoritma Naive Bayes untuk klasifikasi email spam berbasis 10 fitur (kata-kata tertentu yang sering muncul dalam spam). Data dibaca dari file CSV (spambase_10features.csv) yang memuat nilai-nilai fitur dan label (0 untuk bukan spam, 1 untuk spam).

🔧 Fitur Program
1. Membaca data email dari file CSV.
2. Menyimpan data dalam linked list.
3. Menampilkan seluruh data email beserta labelnya.
4. Menghitung probabilitas prior untuk masing-masing label (p(0), p(1)).
5. Memprediksi apakah data uji termasuk spam atau bukan berdasarkan pendekatan jarak ke mean dari masing-masing kelas.

📁 Struktur Data
Menggunakan struct EmailNode untuk menyimpan:
1. float fitur[10]: 10 fitur input.
2. int label: Label spam atau bukan.
3. Pointer next untuk linked list.

📊 Dataset Input

File CSV dengan format:
fitur0, fitur1, ..., fitur9, label
(baris pertama sebagai header akan diabaikan)

📈 Algoritma Prediksi
1. Hitung rata-rata fitur untuk masing-masing label.
2. Hitung jarak absolut antara fitur uji dan rata-rata tiap label.
3. Skor label dihitung berdasarkan jumlah fitur yang lebih dekat ke masing-masing rata-rata label.
4. Skor tertinggi menentukan prediksi label.

🧪 Contoh Penggunaan

Program akan menanyakan input seperti:

Masukkan fitur uji:
Fitur[0] = 0.21
Fitur[1] = 0.12
...
Fitur[9] = 0.05

Output:
Skor 0: 7.00
Skor 1: 3.00
Prediksi label: 0

📦 Cara Kompilasi dan Jalankan
gcc Naive-bayes.c -o naivebayes
./naivebayes
Pastikan file CSV tersedia di direktori yang sesuai dan memiliki nama spambase_10features.csv.

