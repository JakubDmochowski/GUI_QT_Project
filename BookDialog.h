#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>
#include "Book.h"

class BookDialog : public QDialog
{
    Q_OBJECT

public:
    BookDialog(QString modalTitle = "Modal Title", Book* book = nullptr);

public slots:
    void setTitle(const QString& title);
    void setAuthor(const QString& author);
    void setYear(const QString& year);

private:
    Book* _book;
};

#endif // BOOKDIALOG_H
