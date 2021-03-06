/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/

#ifndef NS_TRANSFERSERVER_H
#define NS_TRANSFERSERVER_H

#include <QTcpServer>

#include "../util/settings.h"

/**
 * @brief Server listening for incomming connections
 *
 * This class listens for connection requests from other clients and emits the
 * newTransfer signal when one is received.
 */
class TransferServer : public QTcpServer
{
    Q_OBJECT

public:

    /**
     * @brief Create a new transfer server
     * @param parent parent QObject
     */
    explicit TransferServer(QObject *parent = nullptr);

Q_SIGNALS:

    /**
     * @brief Indicate a new connection attempt
     * @param socketDescriptor socket descriptor
     */
    void newTransfer(qintptr socketDescriptor);

private Q_SLOTS:

    // TODO: what follows below shouldn't be public

    void settingChanged(Settings::Key key);

private:

    void incomingConnection(qintptr socketDescriptor);

    void reload();
};

#endif // NS_TRANSFERSERVER_H
