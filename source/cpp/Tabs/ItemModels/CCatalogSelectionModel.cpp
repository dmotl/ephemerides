#include "CCatalogSelectionModel.h"

#include "CCatalogList.h"
#include "CCatalog.h"

CCatalogSelectionModel::CCatalogSelectionModel(CCatalogList* data, QObject* parent) : QAbstractTableModel(parent), m_data(data)
{
    if (m_data) {
        for (int i = 0; i < m_data->count(); i++) {
            CCatalog* c = m_data->at(i);
            assert(c != nullptr);
            QString key = c->name();
            int insertPos = 0;
            while (insertPos < m_rows.size()) {
                int cmp = m_rows[insertPos]->name.compare(key);
                if (cmp == 0) {
                    insertPos = -1;
                    break;
                }
                if (cmp > 0)
                    break;
                insertPos++;
            }
            if (insertPos >= 0) {
                tCatalog* row = new tCatalog();
                row->name = key;
                m_rows.insert(insertPos, row);
            }
        }
    }
}

CCatalogSelectionModel::~CCatalogSelectionModel()
{
	qDeleteAll(m_rows);
}

void CCatalogSelectionModel::update()
{
}

void CCatalogSelectionModel::clearSelection()
{
    bool modified = false;
    for (int i = 0; i < m_rows.count(); i++) {
        assert(m_rows[i] != nullptr);
        if (m_rows[i]->checked) {
            m_rows[i]->checked = false;
            modified = true;
        }
    }
    if (modified)
        emit dataChanged(index(0, 0), index(m_rows.count() - 1, 0), QList<int>() << Qt::CheckStateRole);
}

void CCatalogSelectionModel::setSelection(const QStringList& catalogList)
{
    bool modified = false;
    for (int i = 0; i < m_rows.count(); i++) {
        assert(m_rows[i] != nullptr);
        bool select = catalogList.contains(m_rows[i]->name);
        if (m_rows[i]->checked != select) {
            m_rows[i]->checked = select;
            modified = true;
        }
    }
    if (modified)
        emit dataChanged(index(0, 0), index(m_rows.count() - 1, 0), QList<int>() << Qt::CheckStateRole);
}

void CCatalogSelectionModel::setSelection(const QString& catalogName, bool select)
{
    for (int i = 0; i < m_rows.count(); i++) {
        assert(m_rows[i] != nullptr);
        if (m_rows[i]->name.compare(catalogName)) {
            if (m_rows[i]->checked != select) {
                m_rows[i]->checked = select;
                emit dataChanged(index(i, 0), index(i, 0), QList<int>() << Qt::CheckStateRole);
            }
            break;
        }
    }
}

QStringList CCatalogSelectionModel::getSelection(void) const
{
    QStringList retval;
    if (m_data) {
        for (int i = 0; i < m_data->count(); i++) {
            CCatalog* c = m_data->at(i);
            assert(c != nullptr);
            QString catalogName = c->name();
            for (int j = 0; j < m_rows.count(); j++) {
                assert(m_rows[j] != nullptr);
                if (m_rows[j]->name.compare(catalogName)) {
                    if (m_rows[j]->checked)
                        retval.append(catalogName);
                    break;
                }
            }
        }
    }
    return retval;

}

QList<CCatalog*> CCatalogSelectionModel::selectedList(void) const
{
    QList<CCatalog*> retval;
    if (m_data) {
        for (int i = 0; i < m_data->count(); i++) {
            CCatalog* c = m_data->at(i);
            assert(c != nullptr);
            QString catalogName = c->name();
            for (int j = 0; j < m_rows.count(); j++) {
                assert(m_rows[j] != nullptr);
                if (m_rows[j]->name.compare(catalogName)) {
                    if (m_rows[j]->checked)
                        retval.append(c);
                    break;
                }
            }
        }
    }
    return retval;
}

bool CCatalogSelectionModel::isSelected(const QString& catalogName)
{
    for (int j = 0; j < m_rows.count(); j++) {
        assert(m_rows[j] != nullptr);
        if (m_rows[j]->name.compare(catalogName))
            return m_rows[j]->checked;
    }
    return false;
}

int CCatalogSelectionModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return m_rows.count();
    return 0;
}

Qt::ItemFlags CCatalogSelectionModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

QVariant CCatalogSelectionModel::data(const QModelIndex& index, int role) const
{
    int row = index.row(), col = index.column();
    if (row >= 0 && row < m_rows.count() && col == 0) {
        tCatalog* c = m_rows[row];
        assert(c != nullptr);
        switch (role)
        {
        case Qt::DisplayRole:
            return c->name;
        case Qt::CheckStateRole:
            return c->checked ? Qt::Checked : Qt::Unchecked;
        }
    }
    return QVariant();
}

bool CCatalogSelectionModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row(), col = index.column();
    if (row >= 0 && row < m_rows.count() && col == 0 && role == Qt::CheckStateRole) {
        tCatalog* c = m_rows[row];
        bool select = value.toInt() != Qt::Unchecked;
        if (c->checked != select) {
            c->checked = select;
            dataChanged(index, index, QList<int>() << Qt::CheckStateRole);
            return true;
        }
    }
    return false;
}

QString CCatalogSelectionModel::indexToName(const QModelIndex& index) const
{
    int row = index.row();
    if (row >= 0 && row < m_rows.count()) 
        return m_rows[row]->name;
    return QString();
}

QModelIndex CCatalogSelectionModel::nameToIndex(const QString& catalogName, int col) const
{
    for (int j = 0; j < m_rows.count(); j++) {
        assert(m_rows[j] != nullptr);
        if (m_rows[j]->name.compare(catalogName))
            return index(j, col);
    }
    return QModelIndex();
}
