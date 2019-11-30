/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2016 Simon Stürz <simon.stuerz@guh.io>                   *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  nymea is free software: you can redistribute it and/or modify          *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 2 of the License.                *
 *                                                                         *
 *  nymea is distributed in the hope that it will be useful,               *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with nymea. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TIMEEVENTITEM_H
#define TIMEEVENTITEM_H

#include <QDateTime>
#include <QVariant>

#include "repeatingoption.h"

class TimeEventItem
{
    Q_GADGET
    Q_PROPERTY(QDateTime datetime READ dateTime WRITE setDateTime USER true)
    Q_PROPERTY(QTime time READ time WRITE setTime USER true)
    Q_PROPERTY(RepeatingOption repeating READ repeatingOption WRITE setRepeatingOption USER true)
public:
    TimeEventItem();

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &dateTime);

    QTime time() const;
    void setTime(const QTime &time);

    RepeatingOption repeatingOption() const;
    void setRepeatingOption(const RepeatingOption &repeatingOption);

    // TODO spectioalDayTime

    bool isValid() const;

    bool evaluate(const QDateTime &lastEvaluationTime, const QDateTime &dateTime) const;

private:
    QDateTime m_dateTime;
    QTime m_time;

    RepeatingOption m_repeatingOption;
};
Q_DECLARE_METATYPE(TimeEventItem)

class TimeEventItems: public QList<TimeEventItem>
{
    Q_GADGET
    Q_PROPERTY(int count READ count)
public:
    TimeEventItems();
    TimeEventItems(const QList<TimeEventItem> &other);
    Q_INVOKABLE QVariant get(int index) const;
    Q_INVOKABLE void put(const QVariant &variant);
};
Q_DECLARE_METATYPE(TimeEventItems)

QDebug operator<<(QDebug dbg, const TimeEventItem &timeEventItem);


#endif // TIMEEVENTITEM_H