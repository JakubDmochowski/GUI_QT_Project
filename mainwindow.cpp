#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QItemSelectionModel>
#include "BookDialog.h"
#include "Book.h"
#include "BookTableModel.h"
#include "BookFilterProxy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _tableModel(new BookTableModel()),
    _filterModel(new BookFilterProxy())
{

    QString dataPath = "C:\\Users\\User\\Documents\\QTProject\\Library.txt";
    //QString dataPath = QFileDialog::getOpenFileName(this, tr("Open Image"), qApp->applicationDirPath());

    QFile file(dataPath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "error", file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        _tableModel->addEntry(Book(in.readLine().split(";")));
    }
    file.close();

    ui->setupUi(this);

    ui->yearInput->setValidator(new QIntValidator());
    _filterModel->setSourceModel(_tableModel);
    connect(ui->titleInput, SIGNAL(textChanged(const QString&)), _filterModel, SLOT(setTitleFilter(const QString&)));
    connect(ui->authorInput, SIGNAL(textChanged(const QString&)), _filterModel, SLOT(setAuthorFilter(const QString&)));
    connect(ui->yearInput, SIGNAL(textChanged(const QString&)), _filterModel, SLOT(setYearFilter(const QString&)));
    connect(ui->addNewBookButton, &QPushButton::pressed, [=]() {
        Book newBook;
        BookDialog* newBookModal = new BookDialog("Add New Book", &newBook);
        if(newBookModal->exec() == QDialog::Accepted) {
            _tableModel->addEntry(newBook);
        }
        ui->LibraryTableView->resizeRowsToContents();
    });
    connect(ui->editBookButton, SIGNAL(pressed()), SLOT(openEditDialog()));
    connect(ui->deleteBookButton, &QPushButton::pressed, [=]() {
        QItemSelectionModel* select = ui->LibraryTableView->selectionModel();
        auto selectedRows = select->selectedRows(0);
        for(auto i = selectedRows.end(); i != selectedRows.begin() ;) {
            _filterModel->removeRow((*--i).row());
        }
        ui->LibraryTableView->clearSelection();
        ui->LibraryTableView->resizeRowsToContents();
    });
    connect(ui->LibraryTableView, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(openEditDialog(const QModelIndex&)));

    _filterModel->sort(0);
    ui->LibraryTableView->setModel(_filterModel);
    ui->LibraryTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->LibraryTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->LibraryTableView->resizeRowsToContents();
}

MainWindow::~MainWindow()
{

    QString dataPath = "C:\\Users\\User\\Documents\\QTProject\\Library.txt";
    //QString dataPath = QFileDialog::getOpenFileName(this, tr("Open Image"), qApp->applicationDirPath());

    QFile file(dataPath);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(nullptr, "error", file.errorString());
    }
    QTextStream out(&file);
    QList<Book> books = _tableModel->getBooks();
    std::for_each(books.begin(), books.end(), [&](Book book){
        out << book.getTitle() << ";" << book.getAuthor() << ";" << book.getYear() << "\r\n";
    });
    file.close();
    delete ui;
}

void MainWindow::openEditDialog ()
{
    QItemSelectionModel* select = ui->LibraryTableView->selectionModel();
    if(select->selectedRows().length() > 1) {
        QMessageBox::information(nullptr, "error", "More than one element is selected.\n Please select just one.");
        return;
    }
    if(select->selectedRows().length() == 0) {
        QMessageBox::information(nullptr, "error", "Nothing is selected.\n Please select an element to edit.");
        return;
    }
    Book editBook;
    editBook.setTitle(_filterModel->data(select->selectedRows(0)[0]).toString());
    editBook.setAuthor(_filterModel->data(select->selectedRows(1)[0]).toString());
    editBook.setYear(_filterModel->data(select->selectedRows(2)[0]).toInt());
    BookDialog* newBookModal = new BookDialog("Edit Book", &editBook);
    if(newBookModal->exec() == QDialog::Accepted) {
        _filterModel->setData(select->selectedRows(0)[0], QVariant(editBook.getTitle()));
        _filterModel->setData(select->selectedRows(1)[0], QVariant(editBook.getAuthor()));
        _filterModel->setData(select->selectedRows(2)[0], QVariant(editBook.getYear()));
    }
    ui->LibraryTableView->resizeRowsToContents();
}

void MainWindow::openEditDialog (const QModelIndex& index)
{
    Q_UNUSED(index)
    QItemSelectionModel* select = ui->LibraryTableView->selectionModel();
    if(select->selectedRows().length() > 1) {
        QMessageBox::information(nullptr, "error", "More than one element is selected.\n Please select just one.");
        return;
    }
    if(select->selectedRows().length() == 0) {
        QMessageBox::information(nullptr, "error", "Nothing is selected.\n Please select an element to edit.");
        return;
    }
    Book editBook;
    editBook.setTitle(_filterModel->data(select->selectedRows(0)[0]).toString());
    editBook.setAuthor(_filterModel->data(select->selectedRows(1)[0]).toString());
    editBook.setYear(_filterModel->data(select->selectedRows(2)[0]).toInt());
    BookDialog* newBookModal = new BookDialog("Edit Book", &editBook);
    if(newBookModal->exec() == QDialog::Accepted) {
        _filterModel->setData(select->selectedRows(0)[0], QVariant(editBook.getTitle()));
        _filterModel->setData(select->selectedRows(1)[0], QVariant(editBook.getAuthor()));
        _filterModel->setData(select->selectedRows(2)[0], QVariant(editBook.getYear()));
    }
    ui->LibraryTableView->resizeRowsToContents();
}
