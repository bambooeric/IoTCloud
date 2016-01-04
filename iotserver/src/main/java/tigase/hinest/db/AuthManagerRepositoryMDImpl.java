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
import tigase.hinest.HinestLog;
import tigase.xmpp.BareJID;
import tigase.xmpp.JID;

import static tigase.db.RepositoryFactory.GEN_USER_DB_URI_PROP_KEY;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
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
public class AuthManagerRepositoryMDImpl implements AuthManagerRepository {
	private static DataRepository data_repo = null;
	
	/* Log output */
	private static Logger log = Logger.getLogger(HinestExtdiscoICE.class.getName());
	
	private final byte AUTH_CLASS_OWNER = 1;
	private final byte AUTH_CLASS_ADMIN = 2;
	private final byte AUTH_CLASS_USERS = 3;
	
	/* insert tig_auth_route sql string */
	private final String TIG_INSERT_AUTH_ROUTE = "insert into tig_auth_route " + 
										 " (from_user_id, to_user_id, auth_class) " + " values (?, ?, ?)";
	
	/* delete tig_auth_route sql string */
	private final String TIG_DELETE_AUTH_ROUTE = "delete from tig_auth_route " + 
										 " where from_user_id like ? and to_user_id like ? ";
	
	private final String TIG_DELETE_USER_AUTH_ROUTE = "delete from tig_auth_route " + 
			 						     " where to_user_id like ? ";
	
	/* select tig_auth_route list sql string */
	private final String TIG_QUERY_AUTH_ROUTE = "select auth_class from tig_auth_route " +
										 " where from_user_id like ? and to_user_id like ?";

	/* select tig_auth_route list sql string */
	private final String TIG_QUERY_AUTH_ROUTE_LIST = "select from_user_id, auth_class from tig_auth_route " +
										 " where to_user_id like ? and auth_class !=" + AUTH_CLASS_OWNER;
	
	/* select tig_auth_attr value sql string */
	private final String TIG_QUERY_AUTH_ATTR = "select auth_attr_value from tig_auth_attr " +
										 " where auth_class like ? and auth_sub_class like ?";
	
	/* insert tig_auth_attr value sql string */
	private final String TIG_INSERT_AUTH_ATTR = "insert auth_attr_value (auth_class, " +
										 "auth_sub_class, auth_attr_value) " + " values(?, ?, ?)";
	
	/* select tig_auth_attr value sql string */
	private final String TIG_DELETE_AUTH_ATTR = "delete from tig_auth_attr " +
										 " where auth_class like ? and auth_sub_class like ?";	
	
	private DataRepository getRepo() {
		if (null == data_repo) {
			String resource = null;
			Map<String, String> map = null;
			
			/* get user resource */
			resource = System.getProperty(GEN_USER_DB_URI_PROP_KEY);
			
			System.out.println("Source list:" + resource.toString());
			
			try {
				data_repo = RepositoryFactory.getDataRepository(null, resource, map);
				data_repo.initPreparedStatement(TIG_INSERT_AUTH_ROUTE, TIG_INSERT_AUTH_ROUTE);
				data_repo.initPreparedStatement(TIG_DELETE_AUTH_ROUTE, TIG_DELETE_AUTH_ROUTE);
				data_repo.initPreparedStatement(TIG_QUERY_AUTH_ROUTE, TIG_QUERY_AUTH_ROUTE);
				data_repo.initPreparedStatement(TIG_QUERY_AUTH_ROUTE_LIST, TIG_QUERY_AUTH_ROUTE_LIST);
				data_repo.initPreparedStatement(TIG_QUERY_AUTH_ATTR, TIG_QUERY_AUTH_ATTR);
				data_repo.initPreparedStatement(TIG_INSERT_AUTH_ATTR, TIG_INSERT_AUTH_ATTR);				
				data_repo.initPreparedStatement(TIG_DELETE_AUTH_ATTR, TIG_DELETE_AUTH_ATTR);
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
	
	@Override
	public void createUserAuthRoute(BareJID user, String to_user) {
		// TODO Auto-generated method stub
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "createUserAuthRoute get repo failed!\n");
			return;
		}
		
		/* add user and turn_name information */
		try {
			ResultSet rs = null;
			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(user, TIG_INSERT_AUTH_ROUTE);
			
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setString(1, user.toString());
				auth_route_st.setString(2, to_user);
				auth_route_st.setByte(3, AUTH_CLASS_OWNER);
				auth_route_st.execute();
			}	
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void addAuthRoute(BareJID user, String from_user, String to_user, byte right_class) {
		// TODO Auto-generated method stub
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "createUserAuthRoute get repo failed!\n");
			return;
		}
		
		/* add user and turn_name information */
		try {
			ResultSet rs = null;
			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(user, TIG_INSERT_AUTH_ROUTE);
			
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setString(1, user.toString());
				auth_route_st.setString(2, to_user);
				auth_route_st.setByte(3,right_class);
				auth_route_st.execute();
			}	
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void delAuthRoute(BareJID user, String from_user, String to_user) {
		// TODO Auto-generated method stub
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "delAuthRoute get repo failed!\n");
			return;
		}
		
		/* add user and turn_name information */
		try {
			ResultSet rs = null;
			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(user, TIG_DELETE_AUTH_ROUTE);
			
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setString(1, user.toString());
				auth_route_st.setString(2, to_user);
				auth_route_st.execute();
			}	
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void destroyUserAuthRoute(BareJID user, String to_user) {
		// TODO Auto-generated method stub
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "destroyUserAuthRoute get repo failed!\n");
			return;
		}
		
		/* add user and turn_name information */
		try {
			ResultSet rs = null;
			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(user, TIG_DELETE_USER_AUTH_ROUTE);
			
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setString(1, to_user);
				auth_route_st.execute();
			}	
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public Map<String, Object> findAuthRouteList(BareJID user, String to_user) {
		// TODO Auto-generated method stub
		Map<String, Object> map = new HashMap<String, Object>();
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "findAuthRouteList get repo failed!\n");
			return map;
		}
		
		try {
			ResultSet rs = null;
			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(user, TIG_QUERY_AUTH_ROUTE_LIST);
			
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setString(1, to_user);
				rs = auth_route_st.executeQuery();

				while (rs.next()) {
					map.put(rs.getString(1), rs.getByte(2));
				} // end of while (rs.next())
			}			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return map;
	}

	@Override
	public boolean findAuthRouteIs(BareJID user, String to_user, byte auth_sub_class, long auth_val) {
		// TODO Auto-generated method stub
		Map<String, Object> map = new HashMap<String, Object>();
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "findAuthRouteList get repo failed!\n");
			return false;
		}
		
		try {
			ResultSet rs = null;
			byte auth_class = 0;
			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(user, TIG_QUERY_AUTH_ROUTE);
			
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setString(1, user.toString());
				auth_route_st.setString(2, to_user);
				rs = auth_route_st.executeQuery();
				
				if (!rs.next()) {
					HinestLog.debug("database no query record!");	
					return false;
				}
				
				auth_class = rs.getByte(1);
			}
			
			return queryAuthAttr(auth_class, auth_sub_class);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return false;
	}

	@Override
	public boolean addAuthAttr(byte auth_class, byte auth_sub_class, long auth_val) {
		// TODO Auto-generated method stub
		Map<String, Object> map = new HashMap<String, Object>();
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "findAuthRouteList get repo failed!\n");
			return false;
		}
		
		try {
			ResultSet rs = null;

			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(null, TIG_INSERT_AUTH_ATTR);
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setByte(1, auth_class);
				auth_route_st.setByte(2, auth_sub_class);
				auth_route_st.setLong(3, auth_val);
				
				
				if (auth_route_st.execute()) {
					return true;
				}
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return false;
	
	}

	@Override
	public void delAuthAttr(byte auth_class, byte auth_sub_class) {
		// TODO Auto-generated method stub
		Map<String, Object> map = new HashMap<String, Object>();
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "findAuthRouteList get repo failed!\n");
			return;
		}
		
		try {
			ResultSet rs = null;

			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(null, TIG_DELETE_AUTH_ATTR);
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setByte(1, auth_class);
				auth_route_st.setByte(2, auth_sub_class);
				
				rs = auth_route_st.executeQuery();
				if (rs.next()) {
					return;
				}
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return;
	}

	@Override
	public boolean modifyAuthAttr(byte auth_class, byte auth_sub_class, long auth_val) {
		delAuthAttr(auth_class, auth_sub_class);
		
		return addAuthAttr(auth_class, auth_sub_class, auth_val);
	}
	
	@Override
	public boolean queryAuthAttr(byte auth_class, byte auth_sub_class) {
		// TODO Auto-generated method stub
		Map<String, Object> map = new HashMap<String, Object>();
		DataRepository repo = getRepo();
		
		if (null == repo) {
			log.log(Level.INFO, "findAuthRouteList get repo failed!\n");
			return false;
		}
		
		try {
			ResultSet rs = null;

			PreparedStatement auth_route_st;
			
			auth_route_st = repo.getPreparedStatement(null, TIG_QUERY_AUTH_ATTR);
			synchronized (auth_route_st) {
				// Load all user count from database
				auth_route_st.setByte(1, auth_class);
				auth_route_st.setByte(2, auth_sub_class);
				
				rs = auth_route_st.executeQuery();
				if (rs.next()) {
					return true;
				}
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return false;
	}

	@Override
	public void modifyAuthAttr(byte auth_class, byte auth_sub_class) {
		// TODO Auto-generated method stub
		
	}
}    // TurnRepository
