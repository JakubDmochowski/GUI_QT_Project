#include "Book.h"

Book::Book()
{}

Book::Book(const QTableWidgetItem& other)
    : QTableWidgetItem(other)
{}

Book::Book(const Book& book)
    : QTableWidgetItem()
    , _title(book.getTitle())
    , _author(book.getAuthor())
    , _year(book.getYear())
{}

Book::Book(QString title, QString author, int year)
    : _title(title)
    , _author(author)
    , _year(year)
{}

Book::Book(const QStringList& source )
    : _title(source.at(0))
    , _author(source.at(1))
    , _year(source.at(2).toInt())
{}

bool Book::operator==(const Book &other) const
{
    return _title == other.getTitle() && _author == other.getAuthor() && _year == other.getYear();
}

int Book::getYear() const
{
    return _year;
}

void Book::setYear(int year)
{
    this->_year = year;
}

QString Book::getTitle() const
{
    return _title;
}

void Book::setTitle(QString title)
{
    this->_title = title;
}

QString Book::getAuthor() const
{
    return _author;
}

void Book::setAuthor(QString author)
{
    this->_author = author;
}
