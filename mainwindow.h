#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BookTableModel.h"
#include "BookFilterProxy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openEditDialog ();
    void openEditDialog (const QModelIndex&);

private:
    Ui::MainWindow *ui;
    BookTableModel* _tableModel;
    BookFilterProxy* _filterModel;
};

#endif // MAINWINDOW_H
