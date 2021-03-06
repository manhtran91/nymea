/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2020, nymea GmbH
* Contact: contact@nymea.io
*
* This file is part of nymea.
* This project including source code and documentation is protected by
* copyright law, and remains the property of nymea GmbH. All rights, including
* reproduction, publication, editing and translation, are reserved. The use of
* this project is subject to the terms of a license agreement to be concluded
* with nymea GmbH in accordance with the terms of use of nymea GmbH, available
* under https://nymea.io/license
*
* GNU General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU General Public License as published by the Free Software
* Foundation, GNU version 3. This project is distributed in the hope that it
* will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <QtTest>

#include "logging/logengine.h"
#include "logging/logvaluetool.h"

using namespace nymeaserver;

class TestLoggingLoading: public QObject
{
    Q_OBJECT
public:
    TestLoggingLoading(QObject* parent = nullptr);

protected slots:
    void initTestCase();

private slots:
    void testLogfileRotation();
};

TestLoggingLoading::TestLoggingLoading(QObject *parent): QObject(parent)
{

    Q_INIT_RESOURCE(loggingloading);

}

void TestLoggingLoading::initTestCase()
{
    // Important for settings
    QCoreApplication::instance()->setOrganizationName("nymea-test");
}

void TestLoggingLoading::testLogfileRotation()
{
    // Create LogEngine with log db from resource file
    QString temporaryDbName = "/tmp/nymea-test/nymead-broken.sqlite";
    QString rotatedDbName = "/tmp/nymea-test/nymead-broken.sqlite.1";

    // Remove the files if there are some left
    if (QFile::exists(temporaryDbName))
        QVERIFY(QFile(temporaryDbName).remove());

    if (QFile::exists(rotatedDbName))
        QVERIFY(QFile(rotatedDbName).remove());

    // Copy broken log db from resources to default settings path and set permissions
    qDebug() << "Copy broken log db to" << temporaryDbName;
    QVERIFY(QFile::copy(":/nymead-broken.sqlite", temporaryDbName));
    QVERIFY(QFile::setPermissions(temporaryDbName, QFile::ReadOwner | QFile::WriteOwner | QFile::ReadGroup | QFile::ReadOther));

    QVERIFY(!QFile::exists(rotatedDbName));
    LogEngine *logEngine = new LogEngine("QSQLITE", temporaryDbName);
    QVERIFY(QFile::exists(rotatedDbName));

    delete logEngine;

    QVERIFY(QFile(temporaryDbName).remove());
    QVERIFY(QFile(rotatedDbName).remove());
}

#include "testloggingloading.moc"
QTEST_MAIN(TestLoggingLoading)
