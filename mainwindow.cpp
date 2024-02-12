#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Selecteaza un folder sursa"), QDir::homePath());
    if (!folderPath.isEmpty()) {

        QDir folderDir(folderPath);
        ui->sourceFolderLineEdit->setText(folderPath);
        QStringList filters;
        filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp";
        QStringList imageFiles = folderDir.entryList(filters);
        ui->listWidget->clear();
        ui->listWidget->addItems(imageFiles);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Selecteaza un folder destinatie"), QDir::homePath());
    if (!folderPath.isEmpty()) {

        QDir folderDir(folderPath);
        ui->destinationFolderLineEdit->setText(folderPath);
        ui->pushButton_3->setEnabled(true);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString sourceFolder = ui->sourceFolderLineEdit->text();
    QString destinationFolder = ui->destinationFolderLineEdit->text();


    QList<QListWidgetItem*> allItems = ui->listWidget->findItems("*", Qt::MatchWildcard);
    for (QListWidgetItem *item : allItems) {
        QString imageName = item->text();
        QString sourceImagePath = sourceFolder + "/" + imageName;
        QString destinationImagePath = destinationFolder + "/" + imageName;

        cv::Mat image = cv::imread(sourceImagePath.toStdString());

        if (!image.empty()) {
            cv::Mat flippedImage;
            cv::flip(image, flippedImage, 1);
            cv::imwrite(destinationImagePath.toStdString(), flippedImage);
        }
    }

    QMessageBox::information(this, tr("Oglindire poze"), tr("Pozele au fost oglindite"));
}




