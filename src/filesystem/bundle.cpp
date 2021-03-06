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

#include <QDir>
#include <QStack>

#include "bundle.h"

Bundle::Bundle()
    : mTotalSize(0)
{
}

void Bundle::addFile(const QString &filename)
{
    QFileInfo info(filename);

    append(FileInfo(info));
    mTotalSize += info.size();
}

void Bundle::addDirectory(const QString &path)
{
    QDir root(path);
    QStack<QString> stack;

    // Push the root path on the stack and then go up one level so that
    // the relative filenames will include the name of the directory
    stack.push(root.absolutePath());
    root.cdUp();

    while(stack.count()) {
        QString tos = stack.pop();

        foreach(QFileInfo info, QDir(tos).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
            if(info.isDir()) {
                stack.push(info.absoluteFilePath());
            } else {
                append(FileInfo(root, info));
                mTotalSize += info.size();
            }
        }
    }
}
