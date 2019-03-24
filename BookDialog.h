#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>
#include "Book.h"

class BookDialog : public QDialog
{
    Q_OBJECT

public:
    BookDialog(QString modalTitle = "Modal Title", Book* book = nullptr);

private:
    Book* _book;
};

#endif // BOOKDIALOG_H
