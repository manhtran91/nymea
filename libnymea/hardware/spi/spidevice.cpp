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
* GNU Lesser General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU Lesser General Public License as published by the Free
* Software Foundation; version 3. This project is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "spidevice.h"
#include "spimanager.h"

#include <QDebug>

/*! \fn QByteArray SPIDevice::readData(int fileDescriptor);
        Reimplement this when implementing reading communication with an SPI device.
        This method will be called repeatedly as soon as the I2CManager is instructed to start
        reading from this device. Read the current value from the device, e.g. a sensor reading
        and return the value.

        The given file descriptor will already be opened, the SPI slave address already be
        selected. The only task is to read the current value. Often that consists of a
        write operation to configure registers on the device followed by a read operation.

        IMPORTANT: This method will be called from a different thread. This means that you
        are free to perform blocking operations, including calling QThread::msleep() but it
        also implies that you must not access other members of the class if they may be
        accessed from code outside of this method. If you absolutely must do so, make sure
        to use mutexes (e.g. QMutex) accordingly.
*/

/*! \fn bool SPIDevice::writeData(int fileDescriptor, const QByteArray &data);
        Reimplement this when implementing writing communication with an I2C device.
        This method will be called when SPIManager::writeData(I2CDevice *device, const QByteArray &data)
        is called. The data to be written is copied and passed on to this method.

        The given file descriptor will already be opened, the I2C slave address already be
        selected. The only task is to write the data to it. Often that consists of a
        write operation to configure registers on the device followed by another write operation
        to write the actual data.

        IMPORTANT: This method will be called from a different thread. This means that you
        are free to perform blocking operations, including calling QThread::msleep() but it
        also implies that you must not access other members of the class if they may be
        accessed from code outside of this method. If you absolutely must do so, make sure
        to use mutexes (e.g. QMutex) accordingly.
*/

/*! Constructs an SPIDevice with the given portName and address. The \a portName
    must match the file name of /dev, for example "spi-0" for /dev/spi-0. The
    \a address describes the SPI slave address for this device.

    SPIManager::scanRegisters() can be used to scan for available SPI devices connected
    to the system.
*/
SPIDevice::SPIDevice(const QString &portName, int address, QObject *parent):
    QObject(parent),
    m_portName(portName),
    m_address(address)
{

}

SPIDevice::~SPIDevice()
{
}

/*! Returns the port name of this SPI device. */
QString SPIDevice::portName() const
{
    return m_portName;
}

/*! Returns the address of this SPI device. */
int SPIDevice::address() const
{
    return m_address;
}

QByteArray SPIDevice::readData(int fileDescriptor)
{
    Q_UNUSED(fileDescriptor)
    return QByteArray();
}

bool SPIDevice::writeData(int fileDescriptor, const QByteArray &data)
{
    Q_UNUSED(fileDescriptor)
    Q_UNUSED(data)
    return false;
}

QDebug operator<<(QDebug debug, const SPIDevice *i2cDevice)
{
    debug.nospace() << "SPIDevice(Port: " << spiDevice->portName() << ", Address: 0x" << QString::number(spiDevice->address(), 16) << ")";
    return debug.space();
}
