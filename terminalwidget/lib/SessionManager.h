/*
    This file is part of Konsole, KDE's terminal.

    Copyright 2007-2008 by Robert Knight <robertknight@gmail.com>
    Copyright 1997,1998 by Lars Doelle <lars.doelle@on-line.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301  USA.
*/

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

// Qt
#include <QHash>
#include <QList>

namespace Konsole {
class Session;

/**
 * Manages running terminal sessions.
 */
class SessionManager : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs a new session manager and loads information about the available
     * profiles.
     */
    SessionManager();

    /**
     * Destroys the SessionManager. All running sessions should be closed
     * (via closeAllSessions()) before the SessionManager is destroyed.
     */
    ~SessionManager() Q_DECL_OVERRIDE;

    /**
     * Returns the session manager instance.
     */
    static SessionManager *instance();

    /** Kill all running sessions. */
    void closeAllSessions();

    /**
     * Returns a list of active sessions.
     */
    QList<Session *> sessions() const;

    // System session management
    void saveSession(Session *session);
    bool removeSession(int id);
    int  getSessionId(Session *session);
    Session *idToSession(int id);

    void setCurrSession(Session *session);
    Session *getCurrSession();

    //用于存储当前的命令提示符
    void saveCurrShellPrompt(QString strPrompt);
    QString getCurrShellPrompt();

    //用于存储当前的执行的命令字符串
    void saveCurrShellCommand(QString strCommand);
    QString getCurrShellCommand();

signals:
    void sessionIdle(bool isIdle);

protected Q_SLOTS:
    /**
     * Called to inform the manager that a session has finished executing.
     *
     * @param session The Session which has finished executing.
     */
    void sessionTerminated(Session *session);

private:
    QList<Session *> _sessions; // list of running sessions
    QHash<Session *, int> _restoreMapping;

    Session *_currSession;
    QString _currShellPrompt;
    QString _currShellCommand;
};

}
#endif //SESSIONMANAGER_H
