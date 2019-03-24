#ifndef BOOK_FILTER_PROXY_H
#define BOOK_FILTER_PROXY_H

#include <QSortFilterProxyModel>

class BookFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    BookFilterProxy(QObject * parent = nullptr) : QSortFilterProxyModel(parent) {}

public slots:
    void setTitleFilter(const QString& filter);
    void setAuthorFilter(const QString& filter);
    void setYearFilter(const QString& filter);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    QString _titleFilter;
    QString _authorFilter;
    QString _yearFilter;
};

#endif // BOOK_FILTER_PROXY_H
