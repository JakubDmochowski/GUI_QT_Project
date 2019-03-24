#include "BookTableModel.h"
#include "Book.h"

BookTableModel::BookTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

BookTableModel::BookTableModel(QList<Book> books, QObject *parent)
    : QAbstractTableModel(parent)
    , _books(books)
{
}

QVariant BookTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Title");

            case 1:
                return tr("Author");

            case 2:
                return tr("Year");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

int BookTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _books.size();
}

int BookTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant BookTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _books.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &book = _books.at(index.row());

        if (index.column() == 0)
            return book.getTitle();
        else if (index.column() == 1)
            return book.getAuthor();
        else if (index.column() == 2)
            return book.getYear();
    }
    return QVariant();
}

bool BookTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        _books.insert(position, Book());

    endInsertRows();
    return true;
}

bool BookTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        _books.removeAt(position);

    endRemoveRows();
    return true;
}

bool BookTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto book = _books.value(row);

        if (index.column() == 0)
            book.setTitle(value.toString());
        else if (index.column() == 1)
            book.setAuthor(value.toString());
        else if (index.column() == 2)
            book.setYear(value.toInt());
        else
            return false;

        _books.replace(row, book);
        emit dataChanged(index, index, {role});

        return true;
    }

    return false;
}

Qt::ItemFlags BookTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index); // | Qt::ItemIsEditable
}

QList<Book> BookTableModel::getBooks() const
{
    return _books;
}

void BookTableModel::addEntry(const Book& newItem)
{
    beginResetModel();
    _books.append(newItem);
    endResetModel();
}
