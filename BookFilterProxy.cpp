#include "BookFilterProxy.h"

bool BookFilterProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);
    auto title = sourceModel()->data(sourceModel()->index(source_row,0)).toString();
    auto author = sourceModel()->data(sourceModel()->index(source_row,1)).toString();
    auto year = sourceModel()->data(sourceModel()->index(source_row,2)).toString();

    return (_titleFilter.size() == 0 || title.contains(_titleFilter,Qt::CaseSensitivity::CaseInsensitive))
            &&
            (_authorFilter.size() == 0 || author.contains(_authorFilter,Qt::CaseSensitivity::CaseInsensitive))
            &&
            (_yearFilter.size() == 0 || year.contains(_yearFilter));

}

bool BookFilterProxy::filterAcceptsColumn(int, const QModelIndex &) const
{
    return true;
}

void BookFilterProxy::setAuthorFilter(const QString& filter)
{
    _authorFilter = filter;
    invalidateFilter();
}

void BookFilterProxy::setYearFilter(const QString& filter)
{
    _yearFilter = filter;
    invalidateFilter();
}

void BookFilterProxy::setTitleFilter(const QString& filter)
{
    _titleFilter = filter;
    invalidateFilter();
}
