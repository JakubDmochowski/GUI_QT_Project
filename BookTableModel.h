#ifndef BOOK_TABLE_MODEL_H
#define BOOK_TABLE_MODEL_H

#include <QAbstractTableModel>
#include "Book.h"

class BookTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BookTableModel(QObject *parent = nullptr);
    explicit BookTableModel(QList<Book> books, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int position, int rows, const QModelIndex &index) override;
    bool removeRows(int position, int rows, const QModelIndex &index) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QList<Book> getBooks() const;
    void addEntry(const Book& newItem);

private:
    QList<Book> _books;
};

#endif // BOOK_TABLE_MODEL_H
