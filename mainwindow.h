#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    double calculation(QString expression);
    ~MainWindow();

private slots:
    void startcalculate();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_div_clicked();

    void on_pushButton_mul_clicked();

    void on_pushButton_sub_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_mod_clicked();

    void on_pushButton_point_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_clr_clicked();

    void on_pushButton_pow_clicked();

    void on_pushButton_pow2_clicked();

    void on_pushButton_pow3_clicked();

    void on_pushButton_sin_clicked();

    void on_pushButton_cos_clicked();

    void on_pushButton_log_clicked();

    void on_pushButton_ln_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_tan_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_pow1_clicked();

    void on_pushButton_clicked();

    void on_pushButton_bin_clicked();

    void on_pushButton_dec_clicked();

    void on_pushButton_hex_clicked();

    void on_pushButton_oct_clicked();

    void on_pushButton_A_clicked();

    void on_pushButton_B_clicked();

    void on_pushButton_C_clicked();

    void on_pushButton_D_clicked();

    void on_pushButton_E_clicked();

    void on_pushButton_F_clicked();

    void on_pushButton_gcd_clicked();

    void on_pushButton_lcm_clicked();

private:
    Ui::MainWindow *ui;
    QString expression="";
    QString wrong="";
    int queue[10005],end[10005],nextpos;
    double bin(QString expression,int l);
    double hex(QString expression,int l);
    double oct(QString expression,int l);
    double solve(QString expression,int l,int r);
    double getnum(QString expression,int l);
    int gcd(int a,int b);
    int lcm(int a,int b);
    QString clearzero(QString ans);
};

#endif // MAINWINDOW_H
