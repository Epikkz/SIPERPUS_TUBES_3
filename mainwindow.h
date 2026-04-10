#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Buku {
    int id;
    QString judul;
    QString penulis;

    bool operator<(const Buku& other) const {
        return id < other.id;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnTambah_clicked();
    void on_btnCari_clicked();
    void on_btnEdit_clicked();
    void on_btnHapus_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Buku> daftarBuku;

    void updateTampilanList();
    int binarySearch(int targetId);
    bool isIdExist(int id);
};

#endif // MAINWINDOW_H