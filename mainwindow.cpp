#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //Menghubungkan Ke Kode C++ Desain UI Nya wak
{
    ui->setupUi(this);

    // Data awal
    daftarBuku.append({101, "Laskar Pelangi", "Andrea Hirata"});
    daftarBuku.append({102, "Bumi Manusia", "Pramoedya Ananta Toer"});
    daftarBuku.append({105, "Kitab Pink", "Jason Ranti"});
    daftarBuku.append({103, "Filosofi Teras", "Henry Manampiring"});
    daftarBuku.append({108, "Pulang", "Leila S. Chudori"});
    daftarBuku.append({107, "Laut Bercerita", "Leila S. Chudori"});
    daftarBuku.append({106, "Cantik Itu Luka", "Eka Kurniawan"});
    daftarBuku.append({104, "Seperti Dendam, Rindu Harus Dibayar Tuntas", "Eka Kurniawan"});
    daftarBuku.append({110, "Kami (Bukan) Sarjana Kertas", "J.S Khairen"});
    daftarBuku.append({112, "Sejarah Filsafat Barat", "Betrand Russel"});
    daftarBuku.append({113, "Catatan Demonstrat", "Soe Hok Gie"});
    daftarBuku.append({115, "Hujan Bulan Juni", "Sapardi Djoko Damono"});

    std::sort(daftarBuku.begin(), daftarBuku.end());
    updateTampilanList(); //Kemudian Memperbaru Tampilannya Disini
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Mengecek apakah ID sudah ada di daftar agar tidak terjadi duplikasi ID
bool MainWindow::isIdExist(int id) {
    for (const auto& b : daftarBuku) {
        if (b.id == id) return true; // Mengembalikan true jika ID ditemukan
    }
    return false; // Mengembalikan false jika ID belum ada
}

// Fungsi untuk menyinkronkan data di memori dengan tampilan ListWidget di UI
void MainWindow::updateTampilanList() {
    ui->listWidget->clear(); // Hapus semua teks lama di list
    for (const auto& b : daftarBuku) {
        // Menggabungkan ID, Judul, dan Penulis menjadi satu baris teks
        ui->listWidget->addItem(
            QString("[%1] %2 - %3")
                .arg(b.id)
                .arg(b.judul)
                .arg(b.penulis)
            );
    }
}

//Fungsi Binary Search Nya Disini
int MainWindow::binarySearch(int targetId) {
    int low = 0; //<<Mencari  Dibawah
    int high = daftarBuku.size() - 1; //<<Mencari Di atas...

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (daftarBuku[mid].id == targetId) return mid; //<<Nah Ketemu
        if (daftarBuku[mid].id < targetId) low = mid + 1; // Jika target lebih besar, cari di belahan kanan
        else high = mid - 1; // Jika target lebih kecil, cari di belahan kiri
    }
    return -1; // Mengembalikan -1 jika ID tidak ditemukan di seluruh daftar
}

//KEMUDIAN KODE CRUD NYA DIBAWAH INI...... :]

// TAMBAH
void MainWindow::on_btnTambah_clicked() {
    int id = ui->inputID->text().toInt();
    QString judul = ui->inputJudul->text();
    QString penulis = ui->inputPenulis->text();

    if (id <= 0 || judul.isEmpty()) {
        QMessageBox::warning(this, "Error", "Data tidak valid!");
        return;
    }

    if (isIdExist(id)) {
        QMessageBox::warning(this, "Error", "ID sudah digunakan!");
        return;
    }

    daftarBuku.append({id, judul, penulis});
    std::sort(daftarBuku.begin(), daftarBuku.end());
    updateTampilanList();

    ui->labelStatus->setText("Buku berhasil ditambahkan");
}

// CARI
void MainWindow::on_btnCari_clicked() {
    int idCari = ui->editCari->text().toInt();
    int index = binarySearch(idCari);

    if (index != -1) {
        ui->labelStatus->setText("Ditemukan: " + daftarBuku[index].judul);
        ui->listWidget->setCurrentRow(index);
    } else {
        ui->labelStatus->setText("ID tidak ditemukan!");
    }
}

// EDIT
void MainWindow::on_btnEdit_clicked() {
    int id = ui->editCari->text().toInt();
    int index = binarySearch(id);

    if (index == -1) {
        QMessageBox::warning(this, "Error", "ID tidak ditemukan!");
        return;
    }

    QString judulBaru = ui->inputJudul->text();
    QString penulisBaru = ui->inputPenulis->text();

    if (judulBaru.isEmpty()) {
        QMessageBox::warning(this, "Error", "Judul tidak boleh kosong!");
        return;
    }

    daftarBuku[index].judul = judulBaru;
    daftarBuku[index].penulis = penulisBaru;

    updateTampilanList();
    ui->listWidget->setCurrentRow(index);

    ui->labelStatus->setText("Data berhasil diupdate");
}

// HAPUS
void MainWindow::on_btnHapus_clicked() {
    int id = ui->editCari->text().toInt();
    int index = binarySearch(id);

    if (index == -1) {
        QMessageBox::warning(this, "Error", "ID tidak ditemukan!");
        return;
    }

    daftarBuku.removeAt(index);
    updateTampilanList();

    ui->labelStatus->setText("Data berhasil dihapus");
}