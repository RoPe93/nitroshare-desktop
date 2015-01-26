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

#include "socketstream.h"

SocketStream::SocketStream(QTcpSocket *socket)
    : mSocket(socket)
{
}

void SocketStream::readFile()
{
    //...
}

void SocketStream::writeFile(const FileInfo &info)
{
    //...
}

void SocketStream::read(char *data, qint32 length)
{
    qint32 lengthRemaining(length);

    while(lengthRemaining) {
        qint64 lengthRead(mSocket->read(data, lengthRemaining));

        if(lengthRead == -1) {
            throw QObject::tr("Unable to read from socket.");
        }

        data += lengthRead;
        lengthRemaining -= lengthRead;

        if(lengthRemaining) {
            if(!mSocket->waitForReadyRead()) {
                throw QObject::tr("Timeout while reading from socket.");
            }
        }
    }
}

void SocketStream::write(const char *data, qint32 length)
{
    if(mSocket->write(data, length) != length) {
        throw QObject::tr("Unable to write to socket.");
    }

    if(!mSocket->waitForBytesWritten()) {
        throw QObject::tr("Timeout while writing to socket.");
    }
}