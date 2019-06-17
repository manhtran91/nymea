/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2019 Michael Zanetti <michael.zanetti@nymea.io>          *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation; either           *
 *  version 2.1 of the License, or (at your option) any later version.     *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; If not, see                           *
 *  <http://www.gnu.org/licenses/>.                                        *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>

#include "device.h"
#include "deviceplugin.h"
#include "types/interface.h"
#include "types/vendor.h"
#include "types/browseritem.h"

class DeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit DeviceManager(QObject *parent = nullptr);
    virtual ~DeviceManager() = default;

    virtual DevicePlugins plugins() const = 0;
    virtual Device::DeviceError setPluginConfig(const PluginId &pluginId, const ParamList &pluginConfig) = 0;

    virtual Vendors supportedVendors() const = 0;
    virtual Interfaces supportedInterfaces() const = 0;
    virtual DeviceClasses supportedDevices(const VendorId &vendorId = VendorId()) const = 0;

    virtual DeviceClass findDeviceClass(const DeviceClassId &deviceClassId) const = 0;

    virtual Devices configuredDevices() const = 0;
    virtual Device* findConfiguredDevice(const DeviceId &id) const = 0;
    virtual Devices findConfiguredDevices(const DeviceClassId &deviceClassId) const = 0;
    virtual Devices findConfiguredDevices(const QString &interface) const = 0;
    virtual Devices findChildDevices(const DeviceId &id) const = 0;

    virtual Device::DeviceError discoverDevices(const DeviceClassId &deviceClassId, const ParamList &params) = 0;

    virtual Device::DeviceError addConfiguredDevice(const DeviceClassId &deviceClassId, const QString &name, const ParamList &params, const DeviceId id = DeviceId::createDeviceId()) = 0;
    virtual Device::DeviceError addConfiguredDevice(const DeviceClassId &deviceClassId, const QString &name, const DeviceDescriptorId &deviceDescriptorId, const ParamList &params = ParamList(), const DeviceId &deviceId = DeviceId::createDeviceId()) = 0;

    virtual Device::DeviceError reconfigureDevice(const DeviceId &deviceId, const ParamList &params, bool fromDiscoveryOrAuto = false) = 0;
    virtual Device::DeviceError reconfigureDevice(const DeviceId &deviceId, const DeviceDescriptorId &deviceDescriptorId) = 0;

    virtual Device::DeviceError editDevice(const DeviceId &deviceId, const QString &name) = 0;
    virtual Device::DeviceError setDeviceSettings(const DeviceId &deviceId, const ParamList &settings) = 0;

    virtual Device::DeviceError pairDevice(const PairingTransactionId &pairingTransactionId, const DeviceClassId &deviceClassId, const QString &name, const ParamList &params) = 0;
    virtual Device::DeviceError pairDevice(const PairingTransactionId &pairingTransactionId, const DeviceClassId &deviceClassId, const QString &name, const DeviceDescriptorId &deviceDescriptorId) = 0;
    virtual Device::DeviceError confirmPairing(const PairingTransactionId &pairingTransactionId, const QString &secret = QString()) = 0;

    virtual Device::DeviceError removeConfiguredDevice(const DeviceId &deviceId) = 0;

    virtual BrowserItems browseDevice(const DeviceId &deviceId, const QString &browser, const BrowserItemId &node = BrowserItemId()) = 0;

    virtual QString translate(const PluginId &pluginId, const QString &string, const QLocale &locale) = 0;

signals:
    void pluginConfigChanged(const PluginId &id, const ParamList &config);
    void eventTriggered(const Event &event);
    void deviceStateChanged(Device *device, const StateTypeId &stateTypeId, const QVariant &value);
    void deviceRemoved(const DeviceId &deviceId);
    void deviceDisappeared(const DeviceId &deviceId);
    void deviceAdded(Device *device);
    void deviceChanged(Device *device);
    void deviceSettingChanged(const DeviceId deviceId, const ParamTypeId &settingParamTypeId, const QVariant &value);
    void devicesDiscovered(const DeviceClassId &deviceClassId, const QList<DeviceDescriptor> &devices);
    void deviceSetupFinished(Device *device, Device::DeviceError status);
    void deviceReconfigurationFinished(Device *device, Device::DeviceError status);
    void pairingFinished(const PairingTransactionId &pairingTransactionId, Device::DeviceError status, const DeviceId &deviceId = DeviceId());
    void actionExecutionFinished(const ActionId &actionId, Device::DeviceError status);

};

#endif // DEVICEMANAGER_H
