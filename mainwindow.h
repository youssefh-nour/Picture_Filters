#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Image_Class.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:


    void on_btnLoad_clicked();

    void on_btnSave_clicked();

    void on_btnBW_clicked();

    void on_btnInvert_clicked();

    void on_btnRotate_clicked();
    void on_btnCrop_clicked();

    void on_btnPurple_clicked();

    void on_btnGrayscale_clicked();

    void on_btnFliphor_clicked();

    void on_btn_fliver_clicked();

    void on_btn_ld_clicked();

    void on_btnEdgedetect_clicked();

    void on_btnOldtv_clicked();

    void on_btnNaturalsunlight_clicked();

    void on_btnmerge_clicked();

    void on_btnskew_clicked();

    void on_btnaddframe_clicked();

    void on_btnresize_clicked();

    void on_btnblur_clicked();

    void on_btninfrared_clicked();

private:
    Ui::MainWindow *ui;
    Image currentImage;    // تعريف كائن الصورة
     void updateDisplayedImage();
};

#endif // MAINWINDOW_H