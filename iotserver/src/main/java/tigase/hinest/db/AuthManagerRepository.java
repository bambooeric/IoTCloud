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
public interface AuthManagerRepository {
	
	// 设备所属者权限等级
	public static final byte AUTH_CLASS_OWNER = 1;
	// 管理员权限等级
	public static final byte AUTH_CLASS_ADMIN = 2;
	// 普通用户权限等级
	public static final byte AUTH_CLASS_NORMAL = 3;
	// 二级权限-控制权限
	public static final byte AUTH_SUB_CLASS_CONTROL = 1;
	// 二级权限-点播权限
	public static final byte AUTH_SUB_CLASS_ORDER = 2;
	// 三级权限-目前无使用，统一采用缺省值
	public static final byte AUTH_ATTR_VAL_DEFUALT = 0;
	
	/* 场景：账号和设备绑定
	 * 功能：创建一个账号和设备的所属关系路由表  */
	public void createUserAuthRoute(BareJID user, String to_user);
	
	/* 场景：设备所有者增加或者修改授权
	 * 功能: 创建或者修改一个账号对设备的访问权限路由表 */
	public void addAuthRoute(BareJID user, String from_user, String to_user, byte right_class);
	
	/* 场景：设备所有者删除授权 
	 * 功能：删除一个账号对设备的访问权限路由表 */
	public void delAuthRoute(BareJID user, String from_user, String to_user);
	
	/* 场景：账号和设备解绑定
	 * 功能：删除一个账号和设备的所属关系路由表，包括它授权的所有记录  */
	public void destroyUserAuthRoute(BareJID user, String to_user);
	
	/* 场景：查找设备授权账号列表
	 * 功能：查找设备对应的授权账号列表 */
	public Map<String, Object> findAuthRouteList(BareJID user, String to_user);
	
	/* 场景：查找设备访问权限
	 * 功能：查找设备对应的授权账号的访问权限 */
	public boolean findAuthRouteIs(BareJID user, String to_user, byte auth_sub_class, long auth_val);
	
	/* 增加权限属性修改 */
	public boolean addAuthAttr(byte auth_class, byte auth_sub_class, long auth_val);
	
	/* 删除权限属性修改 */
	public void delAuthAttr(byte auth_class, byte auth_sub_class);
	
	/* 修改权限属性修改 */
	public void modifyAuthAttr(byte auth_class, byte auth_sub_class);

	/* 查询权限属性修改 */
	public boolean queryAuthAttr(byte auth_class, byte auth_sub_class);

	public boolean modifyAuthAttr(byte auth_class, byte auth_sub_class, long auth_val);
}
