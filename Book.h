#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QTableWidgetItem>

class Book : public QTableWidgetItem
{
public:
    Book();
    Book(const QTableWidgetItem& other);
    Book(const Book& book);
    Book(const QStringList& source);
    Book(QString title, QString author, int year);
    int getYear() const;
    void setYear(int year);

    QString getTitle() const;
    void setTitle(QString title);

    QString getAuthor() const;
    void setAuthor(QString author);

    bool operator==(const Book &other) const;

private:
    QString _title;
    QString _author;
    int _year;

signals:

public slots:
};

#endif // BOOK_H
