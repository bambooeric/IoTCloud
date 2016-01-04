/*
 * Tigase Jabber/XMPP Server
 * Copyright (C) 2004-2012 "Artur Hefczyc" <artur.hefczyc@tigase.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. Look for COPYING file in the top folder.
 * If not, see http://www.gnu.org/licenses/.
 *
 * $Rev$
 * Last modified by $Author$
 * $Date$
 */

package tigase.hinest.db;

import tigase.db.DataRepository;
import tigase.db.Repository;
import tigase.db.TigaseDBException;
import tigase.xmpp.BareJID;
import tigase.xmpp.JID;

import java.util.List;
import java.util.Map;

/**
 * <code>UserRepository</code> interface defines all functionalities required
 * to store user data.
 * It contains adding, removing and searching methods. User repository is
 * organized as hierarchical data base. It means you can add items to repository
 * on different levels like files in file systems. Instead, however of working
 * with directories you work with nodes. You can create many levels of nodes and
 * store data on any level. It helps to organize data in more logical order.
 *
 * <p>
 * Created: Tue Oct 26 15:09:28 2004
 * </p>
 * @author <a href="mailto:artur.hefczyc@tigase.org">Artur Hefczyc</a>
 * @version $Rev$
 */
public interface TurnRepository {
	/*add turn user */
	public void addTurnUser(BareJID user, String turn_name, String turn_passwd) throws TigaseDBException;

	public void delTurnUser(BareJID user) throws TigaseDBException;
	
	public String getShareSecret(BareJID user);
}    // TurnRepository
