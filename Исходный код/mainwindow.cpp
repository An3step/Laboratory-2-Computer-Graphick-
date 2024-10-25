#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Обрабатыватель");
    ui->ReChoice->setEnabled(false);
    //ui->gridLayout->set
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->
            setHorizontalHeaderItem(0,
                                    new QTableWidgetItem("Название"));
            ui->tableWidget->
                    setHorizontalHeaderItem(1,
                                            new QTableWidgetItem("Расширение"));
            ui->tableWidget->
                    setHorizontalHeaderItem(2,
                                            new QTableWidgetItem("Размер"));
            ui->tableWidget->
                    setHorizontalHeaderItem(3,
                                            new QTableWidgetItem("Разрешение"));
            ui->tableWidget->
                    setHorizontalHeaderItem(4,
                                            new QTableWidgetItem("Глубина цвета"));
            ui->tableWidget->
                    setHorizontalHeaderItem(5,
                                            new QTableWidgetItem("Сжатие"));

    //ui->tableView->add
//    QImageWriter i("C:/Games/Qt/FolderImage/Fig1.15(b).bmp");
//    QImageReader imageR("C:/Games/Qt/FolderImage/Fig1.15(b).bmp");
//    //i.setDevice(nullptr);
//    i.setProgressiveScanWrite(true);
//    if(i.canWrite())
//    {
//        //i.setCompression(1);
//        QImage image;
//        image = imageR.read();
//        imageR.quality();
//        if(image.isNull())
//        {
//            ui->InfoImage->setText("no");
//            return;
//        }
//        QPixmap pixmap;
//        pixmap.convertFromImage(image);
//        //ui->InfoImage->setPixmap(pixmap);
//        ui->InfoImage->setText(QString::number(i.compression()));
//    }
//    else
//    {
//        ui->InfoImage->setText("cant read");
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ChoiceFolder_clicked()
{
    ui->ChoiceFolder->setEnabled(false);
    ui->ReChoice->setEnabled(true);
    images.clear();
    QString path = QFileDialog::getExistingDirectory();
    ScanDirectory(path);
    ShowTable();
}

void MainWindow::ScanDirectory(QString path)
{
    QDir d(path);
    QStringList files = d.entryList();
    QString s = "";
    int i = 0;
    for(QString fileName: files)
    {
        if(i <= 1)
        {
            i++;
            continue;
        }
       // s.append(path + '/' + QDir::separator() + '\n');
        QFileInfo file(path + QDir::separator() + fileName);
        if(file.isDir())
        {
            ScanDirectory(path + QDir::separator() + fileName);
        }
        else
        {
            if(file.suffix() == "png"
                    || file.suffix() == "jpg"
                    || file.suffix() == "gif"
                    || file.suffix() == "tif"
                    || file.suffix() == "bmp"
                    || file.suffix() == "pcx"
                    || file.suffix() == "BMP")
            {
                images.push_back(path + QDir::separator() +fileName);
            }
        }
    }
}

void MainWindow::ShowTable()
{
    ui->tableWidget->setRowCount(images.size());
    for(imagenumber = 0; imagenumber < images.size(); imagenumber++)
    {
        QImage pixmap(images[imagenumber]);
        if(pixmap.isNull())
        {
            text = "Null Image";
            for(int i = 0; i < 6; i++)
            {
                ui->tableWidget->setItem(imagenumber, i, new QTableWidgetItem("Null Image"));
            }
        }
        else
        {
            QString name = images[imagenumber]
                    .mid(images[imagenumber]
                             .lastIndexOf(QDir::separator()));
            name[0] = ' ';
            QString sizepixmap = "";
            for(int i = 1; i < name.lastIndexOf('.'); i++)
            {
                sizepixmap.append(name[i]);
            }
            ui->tableWidget->setItem(imagenumber, 0,
                                     new QTableWidgetItem(sizepixmap));
            sizepixmap = "";
            for(int i = name.lastIndexOf('.'); i < name.size(); i++)
            {
                sizepixmap.append(name[i]);
            }
            QString form = sizepixmap;
            ui->tableWidget->setItem(imagenumber, 1,
                                     new QTableWidgetItem(sizepixmap));
            sizepixmap = "";
            sizepixmap += QString::number(pixmap.width());
            sizepixmap += " на ";
            sizepixmap += QString::number(pixmap.height());
            ui->tableWidget->setItem(imagenumber, 2,
                                     new QTableWidgetItem(sizepixmap));
            sizepixmap = "";
            sizepixmap += QString::number(pixmap.physicalDpiX());
            sizepixmap += " на ";
            sizepixmap += QString::number(pixmap.physicalDpiY());
            ui->tableWidget->setItem(imagenumber, 3,
                                     new QTableWidgetItem(sizepixmap));
            ui->tableWidget->setItem(imagenumber, 4,
                                     new QTableWidgetItem(QString::number(pixmap.bitPlaneCount())));
            if(form == ".BMP" || form == ".bmp"
                    || form == ".tif")
            {
                ui->tableWidget->setItem(imagenumber, 5,
                                         new QTableWidgetItem("Не задано"));
            }
            else
            {
                double compression;
                double s = QFileInfo(images[imagenumber]).size();
                if(s == 0)
                {
                    ui->tableWidget->setItem(imagenumber, 5,
                                             new QTableWidgetItem(-1));
                    continue;
                }
                QByteArray byteArray;
                QBuffer buffer(&byteArray);
                buffer.open(QIODevice::WriteOnly);
                pixmap.save(&buffer, "JPEG", 100);
                compression = double(byteArray.size())/s;
                sizepixmap = QString::number(compression);
                ui->tableWidget->setItem(imagenumber, 5,
                                     new QTableWidgetItem(sizepixmap));
            }
        }
        //ui->InfoImage->setText(text);
    }
}

void MainWindow::on_ReChoice_clicked()
{
    images.clear();
    ui->tableWidget->setRowCount(0);
    ui->ChoiceFolder->setEnabled(true);
    ui->ReChoice->setEnabled(false);
}
