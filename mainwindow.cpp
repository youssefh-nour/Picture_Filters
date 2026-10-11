#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_btnLoad_clicked()
{

        // فتح نافذة اختيار ملف صورة

        QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp)");

        if (!fileName.isEmpty()) {
            // تحميل الصورة داخل كائن Image_Class
            currentImage.loadNewImage(fileName.toStdString());

            // عرض الصورة على label الأصلية
            QPixmap pix(fileName);
            ui->lblOriginalImage->setPixmap(pix);
        }

}


void MainWindow::on_btnSave_clicked()
{
#include <QMessageBox>


        QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPG (*.jpg);;BMP (*.bmp)");

        if (!fileName.isEmpty()) {
            currentImage.saveImage(fileName.toStdString());
            QMessageBox::information(this, "Success", "Image saved successfully!");
        }

}



void MainWindow::on_btnBW_clicked()
{
    currentImage.invert_img_fil();
    updateDisplayedImage();
}


void MainWindow::on_btnInvert_clicked()
{
    currentImage.ConvertToBlackAndWhite();
    updateDisplayedImage();

}


void MainWindow::on_btnRotate_clicked()
{
    bool ok;
    int degree = QInputDialog::getInt(this, "Rotate Image", "Enter angle (90, 180, 270):", 90, 90, 270, 90, &ok);
    if (ok) {
        currentImage.RotateImage(degree);
        updateDisplayedImage();
    }
}
void MainWindow::on_btnCrop_clicked() {
    bool ok;
    int startX = QInputDialog::getInt(this, "Crop", "Start X:", 0, 0, currentImage.width - 1, 1, &ok);
    int startY = QInputDialog::getInt(this, "Crop", "Start Y:", 0, 0, currentImage.height - 1, 1, &ok);
    int newW  = QInputDialog::getInt(this, "Crop", "New Width:", 100, 1, currentImage.width - startX, 1, &ok);
    int newH  = QInputDialog::getInt(this, "Crop", "New Height:", 100, 1, currentImage.height - startY, 1, &ok);

    if (ok) {
        currentImage.cropimage(startX, startY, newW, newH);
        updateDisplayedImage();
    }
}
void MainWindow::updateDisplayedImage() {
    currentImage.saveImage("temp_gui_display.png");
    QPixmap pix("temp_gui_display.png");
    ui->lblOriginalImage->setPixmap(pix.scaled(ui->lblOriginalImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::on_btnPurple_clicked()
{
    currentImage.purple_tint();
    updateDisplayedImage();
}


void MainWindow::on_btnGrayscale_clicked()
{
    currentImage.grayscale();
    updateDisplayedImage();
}


void MainWindow::on_btnFliphor_clicked()
{
    currentImage.flipHorizontal();
    updateDisplayedImage();
}


void MainWindow::on_btn_fliver_clicked()
{
    currentImage.flipVertical();
    updateDisplayedImage();
}


void MainWindow::on_btn_ld_clicked()
{
    QStringList items;
    items << "Lighten" << "Darken";
    bool ok;
    QString item = QInputDialog::getItem(this, "Lighten / Darken", "Choose mode:", items, 0, false, &ok);
    if (ok && !item.isEmpty()) {
        char choice = (item == "Lighten") ? 'L' : 'D';
        currentImage.lighten_darken_fil(choice);
        updateDisplayedImage();
    }
}


void MainWindow::on_btnEdgedetect_clicked()
{
    currentImage.detectimageedge();
    updateDisplayedImage();
}


void MainWindow::on_btnOldtv_clicked()
{
    currentImage.oldTVFilter();
    updateDisplayedImage();
}


void MainWindow::on_btnNaturalsunlight_clicked()
{
    currentImage.naturalSunlight();
    updateDisplayedImage();
}


void MainWindow::on_btnmerge_clicked()
{
    QString secondFileName = QFileDialog::getOpenFileName(this, "Select Second Image", "", "Image Files (*.png *.jpg *.jpeg *.bmp)");
    if (!secondFileName.isEmpty()) {
        Image secondImage(secondFileName.toStdString());
        currentImage.mergeResize(secondImage);
        updateDisplayedImage();
    }
}


void MainWindow::on_btnskew_clicked()
{
    bool ok;
    double degree = QInputDialog::getDouble(this, "Skew Image", "Enter angle (1 to 89 degrees):", 30.0, 1.0, 89.0, 1, &ok);
    if (ok) {
        currentImage.skewImage(degree);
        updateDisplayedImage();
    }
}


void MainWindow::on_btnaddframe_clicked()
{
    bool ok;
    int thickness = QInputDialog::getInt(this, "Add Frame", "Enter Frame Thickness (pixels):", 15, 1, 100, 1, &ok);
    if (ok) {
        currentImage.AddFancyFrame(thickness, 0, 0, 150); // إطار أزرق أنيق
        updateDisplayedImage();
    }
}


void MainWindow::on_btnresize_clicked()
{
    bool ok1, ok2;
    int newWidth = QInputDialog::getInt(this, "Resize Image", "Enter New Width:", currentImage.width, 10, 5000, 1, &ok1);
    int newHeight = QInputDialog::getInt(this, "Resize Image", "Enter New Height:", currentImage.height, 10, 5000, 1, &ok2);
    if (ok1 && ok2) {
        currentImage.Resize_Filter(newHeight, newWidth);
        updateDisplayedImage();
    }
}


void MainWindow::on_btnblur_clicked()
{
    bool ok;
    int radius = QInputDialog::getInt(this, "Blur Filter", "Enter Blur Radius (1 - 20):", 5, 1, 20, 1, &ok);
    if (ok) {
        currentImage.Blur(radius);
        updateDisplayedImage();
    }
}


void MainWindow::on_btninfrared_clicked()
{
    currentImage.InfraRed();
    updateDisplayedImage();
}
void MainWindow::on_btnoilpainting_clicked()
{
    bool ok;
    int radius = QInputDialog::getInt(this, "Oil Painting Filter", "Enter Radius Intensity (1 - 10):", 3, 1, 10, 1, &ok);
    if (ok) {
        currentImage.OilPainting(radius);
        updateDisplayedImage();
    }
}
