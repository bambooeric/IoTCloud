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

import tigase.db.DBInitException;
import tigase.db.DataRepository;
import tigase.db.Repository;
import tigase.db.RepositoryFactory;
import tigase.db.TigaseDBException;
import tigase.db.UserRepository;
import tigase.hinest.HinestExtdiscoICE;
import tigase.xmpp.BareJID;
import tigase.xmpp.JID;

import static tigase.db.RepositoryFactory.GEN_USER_DB_URI_PROP_KEY;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

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
public class TurnRepositoryMDImpl implements TurnRepository {
	private static DataRepository data_repo = null;
	
	/* Log output */
	private static Logger log = Logger.getLogger(HinestExtdiscoICE.class.getName());
	
	/* sql string */
	private final String TIGASE_TURN_USERS_QUERY = "select turn_name from tig_turn_users where user_id like ?";
	
	private final String TIGASE_TURN_USERS_DELETE = "delete from tig_turn_users where user_id like ?";
	
	private final String TURN_USERS_LT_DELETE = "delete from turnusers_lt where name like ?";
	
	private final String TIGASE_TURN_USERS_INSERT = "insert into tig_turn_users" + 
										     " (user_id, turn_name) " + " values (?, ?)";
	
	private final String TURN_USERS_LT_INSERT = "insert into turnusers_lt" + 
	        							     " (name, hmackey) " + " values (?, ?)";					
	
	private final String TIGASE_TURN_SECRET_QUERY = "select value from turn_secret";
	
	private DataRepository getRepo() {
		if (null == data_repo) {
			String resource = null;
			Map<String, String> map = null;
	        /*			
			System.out.println("store auth info start......");
			dr_repo = RepositoryFactory.getDataRepository(dr_class, dr_uri, null);
			if (null == dr_repo) {
				System.out.println("store auth info dr_repo is null");
			} else {
				System.out.println("Loaded dst_repo " + dr_repo.getClass().getName() + " for parameters:"
									+ "\n   src_class=" + dr_class + "\n   src_uri=" + dr_uri);
			}*/
			/* get user resource */
			
			resource = System.getProperty(GEN_USER_DB_URI_PROP_KEY);
			
			System.out.println("Source list:" + resource.toString());
			
			try {
				data_repo = RepositoryFactory.getDataRepository(null, resource, map);
				data_repo.initPreparedStatement(TIGASE_TURN_USERS_QUERY, TIGASE_TURN_USERS_QUERY);
				data_repo.initPreparedStatement(TIGASE_TURN_USERS_DELETE, TIGASE_TURN_USERS_DELETE);
				data_repo.initPreparedStatement(TURN_USERS_LT_DELETE, TURN_USERS_LT_DELETE);
				data_repo.initPreparedStatement(TIGASE_TURN_USERS_INSERT, TIGASE_TURN_USERS_INSERT);
				data_repo.initPreparedStatement(TURN_USERS_LT_INSERT, TURN_USERS_LT_INSERT);
				data_repo.initPreparedStatement(TIGASE_TURN_SECRET_QUERY, TIGASE_TURN_SECRET_QUERY);
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InstantiationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (DBInitException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		return data_repo;
	}

	/*add turn user */
	public void addTurnUser(BareJID user_id, String turn_name, String hmac_key) throws TigaseDBException {
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "addTurnUser get repo failed!\n");
			return;
		}
		
		/* delete history user all turn information */
		delTurnUser(user_id);
		
		/* add user and turn_name information */
		try {
			ResultSet rs = null;
			PreparedStatement turn_users_st;
			ArrayList turn_users = new ArrayList();
			
			turn_users_st = repo.getPreparedStatement(user_id, TURN_USERS_LT_INSERT);
			
			synchronized (turn_users_st) {
				// Load all user count from database
				turn_users_st.setString(1, turn_name);
				turn_users_st.setString(2, hmac_key);
				turn_users_st.execute();
			}	
			
			turn_users_st = repo.getPreparedStatement(user_id, TIGASE_TURN_USERS_INSERT);
			
			synchronized (turn_users_st) {
				// Load all user count from database
				turn_users_st.setString(1, user_id.toString());
				turn_users_st.setString(2, turn_name);
				turn_users_st.execute();
			}	
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public void delTurnUser(BareJID user_id) throws TigaseDBException {
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "addTurnUser get repo failed!\n");
			return;
		}
		
		try {
			int has_turn_users = 0;
			ResultSet rs = null;
			PreparedStatement turn_users_st;
			ArrayList turn_users=new ArrayList();
			
			turn_users_st = repo.getPreparedStatement(user_id, TIGASE_TURN_USERS_QUERY);
			
			synchronized (turn_users_st) {
				// Load all user count from database
				turn_users_st.setString(1, user_id.toString());
				rs = turn_users_st.executeQuery();

				while (rs.next()) {
					has_turn_users++;
					turn_users.add(rs.getString(1));
				} // end of while (rs.next())
			}
			
			if (has_turn_users > 0) {
				turn_users_st = repo.getPreparedStatement(user_id, TIGASE_TURN_USERS_DELETE);
				
				synchronized (turn_users_st) {
					// Load all user count from database
					turn_users_st.setString(1, user_id.toString());
					
					System.out.println("del user ps:" + turn_users_st.toString());
					System.out.println("del user sql:" + TIGASE_TURN_USERS_DELETE + " ?=" + user_id.toString());
					
					turn_users_st.execute();
				}
			}

			
			for (int i = 0; i < turn_users.size(); i++) {
				String name = (String)turn_users.get(i);
				
				turn_users_st = repo.getPreparedStatement(user_id, TURN_USERS_LT_DELETE);
				
				synchronized (turn_users_st) {
					// Load all user count from database
					turn_users_st.setString(1, name);
					turn_users_st.execute();
				}
			}			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public String getShareSecret(BareJID user) {
		// TODO Auto-generated method stub
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "addTurnUser get repo failed!\n");
			return null;
		}
		
		try {
			int has_turn_users = 0;
			ResultSet rs = null;
			PreparedStatement turn_users_st;
			ArrayList turn_users=new ArrayList();
			
			turn_users_st = repo.getPreparedStatement(user, TIGASE_TURN_SECRET_QUERY);
			
			synchronized (turn_users_st) {
				// Load all user count from database
				rs = turn_users_st.executeQuery();
				
				if (rs.next()) {
					System.out.println("secret:" + rs.getString(1));
					return rs.getString(1);
				} else {
					System.out.println("secret get failed!");
					return null;
				}
			}	
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return null;
	}
}    // TurnRepository
