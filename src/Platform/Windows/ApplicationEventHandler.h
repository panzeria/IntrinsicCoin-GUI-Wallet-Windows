// Copyright (c) 2015-2017, The Intrinsicoin developers
//
// This file is part of Intrinsicoin.
//
// Intrinsicoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Intrinsicoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Intrinsicoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <QAbstractNativeEventFilter>
#include <QLocalServer>
#include <QUrl>

#include "IApplicationEventHandler.h"

namespace WalletGui {

class ApplicationEventHandler : public QLocalServer, public QAbstractNativeEventFilter, public IApplicationEventHandler {
  Q_OBJECT
  Q_DISABLE_COPY(ApplicationEventHandler)

public:
  explicit ApplicationEventHandler(QObject* _parent);
  ~ApplicationEventHandler();

  virtual bool nativeEventFilter(const QByteArray& _eventType, void* _message, long* _result) override;

  // IApplicationEventHandler
  virtual void init() override;
  virtual QUrl getLastReceivedUrl() override;
  virtual void sendUrl(const QUrl& _url) override;
  virtual void addObserver(IApplicationEventHandlerObserver* _observer) override;
  virtual void removeObserver(IApplicationEventHandlerObserver* _observer) override;

private:
  QUrl m_receivedUrl;

  void accept();
  void readyRead();
  void clientDisconnected();

Q_SIGNALS:
  void urlReceivedSignal(const QUrl& _url);
  void screenLockedSignal();
  void screenUnlockedSignal();
};

}