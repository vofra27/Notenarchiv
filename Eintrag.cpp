#include <QSqlRecord>
#include <QString>
#include <QVariant>
#include <utility>

#include "Eintrag.h"

Eintrag::Eintrag() : m_id(-1), m_fach(), m_name(), m_writer(), m_style(), m_comment(), m_new(true), m_changed(false) {
}

Eintrag::Eintrag(const int id, const QString &name, const QString &writer, const QString &style, const QString &comment, const QString& fach) : m_id(id),
    m_fach(fach), m_name(name), m_writer(writer), m_style(style), m_comment(comment), m_new(false), m_changed(false) {
}

Eintrag::Eintrag(const QSqlRecord& rec) : m_id(rec.value("id").toInt()),
    m_fach(rec.value("fach").toString()),
    m_name(rec.value("name").toString()),
    m_writer(rec.value("komponist").toString()),
    m_style(rec.value("richtung").toString()),
    m_comment(rec.value("bemerkung").toString()),
    m_new(false),
    m_changed(false) {
}

QString Eintrag::GetQueryString() const {
    QString q;

    if (m_new)
        q = "INSERT INTO notenarchiv (name, komponist, richtung, bemerkung, fach) VALUES (\"%1\", \"%2\", \"%3\", \"%4\", \"%5\")";
    else {
        q = "UPDATE notenarchiv SET name = \"%1\", komponist = \"%2\", richtung = \"%3\", bemerkung = \"%4\", fach = \"%5\" WHERE id = ";
        q.append(QVariant(m_id).toString());
    }

    q.arg(m_name, m_writer, m_style, m_comment, m_fach);

    return std::move(q);
}

