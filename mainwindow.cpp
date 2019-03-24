#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include "BookDialog.h"
#include "Book.h"
#include "BookTableModel.h"
#include "BookFilterProxy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    BookTableModel *tableModel = new BookTableModel();
    BookFilterProxy* filterModel = new BookFilterProxy();

    QString dataPath = "C:\\Users\\User\\Documents\\QTProject\\Library.txt";
    //QString dataPath = QFileDialog::getOpenFileName(this, tr("Open Image"), qApp->applicationDirPath());

    QFile file(dataPath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "error", file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        tableModel->addEntry(Book(in.readLine().split(";")));
    }
    file.close();

    ui->setupUi(this);

    ui->yearInput->setValidator(new QIntValidator());
    filterModel->setSourceModel(tableModel);
    connect(ui->titleInput, SIGNAL(textChanged(const QString&)), filterModel, SLOT(setTitleFilter(const QString&)));
    connect(ui->authorInput, SIGNAL(textChanged(const QString&)), filterModel, SLOT(setAuthorFilter(const QString&)));
    connect(ui->yearInput, SIGNAL(textChanged(const QString&)), filterModel, SLOT(setYearFilter(const QString&)));
    connect(ui->addNewBookButton, &QPushButton::pressed, [=]() {
        Book newBook;
        BookDialog* newBookModal = new BookDialog("Add New Book",&newBook);
        if(newBookModal->exec() == QDialog::Accepted) {
            tableModel->addEntry(newBook);
        }
    });

    filterModel->sort(0);
    ui->LibraryTableView->setModel(filterModel);
    ui->LibraryTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->LibraryTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->LibraryTableView->resizeRowsToContents();


    //Write data to the file
    //UNTESTED
//    if(!file.open(QIODevice::WriteOnly)) {
//        QMessageBox::information(nullptr, "error", file.errorString());
//    }
//    QTextStream out(&file);
//    QList<Book> books = tableModel->getBooks();
//    std::for_each(books.begin(), books.end(), [&](Book book){
//        out << book.getTitle() << ";" << book.getAuthor() << ";" << book.getYear() << "\r\n";
//    });
//    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
